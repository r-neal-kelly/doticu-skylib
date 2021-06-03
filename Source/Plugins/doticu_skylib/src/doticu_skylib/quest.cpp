/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/alias_base.h"
#include "doticu_skylib/alias_reference.h"
#include "doticu_skylib/calendar.h"
#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/enum_calendar_date_month.h"
#include "doticu_skylib/enum_comparator.h"
#include "doticu_skylib/forward_list.inl"
#include "doticu_skylib/game.h"
#include "doticu_skylib/global.h"
#include "doticu_skylib/player.h"
#include "doticu_skylib/quest.h"
#include "doticu_skylib/quest_instance.h"
#include "doticu_skylib/quest_objective.h"
#include "doticu_skylib/race.h"
#include "doticu_skylib/reference.h"
#include "doticu_skylib/scrap_array.h"
#include "doticu_skylib/script.h"
#include "doticu_skylib/virtual_arguments.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_machine.inl"
#include "doticu_skylib/virtual_utility.h"
#include "doticu_skylib/virtual_variable.inl"

namespace doticu_skylib {

    Vector_t<some<Quest_t*>> Quest_t::Quests_Static()
    {
        Vector_t<some<Quest_t*>> results;
        Quests_Static(results);
        return results;
    }

    void Quest_t::Quests_Static(Vector_t<some<Quest_t*>>& results)
    {
        Array_t<maybe<Quest_t*>>& quests = Game_t::Self()->Quests();

        size_t quest_count = quests.Count();
        results.reserve(quest_count);

        for (size_t idx = 0, end = quest_count; idx < end; idx += 1) {
            maybe<Quest_t*> quest = quests[idx];
            if (quest && quest->Is_Valid() && !results.Has(quest())) {
                results.push_back(quest());
            }
        }
    }

    Vector_t<some<Quest_t*>> Quest_t::Quests_Static(Filter_i<some<Quest_t*>>& filter)
    {
        Vector_t<some<Quest_t*>> results;
        Quests_Static(results, filter);
        return results;
    }

    void Quest_t::Quests_Static(Vector_t<some<Quest_t*>>& results, Filter_i<some<Quest_t*>>& filter)
    {
        Array_t<maybe<Quest_t*>>& quests = Game_t::Self()->Quests();

        size_t quest_count = quests.Count();
        results.reserve(quest_count);

        for (size_t idx = 0, end = quest_count; idx < end; idx += 1) {
            maybe<Quest_t*> quest = quests[idx];
            if (quest && quest->Is_Valid() && !results.Has(quest()) && filter(quest())) {
                results.push_back(quest());
            }
        }
    }

    Vector_t<some<Quest_t*>> Quest_t::Quests_Dynamic()
    {
        Vector_t<some<Quest_t*>> results;
        Quests_Dynamic(results);
        return results;
    }

    void Quest_t::Quests_Dynamic(Vector_t<some<Quest_t*>>& results)
    {
        class Iterator :
            public Iterator_i<some<Form_t*>>
        {
        public:
            Vector_t<some<Quest_t*>>& results;

        public:
            Iterator(Vector_t<some<Quest_t*>>& results) :
                results(results)
            {
            }

        public:
            virtual Iterator_e operator ()(some<Form_t*> form) override
            {
                maybe<Quest_t*> quest = form->As_Quest();
                if (quest && quest->Is_Valid()) {
                    this->results.push_back(quest());
                }
                return Iterator_e::CONTINUE;
            }
        };

        results.reserve(4096);

        Iterator iterator(results);

        Game_t::Iterate_Forms(iterator);
    }

    Vector_t<some<Quest_t*>> Quest_t::Quests_Dynamic(Filter_i<some<Quest_t*>>& filter)
    {
        Vector_t<some<Quest_t*>> results;
        Quests_Dynamic(results, filter);
        return results;
    }

    void Quest_t::Quests_Dynamic(Vector_t<some<Quest_t*>>& results, Filter_i<some<Quest_t*>>& filter)
    {
        class Iterator :
            public Iterator_i<some<Form_t*>>
        {
        public:
            Vector_t<some<Quest_t*>>&   results;
            Filter_i<some<Quest_t*>>&   filter;

        public:
            Iterator(Vector_t<some<Quest_t*>>& results, Filter_i<some<Quest_t*>>& filter) :
                results(results), filter(filter)
            {
            }

        public:
            virtual Iterator_e operator ()(some<Form_t*> form) override
            {
                maybe<Quest_t*> quest = form->As_Quest();
                if (quest && quest->Is_Valid() && this->filter(quest())) {
                    this->results.push_back(quest());
                }
                return Iterator_e::CONTINUE;
            }
        };

        results.reserve(4096);

        Iterator iterator(results, filter);

        Game_t::Iterate_Forms(iterator);
    }

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

