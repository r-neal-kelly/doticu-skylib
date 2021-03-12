/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.h"
#include "doticu_skylib/reference.h"
#include "doticu_skylib/static.h"

namespace doticu_skylib {

    some<Static_t*> Static_t::X_Marker()
    {
        static some<Static_t*> x_marker = static_cast<Static_t*>(Game_t::Form(0x0000003B)());
        SKYLIB_ASSERT_SOME(x_marker);

        return x_marker;
    }

    some<Static_t*> Static_t::X_Marker_Heading()
    {
        static some<Static_t*> x_marker_heading = static_cast<Static_t*>(Game_t::Form(0x00000034)());
        SKYLIB_ASSERT_SOME(x_marker_heading);

        return x_marker_heading;
    }

    some<Reference_t*> Static_t::Create_X_Marker(maybe<Reference_t*> at)
    {
        maybe<Reference_t*> reference = Reference_t::Create(X_Marker(), 1, at, true, false, true);
        SKYLIB_ASSERT_SOME(reference);

        return reference();
    }

    some<Reference_t*> Static_t::Create_X_Marker_Heading(maybe<Reference_t*> at)
    {
        maybe<Reference_t*> reference = Reference_t::Create(X_Marker_Heading(), 1, at, true, false, true);
        SKYLIB_ASSERT_SOME(reference);

        return reference();
    }

}
