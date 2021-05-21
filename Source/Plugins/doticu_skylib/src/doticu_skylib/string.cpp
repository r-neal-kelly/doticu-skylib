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

    void Static_String_t::Write(maybe<const char*> value)
    {
        Set_Impl(this, value ? value() : "");
    }

    Static_String_t::operator Bool_t() const
    {
        return static_cast<const char*>(*this)[0] != 0;
    }

    Static_String_t::operator const char* () const
    {
        return this->value ? this->value() : "";
    }

    Static_String_t::operator maybe<const char*>() const
    {
        return static_cast<const char*>(*this);
    }

    Static_String_t::operator some<const char*>() const
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

    std::string operator +(const Static_String_t& a, const Static_String_t& b)
    {
        return std::string(a) + std::string(b);
    }

    std::string operator +(const Static_String_t& a, const char* b)
    {
        return std::string(a) + std::string(b);
    }

    std::string operator +(const char* a, const Static_String_t& b)
    {
        return std::string(a) + std::string(b);
    }

    std::string operator +(const Static_String_t& a, const std::string& b)
    {
        return std::string(a) + b;
    }

    std::string operator +(const std::string& a, const Static_String_t& b)
    {
        return a + std::string(b);
    }

    Bool_t operator ==(const Static_String_t& a, const char* b)
    {
        return CString_t::Is_Same(a, b, true);
    }

    Bool_t operator ==(const char* a, const Static_String_t& b)
    {
        return CString_t::Is_Same(a, b, true);
    }

    /* Dynamic_String_t */

    Dynamic_String_t::Dynamic_String_t() :
        value(none<char*>()), length(0), capacity(0), pad_0C(0)
    {
    }

    Dynamic_String_t::Dynamic_String_t(const char* string)
    {
        Write(string);
    }

    Dynamic_String_t::Dynamic_String_t(const Dynamic_String_t& other)
    {
        Write(other);
    }

    Dynamic_String_t::Dynamic_String_t(Dynamic_String_t&& other) noexcept :
        value(std::exchange(other.value, none<char*>())),
        length(std::exchange(other.length, 0)),
        capacity(std::exchange(other.capacity, 0)),
        pad_0C(std::exchange(other.pad_0C, 0))
    {
    }

    Dynamic_String_t& Dynamic_String_t::operator =(const Dynamic_String_t& other)
    {
        if (this != std::addressof(other)) {
            Write(other);
        }
        return *this;
    }

    Dynamic_String_t& Dynamic_String_t::operator =(Dynamic_String_t&& other) noexcept
    {
        if (this != std::addressof(other)) {
            this->value = std::exchange(other.value, none<char*>());
            this->length = std::exchange(other.length, 0);
            this->capacity = std::exchange(other.capacity, 0);
            this->pad_0C = std::exchange(other.pad_0C, 0);
        }
        return *this;
    }

    Dynamic_String_t::~Dynamic_String_t()
    {
        Clear();
    }

    void Dynamic_String_t::Write(maybe<const char*> string)
    {
        static auto set = reinterpret_cast
            <Bool_t(*)(Dynamic_String_t*, const char*, u32 length_without_null)>
            (Game_t::Base_Address() + Dynamic_String_t::Offset_e::SET);

        if (!string) {
            string = "";
        }

        Clear();

        set(this, string(), CString_t::Length(string(), false));
    }

    void Dynamic_String_t::Clear()
    {
        if (this->value) {
            Memory_t::Self()->Deallocate(reinterpret_cast<Byte_t*>(this->value()));
            value = none<char*>();
        }
        this->length = 0;
        this->capacity = 0;
        this->pad_0C = 0;
    }

    Dynamic_String_t::operator Bool_t() const
    {
        return static_cast<const char*>(*this)[0] != 0;
    }

    Dynamic_String_t::operator const char* () const
    {
        return this->value ? this->value() : "";
    }

    Dynamic_String_t::operator maybe<const char*>() const
    {
        return static_cast<const char*>(*this);
    }

    Dynamic_String_t::operator some<const char*>() const
    {
        return static_cast<const char*>(*this);
    }

    Bool_t Dynamic_String_t::operator !() const
    {
        return !static_cast<Bool_t>(*this);
    }

    some<const char*> Dynamic_String_t::operator ()() const
    {
        return static_cast<const char*>(*this);
    }

    Bool_t Dynamic_String_t::operator ==(const Dynamic_String_t& other) const
    {
        return CString_t::Is_Same(*this, other, true);
    }

    Bool_t Dynamic_String_t::operator !=(const Dynamic_String_t& other) const
    {
        return !operator ==(other);
    }

    std::string operator +(const Dynamic_String_t& a, const Dynamic_String_t& b)
    {
        return std::string(a) + std::string(b);
    }

    std::string operator +(const Dynamic_String_t& a, const char* b)
    {
        return std::string(a) + std::string(b);
    }

    std::string operator +(const char* a, const Dynamic_String_t& b)
    {
        return std::string(a) + std::string(b);
    }

    std::string operator +(const Dynamic_String_t& a, const std::string& b)
    {
        return std::string(a) + b;
    }

    std::string operator +(const std::string& a, const Dynamic_String_t& b)
    {
        return a + std::string(b);
    }

    Bool_t operator ==(const Dynamic_String_t& a, const char* b)
    {
        return CString_t::Is_Same(a, b, true);
    }

    Bool_t operator ==(const char* a, const Dynamic_String_t& b)
    {
        return CString_t::Is_Same(a, b, true);
    }

}
