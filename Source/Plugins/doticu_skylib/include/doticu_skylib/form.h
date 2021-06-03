/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/component_form_data.h"
#include "doticu_skylib/enum_comparator.h"
#include "doticu_skylib/enum_form_flags.h"
#include "doticu_skylib/enum_script_type.h"
#include "doticu_skylib/form_id.h"
#include "doticu_skylib/interface.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/mod_index.h"
#include "doticu_skylib/string.h"
#include "doticu_skylib/unique.h"

namespace doticu_skylib {

    class Actor_t;
    class Actor_Base_t;
    class Ammo_t;
    class Armor_t;
    class Book_t;
    class Bound_Object_t;
    class Cell_t;
    class Container_c;
    class Container_t;
    class Equip_Slot_c;
    class Faction_t;
    class Ingredient_t;
    class Key_t;
    class Keyword_t;
    class Keywords_c;
    class Leveled_Actor_Base_t;
    class Leveled_Item_t;
    class Light_t;
    class Location_t;
    class Misc_t;
    class Mod_t;
    class Name_c;
    class Outfit_t;
    class Package_t;
    class Potion_t;
    class Quest_t;
    class Race_c;
    class Race_t;
    class Reference_t;
    class Scroll_t;
    class Soul_Gem_t;
    class Spell_t;
    class Value_c;
    class Weapon_t;
    class Worldspace_t;

    namespace Virtual {

        class Callback_i;

    }

