/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/actor_skills.h"
#include "doticu_skylib/actor_values.h"
#include "doticu_skylib/animated_object.h"
#include "doticu_skylib/dynamic_array.h"
#include "doticu_skylib/component_actor_base_data.h"
#include "doticu_skylib/component_ai.h"
#include "doticu_skylib/component_attack_data.h"
#include "doticu_skylib/component_container.h"
#include "doticu_skylib/component_destructible.h"
#include "doticu_skylib/component_keywords.h"
#include "doticu_skylib/component_name.h"
#include "doticu_skylib/component_package_override.h"
#include "doticu_skylib/component_perks.h"
#include "doticu_skylib/component_race.h"
#include "doticu_skylib/component_skin.h"
#include "doticu_skylib/component_spells.h"
#include "doticu_skylib/enum_relation.h"
#include "doticu_skylib/enum_script_type.h"
#include "doticu_skylib/enum_sex.h"
#include "doticu_skylib/enum_sound_level.h"
#include "doticu_skylib/event_handler.h"
#include "doticu_skylib/interface.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/rarity.h"
#include "doticu_skylib/unique.h"
#include "doticu_skylib/unknown.h"

namespace doticu_skylib {

    class Actor_Class_t;        // TESClass
    class Actor_Face_Data_t;
    class Actor_Head_Data_t;
    class Armor_t;
    class Association_t;
    class Color_t;
    class Combat_Style_t;
    class Faction_t;
    class Form_List_t;
    class Head_Part_t;
    class Outfit_t;
    class Relation_t;

    namespace Virtual {

        class Actor_Base_t;

    }

