/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/GameForms.h"

#include "doticu_skylib/collections.h"
#include "doticu_skylib/form_type.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/utils.h"

namespace doticu_skylib {

    class Form_t;
    class Mod_t;
    class Race_t;

    namespace Virtual {

        class Callback_i;

    }

    class Form_Component_t { // BaseFormComponent
    public:
        virtual ~Form_Component_t(); // 00

        virtual void _01(void); // 01
        virtual void _02(void); // 02
        virtual void _03(void); // 03
    };
    STATIC_ASSERT(sizeof(Form_Component_t) == 0x8);

    class Name_Component_t : public Form_Component_t { // TESFullName
    public:
        virtual             ~Name_Component_t();    // 00

        virtual u32         Name_Length();          // 04
        virtual const char* Name();                 // 05

        String_t    name; // 8
    };
    STATIC_ASSERT(sizeof(Name_Component_t) == 0x10);

    class Description_Component_t : public Form_Component_t // TESDescription
    {
    public:
        virtual ~Description_Component_t();

        u32 description_offset; // 08
        u32 description_text_id; // 0C
    };
    STATIC_ASSERT(sizeof(Description_Component_t) == 0x10);

    class Model_Component_t : public Form_Component_t { // TESModel
    public:
        virtual ~Model_Component_t(); // 00

        String_t    model;              // 08
        void*       textures;           // 10
        void*       model_addons;       // 18
        u16         texture_count;      // 20
        u16         model_addon_count;  // 22
        u32         pad_24;             // 24
    };
    STATIC_ASSERT(sizeof(Model_Component_t) == 0x28);

    class Model_Alternate_Textures_Component_t : public Model_Component_t // TESModelTextureSwap
    {
    public:
        virtual ~Model_Alternate_Textures_Component_t(); // 00

        void*   alternate_textures;         // 28
        u32     alternate_texture_count;    // 30
        u32     pad_34;                     // 34
    };
    STATIC_ASSERT(sizeof(Model_Alternate_Textures_Component_t) == 0x38);

    class Race_Component_t : public Form_Component_t { // TESRaceForm
    public:
        virtual ~Race_Component_t(); // 00

        Race_t* race; // 00
    };
    STATIC_ASSERT(sizeof(Race_Component_t) == 0x10);

    class Actor_Base_Flags_e : public Enum_t<u32>
    {
    public:
        enum
        {
            IS_FEMALE                       = 1lu << 0,
            IS_ESSENTIAL                    = 1lu << 1,
            IS_CHARGEN_FACE_PRESET          = 1lu << 2,
            DOES_RESPAWN                    = 1lu << 3,
            DOES_AUTO_CALCUATE_STATS        = 1lu << 4,
            IS_UNIQUE                       = 1lu << 5,
            DOESNT_AFFECT_STEALTH_METER     = 1lu << 6,
            HAS_PC_LEVEL_MULTIPLIER         = 1lu << 7,
            DOES_USE_TEMPLATE               = 1lu << 8,
            IS_PROTECTED                    = 1lu << 11,
            IS_SUMMONABLE                   = 1lu << 14,
            DOESNT_BLEED                    = 1lu << 16,
            HAS_BLEEDOUT_OVERRIDE           = 1lu << 18,
            HAS_OPPOSITE_GENDER_ANIMATIONS  = 1lu << 19,
            IS_SIMPLE_ACTOR                 = 1lu << 20,
            HAS_LOOPED_SCRIPT               = 1lu << 21,
            HAS_LOOPED_AUDIO                = 1lu << 28,
            IS_GHOST                        = 1lu << 29,
            IS_INVULNERABLE                 = 1lu << 31,
        };
    };

    enum class Actor_Base_Template_Flags_e : u16
    {
        TRAITS              = 1lu << 0,
        STATS               = 1lu << 1,
        FACTIONS            = 1lu << 2,
        SPELLS              = 1lu << 3,
        AI_DATA             = 1lu << 4,
        AI_PACKAGES         = 1lu << 5,
        UNUSED              = 1lu << 6,
        BASE_DATA           = 1lu << 7,
        INVENTORY           = 1lu << 8,
        SCRIPT              = 1lu << 9,
        AI_DEFAULT_PACKAGES = 1lu << 10,
        ATTACK_DATA         = 1lu << 11,
        KEYWORDS            = 1lu << 12,
    };

    class Faction_And_Rank_t
    {
    public:
        Faction_t*      faction;    // 00
        Faction_Rank_t  rank;       // 08
        u8              pad_09;     // 09
        u16             pad_0A;     // 0A
        u32             pad_0C;     // 0C
    };
    STATIC_ASSERT(sizeof(Faction_And_Rank_t) == 0x10);

