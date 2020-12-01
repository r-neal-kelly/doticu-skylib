/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/string.h"

#include "doticu_skylib/component_keywords.h"
#include "doticu_skylib/component_name.h"

#include "doticu_skylib/form.h"
#include "doticu_skylib/reference_handle.h"

namespace doticu_skylib {

    class Actor_Base_t;
    class Faction_t;
    class Keyword_t;
    class Location_Reference_Type;

    class Location_t :
        public Form_t,
        public Name_c,
        public Keywords_c
    {
    public:
        enum
        {
            FORM_TYPE   = Form_Type_e::LOCATION,
            kTypeID     = FORM_TYPE,
        };

        class Unloaded_Reference_t
        {
        public:
            Form_ID_t   reference_id;           // 0
            Form_ID_t   parent_worldspace_id;   // 4 (Cell_t id?)
            u32         unk_10;                 // 8
        };
        STATIC_ASSERT(sizeof(Unloaded_Reference_t) == 0xC);

        class Changed_References_t
        {
        public:
            Array_t<Unloaded_Reference_t>   added;      // 00
            Set_t<Form_ID_t>                removed;    // 18
        };
        STATIC_ASSERT(sizeof(Changed_References_t) == 0x48);

        class Typed_Reference_t
        {
        public:
            Location_Reference_Type*    type;               // 00
            Unloaded_Reference_t        unloaded_reference; // 08
            u32                         pad_14;             // 14
        };
        STATIC_ASSERT(sizeof(Typed_Reference_t) == 0x18);

        class Unique_Actor_t
        {
        public:
            Actor_Base_t*   actor_base;         // 00 (this might be Actor_t*?)
            Form_ID_t       reference_id;       // 08
            u32             pad_0C;             // 0C
            Location_t*     editor_location;    // 10
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
        void*                       music_type;             // 58
        Reference_Handle_t          world_marker;           // 60
        Float_t                     world_radius;           // 64
        Reference_Handle_t          horse_marker;           // 68
        u32                         pad_6C;                 // 6C
        Array_t<Typed_Reference_t>  typed_references;       // 70
        Array_t<Unique_Actor_t>     unique_actors;          // 88 ACUN, LCUN?
        Changed_References_t*       changed_references;     // A0
        void*                       unk_A8;                 // A8
        Array_t<Reference_Handle_t> promoted_references;    // B0
        volatile s32                loaded_count;           // C8
        u32                         file_offset;            // CC
        Array_t<Keyword_Float_t>    keyword_floats;         // D0
        u32                         unk_E8;                 // E8
        Bool_t                      is_cleared;             // EC
        Bool_t                      was_ever_cleared;       // ED
        u16                         pad_EE;                 // EE

        String_t Any_Name();
    };
    STATIC_ASSERT(sizeof(Location_t) == 0xF0);

}
