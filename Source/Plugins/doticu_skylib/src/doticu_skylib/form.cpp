/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/ammo.h"
#include "doticu_skylib/armor.h"
#include "doticu_skylib/book.h"
#include "doticu_skylib/bound_object.h"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/component_container.h"
#include "doticu_skylib/component_equip_slot.h"
#include "doticu_skylib/component_keywords.h"
#include "doticu_skylib/component_name.h"
#include "doticu_skylib/component_race.h"
#include "doticu_skylib/component_value.h"
#include "doticu_skylib/container.h"
#include "doticu_skylib/cstring.h"
#include "doticu_skylib/enum_comparator.h"
#include "doticu_skylib/faction.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/game.inl"
#include "doticu_skylib/ingredient.h"
#include "doticu_skylib/key.h"
#include "doticu_skylib/leveled_actor_base.h"
#include "doticu_skylib/leveled_item.h"
#include "doticu_skylib/light.h"
#include "doticu_skylib/location.h"
#include "doticu_skylib/misc.h"
#include "doticu_skylib/mod.h"
#include "doticu_skylib/outfit.h"
#include "doticu_skylib/package.h"
#include "doticu_skylib/potion.h"
#include "doticu_skylib/quest.h"
#include "doticu_skylib/reference.h"
#include "doticu_skylib/scrap_array.inl"
#include "doticu_skylib/scroll.h"
#include "doticu_skylib/soul_gem.h"
#include "doticu_skylib/spell.h"
#include "doticu_skylib/virtual_arguments.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_machine.inl"
#include "doticu_skylib/virtual_variable.inl"
#include "doticu_skylib/weapon.h"
#include "doticu_skylib/worldspace.h"

namespace doticu_skylib {

    Comparator_e Form_t::Compare_Names(const char* name_a, const char* name_b)
    {
        if (!name_a || !name_a[0]) {
            return Comparator_e::IS_UNORDERED;
        } else if (!name_b || !name_b[0]) {
            return Comparator_e::IS_ORDERED;
        } else if (name_a[0] == '0' && name_a[1] == 'x' && name_b[0] != '0' && name_b[1] != 'x') {
            return Comparator_e::IS_UNORDERED;
        } else if (name_a[0] != '0' && name_a[1] != 'x' && name_b[0] == '0' && name_b[1] == 'x') {
            return Comparator_e::IS_ORDERED;
        } else {
            return _stricmp(name_a, name_b);
        }
    }

    Bool_t Form_t::Is_Valid()       { return static_cast<Bool_t>(form_id); }
    Bool_t Form_t::Is_Static()      { return form_id.Is_Static(); }
    Bool_t Form_t::Is_Dynamic()     { return form_id.Is_Dynamic(); }
    Bool_t Form_t::Is_Heavy()       { return form_id.Is_Heavy(); }
    Bool_t Form_t::Is_Light()       { return form_id.Is_Light(); }
    Bool_t Form_t::Is_Playable()    { return Get_Is_Playable(); }

    Bool_t Form_t::Can_Equip() const
    {
        return Is_Component_Equip_Slot();
    }

    Bool_t Form_t::Has_Keyword(some<Keyword_t*> keyword) const
    {
        SKYLIB_ASSERT_SOME(keyword);

        maybe<Reference_t*> reference = As_Reference();
        if (reference) {
            return reference->Has_Keyword(keyword);
        } else {
            maybe<Keywords_c*> component_keywords = As_Component_Keywords();
            if (component_keywords) {
                return component_keywords->Component_Has_Keyword(keyword);
            } else {
                return false;
            }
        }
    }

    maybe<Heavy_Mod_Index_t>    Form_t::Heavy_Mod_Index()   { return form_id.Heavy_Mod_Index(); }
    maybe<Light_Mod_Index_t>    Form_t::Light_Mod_Index()   { return form_id.Light_Mod_Index(); }
    maybe<Heavy_Form_Index_t>   Form_t::Heavy_Form_Index()  { return form_id.Heavy_Form_Index(); }
    maybe<Light_Form_Index_t>   Form_t::Light_Form_Index()  { return form_id.Light_Form_Index(); }

    maybe<Mod_t*> Form_t::Indexed_Mod()
    {
        return form_id.Mod();
    }

