/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/form.h"

namespace doticu_skylib {

    class Actor_t;

    class Location_t :
        public Form_t,
        public Name_Component_t,
        public Keyword_Component_t
    {
    public:
        enum
        {
            kTypeID = kFormType_Location,
        };

        class Unloaded_Reference_t
        {
        public:
            Form_ID_t   reference_id;           // 0
            Form_ID_t   parent_worldspace_id;   // 4
            u32         unk_10;                 // 8
        };
        STATIC_ASSERT(sizeof(Unloaded_Reference_t) == 0xC);

        class XUnloaded_References_t
        {
        public:
            tArray<Unloaded_Reference_t>    added;      // 00
            Set_t<Form_ID_t>                removed;    // 18
        };
        STATIC_ASSERT(sizeof(XUnloaded_References_t) == 0x48);

        class Typed_Reference_t
        {
        public:
            BGSLocationRefType*     type;               // 00
            Unloaded_Reference_t    unloaded_reference; // 08
            u32                     pad_14;             // 14
        };
        STATIC_ASSERT(sizeof(Typed_Reference_t) == 0x18);

        class Unique_Actor_t
        {
        public:
            Actor_t*    actor;              // 00
            Form_ID_t   reference_id;       // 08
            u32         pad_0C;             // 0C
            Location_t* editor_location;    // 10
        };
        STATIC_ASSERT(sizeof(Unique_Actor_t) == 0x18);

        class Keyword_Float_t
        {
        public:
            Keyword_t*  keyword;    // 00
            Float_t     value;      // 08
            u32         pad_0C;     // 0C
        };
        STATIC_ASSERT(sizeof(Keyword_Float_t) == 0x10);

    public:
        virtual ~Location_t();

        Location_t*                 parent_location;        // 48
        Faction_t*                  crime_faction;          // 50
        BGSMusicType*               music_type;             // 58
        Reference_Handle_t          world_marker;           // 60
        Float_t                     world_radius;           // 64
        Reference_Handle_t          horse_marker;           // 68
        u32                         pad_6C;                 // 6C
        tArray<Typed_Reference_t>   typed_references;       // 70
        tArray<Unique_Actor_t>      unique_actors;          // 88
        XUnloaded_References_t*     xunloaded_references;   // A0
        void*                       unk_A8;                 // A8
        tArray<Reference_Handle_t>  promoted_references;    // B0
        volatile s32                loaded_count;           // C8
        u32                         file_offset;            // CC
        tArray<Keyword_Float_t>     keyword_floats;         // D0
        u32                         unk_E8;                 // E8
        Bool_t                      is_cleared;             // EC
        Bool_t                      was_ever_cleared;       // ED
        u16                         pad_EE;                 // EE

        String_t Any_Name();
    };
    STATIC_ASSERT(sizeof(Location_t) == 0xF0);

}
