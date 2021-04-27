/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/faction.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/reaction.h"

namespace doticu_skylib {

    void Reaction_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Reaction_t::Log");
        SKYLIB_LOG(indent + "{");

        if (this->form) {
            if (this->form->Is_Faction()) {
                this->form->As_Faction()->Log_Basic(indent + SKYLIB_TAB);
            } else {
                this->form->Log_Name_And_Type(indent + SKYLIB_TAB);
            }
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "form: (none)");
        }

        SKYLIB_LOG(indent + SKYLIB_TAB + "modifier: %i", this->modifier);
        SKYLIB_LOG(indent + SKYLIB_TAB + "reaction_type: %s", this->reaction_type.As_String());

        SKYLIB_LOG(indent + "}");
    }

}
