/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#undef TRANSPARENT

#include "doticu_skylib/enum_type.h"

namespace doticu_skylib {

    class Collision_Layer_Type_e_data :
        public Enum_Type_Data_t<s16>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_                          = -1,

            UNIDENTIFIED                    = 0,
            STATIC                          = 1,
            ANIMATED_STATIC                 = 2,
            TRANSPARENT                     = 3,
            CLUTTER                         = 4,
            WEAPON                          = 5,
            PROJECTILE                      = 6,
            SPELL                           = 7,
            BIPED                           = 8,
            TREES                           = 9,
            PROPS                           = 10,
            WATER                           = 11,
            TRIGGER                         = 12,
            TERRAIN                         = 13,
            TRAP                            = 14,
            NON_COLLIDABLE                  = 15,
            CLOUD_TRAP                      = 16,
            GROUND                          = 17,
            PORTAL                          = 18,
            SMALL_DEBRIS                    = 19,
            LARGE_DEBRIS                    = 20,
            ACOUSTIC_SPACE                  = 21,
            ACTOR_ZONE                      = 22,
            PROJECTILE_ZONE                 = 23,
            GAS_TRAP                        = 24,
            SHELL_CASING                    = 25,
            SMALL_TRANSPARENT               = 26,
            INVISIBLE_WALL                  = 27,
            SMALL_ANIMATED_TRANSPARENT      = 28,
            WARD                            = 29,
            CHARACTER_CONTROLLER            = 30,
            STAIR_HELPER                    = 31,
            DEAD_BIPED                      = 32,
            NO_CHARACTER_CONTROLLER_BIPED   = 33,
            AVOID_BOX                       = 34,
            COLLISION_BOX                   = 35,
            CAMERA_SPHERE                   = 36,
            DOOR_DETECTION                  = 37,
            CONE_PROJECTILE                 = 38,
            CAMERA                          = 39,
            ITEM_PICKER                     = 40,
            LINE_OF_SIGHT                   = 41,
            PATH_PICKER                     = 42,
            CUSTOM_PICKER_1                 = 43,
            CUSTOM_PICKER_2                 = 44,
            SPELL_EXPLOSION                 = 45,
            DROP_PICKER                     = 46,
            DEAD_ACTOR_ZONE                 = 47,
            FALLING_TRAP_TRIGGER            = 48,
            NAVCUT                          = 49,
            CRITTER                         = 50,
            SPELL_TRIGGER                   = 51,
            LIVING_AND_DEAD_ACTORS          = 52,
            DETECTION                       = 53,
            TRAP_TRIGGER                    = 54,

            _TOTAL_,
        };

    public:
        static Bool_t                   Is_Valid(value_type value);

        static some<const char* const*> Strings();
        static some<const char*>        To_String(value_type value);
        static value_type               From_String(maybe<const char*> string);
    };

    class Collision_Layer_Type_e :
        public Enum_Type_t<Collision_Layer_Type_e_data>
    {
    public:
        using Enum_Type_t::Enum_Type_t;
    };

    template <>
    class none<Collision_Layer_Type_e> :
        public none_enum<Collision_Layer_Type_e>
    {
    public:
        using none_enum::none_enum;
    };

    template <>
    class maybe<Collision_Layer_Type_e> :
        public maybe_enum<Collision_Layer_Type_e>
    {
    public:
        using maybe_enum::maybe_enum;
    };

    template <>
    class some<Collision_Layer_Type_e> :
        public some_enum<Collision_Layer_Type_e>
    {
    public:
        using some_enum::some_enum;
    };

}
