/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/component_keywords.h"
#include "doticu_skylib/component_name.h"
#include "doticu_skylib/dynamic_array.h"
#include "doticu_skylib/enum_script_type.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/reference_handle.h"
#include "doticu_skylib/string.h"

namespace doticu_skylib {

    class Actor_Base_t;
    class Faction_t;
    class Keyword_t;
    class Location_Reference_Type;

    class Location_t :      // BGSLocation
        public Form_t,      // 00
        public Name_c,      // 20
        public Keywords_c   // 30
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::LOCATION,
        };

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E197F0, // 513980
            };

        public:
            using Enum_t::Enum_t;
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
        static Vector_t<some<Location_t*>>          Locations_Dynamic();
        static void                                 Locations_Dynamic(Vector_t<some<Location_t*>>& results);

        static Vector_t<some<Location_t*>>          Locations_Static();
        static void                                 Locations_Static(Vector_t<some<Location_t*>>& results);

        static const Vector_t<some<Keyword_t*>>&    Civilized_Types();
        static const Vector_t<some<Keyword_t*>>&    Common_Civilized_Types();
        static const Vector_t<some<Keyword_t*>>&    Uncommon_Civilized_Types();

        static const Vector_t<some<Keyword_t*>>&    Dangerous_Types();
        static const Vector_t<some<Keyword_t*>>&    Common_Dangerous_Types();
        static const Vector_t<some<Keyword_t*>>&    Uncommon_Dangerous_Types();

    public:
        virtual ~Location_t();

    public:
        maybe<Location_t*>              parent_location;        // 48
        maybe<Faction_t*>               crime_faction;          // 50
        void*                           music_type;             // 58
        Reference_Handle_t              world_marker;           // 60
        Float_t                         world_radius;           // 64
        Reference_Handle_t              horse_marker;           // 68
        u32                             pad_6C;                 // 6C
        Array_t<Typed_Reference_t>      typed_references;       // 70
        Array_t<Unique_Actor_t>         unique_actors;          // 88 ACUN, LCUN?
        maybe<Changed_References_t*>    changed_references;     // A0
        void*                           unk_A8;                 // A8
        Array_t<Reference_Handle_t>     promoted_references;    // B0
        volatile s32                    loaded_count;           // C8
        u32                             file_offset;            // CC
        Array_t<Keyword_Float_t>        keyword_floats;         // D0
        u32                             unk_E8;                 // E8
        Bool_t                          is_cleared;             // EC
        Bool_t                          was_ever_cleared;       // ED
        u16                             pad_EE;                 // EE

    public:
        Bool_t                      Is_Inn() const;

        Bool_t                      Is_Likely_City_Or_Town() const;
        Bool_t                      Is_Likely_Civilized() const;
        Bool_t                      Is_Likely_Dangerous() const;
        Bool_t                      Is_Likely_Home() const;

        String_t                    Any_Name();

        Vector_t<some<Location_t*>> Parents() const;
        void                        Parents(Vector_t<some<Location_t*>>& results) const;

        Bool_t                      Has_Keyword(some<Keyword_t*> keyword) const;
        Bool_t                      Inherits_Keyword(some<Keyword_t*> keyword) const;
        Bool_t                      Has_Or_Inherits_Keyword(some<Keyword_t*> keyword) const;
        Bool_t                      Has_Any_Keywords(const Vector_t<some<Keyword_t*>> keywords) const;
        Bool_t                      Inherits_Any_Keywords(const Vector_t<some<Keyword_t*>> keywords) const;
        Bool_t                      Has_Or_Inherits_Any_Keywords(const Vector_t<some<Keyword_t*>> keywords) const;
    };
    STATIC_ASSERT(sizeof(Location_t) == 0xF0);

}
