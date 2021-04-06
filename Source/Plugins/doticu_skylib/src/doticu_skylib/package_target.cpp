/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/game.h"
#include "doticu_skylib/package_target.h"
#include "doticu_skylib/reference.h"

namespace doticu_skylib {

    void Package_Target_t::Log(std::string indent) const
    {
        SKYLIB_LOG(indent + "Package_Target_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "target_type: %s", this->target_type.As_String());
        SKYLIB_LOG(indent + SKYLIB_TAB + "count_or_distance: %i", this->count_or_distance);

        if (this->target_type == Package_Target_Type_e::SPECIFIC) {
            maybe<Reference_t*> specific = Reference_t::From_Handle(this->target.specific);
            if (specific) {
                SKYLIB_LOG(indent + SKYLIB_TAB + "specific:");
                specific->Log_Name_And_Type(indent + SKYLIB_TAB + SKYLIB_TAB);
            } else {
                SKYLIB_LOG(indent + SKYLIB_TAB + "specific: (none)");
            }
        } else if (this->target_type == Package_Target_Type_e::FORM_ID) {
            maybe<Form_t*> form = Game_t::Form(this->target.form_id);
            if (form) {
                SKYLIB_LOG(indent + SKYLIB_TAB + "form:");
                form->Log_Name_And_Type(indent + SKYLIB_TAB + SKYLIB_TAB);
            } else {
                SKYLIB_LOG(indent + SKYLIB_TAB + "form: (none)");
            }
        } else if (this->target_type == Package_Target_Type_e::FORM_TYPE) {
            Form_Type_e form_type = this->target.form_type;
            SKYLIB_LOG(indent + SKYLIB_TAB + "form_type: %s", form_type.As_String());
        } else if (this->target_type == Package_Target_Type_e::LINKED) {
            if (this->target.linked) {
                SKYLIB_LOG(indent + SKYLIB_TAB + "linked:");
                this->target.linked->Log_Name_And_Type(indent + SKYLIB_TAB + SKYLIB_TAB);
            } else {
                SKYLIB_LOG(indent + SKYLIB_TAB + "linked: (none)");
            }
        } else if (this->target_type == Package_Target_Type_e::ALIAS_ID) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "alias_id: %u", this->target.alias_id);
        } else if (this->target_type == Package_Target_Type_e::UNKNOWN) {
        } else if (this->target_type == Package_Target_Type_e::SELF) {
        }

        SKYLIB_LOG(indent + "}");
    }

}
