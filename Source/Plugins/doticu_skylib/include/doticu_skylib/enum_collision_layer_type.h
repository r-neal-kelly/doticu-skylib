/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#undef TRANSPARENT // why Microsoft?

#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe_numeric.h"

namespace doticu_skylib {

    class Collision_Layer_Type_e : public Enum_t<u16>
    {
    public:
        enum : value_type
        {
            _NONE_                          = static_cast<value_type>(~0),

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

            _END_,
        };

    public:
        using Enum_t::Enum_t;

    public:
        explicit operator Bool_t() const
        {
            return this->value != _NONE_ && this->value < _END_;
        }

        Bool_t operator!() const
        {
            return !static_cast<Bool_t>(*this);
        }
    };

    template <>
    inline Bool_t Is_Equal(const none<Collision_Layer_Type_e>& a, const Collision_Layer_Type_e& b)
    {
        return !b;
    }

    template <>
    class none<Collision_Layer_Type_e> : public none_numeric<Collision_Layer_Type_e>
    {
    public:
        none() : none_numeric(Collision_Layer_Type_e::_NONE_) {}
    };

    template <>
    class maybe<Collision_Layer_Type_e> : public maybe_numeric<Collision_Layer_Type_e>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<Collision_Layer_Type_e> : public some_numeric<Collision_Layer_Type_e>
    {
    public:
        using some_numeric::some_numeric;
    };

}
