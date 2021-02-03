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

            UNIDENTIFIED                    = static_cast<value_type>(0),
            STATIC                          = static_cast<value_type>(1),
            ANIMATED_STATIC                 = static_cast<value_type>(2),
            TRANSPARENT                     = static_cast<value_type>(3),
            CLUTTER                         = static_cast<value_type>(4),
            WEAPON                          = static_cast<value_type>(5),
            PROJECTILE                      = static_cast<value_type>(6),
            SPELL                           = static_cast<value_type>(7),
            BIPED                           = static_cast<value_type>(8),
            TREES                           = static_cast<value_type>(9),
            PROPS                           = static_cast<value_type>(10),
            WATER                           = static_cast<value_type>(11),
            TRIGGER                         = static_cast<value_type>(12),
            TERRAIN                         = static_cast<value_type>(13),
            TRAP                            = static_cast<value_type>(14),
            NON_COLLIDABLE                  = static_cast<value_type>(15),
            CLOUD_TRAP                      = static_cast<value_type>(16),
            GROUND                          = static_cast<value_type>(17),
            PORTAL                          = static_cast<value_type>(18),
            SMALL_DEBRIS                    = static_cast<value_type>(19),
            LARGE_DEBRIS                    = static_cast<value_type>(20),
            ACOUSTIC_SPACE                  = static_cast<value_type>(21),
            ACTOR_ZONE                      = static_cast<value_type>(22),
            PROJECTILE_ZONE                 = static_cast<value_type>(23),
            GAS_TRAP                        = static_cast<value_type>(24),
            SHELL_CASING                    = static_cast<value_type>(25),
            SMALL_TRANSPARENT               = static_cast<value_type>(26),
            INVISIBLE_WALL                  = static_cast<value_type>(27),
            SMALL_ANIMATED_TRANSPARENT      = static_cast<value_type>(28),
            WARD                            = static_cast<value_type>(29),
            CHARACTER_CONTROLLER            = static_cast<value_type>(30),
            STAIR_HELPER                    = static_cast<value_type>(31),
            DEAD_BIPED                      = static_cast<value_type>(32),
            NO_CHARACTER_CONTROLLER_BIPED   = static_cast<value_type>(33),
            AVOID_BOX                       = static_cast<value_type>(34),
            COLLISION_BOX                   = static_cast<value_type>(35),
            CAMERA_SPHERE                   = static_cast<value_type>(36),
            DOOR_DETECTION                  = static_cast<value_type>(37),
            CONE_PROJECTILE                 = static_cast<value_type>(38),
            CAMERA                          = static_cast<value_type>(39),
            ITEM_PICKER                     = static_cast<value_type>(40),
            LINE_OF_SIGHT                   = static_cast<value_type>(41),
            PATH_PICKER                     = static_cast<value_type>(42),
            CUSTOM_PICKER_1                 = static_cast<value_type>(43),
            CUSTOM_PICKER_2                 = static_cast<value_type>(44),
            SPELL_EXPLOSION                 = static_cast<value_type>(45),
            DROP_PICKER                     = static_cast<value_type>(46),
            DEAD_ACTOR_ZONE                 = static_cast<value_type>(47),
            FALLING_TRAP_TRIGGER            = static_cast<value_type>(48),
            NAVCUT                          = static_cast<value_type>(49),
            CRITTER                         = static_cast<value_type>(50),
            SPELL_TRIGGER                   = static_cast<value_type>(51),
            LIVING_AND_DEAD_ACTORS          = static_cast<value_type>(52),
            DETECTION                       = static_cast<value_type>(53),
            TRAP_TRIGGER                    = static_cast<value_type>(54),

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
