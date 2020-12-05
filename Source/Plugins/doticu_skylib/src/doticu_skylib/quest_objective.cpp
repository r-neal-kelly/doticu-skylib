/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/quest.h"
#include "doticu_skylib/quest_objective.h"

namespace doticu_skylib {

    void Quest_Objective_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Quest_Objective_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "this: 0x%p", this);
        if (display_text.data) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "display_text: %s", display_text.data);
        }
        if (quest) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "quest: %p %s", quest, quest->Get_Editor_ID());
        }
        SKYLIB_LOG(indent + SKYLIB_TAB + "target_count: %u", target_count);
        SKYLIB_LOG(indent + SKYLIB_TAB + "index: %u", index);
        SKYLIB_LOG(indent + SKYLIB_TAB + "state: %s", Quest_Objective_State_e::To_String(state));

        SKYLIB_LOG(indent + "}");
    }

}