    class Form_t :          // TESForm
        public Form_Data_c  // 00
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::FORM,
        };

        static constexpr const char* SCRIPT_NAME = "Form";

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E10E30, // 513848
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        static Comparator_e Compare_Names(const char* name_a, const char* name_b);

    public:
        virtual             ~Form_t();                                                  // 00

        // Form_Data_c
        virtual void        _01(void) override;                                         // 01
        virtual void        _02(void) override;                                         // 02
        virtual void        _03(void) override;                                         // 03

        // Form_t
        virtual void        Initialize_Data();                                          // 04
        virtual void        Clear_Data();                                               // 05
        virtual Bool_t      Load(Mod_t* mod);                                           // 06
        virtual void        _07(void);                                                  // 07
        virtual void        _08(void);                                                  // 08
        virtual Form_t*     Do_Duplicate_Form(Bool_t do_new_editor_id, void* unk_1);    // 09
        virtual Bool_t      Flag_Form_Change(u32 flag);                                 // 0A (verify this is working correctly.)
        virtual void        Unflag_Form_Change(u32 flag);                               // 0B
        virtual Bool_t      Find_In_Mod(Mod_t* mod);                                    // 0C
        virtual void        _0D(void);                                                  // 0D
        virtual void        _0E(void);                                                  // 0E
        virtual void        _0F(void);                                                  // 0F
        virtual void        _10(void);                                                  // 10
        virtual void        _11(void);                                                  // 11
        virtual void        _12(void);                                                  // 12
        virtual void        _13(void);                                                  // 13
        virtual Mod_t*      Get_Highest_Mod();                                          // 14
        virtual void        _15(void);                                                  // 15
        virtual void        _16(void);                                                  // 16
        virtual void        _17(void);                                                  // 17
        virtual void        _18(void);                                                  // 18
        virtual Bool_t      Get_Is_Playable() const;                                    // 19
        virtual void        _1A(void);                                                  // 1A
        virtual void        _1B(void);                                                  // 1B
        virtual void        _1C(void);                                                  // 1C
        virtual void        _1D(void);                                                  // 1D
        virtual void        _1E(void);                                                  // 1E
        virtual void        _1F(void);                                                  // 1F
        virtual void        _20(void);                                                  // 20
        virtual void        _21(void);                                                  // 21
        virtual void        _22(void);                                                  // 22
        virtual void        _23(void);                                                  // 23
        virtual void        _24(void);                                                  // 24
        virtual void        _25(void);                                                  // 25
        virtual void        _26(void);                                                  // 26
        virtual void        _27(void);                                                  // 27
        virtual void        _28(void);                                                  // 28
        virtual void        _29(void);                                                  // 29
        virtual void        _2A(void);                                                  // 2A
        virtual void        _2B(void);                                                  // 2B
        virtual void        _2C(void);                                                  // 2C
        virtual u32         Get_Reference_Count() const;                                // 2D
        virtual void        _2E(void);                                                  // 2E
        virtual void        Do_Copy(Form_t* source_form);                               // 2F
        virtual void        _30(void);                                                  // 30
        virtual void        _31(void);                                                  // 31
        virtual const char* Get_Editor_ID();                                            // 32
        virtual Bool_t      Set_Editor_ID(const char* editor_id);                       // 33
        virtual void        _34(void);                                                  // 34
        virtual void        _35(void);                                                  // 35
        virtual void        _36(void);                                                  // 36
        virtual Bool_t      Do_Activate(Reference_t* target,
                                        Reference_t* activator,
                                        Bool_t do_skip_papyrus_event,
                                        Bound_Object_t* tool,
                                        s32 tool_count);                                // 37 (this doesn't seem to be right.)
        virtual void        _38(void);                                                  // 38
        virtual void        _39(void);                                                  // 39
        virtual void        _3A(void);                                                  // 3A

    public:
        Static_Array_t<Mod_t*>* form_mods;          // 08
        Form_Flags_e            form_flags;         // 10
        Form_ID_t               form_id;            // 14
        Form_Flags_Extra_e      form_flags_extra;   // 18
        Form_Type_e             form_type;          // 1A
        u8                      pad_1B;             // 1B
        u32                     pad_1C;             // 1C

    public:
        Bool_t                      Is_Valid();
        Bool_t                      Is_Static();
        Bool_t                      Is_Dynamic();
        Bool_t                      Is_Heavy();
        Bool_t                      Is_Light();
        Bool_t                      Is_Playable();

        Bool_t                      Can_Equip() const;

        Bool_t                      Has_Keyword(some<Keyword_t*> keyword) const;

        maybe<Heavy_Mod_Index_t>    Heavy_Mod_Index();
        maybe<Light_Mod_Index_t>    Light_Mod_Index();
        maybe<Heavy_Form_Index_t>   Heavy_Form_Index();
        maybe<Light_Form_Index_t>   Light_Form_Index();

        maybe<Mod_t*>               Indexed_Mod();
        Bool_t                      Has_Indexed_Mod(maybe<const char*> mod_name);
        Bool_t                      Has_Indexed_Mod(maybe<Mod_t*> mod);

        Vector_t<Mod_t*>            Mods();

        String_t                    Form_ID_String();
        Vector_t<String_t>          Mod_Names();
        void                        Mod_Names(Vector_t<String_t>& results);

        some<const char*>           Component_Name() const;
        maybe<Race_t*>              Component_Race() const;
        s32                         Component_Value() const;

    public:
        maybe<Actor_t*>                 As_Actor() const;
        maybe<Actor_Base_t*>            As_Actor_Base() const;
        maybe<Ammo_t*>                  As_Ammo() const;
        maybe<Armor_t*>                 As_Armor() const;
        maybe<Book_t*>                  As_Book() const;
        maybe<Bound_Object_t*>          As_Bound_Object() const;
        maybe<Cell_t*>                  As_Cell() const;
        maybe<Container_c*>             As_Component_Container() const;
        maybe<Equip_Slot_c*>            As_Component_Equip_Slot() const;
        maybe<Keywords_c*>              As_Component_Keywords() const;
        maybe<Name_c*>                  As_Component_Name() const;
        maybe<Race_c*>                  As_Component_Race() const;
        maybe<Value_c*>                 As_Component_Value() const;
        maybe<Container_t*>             As_Container() const;
        maybe<Faction_t*>               As_Faction() const;
        maybe<Ingredient_t*>            As_Ingredient() const;
        maybe<Key_t*>                   As_Key() const;
        maybe<Leveled_Actor_Base_t*>    As_Leveled_Actor_Base() const;
        maybe<Leveled_Item_t*>          As_Leveled_Item() const;
        maybe<Light_t*>                 As_Light() const;
        maybe<Location_t*>              As_Location() const;
        maybe<Misc_t*>                  As_Misc() const;
        maybe<Outfit_t*>                As_Outfit() const;
        maybe<Package_t*>               As_Package() const;
        maybe<Potion_t*>                As_Potion() const;
        maybe<Quest_t*>                 As_Quest() const;
        maybe<Reference_t*>             As_Reference() const;
        maybe<Scroll_t*>                As_Scroll() const;
        maybe<Soul_Gem_t*>              As_Soul_Gem() const;
        maybe<Spell_t*>                 As_Spell() const;
        maybe<Weapon_t*>                As_Weapon() const;
        maybe<Worldspace_t*>            As_Worldspace() const;

        Bool_t  Is_Actor() const;
        Bool_t  Is_Actor_Base() const;
        Bool_t  Is_Ammo() const;
        Bool_t  Is_Armor() const;
        Bool_t  Is_Book() const;
        Bool_t  Is_Bound_Object() const;
        Bool_t  Is_Cell() const;
        Bool_t  Is_Component_Container() const;
        Bool_t  Is_Component_Equip_Slot() const;
        Bool_t  Is_Component_Keywords() const;
        Bool_t  Is_Component_Name() const;
        Bool_t  Is_Component_Race() const;
        Bool_t  Is_Component_Value() const;
        Bool_t  Is_Container() const;
        Bool_t  Is_Faction() const;
        Bool_t  Is_Ingredient() const;
        Bool_t  Is_Key() const;
        Bool_t  Is_Leveled_Actor_Base() const;
        Bool_t  Is_Leveled_Item() const;
        Bool_t  Is_Light() const;
        Bool_t  Is_Location() const;
        Bool_t  Is_Misc() const;
        Bool_t  Is_Outfit() const;
        Bool_t  Is_Package() const;
        Bool_t  Is_Potion() const;
        Bool_t  Is_Quest() const;
        Bool_t  Is_Reference() const;
        Bool_t  Is_Scroll() const;
        Bool_t  Is_Soul_Gem() const;
        Bool_t  Is_Spell() const;
        Bool_t  Is_Weapon() const;
        Bool_t  Is_Worldspace() const;

        template <typename T>
        maybe<T*> As() const;
        template <typename T>
        Bool_t Is() const;

    public:
        void Register_Key_Event(Int_t key_code, maybe<Virtual::Callback_i*> v_callback);            // RegisterForKey
        void Register_Key_Event(Int_t key_code, maybe<unique<Callback_i<>>> callback);

        void Unregister_Key_Event(Int_t key_code, maybe<Virtual::Callback_i*> v_callback);          // UnregisterForKey
        void Unregister_Key_Event(Int_t key_code, maybe<unique<Callback_i<>>> callback);

        void Unregister_All_Key_Events(maybe<Virtual::Callback_i*> v_callback);                     // UnregisterForAllKeys
        void Unregister_All_Key_Events(maybe<unique<Callback_i<>>> callback);

        void Register_SKSE_Event(String_t event_name,
                                 String_t callback_name,
                                 maybe<Virtual::Callback_i*> v_callback);                           // RegisterForModEvent
        void Register_SKSE_Event(String_t event_name,
                                 String_t callback_name,
                                 maybe<unique<Callback_i<>>> callback);

        void Unregister_SKSE_Event(String_t event_name, maybe<Virtual::Callback_i*> v_callback);    // UnregisterForModEvent
        void Unregister_SKSE_Event(String_t event_name, maybe<unique<Callback_i<>>> callback);

        void Unregister_All_SKSE_Events(maybe<Virtual::Callback_i*> v_callback);                    // UnregisterForAllModEvents
        void Unregister_All_SKSE_Events(maybe<unique<Callback_i<>>> callback);

    public:
        void    Log_Name_And_Type(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Form_t) == 0x20);

}
