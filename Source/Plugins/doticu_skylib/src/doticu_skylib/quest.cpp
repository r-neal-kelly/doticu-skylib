/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/alias_base.h"
#include "doticu_skylib/alias_reference.h"
#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/enum_comparator.h"
#include "doticu_skylib/forward_list.inl"
#include "doticu_skylib/quest.h"
#include "doticu_skylib/quest_objective.h"
#include "doticu_skylib/reference.h"
#include "doticu_skylib/scrap_array.h"
#include "doticu_skylib/virtual_arguments.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_machine.inl"
#include "doticu_skylib/virtual_utility.h"
#include "doticu_skylib/virtual_variable.inl"

namespace doticu_skylib {

    void Quest_t::Start(const Vector_t<some<Quest_t*>> quests, maybe<Callback_i<Bool_t>*> ucallback)
    {
        using UCallback_t = maybe<Callback_i<Bool_t>*>;

        struct VCallback : public Virtual::Callback_t {
            const Vector_t<some<Quest_t*>> quests;
            size_t index;
            Bool_t did_start_all;
            UCallback_t ucallback;
            VCallback(const Vector_t<some<Quest_t*>> quests, size_t index, Bool_t did_start_all, UCallback_t ucallback) :
                quests(quests), index(index), did_start_all(did_start_all), ucallback(ucallback)
            {
            }
            void operator()(Virtual::Variable_t* did_start)
            {
                if (!did_start) {
                    did_start_all = false;
                }

                if (index < quests.size()) {
                    some<Quest_t*> quest = quests[index];
                    SKYLIB_ASSERT_SOME(quest);
                    quest->Start(new VCallback(quests, index + 1, did_start_all, ucallback));
                } else {
                    if (ucallback) {
                        ucallback()->operator()(did_start_all);
                        delete ucallback();
                    }
                }
            }
        };

        size_t index = 0;
        some<Quest_t*> quest = quests[index];
        SKYLIB_ASSERT_SOME(quest);
        quest->Start(new VCallback(quests, index + 1, true, ucallback));
    }

    void Quest_t::Are_Running(const Vector_t<some<Quest_t*>> quests, some<unique<Callback_i<Bool_t>>> callback)
    {
        using Callback = some<unique<Callback_i<Bool_t>>>;

        class Virtual_Callback :
            public Virtual::Callback_t
        {
        public:
            const Vector_t<some<Quest_t*>>  quests;
            const size_t                    idx;
            const size_t                    end;
            Callback                        callback;

        public:
            Virtual_Callback(const Vector_t<some<Quest_t*>> quests,
                             const size_t idx,
                             const size_t end,
                             Callback callback) :
                quests(std::move(quests)),
                idx(idx),
                end(end),
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator ()(Virtual::Variable_t* result) override
            {
                if (result && result->As<Bool_t>()) {
                    if (this->idx < this->end) {
                        this->quests[this->idx]->Is_Running(
                            new Virtual_Callback(std::move(this->quests), this->idx + 1, this->end, std::move(this->callback))
                        );
                    } else {
                        (*this->callback)(true);
                    }
                } else {
                    (*this->callback)(false);
                }
            }
        };

        SKYLIB_ASSERT_SOME(callback);

        const size_t idx = 0;
        const size_t end = quests.size();
        if (end > 0) {
            quests[0]->Is_Running(new Virtual_Callback(std::move(quests), idx + 1, end, std::move(callback)));
        } else {
            (*callback)(false);
        }
    }

    void Quest_t::Wait_For(const Vector_t<some<Quest_t*>> quests, Float_t wait_interval, some<unique<Callback_i<>>> callback)
    {
        using Callback = some<unique<Callback_i<>>>;

        struct Wait_Callback :
            public Virtual::Callback_t
        {
        public:
            const Vector_t<some<Quest_t*>>  quests;
            Float_t                         wait_interval;
            Callback                        callback;

        public:
            Wait_Callback(const Vector_t<some<Quest_t*>> quests, Float_t wait_interval, Callback callback) :
                quests(std::move(quests)), wait_interval(wait_interval), callback(std::move(callback))
            {
            }

        public:
            virtual void operator ()(Virtual::Variable_t*) override
            {
                class Are_Running_Callback :
                    public doticu_skylib::Callback_i<Bool_t>
                {
                public:
                    const Vector_t<some<Quest_t*>>  quests;
                    Float_t                         wait_interval;
                    Callback                        callback;

                public:
                    Are_Running_Callback(const Vector_t<some<Quest_t*>> quests, Float_t wait_interval, Callback callback) :
                        quests(std::move(quests)), wait_interval(wait_interval), callback(std::move(callback))
                    {
                    }

                public:
                    virtual void operator ()(Bool_t are_running) override
                    {
                        if (are_running) {
                            (*this->callback)();
                        } else {
                            Virtual::Utility_t::Wait_Out_Of_Menu(
                                this->wait_interval,
                                new Wait_Callback(std::move(this->quests), this->wait_interval, std::move(this->callback))
                            );
                        }
                    }
                };
                Quest_t::Are_Running(
                    this->quests,
                    new Are_Running_Callback(std::move(this->quests), this->wait_interval, std::move(this->callback))
                );
            }
        };

        SKYLIB_ASSERT(wait_interval > 0.0f);
        SKYLIB_ASSERT_SOME(callback);

        Virtual::Utility_t::Wait_Out_Of_Menu(
            wait_interval,
            new Wait_Callback(std::move(quests), wait_interval, std::move(callback))
        );
    }