    class Actor_Base_Component_t : public Form_Component_t
    {
    public:
        virtual ~Actor_Base_Component_t();

        Actor_Base_Flags_e          actor_base_flags;           // 08
        s16                         magicka_offset;             // 0C
        s16                         stamina_offset;             // 0E
        u16                         level;                      // 10
        u16                         min_level_calc;             // 12
        u16                         max_level_calc;             // 14
        u16                         speed_multiplier;           // 16
        u16                         base_disposition;           // 18
        Actor_Base_Template_Flags_e actor_base_template_flags;  // 1A
        s16                         health_offset;              // 1C
        s16                         bleedout_override;          // 1E
        TESLevItem*                 death_item;                 // 20
        BGSVoiceType*               voice_type;                 // 28
        Form_t*                     base_template_form;         // 30
        Form_t**                    template_forms;             // 38
        tArray<Faction_And_Rank_t>  factions_and_ranks;         // 40

        Bool_t Is_Male();
        Bool_t Is_Female();
        Bool_t Is_Unique();
        Bool_t Is_Generic();
    };
    STATIC_ASSERT(sizeof(Actor_Base_Component_t) == 0x58);

    class Container_Component_t : public Form_Component_t
    {
    public:
        virtual ~Container_Component_t();

        void**  unk_08; // 08
        u32     count;  // 10
        u32     pad_14; // 14
    };
    STATIC_ASSERT(sizeof(Container_Component_t) == 0x18);

    class Active_Effects_Component_t : public Form_Component_t // TESSpellList
    {
    public:
        virtual ~Active_Effects_Component_t();

        void* active_effects; // 8
    };
    STATIC_ASSERT(sizeof(Active_Effects_Component_t) == 0x10);

    class AI_Component_t : public Form_Component_t
    {
    public:
        virtual ~AI_Component_t();

        u8 data[0x20]; // 08
    };
    STATIC_ASSERT(sizeof(AI_Component_t) == 0x28);

    class Destructible_Component_t : public Form_Component_t
    {
    public:
        virtual ~Destructible_Component_t();

        void* unk_8; // 8
    };
    STATIC_ASSERT(sizeof(Destructible_Component_t) == 0x10);

    class Skin_Component_t : public Form_Component_t // BGSSkinForm
    {
    public:
        virtual ~Skin_Component_t();

        void* unk_8; // 8
    };
    STATIC_ASSERT(sizeof(Skin_Component_t) == 0x10);

    enum class Biped_Slots_e : u32
    {
        HEAD                = 1lu << 0,
        HAIR                = 1lu << 1,
        BODY                = 1lu << 2,
        HANDS               = 1lu << 3,
        FOREARMS            = 1lu << 4,
        AMULET              = 1lu << 5,
        RING                = 1lu << 6,
        FEET                = 1lu << 7,
        CALVES              = 1lu << 8,
        SHIELD              = 1lu << 9,
        TAIL                = 1lu << 10,
        LONG_HAIR           = 1lu << 11,
        CIRCLET             = 1lu << 12,
        EARS                = 1lu << 13,
        DECAPTIATED_HEAD    = 1lu << 20,
        DECAPITATED_NECK    = 1lu << 21,
        FX                  = 1lu << 31,
    };

    enum class Armor_Type_e : u32
    {
        LIGHT_ARMOR = 0,
        HEAVY_ARMOR = 1,
        CLOTHING = 2,
    };

    class Biped_Component_t : public Form_Component_t // BGSBipedObjectForm
    {
    public:
        virtual ~Biped_Component_t();

        Biped_Slots_e   biped_slots;
        Armor_Type_e    biped_armor_type;
    };
    STATIC_ASSERT(sizeof(Biped_Component_t) == 0x10);

    class Keyword_Component_t : public Form_Component_t
    {
    public:
        virtual ~Keyword_Component_t();

        void*   keywords;   // 08
        u32     count;      // 10
        u32     pad_14;     // 14
    };
    STATIC_ASSERT(sizeof(Keyword_Component_t) == 0x18);

    class Attack_Component_t : public Form_Component_t
    {
    public:
        virtual ~Attack_Component_t();

        void* unk_8; // 08
    };
    STATIC_ASSERT(sizeof(Attack_Component_t) == 0x10);

    class Perk_Component_t : public Form_Component_t
    {
    public:
        virtual ~Perk_Component_t();

        void*   perks;  // 08
        u32     count;  // 10
        u32     pad_14; // 14
    };
    STATIC_ASSERT(sizeof(Perk_Component_t) == 0x18);

    class Package_Override_Component_t : public Form_Component_t
    {
    public:
        virtual ~Package_Override_Component_t();