    class Actor_Base_t :                // TESNPC
        public Animated_Object_t,       // 000
        public Actor_Base_Data_c,       // 030
        public Container_c,             // 088
        public Spells_c,                // 0A0
        public AI_c,                    // 0B0
        public Name_c,                  // 0D8
        public Actor_Values_t,          // 0E8
        public Destructible_c,          // 0F0
        public Skin_c,                  // 100
        public Keywords_c,              // 110
        public Attack_Data_c,           // 128
        public Perks_c,                 // 138
        public Race_c,                  // 150
        public Package_Override_c,      // 160
        public Event_Handler_t<void*>   // 188
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::ACTOR_BASE,
        };

        static constexpr const char* SCRIPT_NAME = "ActorBase";

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E14C08, // 513923
            };
            using Enum_t::Enum_t;
        };

        class Form_Flags_e :
            public Enum_t<u32>
        {
        public:
            enum enum_type : value_type
            {
                IS_DELETED = static_cast<value_type>(1 << 5),
            };
            using Enum_t::Enum_t;
        };

        class Form_Change_Flags_e :
            public Enum_t<u32>
        {
        public:
            enum enum_type : value_type
            {
                ACTOR_BASE_DATA = static_cast<value_type>(1 << 1),
                ATTRIBUTES      = static_cast<value_type>(1 << 2),
                AI              = static_cast<value_type>(1 << 3),
                SPELLS          = static_cast<value_type>(1 << 4),
                NAME            = static_cast<value_type>(1 << 5),
                FACTIONS        = static_cast<value_type>(1 << 6),
                SKILLS          = static_cast<value_type>(1 << 9),
                CLASS           = static_cast<value_type>(1 << 10),
                FACE            = static_cast<value_type>(1 << 11),
                DEFAULT_OUTFIT  = static_cast<value_type>(1 << 12), // (DOFT)
                SLEEP_OUTFIT    = static_cast<value_type>(1 << 13),
                GENDER          = static_cast<value_type>(1 << 24),
                RACE            = static_cast<value_type>(1 << 25),
            };
            using Enum_t::Enum_t;
        };

    public:
        static size_t                           Static_Actor_Base_Count();

        static Vector_t<some<Actor_Base_t*>>    All_Actor_Bases();
        static void                             All_Actor_Bases(Vector_t<some<Actor_Base_t*>>& results);
        static Vector_t<some<Actor_Base_t*>>    Static_Actor_Bases();
        static void                             Static_Actor_Bases(Vector_t<some<Actor_Base_t*>>& results);
        static Vector_t<some<Actor_Base_t*>>    Dynamic_Actor_Bases();
        static void                             Dynamic_Actor_Bases(Vector_t<some<Actor_Base_t*>>& results);
        static void                             Log_Static_Actor_Bases();
        static void                             Log_Dynamic_Actor_Bases();

        static void                             Stream_Actor_Bases(Vector_t<some<Actor_Base_t*>>& actor_bases, std::fstream& fstream);

        static Int_t                            Compare_Names(some<Actor_Base_t*>& a, some<Actor_Base_t*>& b);

        static some<Actor_Base_t*>              Create_Temporary_Copy(some<Actor_Base_t*> source);
        static void                             Destroy(some<Actor_Base_t*> actor_base);

    public:
        virtual                 ~Actor_Base_t();                                // 00

        virtual Bool_t          _53() const;                                    // 53
        virtual Combat_Style_t* Get_Combat_Style() const;                       // 54
        virtual void            Set_Combat_Style(Combat_Style_t* combat_style); // 55
        virtual Form_t*         Get_As_Form() const;                            // 56

    public:
        Actor_Skills_t                      actor_skills;           // 190
        maybe<Actor_Class_t*>               actor_class;            // 1C0
        maybe<Actor_Head_Data_t*>           head_data;              // 1C8
        maybe<Form_List_t*>                 gift_filter;            // 1D0
        maybe<Combat_Style_t*>              combat_style;           // 1D8
        u32                                 file_offset;            // 1E0
        u32                                 pad_1E4;                // 1E4
        maybe<Race_t*>                      original_race;          // 1E8 (attack_race?) (ATKR)
        maybe<Actor_Base_t*>                face_template;          // 1F0
        Float_t                             height;                 // 1F8
        Float_t                             weight;                 // 1FC
        void*                               sounds;                 // 200
        String_t                            short_name;             // 208 (SHRT)
        maybe<Armor_t*>                     far_skin;               // 210 (maybe worn armor?) (WNAM)
        maybe<Outfit_t*>                    default_outfit;         // 218 (DOFT)
        maybe<Outfit_t*>                    sleep_outfit;           // 220
        maybe<Form_List_t*>                 default_package_list;   // 228 (DPLT)
        maybe<Faction_t*>                   crime_faction;          // 230
        maybe<Head_Part_t*>                 head_parts;             // 238
        s8                                  head_part_count;        // 240
        u8                                  unk_241;                // 241
        u8                                  unk_242;                // 242
        u8                                  unk_243;                // 243
        u8                                  unk_244;                // 244
        Sound_Level_e                       sound_level;            // 245
        u8_rgba                             body_tint;              // 246
        u16                                 pad_24A;                // 24A
        u32                                 pad_24C;                // 24C
        maybe<Array_t<maybe<Relation_t*>>*> relations;              // 250
        maybe<Actor_Face_Data_t*>           face_data;              // 258
        maybe<Array_t<void*>*>              tint_layers;            // 260

    public:
        Bool_t                          Is_Deleted();
        Bool_t                          Isnt_Deleted();

        Bool_t                          Has_Template_FF000800(); // this is only found on certain actor bases, ones that are instantiated by its template form, I think.

        Sex_e                           Sex();
        Rarity_e                        Rarity();
        some<Relation_e>                Relation(some<Actor_Base_t*> other);
        void                            Relation(some<Actor_Base_t*> other, some<Relation_e> relation);
        maybe<Race_t*>                  Race();

        Float_t                         Weight();
        void                            Weight(Float_t weight);

        Vector_t<Keyword_t*>            Keywords(Bool_t include_templates = true);
        void                            Keywords(Vector_t<Keyword_t*>& results, Bool_t include_templates = true);

        some<Actor_Base_t*>             Base_Root();
        some<Actor_Base_t*>             Instantiated_Base();
        some<Actor_Base_t*>             Template_Root();
        Vector_t<Actor_Base_t*>         Templates();
        void                            Templates(Vector_t<Actor_Base_t*>& results);

        maybe<Actor_Base_t*>            Identifiable_Static_Base();

        maybe<Outfit_t*>                Default_Outfit();
        void                            Default_Outfit(maybe<Outfit_t*> default_outfit);
        maybe<Outfit_t*>                Sleep_Outfit();
        void                            Sleep_Outfit(maybe<Outfit_t*> sleep_outfit);

        maybe<Faction_t*>               Crime_Faction();
        void                            Crime_Faction(maybe<Faction_t*> faction);

        maybe<Color_t*>                 Hair_Color();
        void                            Hair_Color(maybe<Color_t*> hair_color, Bool_t do_save);

        maybe<Combat_Style_t*>          Combat_Style();
        void                            Combat_Style(maybe<Combat_Style_t*> combat_style);

        String_t                        Any_Name();
        String_t                        Name();
        void                            Name(String_t name, Bool_t do_save);

        maybe<Relation_t*>              Relation_Static(some<Actor_Base_t*> other);
        maybe<Association_t*>           Association(some<Actor_Base_t*> other);
        maybe<String_t>                 Association_String(some<Actor_Base_t*> other);

    public:
        void Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Actor_Base_t) == 0x268);

}
