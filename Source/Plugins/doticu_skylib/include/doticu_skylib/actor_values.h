/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_actor_value_type.h"
#include "doticu_skylib/enum_actor_value_modifier.h"

namespace doticu_skylib {

    class Actor_Values_t // ActorValueOwner
    {
    public:
        virtual         ~Actor_Values_t();                                                                                      // 0
        virtual Float_t Get_Current_Actor_Value(Raw_Actor_Value_Type_t type);                                                   // 1
        virtual Float_t Get_Maximum_Actor_Value(Raw_Actor_Value_Type_t type);                                                   // 2
        virtual Float_t Get_Default_Actor_Value(Raw_Actor_Value_Type_t type);                                                   // 3
        virtual void    Set_Default_Actor_Value(Raw_Actor_Value_Type_t type, Float_t value);                                    // 4
        virtual void    Do_Mod_Default_Actor_Value(Raw_Actor_Value_Type_t type, Float_t value);                                 // 5
        virtual void    Do_Mod_Current_Actor_Value(Raw_Actor_Value_Modifier_t mod, Raw_Actor_Value_Type_t type, Float_t value); // 6
        virtual void    Set_Default_Actor_Value_2(Raw_Actor_Value_Type_t type, Float_t value);                                  // 7 (what is the difference?)
        virtual Bool_t  Get_Is_Player_Values();                                                                                 // 8

    public:
        void Damage_Actor_Value(Actor_Value_Type_e actor_value_type, Float_t amount);
        void Restore_Actor_Value(Actor_Value_Type_e actor_value_type, Float_t amount);

    public:
        void Log_Actor_Value(Actor_Value_Type_e actor_value_type, std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Actor_Values_t) == 0x8);

}
