/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/enum_comparator.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/game_macros.h"
#include "doticu_skylib/keyword.h"
#include "doticu_skylib/mod.h"

namespace doticu_skylib {

    Int_t Keyword_t::Compare_Any_Names(Keyword_t*& a, Keyword_t*& b)
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

    String_t Keyword_t::Any_Name()
    {
        const char* name = Get_Editor_ID();
        if (name && name[0]) {
            return name;
        } else {
            return Form_ID_String();
        }
    }

    void Keyword_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Keyword_t::Log");
        SKYLIB_LOG(indent + "{");

        if (this->editor_id) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "editor_id: %s", this->editor_id);
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "editor_id: (none)");
        }

        SKYLIB_LOG(indent + SKYLIB_TAB + "form_id: %s", this->form_id.As_String());

        SKYLIB_LOG(indent + "}");
    }

}