    Int_t Quest_t::Compare_Any_Names(Quest_t*& a, Quest_t*& b)
    {
        if (!a) {
            return Comparator_e::IS_UNORDERED;
        } else if (!b) {
            return Comparator_e::IS_ORDERED;
        } else {
            Comparator_e result = Form_t::Compare_Names(
                a->Any_Name(),
                b->Any_Name()
            );
            if (result == Comparator_e::IS_EQUAL) {
                return a->form_id - b->form_id;
            } else {
                return result;
            }
        }
    }

    Int_t Quest_t::Compare_Any_Names(some<Quest_t*>& a, some<Quest_t*>& b)
    {
        return Compare_Any_Names(reinterpret_cast<Quest_t*&>(a), reinterpret_cast<Quest_t*&>(b));
    }

    Bool_t Quest_t::Is_Enabled()            { return this->quest_flags.Is_Flagged(Quest_Flags_e::IS_ENABLED); }
    Bool_t Quest_t::Is_Completed()          { return this->quest_flags.Is_Flagged(Quest_Flags_e::IS_COMPLETED); }
    Bool_t Quest_t::Does_Start_Enabled()    { return this->quest_flags.Is_Flagged(Quest_Flags_e::DOES_START_ENABLED); }
    Bool_t Quest_t::Is_Displayed_In_HUD()   { return this->quest_flags.Is_Flagged(Quest_Flags_e::IS_DISPLAYED_IN_HUD); }
    Bool_t Quest_t::Is_Failed()             { return this->quest_flags.Is_Flagged(Quest_Flags_e::IS_FAILED); }
    Bool_t Quest_t::Does_Run_Once()         { return this->quest_flags.Is_Flagged(Quest_Flags_e::DOES_RUN_ONCE); }
    Bool_t Quest_t::Is_Active()             { return this->quest_flags.Is_Flagged(Quest_Flags_e::IS_ACTIVE); }

    Bool_t Quest_t::Is_Completed_Or_Failed()
    {
        return Is_Completed() || Is_Failed();
    }

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

    maybe<Alias_Base_t*> Quest_t::Alias_Base(some<const char*> name)
    {
        Read_Locker_t locker(this->aliases_lock);

        for (size_t idx = 0, end = this->aliases.Count(); idx < end; idx += 1) {
            maybe<Alias_Base_t*> alias_base = this->aliases[idx];
            if (alias_base && alias_base->name == name) {
                return alias_base;
            }
        }

        return none<Alias_Base_t*>();
    }

    maybe<Alias_Reference_t*> Quest_t::Alias_Reference(some<const char*> name)
    {
        maybe<Alias_Base_t*> alias_base = Alias_Base(name);
        if (alias_base) {
            return alias_base->As_Alias_Reference();
        } else {
            return none<Alias_Reference_t*>();
        }
    }

    Bool_t Quest_t::Has_Alias_Index(size_t index)
    {
        return Index_To_Alias_Base(index) != none<Alias_Base_t*>();
    }

    Bool_t Quest_t::Has_Alias_ID(Alias_ID_t id)
    {
        return ID_To_Alias_Base(id) != none<Alias_Base_t*>();
    }

    Vector_t<some<Alias_Base_t*>> Quest_t::Alias_Bases()
    {
        Vector_t<some<Alias_Base_t*>> results;
        Alias_Bases(results);
        return results;
    }

    void Quest_t::Alias_Bases(Vector_t<some<Alias_Base_t*>>& results)
    {
        Read_Locker_t locker(this->aliases_lock);

        for (size_t idx = 0, end = this->aliases.Count(); idx < end; idx += 1) {
            if (this->aliases[idx]) {
                results.push_back(this->aliases[idx]());
            }
        }
    }

    Vector_t<some<Alias_Reference_t*>> Quest_t::Alias_References()
    {
        Vector_t<some<Alias_Reference_t*>> results;
        Alias_References(results);
        return results;
    }

    void Quest_t::Alias_References(Vector_t<some<Alias_Reference_t*>>& results)
    {
        Read_Locker_t locker(this->aliases_lock);

        for (size_t idx = 0, end = this->aliases.Count(); idx < end; idx += 1) {
            if (this->aliases[idx]) {
                maybe<Alias_Reference_t*> alias_reference = this->aliases[idx]->As_Alias_Reference();
                if (alias_reference) {
                    results.push_back(alias_reference());
                }
            }
        }
    }

