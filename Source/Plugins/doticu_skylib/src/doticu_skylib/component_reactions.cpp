/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/component_reactions.h"
#include "doticu_skylib/forward_list.inl"
#include "doticu_skylib/reaction.h"

namespace doticu_skylib {

    void Reactions_c::Component_Reactions_Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Reactions_c::Component_Reactions_Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "reaction_form_type: %s", this->reaction_form_type.As_String());

        if (!this->reactions.Is_Empty()) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "reactions:");
            size_t idx = 0;
            for (maybe<List_t<maybe<Reaction_t*>>::Node_t*> it = &this->reactions.head; it; it = it->next) {
                maybe<Reaction_t*> reaction = it->value;
                if (reaction) {
                    SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_TAB + "%zu:", idx);
                    reaction->Log(indent + SKYLIB_TAB + SKYLIB_TAB + SKYLIB_TAB);
                } else {
                    SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_TAB + "%zu: (none)", idx);
                }
                idx += 1;
            }
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "reactions: (none)");
        }

        SKYLIB_LOG(indent + "}");
    }

}
