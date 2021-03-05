/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/PapyrusInput.h"

#include "doticu_skylib/scrap_array.inl"
#include "doticu_skylib/virtual_arguments.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_input.h"
#include "doticu_skylib/virtual_machine.h"
#include "doticu_skylib/virtual_utility.h"
#include "doticu_skylib/virtual_variable.inl"

namespace doticu_skylib { namespace Virtual {

    Int_t Input_t::Control_To_Key(String_t control, u32 device_type)
    {
        return papyrusInput::GetMappedKey(0, reinterpret_cast<BSFixedString&>(control), device_type);
    }

    String_t Input_t::Key_To_Control(Int_t key)
    {
        BSFixedString result = papyrusInput::GetMappedControl(0, key);
        return reinterpret_cast<String_t&>(result);
    }

    void Input_t::Is_Key_Pressed(Int_t key, some<Virtual::Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Virtual::Arguments_t
        {
        public:
            Int_t key;

        public:
            Virtual_Arguments(Int_t key) :
                key(key)
            {
            }

        public:
            virtual Bool_t operator()(Scrap_Array_t<Virtual::Variable_t>* args) override
            {
                args->Resize(1);
                args->At(0).As<Int_t>(key);
                return true;
            }
        };

        SKYLIB_ASSERT_SOME(v_callback);

        Virtual::Machine_t::Self()->Call_Global(
            SCRIPT_NAME,
            "IsKeyPressed",
            Virtual_Arguments(key),
            v_callback()
        );
    }

    void Input_t::Is_Key_Pressed(Int_t key, some<unique<doticu_skylib::Callback_i<Bool_t>>> callback)
    {
        using Callback = some<unique<doticu_skylib::Callback_i<Bool_t>>>;

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
            virtual void operator()(Virtual::Variable_t* result) override
            {
                (*this->callback)(result ? result->As<Bool_t>() : false);
            }
        };

        SKYLIB_ASSERT_SOME(callback);

        Is_Key_Pressed(key, new Virtual_Callback(std::move(callback)));
    }

    void Input_t::Tap_Key(Int_t key, maybe<Virtual::Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Virtual::Arguments_t
        {
        public:
            Int_t key;

        public:
            Virtual_Arguments(Int_t key) :
                key(key)
            {
            }

        public:
            virtual Bool_t operator()(Scrap_Array_t<Virtual::Variable_t>* args) override
            {
                args->Resize(1);
                args->At(0).As<Int_t>(key);
                return true;
            }
        };

        Virtual::Machine_t::Self()->Call_Global(
            SCRIPT_NAME,
            "TapKey",
            Virtual_Arguments(key),
            v_callback
        );
    }

    void Input_t::Tap_Key(Int_t key, maybe<unique<doticu_skylib::Callback_i<>>> callback)
    {
        using Callback = maybe<unique<doticu_skylib::Callback_i<>>>;

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

        Tap_Key(key, new Virtual_Callback(std::move(callback)));
    }

    void Input_t::Tap_Inventory_Key(maybe<Virtual::Callback_i*> v_callback)
    {
        Int_t inventory_key = Control_To_Key("Quick Inventory");
        Tap_Key(inventory_key, v_callback);
    }

    void Input_t::Tap_Inventory_Key(maybe<unique<doticu_skylib::Callback_i<>>> callback)
    {
        Int_t inventory_key = Control_To_Key("Quick Inventory");
        Tap_Key(inventory_key, std::move(callback));
    }

    void Input_t::Close_Menus(maybe<unique<doticu_skylib::Callback_i<Bool_t>>> callback)
    {
        using Callback = maybe<unique<doticu_skylib::Callback_i<Bool_t>>>;

        class Is_In_Menu_Mode_Callback :
            public Virtual::Callback_t
        {
        public:
            Int_t       menu_key;
            Callback    callback;

        public:
            Is_In_Menu_Mode_Callback(Int_t menu_key, Callback callback) :
                menu_key(menu_key), callback(std::move(callback))
            {
            }

        public:
            virtual void operator()(Virtual::Variable_t* result) override
            {
                if (result && result->As<Bool_t>()) {
                    class Tap_Key_Callback :
                        public Virtual::Callback_t
                    {
                    public:
                        Int_t       menu_key;
                        Callback    callback;

                    public:
                        Tap_Key_Callback(Int_t menu_key, Callback callback) :
                            menu_key(menu_key), callback(std::move(callback))
                        {
                        }

                    public:
                        virtual void operator()(Virtual::Variable_t*) override
                        {
                            class Wait_Callback :
                                public Virtual::Callback_t
                            {
                            public:
                                Int_t       menu_key;
                                Callback    callback;

                            public:
                                Wait_Callback(Int_t menu_key, Callback callback) :
                                    menu_key(menu_key), callback(std::move(callback))
                                {
                                }

                            public:
                                virtual void operator()(Virtual::Variable_t*) override
                                {
                                    Utility_t::Is_In_Menu_Mode(new Is_In_Menu_Mode_Callback(this->menu_key, std::move(this->callback)));
                                }
                            };
                            Utility_t::Wait_Even_In_Menu(0.1f, new Wait_Callback(this->menu_key, std::move(this->callback)));
                        }
                    };
                    Input_t::Tap_Key(this->menu_key, new Tap_Key_Callback(this->menu_key, std::move(this->callback)));
                } else {
                    if (this->callback) {
                        (*this->callback)(true);
                    }
                }
            }
        };

        Int_t menu_key = Control_To_Key("Tween Menu");
        if (menu_key > -1) {
            Utility_t::Is_In_Menu_Mode(new Is_In_Menu_Mode_Callback(menu_key, std::move(callback)));
        } else {
            if (callback) {
                (*callback)(false);
            }
        }
    }

}}
