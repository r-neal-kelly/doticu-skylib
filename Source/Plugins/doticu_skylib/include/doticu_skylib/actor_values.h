/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_actor_value.h"
#include "doticu_skylib/enum_actor_value_modifier.h"

namespace doticu_skylib {

    class Actor_Values_t
    {
    public:
        virtual ~Actor_Values_t(); // 0

        virtual Float_t Get_Actor_Value(Actor_Value_e::value_type type);                                                        // 1
        virtual Float_t Get_Actor_Permanent_Value(Actor_Value_e::value_type type);                                              // 2
        virtual Float_t Get_Actor_Base_Value(Actor_Value_e::value_type type);                                                   // 3
        virtual void    Set_Actor_Base_Value(Actor_Value_e::value_type type, Float_t value);                                    // 4
        virtual void    Mod_Actor_Value(Actor_Value_e::value_type type, Float_t value);                                         // 5
        virtual void    Restore_Actor_Value(Actor_Value_Modifier_e::value_type modifier, Actor_Value_e type, Float_t value);    // 6
        virtual void    Set_Actor_Value(Actor_Value_e::value_type type, Float_t value);                                         // 7
        virtual Bool_t  Is_Player_Values();                                                                                     // 8
    };
    STATIC_ASSERT(sizeof(Actor_Values_t) == 0x8);

}
