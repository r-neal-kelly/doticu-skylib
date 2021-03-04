/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"
#include "doticu_skylib/string.h"

#include "doticu_skylib/enum_ni_3d_flags.h"

#include "doticu_skylib/ni_bounds.h"
#include "doticu_skylib/ni_extras.h"
#include "doticu_skylib/ni_transform.h"

namespace doticu_skylib {

    class NI_Collidable_t;
    class NI_Node_t;
    class NI_Update_t;
    class Reference_t;

    class NI_3D_t :         // NiAVObject
        public NI_Extras_t  // 00
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI            = 0x01E14690,   // 684827

                SET_MOTION_TYPE = 0x00DA81E0,   // 76033
                UPDATE          = 0x00C56B50,   // 68900
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~NI_3D_t(); // 00

    public:
        maybe<NI_Node_t*>       parent_node;                // 030
        u32                     parent_index;               // 038
        u32                     unk_03C;                    // 03C
        maybe<NI_Collidable_t*> collidable;                 // 040
        NI_Transform_t          local_transform;            // 048
        NI_Transform_t          world_transform;            // 07C
        NI_Transform_t          previous_world_transform;   // 0B0
        NI_Bounds_t             world_bounds;               // 0E4
        NI_3D_Flags_e           ni_3d_flags;                // 0F4
        maybe<Reference_t*>     reference;                  // 0F8
        Float_t                 fade_amount;                // 100
        u32                     last_updated_frame_counter; // 104
        u64                     unk_108;                    // 108

    public:
        Vector_t<some<NI_3D_t*>>            Children();
        void                                Children(Vector_t<some<NI_3D_t*>>& results);
        Vector_t<some<NI_Collidable_t*>>    Collidables();
        void                                Collidables(Vector_t<some<NI_Collidable_t*>>& results);
        void                                Update(NI_Update_t& ni_update);

        String_t                            Name();

    public:
        void Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(NI_3D_t) == 0x110);

}