    Int_t Quest_t::Compare_Any_Names(Quest_t** a, Quest_t** b)
    {
        if (!a || !*a) {
            return Comparator_e::IS_UNORDERED;
        } else if (!b || !*b) {
            return Comparator_e::IS_ORDERED;
        } else {
            Comparator_e result = Form_t::Compare_Names(
                (*a)->Any_Name(),
                (*b)->Any_Name()
            );
            if (result == Comparator_e::IS_EQUAL) {
                return (*a)->form_id - (*b)->form_id;
            } else {
                return result;
            }
        }
    }

    Int_t Quest_t::Compare_Any_Names(some<Quest_t*>* a, some<Quest_t*>* b)
    {
        return Compare_Any_Names(reinterpret_cast<Quest_t**>(a), reinterpret_cast<Quest_t**>(b));
    }

    Bool_t Quest_t::Is_Enabled()            { return this->quest_flags.Is_Flagged(Quest_Flags_e::IS_ENABLED); }
    Bool_t Quest_t::Is_Completed()          { return this->quest_flags.Is_Flagged(Quest_Flags_e::IS_COMPLETED); }
    Bool_t Quest_t::Does_Start_Enabled()    { return this->quest_flags.Is_Flagged(Quest_Flags_e::DOES_START_ENABLED); }
    Bool_t Quest_t::Is_Displayed_In_HUD()   { return this->quest_flags.Is_Flagged(Quest_Flags_e::IS_DISPLAYED_IN_HUD); }
    Bool_t Quest_t::Is_Failed()             { return this->quest_flags.Is_Flagged(Quest_Flags_e::IS_FAILED); }
    Bool_t Quest_t::Does_Run_Once()         { return this->quest_flags.Is_Flagged(Quest_Flags_e::DOES_RUN_ONCE); }
    Bool_t Quest_t::Is_Active()             { return this->quest_flags.Is_Flagged(Quest_Flags_e::IS_ACTIVE); }

    Bool_t Quest_t::Has_Filled_Alias(Alias_ID_t alias_id)
    {
        Read_Locker_t locker(this->aliases_lock);

        return filled_aliases.Has(alias_id);
    }

    String_t Quest_t::Any_Name()
    {
        const char* name = Name();
        if (name && name[0]) {
            return name;
        } else {
            name = Get_Editor_ID();
            if (name && name[0]) {
                return name;
            } else {
                return Form_ID_String();
            }
        }
    }

    maybe<Alias_Base_t*> Quest_t::Index_To_Alias_Base(size_t index)
    {
        Read_Locker_t locker(this->aliases_lock);

        if (index < this->aliases.Count()) {
            return this->aliases[index];
        } else {
            return none<Alias_Base_t*>();
        }
    }

    maybe<Alias_Base_t*> Quest_t::ID_To_Alias_Base(Alias_ID_t id)
    {
        Read_Locker_t locker(this->aliases_lock);

        for (size_t idx = 0, end = this->aliases.Count(); idx < end; idx += 1) {
            maybe<Alias_Base_t*> alias_base = this->aliases[idx];
            if (alias_base && alias_base->id == id) {
                return alias_base;
            }
        }

        return none<Alias_Base_t*>();
    }

    maybe<Alias_Reference_t*> Quest_t::Index_To_Alias_Reference(size_t index)
    {
        maybe<Alias_Base_t*> alias_base = Index_To_Alias_Base(index);
        if (alias_base) {
            return alias_base->As_Alias_Reference();
        } else {
            return none<Alias_Reference_t*>();
        }
    }

    maybe<Alias_Reference_t*> Quest_t::ID_To_Alias_Reference(Alias_ID_t id)
    {
        maybe<Alias_Base_t*> alias_base = ID_To_Alias_Base(id);
        if (alias_base) {
            return alias_base->As_Alias_Reference();
        } else {
            return none<Alias_Reference_t*>();
        }
    }

