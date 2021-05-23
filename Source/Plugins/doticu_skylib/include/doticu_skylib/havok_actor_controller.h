/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/dynatomic_count.h"
#include "doticu_skylib/enum_actor_controller_flags.h"
#include "doticu_skylib/event_dispatcher.h"
#include "doticu_skylib/havok_quad.h"
#include "doticu_skylib/havok_step_time.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/ni_extra_bounds.h"
#include "doticu_skylib/unknown.h"

namespace doticu_skylib {

    class Havok_Rigid_Body_t;
    class Havok_Shape_Base_t;

    class Havok_Actor_Controller_t :        // bhkCharacterController
        public Dynatomic_Count_t,           // 000
        public Event_Dispatcher_t<void*>    // 010
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E9F410, // 690766
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Havok_Actor_Controller_t(); // 0

    public:
        u64                         pad_068;                        // 068
        Havok_Quad_t                forward_quad;                   // 070
        Havok_Step_Time_t           step_time;                      // 080
        Havok_Quad_t                unk_090;                        // 090
        Havok_Quad_t                unk_0A0;                        // 0A0
        Havok_Quad_t                unk_0B0;                        // 0B0
        Havok_Quad_t                unk_0C0;                        // 0C0
        Havok_Quad_t                unk_0D0;                        // 0D0
        Havok_Quad_t                unk_0E0;                        // 0E0
        Havok_Quad_t                unk_0F0;                        // 0F0
        Havok_Quad_t                unk_100;                        // 100
        Havok_Quad_t                unk_110;                        // 110
        NI_Extra_Bounds_t           collision_bounds;               // 120
        NI_Extra_Bounds_t           bumped_collision_bounds;        // 150
        u64                         unk_180;                        // 180
        u64                         unk_188;                        // 188
        void*                       unk_190;                        // 190
        u64                         pad_198;                        // 198
        Byte_t                      data_1A0[0x78];                 // 1A0
        Actor_Controller_Flags_e    actor_controller_flags;         // 218
        u32                         unk_21C;                        // 21C
        Float_t                     unk_220;                        // 220
        Float_t                     unk_224;                        // 224
        Float_t                     unk_228;                        // 228
        Float_t                     unk_22C;                        // 22C
        Float_t                     unk_230;                        // 230
        Float_t                     unk_234;                        // 234
        Float_t                     unk_238;                        // 238
        Float_t                     unk_23C;                        // 23C
        Float_t                     unk_240;                        // 240
        Float_t                     unk_244;                        // 244
        Float_t                     unk_248;                        // 248
        Float_t                     unk_24C;                        // 24C
        Float_t                     unk_250;                        // 250
        Float_t                     unk_254;                        // 254
        Float_t                     unk_258;                        // 258
        Float_t                     unk_25C;                        // 25C
        Float_t                     unk_260;                        // 260
        Float_t                     unk_264;                        // 264
        u32                         unk_268;                        // 268
        u32                         unk_26C;                        // 26C
        u64                         unk_270;                        // 270
        u64                         unk_278;                        // 278
        maybe<Havok_Shape_Base_t*>  unk_280;                        // 280
        maybe<Havok_Shape_Base_t*>  unk_288;                        // 288
        u64                         unk_290;                        // 290
        u64                         unk_298;                        // 298
        u64                         unk_2A0;                        // 2A0
        u64                         unk_2A8;                        // 2A8
        maybe<Havok_Rigid_Body_t*>  support_body;                   // 2B0
        Float_t                     bumped_force;                   // 2B8
        u32                         pad_2BC;                        // 2BC
        maybe<Havok_Rigid_Body_t*>  currently_colliding_reference;  // 2C0
        maybe<Havok_Rigid_Body_t*>  currently_colliding_actor;      // 2C8
        Hash_Map_t<void*, void*>    unk_2D0;                        // 2D0
        u64                         unk_300;                        // 300
        u64                         unk_308;                        // 308
        u64                         unk_310;                        // 310
        u64                         unk_318;                        // 318
        u64                         unk_320;                        // 320
        u64                         unk_328;                        // 328
    };
    STATIC_ASSERT(sizeof(Havok_Actor_Controller_t) == 0x330);

}
