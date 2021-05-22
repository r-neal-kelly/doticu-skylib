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

        if (display_text) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "display_text: %s", display_text);
        }
        if (quest) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "quest: %s, %s", quest->form_id.As_String(), quest->Any_Name());
        }
        SKYLIB_LOG(indent + SKYLIB_TAB + "target_count: %u", target_count);
        SKYLIB_LOG(indent + SKYLIB_TAB + "index: %u", index);
        SKYLIB_LOG(indent + SKYLIB_TAB + "is_initialized: %s", is_initialized ? "true" : "false");
        SKYLIB_LOG(indent + SKYLIB_TAB + "state: %s", state.As_String());

        SKYLIB_LOG(indent + "}");
    }

}
