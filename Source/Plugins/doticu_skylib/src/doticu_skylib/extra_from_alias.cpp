/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_data.inl"
#include "doticu_skylib/extra_from_alias.h"
#include "doticu_skylib/quest.h"

namespace doticu_skylib {

    some<Extra_From_Alias_t*> Extra_From_Alias_t::Create()
    {
        some<Extra_From_Alias_t*> x_from_alias = Extra_Data_t::Create<Extra_From_Alias_t>();

        x_from_alias->quest = none<Quest_t*>();
        x_from_alias->alias_id = 0;
        x_from_alias->pad_1C = 0;

        return x_from_alias;
    }

    some<Extra_From_Alias_t*> Extra_From_Alias_t::Create(maybe<Quest_t*> quest, Alias_ID_t alias_id)
    {
        some<Extra_From_Alias_t*> x_from_alias = Create();

        x_from_alias->Quest(quest);
        x_from_alias->Alias_ID(alias_id);

        return x_from_alias;
    }

    some<Extra_From_Alias_t*> Extra_From_Alias_t::Create(const Extra_From_Alias_t& other)
    {
        some<Extra_From_Alias_t*> x_from_alias = Extra_Data_t::Create<Extra_From_Alias_t>();

        x_from_alias->quest = other.quest;
        x_from_alias->alias_id = other.alias_id;
        x_from_alias->pad_1C = other.pad_1C;

        return x_from_alias;
    }

    void Extra_From_Alias_t::Destroy(some<Extra_From_Alias_t*> x_from_alias)
    {
        SKYLIB_ASSERT_SOME(x_from_alias);

        Extra_Data_t::Destroy<Extra_From_Alias_t>(x_from_alias);
    }

    maybe<Quest_t*> Extra_From_Alias_t::Quest() const
    {
        return this->quest;
    }

    void Extra_From_Alias_t::Quest(maybe<Quest_t*> quest)
    {
        this->quest = quest;
    }

    Alias_ID_t Extra_From_Alias_t::Alias_ID() const
    {
        return this->alias_id;
    }

    void Extra_From_Alias_t::Alias_ID(Alias_ID_t alias_id)
    {
        this->alias_id = alias_id;
    }

    void Extra_From_Alias_t::Log(std::string indent) const
    {
        SKYLIB_LOG(indent + "Extra_From_Alias_t::Log");
        SKYLIB_LOG(indent + "{");

        maybe<Quest_t*> quest = Quest();
        if (quest) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "quest: %s, %s", quest->Form_ID_String(), quest->Any_Name());
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "quest: (none)");
        }

        SKYLIB_LOG(indent + SKYLIB_TAB + "alias_id: %u", Alias_ID());

        SKYLIB_LOG(indent + "}");
    }

}
