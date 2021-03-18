/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"

#include "doticu_skylib/form.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/mod.h"

namespace doticu_skylib {

    #define DEFINE_MOD(NAME_)                                               \
    SKYLIB_M                                                                \
        static maybe<Mod_t*> mod = doticu_skylib::Mod_t::Active_Mod(NAME_); \
        return mod;                                                         \
    SKYLIB_W

    #define DEFINE_SOME_MOD(NAME_)                                              \
    SKYLIB_M                                                                    \
        static some<Mod_t*> mod = doticu_skylib::Mod_t::Active_Mod(NAME_)();    \
        SKYLIB_ASSERT_SOME(mod);                                                \
        return mod;                                                             \
    SKYLIB_W

    #define DEFINE_FORM(MOD_, TYPE_, LOWER_FORM_ID_)            \
    SKYLIB_M                                                    \
        SKYLIB_ASSERT(MOD_);                                    \
        static maybe<TYPE_*> form = static_cast<maybe<TYPE_*>>  \
            (Game_t::Form(MOD_(), LOWER_FORM_ID_));             \
        SKYLIB_ASSERT(form);                                    \
        return form();                                          \
    SKYLIB_W

    #define DEFINE_VERSION(TYPE_, ...)                      \
    SKYLIB_M                                                \
        static const Version_t<TYPE_> version(__VA_ARGS__); \
        return version;                                     \
    SKYLIB_W

}
