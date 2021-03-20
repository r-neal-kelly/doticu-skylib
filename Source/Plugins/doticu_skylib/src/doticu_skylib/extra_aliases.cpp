/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/alias_base.h"
#include "doticu_skylib/alias_reference.h"
#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/extra_aliases.h"

namespace doticu_skylib {

    void Extra_Aliases_t::Instance_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Extra_Aliases_t::Instance_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + "}");
    }

    Bool_t Extra_Aliases_t::Is_Aliased()
    {
        Read_Locker_t locker(this->lock);

        return this->instances.Count() > 0;
    }

    Bool_t Extra_Aliases_t::Is_Aliased(some<Quest_t*> quest)
    {
        SKYLIB_ASSERT_SOME(quest);

        Read_Locker_t locker(this->lock);

        for (size_t idx = 0, end = this->instances.Count(); idx < end; idx += 1) {
            maybe<Extra_Aliases_t::Instance_t*> instance = this->instances[idx];
            if (instance && instance->quest == quest) {
                return true;
            }
        }

        return false;
    }

    Bool_t Extra_Aliases_t::Is_Aliased(some<Quest_t*> quest, Alias_ID_t alias_id)
    {
        SKYLIB_ASSERT_SOME(quest);

        Read_Locker_t locker(this->lock);

        for (size_t idx = 0, end = this->instances.Count(); idx < end; idx += 1) {
            maybe<Extra_Aliases_t::Instance_t*> instance = this->instances[idx];
            if (instance && instance->quest == quest && instance->alias_base && instance->alias_base->id == alias_id) {
                return true;
            }
        }

        return false;
    }

    Bool_t Extra_Aliases_t::Is_Protected()
    {
        Read_Locker_t locker(this->lock);

        for (size_t idx = 0, end = this->instances.Count(); idx < end; idx += 1) {
            maybe<Extra_Aliases_t::Instance_t*> instance = this->instances[idx];
            if (instance && instance->alias_base && instance->alias_base->Is_Protected()) {
                return true;
            }
        }

        return false;
    }

    Bool_t Extra_Aliases_t::Is_Essential()
    {
        Read_Locker_t locker(this->lock);

        for (size_t idx = 0, end = this->instances.Count(); idx < end; idx += 1) {
            maybe<Extra_Aliases_t::Instance_t*> instance = this->instances[idx];
            if (instance && instance->alias_base && instance->alias_base->Is_Essential()) {
                return true;
            }
        }

        return false;
    }

    Bool_t Extra_Aliases_t::Is_Quest_Item() const
    {
        Read_Locker_t locker(this->lock);

        for (size_t idx = 0, end = this->instances.Count(); idx < end; idx += 1) {
            maybe<Extra_Aliases_t::Instance_t*> instance = this->instances[idx];
            if (instance && instance->alias_base && instance->alias_base->Is_Quest_Item()) {
                return true;
            }
        }

        return false;
    }

    Vector_t<some<Alias_Base_t*>> Extra_Aliases_t::Alias_Bases()
    {
        Vector_t<some<Alias_Base_t*>> results;
        Alias_Bases(results);
        return results;
    }

    void Extra_Aliases_t::Alias_Bases(Vector_t<some<Alias_Base_t*>>& results)
    {
        Read_Locker_t locker(this->lock);

        for (size_t idx = 0, end = this->instances.Count(); idx < end; idx += 1) {
            maybe<Extra_Aliases_t::Instance_t*> instance = this->instances[idx];
            if (instance) {
                maybe<Alias_Base_t*> alias_base = instance->alias_base;
                if (alias_base && !results.Has(alias_base())) {
                    results.push_back(alias_base());
                }
            }
        }
    }

    Vector_t<some<Alias_Reference_t*>> Extra_Aliases_t::Alias_References()
    {
        Vector_t<some<Alias_Reference_t*>> results;
        Alias_References(results);
        return results;
    }

    void Extra_Aliases_t::Alias_References(Vector_t<some<Alias_Reference_t*>>& results)
    {
        Read_Locker_t locker(this->lock);

        for (size_t idx = 0, end = this->instances.Count(); idx < end; idx += 1) {
            maybe<Extra_Aliases_t::Instance_t*> instance = this->instances[idx];
            if (instance && instance->alias_base) {
                maybe<Alias_Reference_t*> alias_reference = instance->alias_base->As_Alias_Reference();
                if (alias_reference && !results.Has(alias_reference())) {
                    results.push_back(alias_reference());
                }
            }
        }
    }

    Vector_t<some<Quest_t*>> Extra_Aliases_t::Quests()
    {
        Vector_t<some<Quest_t*>> results;
        Quests(results);
        return results;
    }

    void Extra_Aliases_t::Quests(Vector_t<some<Quest_t*>>& results)
    {
        Read_Locker_t locker(this->lock);

        for (size_t idx = 0, end = this->instances.Count(); idx < end; idx += 1) {
            maybe<Extra_Aliases_t::Instance_t*> instance = this->instances[idx];
            if (instance) {
                maybe<Quest_t*> quest = instance->quest;
                if (quest && !results.Has(quest())) {
                    results.push_back(quest());
                }
            }
        }
    }

    void Extra_Aliases_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Extra_Aliases_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "is_quest_item: %s", Is_Quest_Item() ? "true" : "false");

        SKYLIB_LOG(indent + "}");
    }

}