    Bool_t Form_t::Has_Indexed_Mod(maybe<const char*> mod_name)
    {
        if (mod_name && mod_name[0]) {
            if (Is_Static()) {
                maybe<Mod_t*> mod = Indexed_Mod();
                if (mod) {
                    return CString_t::Is_Same(mod_name(), mod->Name(), true);
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            if (Is_Dynamic()) {
                return true;
            } else {
                return false;
            }
        }
    }

    Bool_t Form_t::Has_Indexed_Mod(maybe<Mod_t*> mod)
    {
        if (mod) {
            return Indexed_Mod() == mod;
        } else {
            return Is_Dynamic();
        }
    }

    Vector_t<Mod_t*> Form_t::Mods()
    {
        Vector_t<Mod_t*> mods;
        if (form_mods) {
            for (size_t idx = 0, end = form_mods->count; idx < end; idx += 1) {
                Mod_t* mod = form_mods->entries[idx];
                if (mod) {
                    mods.push_back(mod);
                }
            }
        }
        return mods;
    }

    String_t Form_t::Form_ID_String()
    {
        return static_cast<String_t>(this->form_id);
    }

    Vector_t<String_t> Form_t::Mod_Names()
    {
        Vector_t<String_t> results;
        Mod_Names(results);
        return results;
    }

    void Form_t::Mod_Names(Vector_t<String_t>& results)
    {
        if (form_mods) {
            results.reserve(form_mods->count);
            for (size_t idx = 0, end = form_mods->count; idx < end; idx += 1) {
                Mod_t* mod = form_mods->entries[idx];
                if (mod) {
                    results.push_back(mod->Name());
                }
            }
        }
    }

    some<const char*> Form_t::Component_Name() const
    {
        maybe<Name_c*> component_name = As_Component_Name();
        if (component_name) {
            const char* name = component_name->Name();
            if (name) {
                return name;
            } else {
                return "";
            }
        } else {
            return "";
        }
    }

    maybe<Race_t*> Form_t::Component_Race() const
    {
        maybe<Race_c*> component_race = As_Component_Race();
        if (component_race) {
            return component_race->race;
        } else {
            return none<Race_t*>();
        }
    }

    s32 Form_t::Component_Value() const
    {
        maybe<Value_c*> component_value = As_Component_Value();
        if (component_value) {
            return component_value->value;
        } else {
            return -1;
        }
    }

    maybe<Actor_t*>                 Form_t::As_Actor() const                { return Game_t::Runtime_Cast<Form_t, Actor_t>(this); }
    maybe<Actor_Base_t*>            Form_t::As_Actor_Base() const           { return Game_t::Runtime_Cast<Form_t, Actor_Base_t>(this); }
    maybe<Ammo_t*>                  Form_t::As_Ammo() const                 { return Game_t::Runtime_Cast<Form_t, Ammo_t>(this); }
    maybe<Armor_t*>                 Form_t::As_Armor() const                { return Game_t::Runtime_Cast<Form_t, Armor_t>(this); }
    maybe<Book_t*>                  Form_t::As_Book() const                 { return Game_t::Runtime_Cast<Form_t, Book_t>(this); }
    maybe<Bound_Object_t*>          Form_t::As_Bound_Object() const         { return Game_t::Runtime_Cast<Form_t, Bound_Object_t>(this); }
    maybe<Cell_t*>                  Form_t::As_Cell() const                 { return Game_t::Runtime_Cast<Form_t, Cell_t>(this); }
    maybe<Container_c*>             Form_t::As_Component_Container() const  { return Game_t::Runtime_Cast<Form_t, Container_c>(this); }
    maybe<Equip_Slot_c*>            Form_t::As_Component_Equip_Slot() const { return Game_t::Runtime_Cast<Form_t, Equip_Slot_c>(this); }
    maybe<Keywords_c*>              Form_t::As_Component_Keywords() const   { return Game_t::Runtime_Cast<Form_t, Keywords_c>(this); }
    maybe<Name_c*>                  Form_t::As_Component_Name() const       { return Game_t::Runtime_Cast<Form_t, Name_c>(this); }
    maybe<Race_c*>                  Form_t::As_Component_Race() const       { return Game_t::Runtime_Cast<Form_t, Race_c>(this); }
    maybe<Value_c*>                 Form_t::As_Component_Value() const      { return Game_t::Runtime_Cast<Form_t, Value_c>(this); }
    maybe<Container_t*>             Form_t::As_Container() const            { return Game_t::Runtime_Cast<Form_t, Container_t>(this); }
    maybe<Faction_t*>               Form_t::As_Faction() const              { return Game_t::Runtime_Cast<Form_t, Faction_t>(this); }
    maybe<Ingredient_t*>            Form_t::As_Ingredient() const           { return Game_t::Runtime_Cast<Form_t, Ingredient_t>(this); }
    maybe<Key_t*>                   Form_t::As_Key() const                  { return Game_t::Runtime_Cast<Form_t, Key_t>(this); }
    maybe<Leveled_Actor_Base_t*>    Form_t::As_Leveled_Actor_Base() const   { return Game_t::Runtime_Cast<Form_t, Leveled_Actor_Base_t>(this); }
    maybe<Leveled_Item_t*>          Form_t::As_Leveled_Item() const         { return Game_t::Runtime_Cast<Form_t, Leveled_Item_t>(this); }
    maybe<Light_t*>                 Form_t::As_Light() const                { return Game_t::Runtime_Cast<Form_t, Light_t>(this); }
    maybe<Location_t*>              Form_t::As_Location() const             { return Game_t::Runtime_Cast<Form_t, Location_t>(this); }
    maybe<Misc_t*>                  Form_t::As_Misc() const                 { return Game_t::Runtime_Cast<Form_t, Misc_t>(this); }
    maybe<Outfit_t*>                Form_t::As_Outfit() const               { return Game_t::Runtime_Cast<Form_t, Outfit_t>(this); }
    maybe<Package_t*>               Form_t::As_Package() const              { return Game_t::Runtime_Cast<Form_t, Package_t>(this); }
    maybe<Potion_t*>                Form_t::As_Potion() const               { return Game_t::Runtime_Cast<Form_t, Potion_t>(this); }
    maybe<Quest_t*>                 Form_t::As_Quest() const                { return Game_t::Runtime_Cast<Form_t, Quest_t>(this); }
    maybe<Reference_t*>             Form_t::As_Reference() const            { return Game_t::Runtime_Cast<Form_t, Reference_t>(this); }
    maybe<Scroll_t*>                Form_t::As_Scroll() const               { return Game_t::Runtime_Cast<Form_t, Scroll_t>(this); }
    maybe<Soul_Gem_t*>              Form_t::As_Soul_Gem() const             { return Game_t::Runtime_Cast<Form_t, Soul_Gem_t>(this); }
    maybe<Spell_t*>                 Form_t::As_Spell() const                { return Game_t::Runtime_Cast<Form_t, Spell_t>(this); }
    maybe<Weapon_t*>                Form_t::As_Weapon() const               { return Game_t::Runtime_Cast<Form_t, Weapon_t>(this); }
    maybe<Worldspace_t*>            Form_t::As_Worldspace() const           { return Game_t::Runtime_Cast<Form_t, Worldspace_t>(this); }

    Bool_t  Form_t::Is_Actor() const                { return As_Actor() != none<Actor_t*>(); }
    Bool_t  Form_t::Is_Actor_Base() const           { return As_Actor_Base() != none<Actor_Base_t*>(); }
    Bool_t  Form_t::Is_Ammo() const                 { return As_Ammo() != none<Ammo_t*>(); }
    Bool_t  Form_t::Is_Armor() const                { return As_Armor() != none<Armor_t*>(); }
    Bool_t  Form_t::Is_Book() const                 { return As_Book() != none<Book_t*>(); }
    Bool_t  Form_t::Is_Bound_Object() const         { return As_Bound_Object() != none<Bound_Object_t*>(); }
    Bool_t  Form_t::Is_Cell() const                 { return As_Cell() != none<Cell_t*>(); }
    Bool_t  Form_t::Is_Component_Container() const  { return As_Component_Container() != none<Container_c*>(); }
    Bool_t  Form_t::Is_Component_Equip_Slot() const { return As_Component_Equip_Slot() != none<Equip_Slot_c*>(); }
    Bool_t  Form_t::Is_Component_Keywords() const   { return As_Component_Keywords() != none<Keywords_c*>(); }
    Bool_t  Form_t::Is_Component_Name() const       { return As_Component_Name() != none<Name_c*>(); }
    Bool_t  Form_t::Is_Component_Race() const       { return As_Component_Race() != none<Race_c*>(); }
    Bool_t  Form_t::Is_Component_Value() const      { return As_Component_Value() != none<Value_c*>(); }
    Bool_t  Form_t::Is_Container() const            { return As_Container() != none<Container_t*>(); }
    Bool_t  Form_t::Is_Faction() const              { return As_Faction() != none<Faction_t*>(); }
    Bool_t  Form_t::Is_Ingredient() const           { return As_Ingredient() != none<Ingredient_t*>(); }
    Bool_t  Form_t::Is_Key() const                  { return As_Key() != none<Key_t*>(); }
    Bool_t  Form_t::Is_Leveled_Actor_Base() const   { return As_Leveled_Actor_Base() != none<Leveled_Actor_Base_t*>(); }
    Bool_t  Form_t::Is_Leveled_Item() const         { return As_Leveled_Item() != none<Leveled_Item_t*>(); }
    Bool_t  Form_t::Is_Light() const                { return As_Light() != none<Light_t*>(); }
    Bool_t  Form_t::Is_Location() const             { return As_Location() != none<Location_t*>(); }
    Bool_t  Form_t::Is_Misc() const                 { return As_Misc() != none<Misc_t*>(); }
    Bool_t  Form_t::Is_Outfit() const               { return As_Outfit() != none<Outfit_t*>(); }
    Bool_t  Form_t::Is_Package() const              { return As_Package() != none<Package_t*>(); }
    Bool_t  Form_t::Is_Potion() const               { return As_Potion() != none<Potion_t*>(); }
    Bool_t  Form_t::Is_Quest() const                { return As_Quest() != none<Quest_t*>(); }
    Bool_t  Form_t::Is_Reference() const            { return As_Reference() != none<Reference_t*>(); }
    Bool_t  Form_t::Is_Scroll() const               { return As_Scroll() != none<Scroll_t*>(); }
    Bool_t  Form_t::Is_Soul_Gem() const             { return As_Soul_Gem() != none<Soul_Gem_t*>(); }
    Bool_t  Form_t::Is_Spell() const                { return As_Spell() != none<Spell_t*>(); }
    Bool_t  Form_t::Is_Weapon() const               { return As_Weapon() != none<Weapon_t*>(); }
    Bool_t  Form_t::Is_Worldspace() const           { return As_Worldspace() != none<Worldspace_t*>(); }

    void Form_t::Register_Key_Event(Int_t key_code, maybe<Virtual::Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Virtual::Arguments_t
        {
        public:
            Int_t key_code;

        public:
            Virtual_Arguments(Int_t key_code) :
                key_code(key_code)
            {
            }

        public:
            virtual Bool_t operator ()(Scrap_Array_t<Virtual::Variable_t>* args) override
            {
                args->Resize(1);
                args->At(0).As<Int_t>(this->key_code);
                return true;
            }
        };

        Virtual::Machine_t::Ready_Scriptable<Form_t*>(this);
        Virtual::Machine_t::Self()->Call_Method(
            this,
            SCRIPT_NAME,
            "RegisterForKey",
            Virtual_Arguments(key_code),
            v_callback
        );
    }

    void Form_t::Register_Key_Event(Int_t key_code, maybe<unique<Callback_i<>>> callback)
    {
        using Callback = maybe<unique<Callback_i<>>>;

        class Virtual_Callback :
            public Virtual::Callback_t
        {
        public:
            Callback callback;

        public:
            Virtual_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator ()(Virtual::Variable_t*) override
            {
                if (this->callback) {
                    (*this->callback)();
                }
            }
        };

        Register_Key_Event(key_code, new Virtual_Callback(std::move(callback)));
    }

    void Form_t::Unregister_Key_Event(Int_t key_code, maybe<Virtual::Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Virtual::Arguments_t
        {
        public:
            Int_t key_code;

        public:
            Virtual_Arguments(Int_t key_code) :
                key_code(key_code)
            {
            }

        public:
            virtual Bool_t operator ()(Scrap_Array_t<Virtual::Variable_t>* args) override
            {
                args->Resize(1);
                args->At(0).As<Int_t>(this->key_code);
                return true;
            }
        };

        Virtual::Machine_t::Ready_Scriptable<Form_t*>(this);
        Virtual::Machine_t::Self()->Call_Method(
            this,
            SCRIPT_NAME,
            "UnregisterForKey",
            Virtual_Arguments(key_code),
            v_callback
        );
    }

    void Form_t::Unregister_Key_Event(Int_t key_code, maybe<unique<Callback_i<>>> callback)
    {
        using Callback = maybe<unique<Callback_i<>>>;

        class Virtual_Callback :
            public Virtual::Callback_t
        {
        public:
            Callback callback;

        public:
            Virtual_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator ()(Virtual::Variable_t*) override
            {
                if (this->callback) {
                    (*this->callback)();
                }
            }
        };

        Unregister_Key_Event(key_code, new Virtual_Callback(std::move(callback)));
    }

    void Form_t::Unregister_All_Key_Events(maybe<Virtual::Callback_i*> v_callback)
    {
        Virtual::Machine_t::Ready_Scriptable<Form_t*>(this);
        Virtual::Machine_t::Self()->Call_Method(
            this,
            SCRIPT_NAME,
            "UnregisterForAllKeys",
            none<Virtual::Arguments_i*>(),
            v_callback
        );
    }

    void Form_t::Unregister_All_Key_Events(maybe<unique<Callback_i<>>> callback)
    {
        using Callback = maybe<unique<Callback_i<>>>;

        class Virtual_Callback :
            public Virtual::Callback_t
        {
        public:
            Callback callback;

        public:
            Virtual_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator ()(Virtual::Variable_t*) override
            {
                if (this->callback) {
                    (*this->callback)();
                }
            }
        };

        Unregister_All_Key_Events(new Virtual_Callback(std::move(callback)));
    }

    void Form_t::Register_SKSE_Event(String_t event_name, String_t callback_name, maybe<Virtual::Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Virtual::Arguments_t
        {
        public:
            String_t event_name;
            String_t callback_name;

        public:
            Virtual_Arguments(String_t event_name, String_t callback_name) :
                event_name(event_name), callback_name(callback_name)
            {
            }

        public:
            virtual Bool_t operator()(Scrap_Array_t<Virtual::Variable_t>* args) override
            {
                args->Resize(2);
                args->At(0).As<String_t>(this->event_name);
                args->At(1).As<String_t>(this->callback_name);
                return true;
            }
        };

        Virtual::Machine_t::Ready_Scriptable<Form_t*>(this);
        Virtual::Machine_t::Self()->Call_Method(
            this,
            SCRIPT_NAME,
            "RegisterForModEvent",
            Virtual_Arguments(event_name, callback_name),
            v_callback
        );
    }

    void Form_t::Register_SKSE_Event(String_t event_name, String_t callback_name, maybe<unique<Callback_i<>>> callback)
    {
        using Callback = maybe<unique<Callback_i<>>>;

        class Virtual_Callback :
            public Virtual::Callback_t
        {
        public:
            Callback callback;

        public:
            Virtual_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator()(Virtual::Variable_t*) override
            {
                if (this->callback) {
                    (*this->callback)();
                }
            }
        };

        Register_SKSE_Event(event_name, callback_name, new Virtual_Callback(std::move(callback)));
    }

    void Form_t::Unregister_SKSE_Event(String_t event_name, maybe<Virtual::Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Virtual::Arguments_t
        {
        public:
            String_t event_name;

        public:
            Virtual_Arguments(String_t event_name) :
                event_name(event_name)
            {
            }

        public:
            virtual Bool_t operator()(Scrap_Array_t<Virtual::Variable_t>* args) override
            {
                args->Resize(1);
                args->At(0).As<String_t>(this->event_name);
                return true;
            }
        };

        Virtual::Machine_t::Ready_Scriptable<Form_t*>(this);
        Virtual::Machine_t::Self()->Call_Method(
            this,
            SCRIPT_NAME,
            "UnregisterForModEvent",
            Virtual_Arguments(event_name),
            v_callback
        );
    }

    void Form_t::Unregister_SKSE_Event(String_t event_name, maybe<unique<Callback_i<>>> callback)
    {
        using Callback = maybe<unique<Callback_i<>>>;

        class Virtual_Callback :
            public Virtual::Callback_t
        {
        public:
            Callback callback;

        public:
            Virtual_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator()(Virtual::Variable_t*) override
            {
                if (this->callback) {
                    (*this->callback)();
                }
            }
        };

        Unregister_SKSE_Event(event_name, new Virtual_Callback(std::move(callback)));
    }

    void Form_t::Unregister_All_SKSE_Events(maybe<Virtual::Callback_i*> v_callback)
    {
        Virtual::Machine_t::Ready_Scriptable<Form_t*>(this);
        Virtual::Machine_t::Self()->Call_Method(
            this,
            SCRIPT_NAME,
            "UnregisterForAllModEvents",
            none<Virtual::Arguments_i*>(),
            v_callback
        );
    }

    void Form_t::Unregister_All_SKSE_Events(maybe<unique<Callback_i<>>> callback)
    {
        using Callback = maybe<unique<Callback_i<>>>;

        class Virtual_Callback :
            public Virtual::Callback_t
        {
        public:
            Callback callback;

        public:
            Virtual_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator()(Virtual::Variable_t*) override
            {
                if (this->callback) {
                    (*this->callback)();
                }
            }
        };

        Unregister_All_SKSE_Events(new Virtual_Callback(std::move(callback)));
    }

    void Form_t::Log_Name_And_Type(std::string indent)
    {
        SKYLIB_LOG(indent + "Form_t::Log_Name_And_Type");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "form_type: %s, form_id: %s, component_name: %s",
                   this->form_type.As_String(),
                   this->form_id.As_String(),
                   Component_Name());

        SKYLIB_LOG(indent + "}");
    }

}
