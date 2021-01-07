/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Bound_Object_t;

    class Menu_Display_c : public Form_Data_c // BGSMenuDisplayObject
    {
    public:
        virtual ~Menu_Display_c(); // 0

    public:
        Bound_Object_t* menu_display;
    };
    STATIC_ASSERT(sizeof(Menu_Display_c) == 0x10);

}
