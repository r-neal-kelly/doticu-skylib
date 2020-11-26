/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/utils.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/reference.h"

namespace doticu_skylib {

    class Magic_Target_t
    {
    public:
        virtual ~Magic_Target_t();

        void*   unk_08; // 08
        u8      unk_10; // 10
        u8      pad_11; // 11
        u16     pad_12; // 12
        u32     pad_14; // 14
    };
    STATIC_ASSERT(sizeof(Magic_Target_t) == 0x18);

    class Actor_State_t
    {
    public:
        virtual ~Actor_State_t();

        class State_t
        {
        public:
            Bool_t moving_back : 1;         // 0::0
            Bool_t moving_forward : 1;      // 0::1
            Bool_t moving_right : 1;        // 0::2
            Bool_t moving_left : 1;         // 0::3
            Bool_t unk_0_4 : 1;             // 0::4
            Bool_t unk_0_5 : 1;             // 0::5
            Bool_t walking : 1;             // 0::6
            Bool_t running : 1;             // 0::7
            Bool_t sprinting : 1;           // 1::0
            Bool_t sneaking : 1;            // 1::1
            Bool_t swimming : 1;            // 1::2
            Bool_t unk_1_3 : 1;             // 1::3
            Bool_t unk_1_4 : 1;             // 1::4
            Bool_t unk_1_5 : 1;             // 1::5
            Bool_t sitting_sleeping_0 : 1;  // 1::6
            Bool_t sitting_sleeping_1 : 1;  // 1::7
            Bool_t sitting_sleeping_2 : 1;  // 2::0
            Bool_t sitting_sleeping_3 : 1;  // 2::1
            Bool_t flying_0 : 1;            // 2::2
            Bool_t flying_1 : 1;            // 2::3
            Bool_t flying_2 : 1;            // 2::4
            Bool_t living_0 : 1;            // 2::5
            Bool_t living_1 : 1;            // 2::6
            Bool_t living_2 : 1;            // 2::7
            Bool_t living_3 : 1;            // 3::0
            Bool_t knocked_0 : 1;           // 3::1
            Bool_t knocked_1 : 1;           // 3::2
            Bool_t knocked_2 : 1;           // 3::3
            Bool_t melee_0 : 1;             // 3::4
            Bool_t melee_1 : 1;             // 3::5
            Bool_t melee_2 : 1;             // 3::6
            Bool_t melee_3 : 1;             // 3::7
            Bool_t talking_to_player : 1;   // 4::0
            Bool_t force_running : 1;       // 4::1
            Bool_t force_sneaking : 1;      // 4::2
            Bool_t head_tracking : 1;       // 4::3
            Bool_t reanimating : 1;         // 4::4
            Bool_t weapon_0 : 1;            // 4::5
            Bool_t weapon_1 : 1;            // 4::6
            Bool_t weapon_2 : 1;            // 4::7
            Bool_t wants_blocking : 1;      // 5::0
            Bool_t flight_blocked : 1;      // 5::1
            Bool_t recoil_0 : 1;            // 5::2
            Bool_t recoil_1 : 1;            // 5::3
            Bool_t flying_allowed : 1;      // 5::4
            Bool_t staggered : 1;           // 5::5
        };

        enum class Weapon_e : UInt8
        {
            SHEATHED = 0,
            WANTS_TO_DRAW = 1,
            DRAWING = 2,
            DRAWN = 3,
            WANTS_TO_SHEATHE = 4,
            SHEATHING = 5,
        };

        Bool_t Is_Moving();

        Weapon_e Weapon_State();

        State_t state;
    };
    STATIC_ASSERT(sizeof(Actor_State_t) == 0x10);

    class Actor_t;
    class Loaded_Actor_t
    {
    public:
        Actor_t*    actor;
        Cell_t*     cell;

        Loaded_Actor_t();
        Loaded_Actor_t(Actor_t* actor, Cell_t* cell);
        Loaded_Actor_t(Form_ID_t actor_form_id, Form_ID_t cell_form_id);
        Loaded_Actor_t(const Loaded_Actor_t& other);
        Loaded_Actor_t(Loaded_Actor_t&& other) noexcept;
        ~Loaded_Actor_t();

        Loaded_Actor_t& operator=(const Loaded_Actor_t& other);
        Loaded_Actor_t& operator=(Loaded_Actor_t&& other) noexcept;
        Bool_t operator==(const Loaded_Actor_t& other);
        Bool_t operator!=(const Loaded_Actor_t& other);

        Bool_t Is_Valid();

        operator Bool_t();
    };
    STATIC_ASSERT(sizeof(Loaded_Actor_t) == 0x10);

    class Actor_t :
        public Reference_t,
        public Magic_Target_t,
        public Actor_Values_t,
        public Actor_State_t,
        public Event_Sink_t<void**>,
        public Event_Sink_t<void***>,
        public IPostAnimationChannelUpdateFunctor
    {
    public:
        enum
        {
            kTypeID = kFormType_Character,
        };

        static Vector_t<Loaded_Actor_t> Loaded_Actors();
        static void                     Loaded_Actors(Vector_t<Loaded_Actor_t>& results);
        static void                     Log_Loaded_Actors();

    public:
        virtual ~Actor_t(); // 00

        Race_t*                 Race();
        Actor_Base_t*           Actor_Base();
        Vector_t<Actor_Base_t*> Actor_Bases();
        void                    Actor_Bases(Vector_t<Actor_Base_t*>& results);

        const char*             Base_Name();
        String_t                Any_Name();
    };
    //STATIC_ASSERT(sizeof(Actor_t) == 0x0);

}
