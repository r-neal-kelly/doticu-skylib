/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    /*
    Raw_Form_ID_t for footprints
    Form_ID_t wrapper. none == 0. should have a constructor that takes a Lower_Form_ID_t and Mod_Index_t
    Lower_Form_ID_t wrapper.
    Light_Form_ID_t inherits Form_ID_t, and none == invalid range on either mod or lower form id.
    Heavy_Form_ID_t ""
    */

    using Form_ID_t         = u32;
    using Lower_Form_ID_t   = u32;

}
