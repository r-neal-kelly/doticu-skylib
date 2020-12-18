/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/cstring.h"
#include "doticu_skylib/string.h"

#include "doticu_skylib/game.h"

namespace doticu_skylib {

    static void Create_Impl(Static_String_t* self, const char* string)
    {
        static auto create = reinterpret_cast
            <void(*)(Static_String_t*, const char*)>
            (Game_t::Base_Address() + Static_String_t::Offset_e::CREATE);
        create(self, string);
    }

    static void Destroy_Impl(Static_String_t* self)
    {
        static auto destroy = reinterpret_cast
            <void(*)(Static_String_t*)>
            (Game_t::Base_Address() + Static_String_t::Offset_e::DESTROY);
        destroy(self);
    }

    static void Set_Impl(Static_String_t* self, const char* string)
    {
        static auto set = reinterpret_cast
            <Static_String_t * (*)(Static_String_t*, const char*)>
            (Game_t::Base_Address() + Static_String_t::Offset_e::SET);
        set(self, string ? string : "");
    }

    Static_String_t::Static_String_t()
    {
        Create_Impl(this, "");
    }

    Static_String_t::Static_String_t(const char* string)
    {
        Create_Impl(this, string);
    }

    Static_String_t::Static_String_t(std::string& string)
    {
        Create_Impl(this, string.c_str());
    }

    Static_String_t::Static_String_t(std::string&& string)
    {
        Create_Impl(this, string.c_str());
    }

    void Static_String_t::Destroy()
    {
        Destroy_Impl(this);
        data = "";
    }

    const char* Static_String_t::Value()
    {
        return data ? data : "";
    }

    void Static_String_t::Value(const char* value)
    {
        Set_Impl(this, value);
    }

    Bool_t Static_String_t::operator==(const Static_String_t& other)
    {
        return CString_t::Is_Same(this->data, other.data, true);
    }

    Bool_t Static_String_t::operator!=(const Static_String_t& other)
    {
        return !operator==(other);
    }

    Static_String_t::operator Bool_t()
    {
        return data && data[0];
    }

    Static_String_t::operator Bool_t() const
    {
        return data && data[0];
    }

    Static_String_t::operator const char*()
    {
        return data;
    }

}
