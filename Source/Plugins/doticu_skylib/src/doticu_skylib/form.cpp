/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/bound_object.h"
#include "doticu_skylib/component_container.h"
#include "doticu_skylib/component_name.h"
#include "doticu_skylib/container.h"
#include "doticu_skylib/cstring.h"
#include "doticu_skylib/faction.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/game.inl"
#include "doticu_skylib/leveled_item.h"
#include "doticu_skylib/mod.h"
#include "doticu_skylib/scrap_array.inl"
#include "doticu_skylib/virtual_arguments.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_machine.inl"
#include "doticu_skylib/virtual_variable.inl"

namespace doticu_skylib {

    Int_t Form_t::Compare_Names(const char* name_a, const char* name_b)
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
            for (Index_t idx = 0, end = form_mods->count; idx < end; idx += 1) {
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
            for (Index_t idx = 0, end = form_mods->count; idx < end; idx += 1) {
                Mod_t* mod = form_mods->entries[idx];
                if (mod) {
                    results.push_back(mod->Name());
                }
            }
        }
    }

    some<const char*> Form_t::Component_Name()
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

    Bool_t  Form_t::Is_Actor()                  { return As_Actor() != none<Actor_t*>(); }
    Bool_t  Form_t::Is_Actor_Base()             { return As_Actor_Base() != none<Actor_Base_t*>(); }
    Bool_t  Form_t::Is_Bound_Object()           { return As_Bound_Object() != none<Bound_Object_t*>(); }
    Bool_t  Form_t::Is_Component_Container()    { return As_Component_Container() != none<Container_c*>(); }
    Bool_t  Form_t::Is_Component_Name()         { return As_Component_Name() != none<Name_c*>(); }
    Bool_t  Form_t::Is_Container()              { return As_Container() != none<Container_t*>(); }
    Bool_t  Form_t::Is_Faction()                { return As_Faction() != none<Faction_t*>(); }
    Bool_t  Form_t::Is_Leveled_Item()           { return As_Leveled_Item() != none<Leveled_Item_t*>(); }
    Bool_t  Form_t::Is_Reference()              { return As_Reference() != none<Reference_t*>(); }

    maybe<Actor_t*>         Form_t::As_Actor()                  { return Game_t::Runtime_Cast<Form_t, Actor_t>(this); }
    maybe<Actor_Base_t*>    Form_t::As_Actor_Base()             { return Game_t::Runtime_Cast<Form_t, Actor_Base_t>(this); }
    maybe<Bound_Object_t*>  Form_t::As_Bound_Object()           { return Game_t::Runtime_Cast<Form_t, Bound_Object_t>(this); }
    maybe<Container_c*>     Form_t::As_Component_Container()    { return Game_t::Runtime_Cast<Form_t, Container_c>(this); }
    maybe<Name_c*>          Form_t::As_Component_Name()         { return Game_t::Runtime_Cast<Form_t, Name_c>(this); }
    maybe<Container_t*>     Form_t::As_Container()              { return Game_t::Runtime_Cast<Form_t, Container_t>(this); }
    maybe<Faction_t*>       Form_t::As_Faction()                { return Game_t::Runtime_Cast<Form_t, Faction_t>(this); }
    maybe<Leveled_Item_t*>  Form_t::As_Leveled_Item()           { return Game_t::Runtime_Cast<Form_t, Leveled_Item_t>(this); }
    maybe<Reference_t*>     Form_t::As_Reference()              { return Game_t::Runtime_Cast<Form_t, Reference_t>(this); }

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

}
