/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/utils.h"
#include "doticu_skylib/string.h"

namespace doticu_skylib {

    static void Create_Impl(String_t* self, const char* string)
    {
        static auto create = reinterpret_cast
            <void(*)(String_t*, const char*)>
            (RelocationManager::s_baseAddr + String_t::Offset_e::CREATE);
        create(self, string);
    }

    static void Destroy_Impl(String_t* self)
    {
        static auto destroy = reinterpret_cast
            <void(*)(String_t*)>
            (RelocationManager::s_baseAddr + String_t::Offset_e::DESTROY);
        destroy(self);
    }

    static void Set_Impl(String_t* self, const char* string)
    {
        static auto set = reinterpret_cast
            <String_t * (*)(String_t*, const char*)>
            (RelocationManager::s_baseAddr + String_t::Offset_e::SET);
        set(self, string ? string : "");
    }

    String_t::String_t()
    {
        Create_Impl(this, "");
    }

    String_t::String_t(const char* string)
    {
        Create_Impl(this, string);
    }

    String_t::String_t(std::string&& string)
    {
        Create_Impl(this, string.c_str());
    }

    void String_t::Destroy()
    {
        Destroy_Impl(this);
        data = "";
    }

    const char* String_t::Value()
    {
        return data ? data : "";
    }

    void String_t::Value(const char* value)
    {
        Set_Impl(this, value);
    }

    Bool_t String_t::operator==(const String_t& other)
    {
        return CString_t::Is_Same(this->data, other.data, true);
    }

    Bool_t String_t::operator!=(const String_t& other)
    {
        return !operator==(other);
    }

    Bool_t String_t::operator!()
    {
        return !static_cast<Bool_t>(*this);
    }

    String_t::operator Bool_t()
    {
        return data && data[0];
    }

}
