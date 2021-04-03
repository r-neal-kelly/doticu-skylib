/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/spell.h"

namespace doticu_skylib {

    void Spell_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Spell_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "component_name: %s", Component_Name());
        SKYLIB_LOG(indent + SKYLIB_TAB + "form_id: %s", this->form_id.As_String());

        SKYLIB_LOG(indent + SKYLIB_TAB + "keywords:");
        Keywords_c::Log_Component_Keywords(indent + SKYLIB_TAB + SKYLIB_TAB);

        SKYLIB_LOG(indent + "}");
    }

}
