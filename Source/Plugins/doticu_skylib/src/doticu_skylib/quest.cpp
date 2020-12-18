/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/forward_list.inl"

#include "doticu_skylib/reference.h"
#include "doticu_skylib/quest.h"
#include "doticu_skylib/quest_objective.h"

#include "doticu_skylib/virtual_arguments.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_machine.h"
#include "doticu_skylib/virtual_variable.h"

namespace doticu_skylib {

    void Quest_t::Start(const Vector_t<Quest_t*> quests, Callback_i<>* ucallback)
    {
        using UCallback_t = Callback_i<>;
        SKYLIB_ASSERT(ucallback);

        struct VCallback : public Virtual::Callback_t {
            const Vector_t<Quest_t*> quests;
            size_t index;
            UCallback_t* ucallback;
            VCallback(const Vector_t<Quest_t*> quests, size_t index, UCallback_t* ucallback) :
                quests(quests), index(index), ucallback(ucallback)
            {
            }
            void operator()(Virtual::Variable_t* result)
            {
                if (index < quests.size()) {
                    Quest_t* quest = quests[index];
                    if (quest) {
                        quest->Start(new VCallback(quests, index + 1, ucallback));
                    } else {
                        ucallback->operator()();
                        delete ucallback;
                    }
                } else {
                    ucallback->operator()();
                    delete ucallback;
                }
            }
        };

        size_t index = 0;
        Quest_t* quest = quests[index];
        if (quest) {
            quest->Start(new VCallback(quests, index + 1, ucallback));
        } else {
            ucallback->operator()();
            delete ucallback;
        }
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

    Bool_t Quest_t::Has_Filled_Alias(Alias_ID_t alias_id)
    {
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

    void Quest_t::Log_Objectives(std::string indent)
    {
        SKYLIB_LOG(indent + "Quest_t::Log_Objectives");
        SKYLIB_LOG(indent + "{");

        if (!objectives.Is_Empty()) {
            for (List_t<Quest_Objective_t*>::Node_t* node = &objectives.head; node; node = node->next) {
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
        for (Index_t idx = 0, end = promoted_references.count; idx < end; idx += 1) {
            Reference_Handle_t reference_handle = promoted_references.entries[idx];
            Reference_t* reference = Reference_t::From_Handle(reference_handle);
            if (reference) {
                _MESSAGE("%s", reference->Any_Name());
            }
        }
    }

    void Quest_t::Start(Virtual::Callback_i* vcallback)
    {
        Virtual::Machine_t::Self()->Call_Method(
            this,
            "Quest",
            "Start",
            nullptr,
            &vcallback
        );
    }

    void Quest_t::Start(Callback_i<Bool_t>* ucallback)
    {
        using UCallback_t = Callback_i<Bool_t>;

        struct VCallback : public Virtual::Callback_t {
            UCallback_t* ucallback;
            VCallback(UCallback_t* ucallback) :
                ucallback(ucallback)
            {
            }
            void operator()(Virtual::Variable_t* result)
            {
                if (ucallback) {
                    Bool_t did_start = result ? result->Bool() : false;
                    ucallback->operator()(did_start);
                    delete ucallback;
                }
            }
        };
        Start(new VCallback(ucallback));
    }

    void Quest_t::Display_Objective(Int_t objective, Bool_t do_force, maybe<Virtual::Callback_i*> vcallback)
    {
        class Arguments_t : public Virtual::Arguments_t
        {
        public:
            Int_t objective;
            Bool_t do_force;
            Arguments_t(Int_t objective, Bool_t do_force) :
                objective(objective), do_force(do_force)
            {
            }
            Bool_t operator()(Buffer_t<Virtual::Variable_t>* variables)
            {
                variables->Resize(3);
                variables->At(0)->Int(objective);
                variables->At(1)->Bool(true);
                variables->At(2)->Bool(do_force);
                return true;
            }
        } varguments(objective, do_force);

        Virtual::Machine_t::Self()->Call_Method(
            this,
            "Quest",
            "SetObjectiveDisplayed",
            &varguments,
            vcallback
        );
    }

    void Quest_t::Undisplay_Objective(Int_t objective, Bool_t do_force, maybe<Virtual::Callback_i*> vcallback)
    {
        class Arguments_t : public Virtual::Arguments_t
        {
        public:
            Int_t objective;
            Bool_t do_force;
            Arguments_t(Int_t objective, Bool_t do_force) :
                objective(objective), do_force(do_force)
            {
            }
            Bool_t operator()(Buffer_t<Virtual::Variable_t>* variables)
            {
                variables->Resize(3);
                variables->At(0)->Int(objective);
                variables->At(1)->Bool(false);
                variables->At(2)->Bool(do_force);
                return true;
            }
        } varguments(objective, do_force);

        Virtual::Machine_t::Self()->Call_Method(
            this,
            "Quest",
            "SetObjectiveDisplayed",
            &varguments,
            vcallback
        );
    }

}