        void*   spectator_overrides;        // 08
        void*   observe_corpse_overrides;   // 10
        void*   guard_overrides;            // 18
        void*   combat_overrides;           // 20
    };
    STATIC_ASSERT(sizeof(Package_Override_Component_t) == 0x28);

    class Leveled_Component_t : public Form_Component_t
    {
    public:
        class Entry_t
        {
        public:
            Form_t* form;   // 00
            u16     count;  // 08
            u16     level;  // 0A
            u32     pad_0C; // 0C
            void*   extra;  // 10
        };

    public:
        virtual ~Leveled_Component_t();

        Entry_t*    leveled_entries;        // 08
        u8          chance_of_none;         // 10
        u8          leveled_flags;          // 11
        u8          leveled_entry_count;    // 12
        u8          unk_13;                 // 13
        u32         pad_14;                 // 14
        void*       unk_18;                 // 18
        TESGlobal*  chance_of_none_global;  // 20;
    };
    STATIC_ASSERT(sizeof(Leveled_Component_t) == 0x28);

    class Form_t : public Form_Component_t
    {
    public:
        enum
        {
            kTypeID = kFormType_None,
        };

    public:
        virtual             ~Form_t();                              // 00

        virtual void        _01(void) override;                     // 01
        virtual void        _02(void) override;                     // 02
        virtual void        _03(void) override;                     // 03

        virtual void        _04(void);                              // 04
        virtual void        _05(void);                              // 05
        virtual void        _06(void);                              // 06
        virtual void        _07(void);                              // 07
        virtual void        _08(void);                              // 08
        virtual void        _09(void);                              // 09
        virtual void        _0A(void);                              // 0A
        virtual void        _0B(void);                              // 0B
        virtual void        _0C(void);                              // 0C
        virtual void        _0D(void);                              // 0D
        virtual void        _0E(void);                              // 0E
        virtual void        _0F(void);                              // 0F
        virtual void        _10(void);                              // 10
        virtual void        _11(void);                              // 11
        virtual void        _12(void);                              // 12
        virtual void        _13(void);                              // 13
        virtual Mod_t*      Get_Highest_Mod();                      // 14
        virtual void        _15(void);                              // 15
        virtual void        _16(void);                              // 16
        virtual void        _17(void);                              // 17
        virtual void        _18(void);                              // 18
        virtual void        _19(void);                              // 19
        virtual void        _1A(void);                              // 1A
        virtual void        _1B(void);                              // 1B
        virtual void        _1C(void);                              // 1C
        virtual void        _1D(void);                              // 1D
        virtual void        _1E(void);                              // 1E
        virtual void        _1F(void);                              // 1F
        virtual void        _20(void);                              // 20
        virtual void        _21(void);                              // 21
        virtual void        _22(void);                              // 22
        virtual void        _23(void);                              // 23
        virtual void        _24(void);                              // 24
        virtual void        _25(void);                              // 25
        virtual void        _26(void);                              // 26
        virtual void        _27(void);                              // 27
        virtual void        _28(void);                              // 28
        virtual void        _29(void);                              // 29
        virtual void        _2A(void);                              // 2A
        virtual void        _2B(void);                              // 2B
        virtual void        _2C(void);                              // 2C
        virtual void        _2D(void);                              // 2D
        virtual void        _2E(void);                              // 2E
        virtual void        _2F(void);                              // 2F
        virtual void        _30(void);                              // 30
        virtual void        _31(void);                              // 31
        virtual const char* Get_Editor_ID();                        // 32
        virtual Bool_t      Set_Editor_ID(const char* editor_id);   // 33
        virtual void        _34(void);                              // 34
        virtual void        _35(void);                              // 35
        virtual void        _36(void);                              // 36
        virtual void        _37(void);                              // 37
        virtual void        _38(void);                              // 38
        virtual void        _39(void);                              // 39
        virtual void        _3A(void);                              // 3A

    public:
        Static_Array_t<Mod_t*>* form_files;     // 08
        u32                     form_flags;     // 10
        Form_ID_t               form_id;        // 14
        u16                     form_flags2;    // 18
        Form_Type_e             form_type;      // 1A
        u8                      pad_1B;         // 1B
        u32                     pad_1C;         // 1C

    public:
        Vector_t<Mod_t*>    Mods();

        String_t            Form_ID_String();
        Vector_t<String_t>  Mod_Names();

    public:
        void                Register_Mod_Event(String_t event_name, String_t callback_name, Virtual::Callback_i* vcallback = nullptr);
        void                Unregister_Mod_Event(String_t event_name, Virtual::Callback_i* vcallback = nullptr);
        void                Unregister_Mod_Events(Virtual::Callback_i* vcallback = nullptr);
    };
    STATIC_ASSERT(sizeof(Form_t) == 0x20);

}
