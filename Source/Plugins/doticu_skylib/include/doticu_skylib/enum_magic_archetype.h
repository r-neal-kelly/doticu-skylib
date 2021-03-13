/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Magic_Archetype_e :
        public Enum_t<u32>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_                      = static_cast<value_type>(-1),

            VALUE_MODIFIER              = static_cast<value_type>(0),
            SCRIPT                      = static_cast<value_type>(1),
            DISPEL                      = static_cast<value_type>(2),
            CURE_DISEASE                = static_cast<value_type>(3),
            ABSORB                      = static_cast<value_type>(4),
            DUAL_VALUE_MODIFIER         = static_cast<value_type>(5),
            CALM                        = static_cast<value_type>(6),
            DEMORALIZE                  = static_cast<value_type>(7),
            FRENZY                      = static_cast<value_type>(8),
            DISARM                      = static_cast<value_type>(9),
            COMMAND_SUMMONED            = static_cast<value_type>(10),
            INVISIBILITY                = static_cast<value_type>(11),
            LIGHT                       = static_cast<value_type>(12),
            DARKNESS                    = static_cast<value_type>(13),
            NIGHT_EYE                   = static_cast<value_type>(14),
            LOCK                        = static_cast<value_type>(15),
            OPEN                        = static_cast<value_type>(16),
            BOUND_WEAPON                = static_cast<value_type>(17),
            SUMMON_CREATURE             = static_cast<value_type>(18),
            DETECT_LIFE                 = static_cast<value_type>(19),
            TELEKINESIS                 = static_cast<value_type>(20),
            PARALYSIS                   = static_cast<value_type>(21),
            REANIMATE                   = static_cast<value_type>(22),
            SOUL_TRAP                   = static_cast<value_type>(23),
            TURN_UNDEAD                 = static_cast<value_type>(24),
            GUIDE                       = static_cast<value_type>(25),
            WEREWOLF_FEED               = static_cast<value_type>(26),
            CURE_PARALYSIS              = static_cast<value_type>(27),
            CURE_ADDICTION              = static_cast<value_type>(28),
            CURE_POISON                 = static_cast<value_type>(29),
            CONCUSSION                  = static_cast<value_type>(30),
            VALUE_AND_PARTS             = static_cast<value_type>(31),
            ACCUMULATE_MAGNITUDE        = static_cast<value_type>(32),
            STAGGER                     = static_cast<value_type>(33),
            PEAK_VALUE_MODIFIER         = static_cast<value_type>(34),
            CLOAK                       = static_cast<value_type>(35),
            WEREWOLF                    = static_cast<value_type>(36),
            SLOW_TIME                   = static_cast<value_type>(37),
            RALLY                       = static_cast<value_type>(38),
            ENHANCE_WEAPON              = static_cast<value_type>(39),
            SPAWN_HAZARD                = static_cast<value_type>(40),
            ETHEREALIZE                 = static_cast<value_type>(41),
            BANISH                      = static_cast<value_type>(42),
            SPAWN_SCRIPTED_REFERENCE    = static_cast<value_type>(43),
            DISGUISE                    = static_cast<value_type>(44),
            GRAB_ACTOR                  = static_cast<value_type>(45),
            VAMPIRE_LORD                = static_cast<value_type>(46),

            _TOTAL_                     = static_cast<value_type>(47),
        };
        using Enum_t::Enum_t;
    };

}
