/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"

#include "doticu_skylib/form_type.h"

namespace doticu_skylib {

    namespace Virtual {

        class Class_t;

    }

    using Raw_Script_Type_t = u32;

    class Script_Type_e :
        public Form_Type_Base_e,
        public Enum_t<Raw_Script_Type_t>
    {
    public:
        enum : _TYPE_
        {
            ALIAS_BASE          = 0x8B,
            ALIAS_REFERENCE     = 0x8C,
            ALIAS_LOCATION      = 0x8D,
            ACTIVE_MAGIC_EFFECT = 0x8E,

            _END_               = 0x8F, // I think user defined types begin here. Are they a pointer to their Class_t?
        };
        using Enum_t::Enum_t;

        template <typename Scriptable_t>
        static Script_Type_e From()
        {
            return std::remove_pointer_t<Scriptable_t>::SCRIPT_TYPE;
        }

    public:
        maybe<Virtual::Class_t*> Class();
    };
    STATIC_ASSERT(sizeof(Script_Type_e) == 0x4);

    template <>
    class none<Script_Type_e>
    {
    private:
        Script_Type_e value;

    public:
        none() :
            value(Script_Type_e::_END_)
        {
        }

        Script_Type_e operator()()
        {
            return operator Script_Type_e();
        }

        Script_Type_e operator()() const
        {
            return operator Script_Type_e();
        }

        operator Script_Type_e()
        {
            return value;
        }

        operator Script_Type_e() const
        {
            return value;
        }
    };

    template <>
    class maybe<Script_Type_e>
    {
    private:
        Script_Type_e value;

    public:
        maybe() :
            value(none<Script_Type_e>())
        {
        }

        maybe(Raw_Script_Type_t value) :
            value(value)
        {
        }

        maybe(Script_Type_e value) :
            value(value)
        {
        }

        maybe(none<Script_Type_e> value) :
            value(value)
        {
        }

        maybe(const maybe& other) :
            value(other.value)
        {
        }

        maybe(maybe&& other) noexcept :
            value(std::exchange(other.value, none<Script_Type_e>()))
        {
        }

        maybe& operator=(const maybe& other)
        {
            if (this != &other) {
                value = other.value;
            }
            return *this;
        }

        maybe& operator=(maybe&& other)
        {
            if (this != &other) {
                value = std::exchange(other.value, none<Script_Type_e>());
            }
            return *this;
        }

        Script_Type_e operator()()
        {
            return operator Script_Type_e();
        }

        Script_Type_e operator()() const
        {
            return operator Script_Type_e();
        }

        operator Script_Type_e()
        {
            return value;
        }

        operator Script_Type_e() const
        {
            return value;
        }

        operator Bool_t()
        {
            return value != none<Script_Type_e>()();
        }

        operator Bool_t() const
        {
            return value != none<Script_Type_e>()();
        }
    };

    template <>
    class some<Script_Type_e>
    {
    private:
        Script_Type_e value;

    public:
        some() = delete;

        some(Raw_Script_Type_t value) :
            value(value)
        {
        }

        some(Script_Type_e value) :
            value(value)
        {
        }

        some(maybe<Script_Type_e> value) :
            value(value)
        {
        }

        some(const some& other) :
            value(other.value)
        {
        }

        some(some&& other) noexcept :
            value(std::exchange(other.value, none<Script_Type_e>()))
        {
        }

        some& operator=(const some& other)
        {
            if (this != &other) {
                value = other.value;
            }
            return *this;
        }

        some& operator=(some&& other) noexcept
        {
            if (this != &other) {
                value = std::exchange(other.value, none<Script_Type_e>());
            }
            return *this;
        }

        Script_Type_e operator()()
        {
            return value;
        }

        Script_Type_e operator()() const
        {
            return value;
        }

        operator Script_Type_e()
        {
            return value;
        }

        operator Script_Type_e() const
        {
            return value;
        }

        operator Bool_t()
        {
            return value != none<Script_Type_e>()();
        }

        operator Bool_t() const
        {
            return value != none<Script_Type_e>()();
        }
    };

}
