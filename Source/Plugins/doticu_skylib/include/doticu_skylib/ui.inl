/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/ui.h"

#include "doticu_skylib/virtual_array.h"

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
        SetString(value);
    }

    template <>
    inline void GFx_Value_t::Value<const wchar_t*>(const wchar_t* value)
    {
        SetWideString(value);
    }

    template <typename Type>
    inline Type UI_t::Value(String_t menu, String_t target)
    {
        MenuManager* menu_manager = MenuManager::GetSingleton();
        if (menu_manager) {
            GFxMovieView* view = menu_manager->GetMovieView(reinterpret_cast<BSFixedString*>(&menu));
            if (view) {
                GFx_Value_t gfx_value;
                if (view->GetVariable(&gfx_value, target)) {
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
    }

    template <typename Type>
    inline void UI_t::Value(String_t menu, String_t target, Type value)
    {
        MenuManager* menu_manager = MenuManager::GetSingleton();
        if (menu_manager) {
            GFxMovieView* view = menu_manager->GetMovieView(reinterpret_cast<BSFixedString*>(&menu));
            if (view) {
                GFx_Value_t gfx_value;
                gfx_value.Value<Type>(value);
                view->SetVariable(target, &gfx_value, 1);
            }
        }
    }

    template <typename Type>
    inline void UI_t::Run(String_t menu, String_t target, Type argument)
    {
        UIManager* ui_manager = UIManager::GetSingleton();
        if (ui_manager) {
            UIInvokeDelegate delegate(menu, target);
            delegate.args.resize(1);
            reinterpret_cast<GFx_Value_t*>
                (&delegate.args[0])->Value<Type>(argument);
            delegate.Run();
        }
    }

    template <typename Type>
    inline void UI_t::Run(String_t menu, String_t target, Vector_t<Type> arguments)
    {
        UIManager* ui_manager = UIManager::GetSingleton();
        if (ui_manager) {
            size_t argument_count = arguments.size();
            UIInvokeDelegate delegate(menu, target);
            delegate.args.resize(argument_count);
            for (size_t idx = 0; idx < argument_count; idx += 1) {
                reinterpret_cast<GFx_Value_t*>
                    (&delegate.args[idx])->Value<Type>(arguments[idx]);
            }
            delegate.Run();
        }
    }

    template <typename Type>
    inline void UI_t::Run(String_t menu, String_t target, Virtual::Array_t* arguments)
    {
        UIManager* ui_manager = UIManager::GetSingleton();
        if (ui_manager) {
            size_t argument_count = arguments->count;
            UIInvokeDelegate delegate(menu, target);
            delegate.args.resize(argument_count);
            for (size_t idx = 0; idx < argument_count; idx += 1) {
                reinterpret_cast<GFx_Value_t*>
                    (&delegate.args[idx])->Value<Type>(*reinterpret_cast<Type*>(&arguments->Point(idx)->data));
            }
            delegate.Run();
        }
    }

}