    maybe<Quest_Objective_t*> Quest_t::Objective(u16 objective_index)
    {
        if (!this->objectives.Is_Empty()) {
            for (maybe<List_t<Quest_Objective_t*>::Node_t*> node = &this->objectives.head; node; node = node->next) {
                maybe<Quest_Objective_t*> objective = node->value;
                if (objective && objective->index == objective_index) {
                    return objective;
                }
            }
            return none<Quest_Objective_t*>();
        } else {
            return none<Quest_Objective_t*>();
        }
    }

    Vector_t<some<Quest_Objective_t*>> Quest_t::Objectives()
    {
        Vector_t<some<Quest_Objective_t*>> results;
        Objectives(results);
        return results;
    }

    void Quest_t::Objectives(Vector_t<some<Quest_Objective_t*>>& results)
    {
        if (!this->objectives.Is_Empty()) {
            for (maybe<List_t<Quest_Objective_t*>::Node_t*> node = &this->objectives.head; node; node = node->next) {
                maybe<Quest_Objective_t*> objective = node->value;
                if (objective) {
                    results.push_back(objective());
                }
            }
        }
    }

    maybe<Quest_Objective_Index_t> Quest_t::Lowest_Objective_Index()
    {
        Vector_t<some<Quest_Objective_t*>> objectives = Objectives();
        size_t objective_count = objectives.size();
        if (objective_count > 0) {
            Quest_Objective_Index_t index = Quest_Objective_Index_t::_MAX_;
            for (size_t idx = 0, end = objective_count; idx < end; idx += 1) {
                if (objectives[idx]->index < index) {
                    index = objectives[idx]->index;
                }
            }
            return index;
        } else {
            return none<Quest_Objective_Index_t>();
        }
    }

    maybe<Quest_Objective_Index_t> Quest_t::Highest_Objective_Index()
    {
        Vector_t<some<Quest_Objective_t*>> objectives = Objectives();
        size_t objective_count = objectives.size();
        if (objective_count > 0) {
            Quest_Objective_Index_t index = Quest_Objective_Index_t::_MIN_;
            for (size_t idx = 0, end = objective_count; idx < end; idx += 1) {
                if (objectives[idx]->index > index) {
                    index = objectives[idx]->index;
                }
            }
            return index;
        } else {
            return none<Quest_Objective_Index_t>();
        }
    }

    maybe<Quest_Instance_t*> Quest_t::Instance(u32 instance_id)
    {
        for (size_t idx = 0, end = this->instances.Count(); idx < end; idx += 1) {
            maybe<Quest_Instance_t*> instance = this->instances[idx];
            if (instance && instance->id == instance_id) {
                return instance;
            }
        }
        return none<Quest_Instance_t*>();
    }

    maybe<Quest_Instance_Alias_t*> Quest_t::Instance_Alias(u32 instance_id, some<const char*> alias_name)
    {
        maybe<Alias_Base_t*> alias_base = Alias_Base(alias_name);
        if (alias_base) {
            return Instance_Alias(instance_id, alias_base->id);
        } else {
            return none<Quest_Instance_Alias_t*>();
        }
    }

    maybe<Quest_Instance_Alias_t*> Quest_t::Instance_Alias(u32 instance_id, Alias_ID_t alias_id)
    {
        maybe<Quest_Instance_t*> instance = Instance(instance_id);
        if (instance) {
            return instance->Alias(alias_id);
        } else {
            return none<Quest_Instance_Alias_t*>();
        }
    }

    maybe<Form_t*> Quest_t::Instance_Alias_Data(u32 instance_id, some<const char*> alias_name)
    {
        maybe<Alias_Base_t*> alias_base = Alias_Base(alias_name);
        if (alias_base) {
            return Instance_Alias_Data(instance_id, alias_base->id);
        } else {
            return none<Form_t*>();
        }
    }

    maybe<Form_t*> Quest_t::Instance_Alias_Data(u32 instance_id, Alias_ID_t alias_id)
    {
        maybe<Quest_Instance_Alias_t*> instance_alias = Instance_Alias(instance_id, alias_id);
        if (instance_alias) {
            return instance_alias->Data_Form();
        } else {
            return none<Form_t*>();
        }
    }

