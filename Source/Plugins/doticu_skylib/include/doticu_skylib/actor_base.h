/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/collections.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/xlist.h"

namespace doticu_skylib {

    class Form_t;
    class Race_t;

    class Object_t : public Form_t
    {
    public:
        virtual ~Object_t();
    };
    STATIC_ASSERT(sizeof(Object_t) == 0x20);

    class Bound_Object_t : public Object_t
    {
    public:
        virtual ~Bound_Object_t();

        Short_XYZ_t bound_min;  // 20
        Short_XYZ_t bound_max;  // 26
        u32         pad_2C;     // 2C
    };
    STATIC_ASSERT(sizeof(Bound_Object_t) == 0x30);

    class Animated_Object_t : public Bound_Object_t
    {
    public:
        virtual ~Animated_Object_t();
    };
    STATIC_ASSERT(sizeof(Animated_Object_t) == 0x30);

    class Actor_Value_e : public Enum_t<u32>
    {
    public:
        enum : u32
        {
            AGGRESSION = 0,
        };
        using Enum_t::Enum_t;
    };

    class Actor_Value_Modifier_e : public Enum_t<u32>
    {
    public:
        enum : u32
        {
            PERMANENT   = 0,
            TEMPORARY   = 1,
            DAMAGE      = 2,
            INVALID     = 3,
        };
        using Enum_t::Enum_t;
    };

    class Actor_Values_t
    {
    public:
        virtual ~Actor_Values_t(); // 0

        virtual Float_t Get_Actor_Value(Actor_Value_e actor_value);                                                     // 1
        virtual Float_t Get_Actor_Permanent_Value(Actor_Value_e actor_value);                                           // 2
        virtual Float_t Get_Actor_Base_Value(Actor_Value_e actor_value);                                                // 3
        virtual void    Set_Actor_Base_Value(Actor_Value_e actor_value, Float_t value);                                 // 4
        virtual void    Mod_Actor_Value(Actor_Value_e actor_value, Float_t value);                                      // 5
        virtual void    Restore_Actor_Value(Actor_Value_Modifier_e modifier, Actor_Value_e actor_value, Float_t value); // 6
        virtual void    Set_Actor_Value(Actor_Value_e actor_value, Float_t value);                                      // 7
        virtual Bool_t  Is_Player_Values();                                                                             // 8
    };
    STATIC_ASSERT(sizeof(Actor_Values_t) == 0x8);

    class Sex_e : Enum_t<Int_t>
    {
    public:
        enum : Int_t
        {
            NONE    = -1,
            MALE    = 0,
            FEMALE  = 1,
        };
        using Enum_t::Enum_t;
    };

    class Actor_Base_t :
        public Animated_Object_t,
        public Actor_Base_Component_t,
        public Container_Component_t,
        public Active_Effects_Component_t,
        public AI_Component_t,
        public Name_Component_t,
        public Actor_Values_t,
        public Destructible_Component_t,
        public Skin_Component_t,
        public Keyword_Component_t,
        public Attack_Component_t,
        public Perk_Component_t,
        public Race_Component_t,
        public Package_Override_Component_t,
        public Event_Sink_t<void*>
    {
    public:
        enum
        {
            FORM_TYPE   = Form_Type_e::ACTOR_BASE,
            kTypeID     = kFormType_NPC,
        };

        static size_t                   Actor_Base_Count();
        static Vector_t<Actor_Base_t*>  Actor_Bases();
        static void                     Actor_Bases(Vector_t<Actor_Base_t*>& results);
        static Vector_t<Actor_Base_t*>  Dynamic_Actor_Bases();
        static void                     Dynamic_Actor_Bases(Vector_t<Actor_Base_t*>& results);
        static void                     Log_Actor_Bases();
        static void                     Log_Dynamic_Actor_Bases();

    public:
        virtual ~Actor_Base_t();

        u8              skills[18];     // 190 // 00
        u8              unk_1A2[18];    // 1A2 // 12
        u16             attributes[3];  // 1B4 // 24
        u16             pad_1BA;        // 1BA // 2A
        Float_t         unk_1BC;        // 1BC // 2C
        TESClass*       actor_class;    // 1C0
        void*           head_data;      // 1C8
        void*           unk_1D0;        // 1D0
        TESCombatStyle* combat_style;   // 1D8
        u32             file_offset;    // 1E0
        u32             pad_1E4;        // 1E4
        Race_t*         extra_race;     // 1E8
        Actor_Base_t*   template_list;  // 1F0
        Float_t         height;         // 1F8
        Float_t         weight;         // 1FC
        // ...

        Sex_e                   Sex();
        Race_t*                 Race();
        Vector_t<Actor_Base_t*> Templates();
        void                    Templates(Vector_t<Actor_Base_t*>& results);

        String_t                Any_Name();
    };
    //STATIC_ASSERT(sizeof(Actor_Base_t) == 0x0);

}
