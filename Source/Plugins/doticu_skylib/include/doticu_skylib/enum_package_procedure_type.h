/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Package_Procedure_Type_e :
        public Enum_t<u8>
    {
    public:
        enum : value_type
        {
            FIND = 0,
            FOLLOWER,
            ESCORT,
            EAT,
            SLEEP,
            WANDER,
            TRAVEL,
            ACCOMPANY,
            USE_ITEM_AT,
            AMBUSH,
            FLEE_NOT_COMBAT,
            CAST_MAGIC,
            SANDBOX,
            PATROL,
            GUARD,
            DIALOGUE,
            USE_WEAPON,
            FIND_2,
            PACKAGE,
            PACKAGE_TEMPLATE,
            ACTIVATE,
            ALARM,
            FLEE,
            TRESPASS,
            SPECTATOR,
            REACT_TO_DEAD,
            GET_UP_FROM_CHAIR_OR_BED,
            DO_NOTHING,
            IN_GAME_DIALOGUE,
            SURFACE,
            SEARCH_FOR_ATTACKER,
            AVOID_PLAYER,
            REACT_TO_DESTROYED_OBJECT,
            REACT_TO_GRENADE_OR_MINE,
            STEAL_WARNING,
            PICK_POCKET_WARNING,
            MOVEMENT_BLOCKED,
            VAMPIRE_FEED,
            CANNIBAL
        };
        using Enum_t::Enum_t;
    };

}
