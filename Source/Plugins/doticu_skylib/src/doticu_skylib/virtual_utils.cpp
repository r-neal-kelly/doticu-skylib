/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/PapyrusInput.h"

#include "doticu_skylib/collections.h"

#include "doticu_skylib/virtual_arguments.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_machine.h"
#include "doticu_skylib/virtual_utils.h"
#include "doticu_skylib/virtual_variable.h"

namespace doticu_skylib { namespace Virtual {

    void Utils_t::Wait(Float_t seconds, Callback_i* vcallback)
    {
        struct Arguments : public Arguments_t {
            Float_t seconds;
            Arguments(Float_t seconds) :
                seconds(seconds)
            {
            }
            Bool_t operator()(Buffer_t<Variable_t>* arguments)
            {
                arguments->Resize(1);
                arguments->At(0)->Float(seconds);
                return true;
            }
        } arguments(seconds);

        Machine_t::Self()->Call_Global(
            "Utility",
            "WaitMenuMode",
            &arguments,
            &vcallback
        );
    }

    void Utils_t::Wait_Out_Of_Menu(Float_t seconds, Callback_i* vcallback)
    {
        struct Arguments : public Arguments_t {
            Float_t seconds;
            Arguments(Float_t seconds) :
                seconds(seconds)
            {
            }
            Bool_t operator()(Buffer_t<Variable_t>* arguments)
            {
                arguments->Resize(1);
                arguments->At(0)->Float(seconds);
                return true;
            }
        } arguments(seconds);

        Machine_t::Self()->Call_Global(
            "Utility",
            "Wait",
            &arguments,
            &vcallback
        );
    }

    void Utils_t::Is_In_Menu_Mode(Callback_i* vcallback)
    {
        Machine_t::Self()->Call_Global(
            "Utility",
            "IsInMenuMode",
            nullptr,
            vcallback ? &vcallback : nullptr
        );
    }

    void Utils_t::Tap_Key(Int_t key, Callback_i* vcallback)
    {
        struct Arguments : public Arguments_t
        {
            Int_t key;
            Arguments(Int_t key) :
                key(key)
            {
            }
            Bool_t operator()(Buffer_t<Variable_t>* arguments)
            {
                arguments->Resize(1);
                arguments->At(0)->Int(key);
                return true;
            }
        } arguments(key);

        Machine_t::Self()->Call_Global(
            "Input",
            "TapKey",
            &arguments,
            vcallback ? &vcallback : nullptr
        );
    }

    void Utils_t::Close_Menus(doticu_skylib::Callback_i<Bool_t>* ucallback)
    {
        using UCallback_t = doticu_skylib::Callback_i<Bool_t>;

        Int_t key = papyrusInput::GetMappedKey(0, "Tween Menu", 0xFF);
        if (key > -1) {
            class Is_Open_VCallback : public Callback_t
            {
            public:
                Int_t key;
                UCallback_t* ucallback;
                Is_Open_VCallback(Int_t key, UCallback_t* ucallback) :
                    key(key), ucallback(ucallback)
                {
                }
                void operator()(Variable_t* result)
                {
                    if (result && result->Bool()) {
                        class Tap_VCallback : public Callback_t
                        {
                        public:
                            Int_t key;
                            UCallback_t* ucallback;
                            Tap_VCallback(Int_t key, UCallback_t* ucallback) :
                                key(key), ucallback(ucallback)
                            {
                            }
                            void operator()(Variable_t*)
                            {
                                class Wait_VCallback : public Callback_t
                                {
                                public:
                                    Int_t key;
                                    UCallback_t* ucallback;
                                    Wait_VCallback(Int_t key, UCallback_t* ucallback) :
                                        key(key), ucallback(ucallback)
                                    {
                                    }
                                    void operator()(Variable_t*)
                                    {
                                        Is_In_Menu_Mode(new Is_Open_VCallback(key, ucallback));
                                    }
                                };
                                Wait(0.1f, new Wait_VCallback(key, ucallback));
                            }
                        };
                        Tap_Key(key, new Tap_VCallback(key, ucallback));
                    } else {
                        if (ucallback) {
                            ucallback->operator()(true);
                            delete ucallback;
                        }
                    }
                }
            };
            Is_In_Menu_Mode(new Is_Open_VCallback(key, ucallback));
        } else {
            if (ucallback) {
                ucallback->operator()(false);
                delete ucallback;
            }
        }
    }

    /*void Funcs_t::Open_Container(Reference_t* container, Virtual_Callback_i* vcallback)
    {
        struct Arguments : public Virtual_Arguments_t
        {
            Reference_t* container;
            Arguments(Reference_t* container) :
                container(container)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(1);
                arguments->At(0)->Pack(container);
                return true;
            }
        } arguments(container);

        Virtual_Machine_t::Self()->Call_Method(
            Consts::Funcs_Quest(),
            Class_Name(),
            "Open_Container",
            &arguments,
            vcallback ? &vcallback : nullptr
        );
    }
    
    void Funcs_t::Force_Third_Person(Virtual_Callback_i* vcallback)
    {
        Virtual_Machine_t::Self()->Call_Global(
            "Game",
            "ForceThirdPerson",
            nullptr,
            vcallback ? &vcallback : nullptr
        );
    }*/

}}
