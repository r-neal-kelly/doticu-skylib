/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/PapyrusUI.h"

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/virtual_array.h"
#include "doticu_skylib/virtual_callback.h"

namespace doticu_skylib {

    class GFx_Value_t : public GFxValue {
    public:
        template <typename Type>
        Type Value();
        template <typename Type>
        void Value(Type value);
    };

    class UI_t {
    public:
        template <typename Type>
        static Type Value(String_t menu, String_t target);
        template <typename Type>
        static void Value(String_t menu, String_t target, Type value);

        template <typename Type>
        static void Run(String_t menu, String_t target, Type argument);
        template <typename Type>
        static void Run(String_t menu, String_t target, Vector_t<Type> arguments);
        template <typename Type>
        static void Run(String_t menu, String_t target, Virtual::Array_t* arguments);
        static void Run(String_t menu, String_t target);

        static void Notification(String_t note, Virtual::Callback_i* vcallback = nullptr);
        static void Message_Box(String_t message, Virtual::Callback_i* vcallback = nullptr);

        static Bool_t Is_Menu_Open(String_t menu);
        static void Is_In_Menu_Mode(Virtual::Callback_i* vcallback);
        static void Is_In_Menu_Mode(Callback_i<Bool_t>* ucallback);
    };

}

namespace doticu_skylib {

    template <typename Type>
    inline Type GFx_Value_t::Value()
    {
        STATIC_ASSERT(false);
    }

    template <>
    inline Bool_t GFx_Value_t::Value<Bool_t>()
    {
        return GetType() == GFxValue::kType_Bool ? GetBool() : false;
    }

    template <>
    inline Int_t GFx_Value_t::Value<Int_t>()
    {
        return GetType() == GFxValue::kType_Number ? GetNumber() : 0;
    }

    template <>
    inline Float_t GFx_Value_t::Value<Float_t>()
    {
        return GetType() == GFxValue::kType_Number ? GetNumber() : 0.0f;
    }

    template <>
    inline String_t GFx_Value_t::Value<String_t>()
    {
        return GetType() == GFxValue::kType_String ? GetString() : "";
    }

    template <typename Type>
    inline void GFx_Value_t::Value(Type value)
    {
        STATIC_ASSERT(false);
    }

    template <>
    inline void GFx_Value_t::Value<Bool_t>(Bool_t value)
    {
        SetBool(value);
    }

    template <>
    inline void GFx_Value_t::Value<Int_t>(Int_t value)
    {
        SetNumber(value);
    }

    template <>
    inline void GFx_Value_t::Value<Float_t>(Float_t value)
    {
        SetNumber(value);
    }

    template <>
    inline void GFx_Value_t::Value<String_t>(String_t value)
    {
        if (value.data) {
            SetString(value.data);
        } else {
            SetString("");
        }
    }

    template <typename Type>
    inline Type UI_t::Value(String_t menu, String_t target)
    {
        if (menu.data && target.data) {
            MenuManager* menu_manager = MenuManager::GetSingleton();
            if (menu_manager) {
                GFxMovieView* view = menu_manager->GetMovieView(&menu);
                if (view) {
                    GFx_Value_t gfx_value;
                    if (view->GetVariable(&gfx_value, target.data)) {
                        return gfx_value.Value<Type>();
                    } else {
                        return 0;
                    }
                } else {
                    return 0;
                }
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }

    template <typename Type>
    inline void UI_t::Value(String_t menu, String_t target, Type value)
    {
        if (menu.data && target.data) {
            MenuManager* menu_manager = MenuManager::GetSingleton();
            if (menu_manager) {
                GFxMovieView* view = menu_manager->GetMovieView(&menu);
                if (view) {
                    GFx_Value_t gfx_value;
                    gfx_value.Value<Type>(value);
                    view->SetVariable(target.data, &gfx_value, 1);
                }
            }
        }
    }

    template <typename Type>
    inline void UI_t::Run(String_t menu, String_t target, Type argument)
    {
        if (menu.data && target.data) {
            UIManager* ui_manager = UIManager::GetSingleton();
            if (ui_manager) {
                UIInvokeDelegate delegate(menu.data, target.data);
                delegate.args.resize(1);
                reinterpret_cast<GFx_Value_t*>
                    (&delegate.args[0])->Value<Type>(argument);
                delegate.Run();
            }
        }
    }

    template <typename Type>
    inline void UI_t::Run(String_t menu, String_t target, Vector_t<Type> arguments)
    {
        if (menu.data && target.data) {
            UIManager* ui_manager = UIManager::GetSingleton();
            if (ui_manager) {
                size_t argument_count = arguments.size();
                UIInvokeDelegate delegate(menu.data, target.data);
                delegate.args.resize(argument_count);
                for (size_t idx = 0; idx < argument_count; idx += 1) {
                    reinterpret_cast<GFx_Value_t*>
                        (&delegate.args[idx])->Value<Type>(arguments[idx]);
                }
                delegate.Run();
            }
        }
    }

    template <typename Type>
    inline void UI_t::Run(String_t menu, String_t target, Virtual::Array_t* arguments)
    {
        if (menu.data && target.data) {
            UIManager* ui_manager = UIManager::GetSingleton();
            if (ui_manager) {
                size_t argument_count = arguments->count;
                UIInvokeDelegate delegate(menu.data, target.data);
                delegate.args.resize(argument_count);
                for (size_t idx = 0; idx < argument_count; idx += 1) {
                    reinterpret_cast<GFx_Value_t*>
                        (&delegate.args[idx])->Value<Type>(*reinterpret_cast<Type*>(&arguments->Point(idx)->data));
                }
                delegate.Run();
            }
        }
    }

}