    maybe<Quest_Instance_Global_t*> Quest_t::Instance_Global(u32 instance_id, some<const char*> global_editor_id)
    {
        maybe<Quest_Instance_t*> instance = Instance(instance_id);
        if (instance) {
            return instance->Global(global_editor_id);
        } else {
            return none<Quest_Instance_Global_t*>();
        }
    }

    maybe<Quest_Instance_Global_t*> Quest_t::Instance_Global(u32 instance_id, some<Global_t*> global)
    {
        return Instance_Global(instance_id, global->editor_id);
    }

    std::string Quest_t::Replacement_Text(some<const char*> tag,
                                          some<const char*> sub_tag,
                                          some<const char*> value,
                                          u32 instance_id)
    {
        SKYLIB_ASSERT_SOME(tag);
        SKYLIB_ASSERT_SOME(sub_tag);
        SKYLIB_ASSERT_SOME(value);

        std::string result = "[...]";

        if (CString_t::Is_Same(tag(), "Alias", true)) {
            maybe<Form_t*> data = CString_t::Is_Same(value(), "Player", true) ?
                Player_t::Self()() : Instance_Alias_Data(instance_id, value);
            if (data) {
                if (CString_t::Starts_With(sub_tag(), "ShortName", true)) {
                    maybe<Actor_Base_t*> actor_base = data->As_Actor_Base();
                    if (actor_base && actor_base->short_name) {
                        result = actor_base->short_name;
                    } else {
                        result = data->Component_Name()();
                    }
                } else if (CString_t::Starts_With(sub_tag(), "Race", true)) {
                    maybe<Race_t*> race = data->Component_Race();
                    if (race) {
                        result = race->Component_Name()();
                    }
                } else if (CString_t::Starts_With(sub_tag(), "Pronoun", true)) {
                    maybe<Actor_Base_t*> actor_base = data->As_Actor_Base();
                    result = actor_base ? actor_base->Sex() == Sex_e::FEMALE ? "she" : "he" : "it";
                } else if (CString_t::Starts_With(sub_tag(), "PronounObj", true)) {
                    maybe<Actor_Base_t*> actor_base = data->As_Actor_Base();
                    result = actor_base ? actor_base->Sex() == Sex_e::FEMALE ? "her" : "him" : "it";
                } else if (CString_t::Starts_With(sub_tag(), "PronounPos", true)) {
                    maybe<Actor_Base_t*> actor_base = data->As_Actor_Base();
                    result = actor_base ? actor_base->Sex() == Sex_e::FEMALE ? "hers" : "his" : "its";
                } else if (CString_t::Starts_With(sub_tag(), "PronounPosObj", true)) {
                    maybe<Actor_Base_t*> actor_base = data->As_Actor_Base();
                    result = actor_base ? actor_base->Sex() == Sex_e::FEMALE ? "her" : "his" : "its";
                } else if (CString_t::Starts_With(sub_tag(), "PronounRef", true)) {
                    maybe<Actor_Base_t*> actor_base = data->As_Actor_Base();
                    result = actor_base ? actor_base->Sex() == Sex_e::FEMALE ? "herself" : "himself" : "itself";
                } else if (CString_t::Starts_With(sub_tag(), "PronounInt", true)) {
                    maybe<Actor_Base_t*> actor_base = data->As_Actor_Base();
                    result = actor_base ? actor_base->Sex() == Sex_e::FEMALE ? "herself" : "himself" : "itself";
                } else {
                    result = data->Component_Name()();
                }
                if (CString_t::Ends_With(sub_tag(), "Cap", true)) {
                    for (size_t idx = 0, end = result.length(); idx < end; idx += 1) {
                        if (idx == 0 || result[idx - 1] == ' ') {
                            result[idx] = toupper(result[idx]);
                        }
                    }
                }
            }
        } else if (CString_t::Is_Same(tag(), "Global", true)) {
            maybe<Quest_Instance_Global_t*> data = Instance_Global(instance_id, value());
            if (data && data->global) {
                if (CString_t::Is_Same(sub_tag(), "Hour12", true)) {
                    maybe<Calendar_Now_t> now = Calendar_t::Days_Passed_Now(data->Float(), true);
                    if (now) {
                        result = std::to_string(now.Hour_12()());
                    }
                } else if (CString_t::Is_Same(sub_tag(), "Minutes", true)) {
                    maybe<Calendar_Now_t> now = Calendar_t::Days_Passed_Now(data->Float(), true);
                    if (now) {
                        result = std::to_string(now.Minute()());
                    }
                } else if (CString_t::Is_Same(sub_tag(), "Month", true)) {
                    maybe<Calendar_Now_t> now = Calendar_t::Days_Passed_Now(data->Float(), true);
                    if (now) {
                        result = std::to_string(now.Month()());
                    }
                } else if (CString_t::Is_Same(sub_tag(), "MonthWord", true)) {
                    maybe<Calendar_Now_t> now = Calendar_t::Days_Passed_Now(data->Float(), true);
                    if (now) {
                        result = Calendar_Date_Month_e::To_English_String(now.Month()())();
                    }
                } else if (CString_t::Is_Same(sub_tag(), "Day", true)) {
                    maybe<Calendar_Now_t> now = Calendar_t::Days_Passed_Now(data->Float(), true);
                    if (now) {
                        result = std::to_string(now.Day()());
                    }
                } else if (CString_t::Is_Same(sub_tag(), "WeekDay", true)) {
                    maybe<Calendar_Date_Weekday_e> weekday = Calendar_t::Days_Passed_Weekday(data->Float());
                    if (weekday) {
                        result = Calendar_Date_Weekday_e::To_English_String(weekday())();
                    }
                } else if (CString_t::Is_Same(sub_tag(), "Year", true)) {
                    maybe<Calendar_Now_t> now = Calendar_t::Days_Passed_Now(data->Float(), true);
                    if (now) {
                        result = std::to_string(now.Year()());
                    }
                } else if (CString_t::Is_Same(sub_tag(), "TimeSpan", true)) {
                    maybe<Calendar_Now_t> now = Calendar_t::Days_Passed_Now(data->Float(), true);
                    if (now) {
                        some<Calendar_Time_Hour_24_t> hour_24 = now.Hour_24();
                        if (hour_24() > 18) result = "Evening";
                        else if (hour_24() > 12) result = "Afternoon";
                        else if (hour_24() > 6) result = "Morning";
                        else if (hour_24() > 0) result = "Night";
                    }
                } else if (CString_t::Is_Same(sub_tag(), "Meridiem", true)) {
                    maybe<Calendar_Now_t> now = Calendar_t::Days_Passed_Now(data->Float(), true);
                    if (now) {
                        result = now.Time_12().As_String();
                    }
                } else if (CString_t::Is_Same(sub_tag(), "Time", true)) {
                    Float_t value = data->Float();
                    if (value >= 2) {
                        result = std::to_string(static_cast<u64>(floor(value))) + " hours";
                    } else if (value >= 1) {
                        result = "1 hour";
                    } else {
                        result = std::to_string(static_cast<u64>((value - floor(value)) * 60));
                    }
                } else {
                    if (data->Is_Float()) {
                        result = data->Float_String();
                    } else {
                        result = data->Long_String();
                    }
                }
            }
        } else if (CString_t::Is_Same(tag(), "Relationship", true)) {
            maybe<Form_t*> subject_data = Instance_Alias_Data(instance_id, value);
            maybe<Form_t*> object_data = Instance_Alias_Data(instance_id, sub_tag);
            if (subject_data && object_data) {
                maybe<Actor_Base_t*> subject = subject_data->As_Actor_Base();
                maybe<Actor_Base_t*> object = object_data->As_Actor_Base();
                if (subject && object) {
                    maybe<String_t> association = subject->Association_String(object());
                    if (association.Has_Value()) {
                        result = association.Value();
                    }
                }
            }
        }

        return result;
    }

    void Quest_t::Is_Objective_Completed(u16 index, Bool_t value)
    {
        unique<Script_t> script = Script_t::Create();
        Is_Objective_Completed(index, value, script());
    }

    void Quest_t::Is_Objective_Completed(u16 index, Bool_t value, some<Script_t*> script)
    {
        SKYLIB_ASSERT_SOME(script);

        script->Console_Is_Objective_Completed(this, index, value);
    }

    void Quest_t::Is_Objective_Displayed(u16 index, Bool_t value, Bool_t do_force)
    {
        unique<Script_t> script = Script_t::Create();
        Is_Objective_Displayed(index, value, do_force, script());
    }

    void Quest_t::Is_Objective_Displayed(u16 index, Bool_t value, Bool_t do_force, some<Script_t*> script)
    {
        SKYLIB_ASSERT_SOME(script);

        if (value && do_force) {
            script->Console_Is_Objective_Completed(this, index, false);
        }
        script->Console_Is_Objective_Displayed(this, index, value);
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

    void Quest_t::Unfill_Aliases(maybe<unique<Callback_i<>>> callback)
    {
        Alias_Reference_t::Unfill(Alias_References(), std::move(callback));
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
