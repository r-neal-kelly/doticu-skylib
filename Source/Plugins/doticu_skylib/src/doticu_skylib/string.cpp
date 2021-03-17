/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/cstring.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/memory.h"
#include "doticu_skylib/string.h"

namespace doticu_skylib {

    /* Static_String_t */

    static void Create_Impl(some<Static_String_t*> self, some<const char*> string)
    {
        static auto create = reinterpret_cast
            <void(*)(Static_String_t*, const char*)>
            (Game_t::Base_Address() + Static_String_t::Offset_e::CREATE);

        create(self(), string());
    }

    static void Destroy_Impl(some<Static_String_t*> self)
    {
        static auto destroy = reinterpret_cast
            <void(*)(Static_String_t*)>
            (Game_t::Base_Address() + Static_String_t::Offset_e::DESTROY);

        destroy(self());
    }

    static void Set_Impl(some<Static_String_t*> self, some<const char*> string)
    {
        static auto set = reinterpret_cast
            <Static_String_t * (*)(Static_String_t*, const char*)>
            (Game_t::Base_Address() + Static_String_t::Offset_e::SET);

        set(self(), string());
    }

    Static_String_t::Static_String_t() :
        Static_String_t("")
    {
    }

    Static_String_t::Static_String_t(const char* string)
    {
        Create_Impl(this, string ? string : "");
    }

    Static_String_t::Static_String_t(maybe<const char*> string) :
        Static_String_t(string())
    {
    }

    Static_String_t::Static_String_t(some<const char*> string) :
        Static_String_t(string())
    {
    }

    Static_String_t::Static_String_t(std::string& string) :
        Static_String_t(string.c_str())
    {
    }

    Static_String_t::Static_String_t(std::string&& string) noexcept :
        Static_String_t(string.c_str())
    {
    }

    Static_String_t::Static_String_t(const Static_String_t& other) :
        value(other.value)
    {
    }

    Static_String_t::Static_String_t(Static_String_t&& other) noexcept :
        value(std::exchange(other.value, ""))
    {
    }

    Static_String_t& Static_String_t::operator =(const Static_String_t& other)
    {
        if (this != std::addressof(other)) {
            this->value = other.value;
        }
        return *this;
    }

    Static_String_t& Static_String_t::operator =(Static_String_t&& other) noexcept
    {
        if (this != std::addressof(other)) {
            this->value = std::exchange(other.value, "");
        }
        return *this;
    }

    Static_String_t::~Static_String_t()
    {
        this->value = "";
    }

    void Static_String_t::Destroy()
    {
        Destroy_Impl(this);
        this->value = "";
    }

    void Static_String_t::Write(const char* value)
    {
        Set_Impl(this, value ? value : "");
    }

    Static_String_t::operator Bool_t() const
    {
        return static_cast<const char*>(*this)[0] != 0;
    }

    Static_String_t::operator const char*() const
    {
        return this->value ? this->value() : "";
    }

    Static_String_t::operator some<const char*>() const
    {
        return static_cast<const char*>(*this);
    }

    Static_String_t::operator std::string() const
    {
        return static_cast<const char*>(*this);
    }

    Bool_t Static_String_t::operator !() const
    {
        return !static_cast<Bool_t>(*this);
    }

    Bool_t Static_String_t::operator ==(const Static_String_t& other) const
    {
        return CString_t::Is_Same(*this, other, true);
    }

    Bool_t Static_String_t::operator !=(const Static_String_t& other) const
    {
        return !operator ==(other);
    }

    std::string operator +(const std::string& a, const Static_String_t& b)
    {
        return a + static_cast<const char*>(b);
    }

    /* Dynamic_String_t */

    static Bool_t Set_Impl(Dynamic_String_t* self, some<const char*> string)
    {
        static auto set = reinterpret_cast
            <Bool_t(*)(Dynamic_String_t*, const char*, u32)>
            (Game_t::Base_Address() + Dynamic_String_t::Offset_e::SET);

        SKYLIB_ASSERT_SOME(string);
        return set(self, string(), CString_t::Length(string(), false));
    }

    Dynamic_String_t::Dynamic_String_t() :
        data(nullptr), length(0), capacity(0)
    {
    }

    Dynamic_String_t::Dynamic_String_t(const char* other) :
        data(nullptr), length(0), capacity(0)
    {
        Set_Impl(this, other ? other : "");
    }

    Dynamic_String_t::Dynamic_String_t(Dynamic_String_t&& other) noexcept :
        data(std::exchange(other.data, nullptr)), length(other.length), capacity(other.capacity)
    {
    }

    Dynamic_String_t& Dynamic_String_t::operator=(const char* other)
    {
        data = nullptr;
        length = 0;
        capacity = 0;
        Set_Impl(this, other ? other : "");
    }

    Dynamic_String_t::~Dynamic_String_t()
    {
        if (data) {
            Memory_t::Self()->Deallocate(reinterpret_cast<Byte_t*>(data));
            data = nullptr;
        }
    }

    Bool_t Dynamic_String_t::operator==(const char* other) const
    {
        return CString_t::Is_Same(this->data, other, true);
    }

    Bool_t Dynamic_String_t::operator!=(const char* other) const
    {
        return !operator==(other);
    }

    Dynamic_String_t::operator Bool_t() const
    {
        return data && data[0];
    }

    Bool_t Dynamic_String_t::operator !() const
    {
        return !static_cast<Bool_t>(*this);
    }

    Dynamic_String_t::operator const char* () const
    {
        return data ? data : "";
    }

}
