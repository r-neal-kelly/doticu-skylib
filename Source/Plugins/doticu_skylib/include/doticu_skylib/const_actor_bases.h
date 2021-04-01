/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Actor_Base_t;

}

namespace doticu_skylib { namespace Const { namespace Actor_Base {

    some<Actor_Base_t*> Player();

}}}
