/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/string.h"

namespace doticu_skylib {

    String_t::String_t()
    {
        String_t("");
    }

    String_t::String_t(const char* string)
    {
        static auto create = reinterpret_cast
            <void(*)(String_t*, const char*)>
            (RelocationManager::s_baseAddr + static_cast<Word_t>(Offset_e::CREATE));
        create(this, string);
    }

    String_t::String_t(std::string string)
    {
        String_t(string.c_str());
    }

    void String_t::Destroy()
    {
        static auto destroy = reinterpret_cast
            <void(*)(String_t*)>
            (RelocationManager::s_baseAddr + static_cast<Word_t>(Offset_e::DESTROY));
        destroy(this);
        data = "";
    }

    const char* String_t::Value()
    {
        return data ? data : "";
    }

    void String_t::Value(const char* value)
    {
        static auto set = reinterpret_cast
            <String_t*(*)(String_t*, const char*)>
            (RelocationManager::s_baseAddr + static_cast<Word_t>(Offset_e::SET));
        set(this, value ? value : "");
    }

}