    void Quest_t::Start(maybe<Virtual::Callback_i*> v_callback)
    {
        Virtual::Machine_t::Ready_Scriptable<Quest_t*>(this);
        Virtual::Machine_t::Self()->Call_Method(
            this,
            SCRIPT_NAME,
            "Start",
            none<Virtual::Arguments_i*>(),
            v_callback
        );
    }

    void Quest_t::Start(maybe<unique<Callback_i<Bool_t>>> callback)
    {
        using Callback = maybe<unique<Callback_i<Bool_t>>>;

        class Virtual_Callback :
            public Virtual::Callback_t
        {
        public:
            Callback callback;

        public:
            Virtual_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator()(Virtual::Variable_t* result) override
            {
                if (this->callback) {
                    (*this->callback)(result ? result->As<Bool_t>() : false);
                }
            }
        };

        Start(new Virtual_Callback(std::move(callback)));
    }

    void Quest_t::Is_Running(some<Virtual::Callback_i*> v_callback)
    {
        SKYLIB_ASSERT_SOME(v_callback);

        Virtual::Machine_t::Ready_Scriptable<Quest_t*>(this);
        Virtual::Machine_t::Self()->Call_Method(
            this,
            SCRIPT_NAME,
            "IsRunning",
            none<Virtual::Arguments_i*>(),
            v_callback()
        );
    }

    void Quest_t::Is_Running(some<unique<Callback_i<Bool_t>>> callback)
    {
        using Callback = some<unique<Callback_i<Bool_t>>>;

        class Virtual_Callback :
            public Virtual::Callback_t
        {
        public:
            Callback callback;

        public:
            Virtual_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator ()(Virtual::Variable_t* result) override
            {
                (*this->callback)(result ? result->As<Bool_t>() : false);
            }
        };

        SKYLIB_ASSERT_SOME(callback);

        Is_Running(new Virtual_Callback(std::move(callback)));
    }

    void Quest_t::Do_Display_Objective(Int_t objective,
                                       Bool_t do_display,
                                       Bool_t do_force,
                                       maybe<Virtual::Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Virtual::Arguments_t
        {
        public:
            Int_t   objective;
            Bool_t  do_display;
            Bool_t  do_force;

        public:
            Virtual_Arguments(Int_t objective, Bool_t do_display, Bool_t do_force) :
                objective(objective), do_display(do_display), do_force(do_force)
            {
            }

        public:
            virtual Bool_t operator()(Scrap_Array_t<Virtual::Variable_t>* args) override
            {
                args->Resize(3);
                args->At(0).As<Int_t>(this->objective);
                args->At(1).As<Bool_t>(this->do_display);
                args->At(2).As<Bool_t>(this->do_force);
                return true;
            }
        };

        Virtual::Machine_t::Ready_Scriptable<Quest_t*>(this);
        Virtual::Machine_t::Self()->Call_Method(
            this,
            SCRIPT_NAME,
            "SetObjectiveDisplayed",
            Virtual_Arguments(objective, do_display, do_force),
            v_callback
        );
    }

    void Quest_t::Do_Display_Objective(Int_t objective,
                                       Bool_t do_display,
                                       Bool_t do_force,
                                       maybe<unique<Callback_i<>>> callback)
    {
        using Callback = maybe<unique<Callback_i<>>>;

        class Virtual_Callback :
            public Virtual::Callback_t
        {
        public:
            Callback callback;

        public:
            Virtual_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator()(Virtual::Variable_t*) override
            {
                if (this->callback) {
                    (*this->callback)();
                }
            }
        };

        Do_Display_Objective(objective, do_display, do_force, new Virtual_Callback(std::move(callback)));
    }

    void Quest_t::Log_Objectives(std::string indent)
    {
        SKYLIB_LOG(indent + "Quest_t::Log_Objectives");
        SKYLIB_LOG(indent + "{");

        if (!objectives.Is_Empty()) {
            for (maybe<List_t<Quest_Objective_t*>::Node_t*> node = &objectives.head; node; node = node->next) {
                Quest_Objective_t* objective = node->value;
                if (objective) {
                    objective->Log(indent + SKYLIB_TAB);
                }
            }
        }

        SKYLIB_LOG(indent + "}");
    }

    void Quest_t::Log_Promoted_References()
    {
        for (size_t idx = 0, end = promoted_references.Count(); idx < end; idx += 1) {
            Reference_Handle_t reference_handle = promoted_references[idx];
            Reference_t* reference = Reference_t::From_Handle(reference_handle);
            if (reference) {
                SKYLIB_LOG("%s", reference->Any_Name());
            }
        }
    }

}
