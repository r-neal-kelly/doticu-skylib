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
        enum : value_type
        {
            ALIAS_BASE          = 0x8B,
            ALIAS_REFERENCE     = 0x8C,
            ALIAS_LOCATION      = 0x8D,
            ACTIVE_MAGIC_EFFECT = 0x8E,

            _END_               = 0x8F, // user defined types do not have script types.
        };
        using Enum_t::Enum_t;

        Raw_Script_Type_t Raw()
        {
            return value;
        }

        template <typename Scriptable_t> // this can be overloaded for user types
        static some<Script_Type_e> From()
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
    public:
        using value_type = Script_Type_e;

    private:
        Script_Type_e value;

    public:
        none() : value(Script_Type_e::_END_) {}

        Script_Type_e operator()() { return value; }
        Script_Type_e operator()() const { return value; }

        friend Bool_t operator==(const none<Script_Type_e>& a, const Script_Type_e b) { return b >= Script_Type_e::_END_; }
        friend Bool_t operator==(const Script_Type_e a, const none<Script_Type_e>& b) { return a >= Script_Type_e::_END_; }
        friend Bool_t operator==(const none<Script_Type_e>&& a, const Script_Type_e b) { return b >= Script_Type_e::_END_; }
        friend Bool_t operator==(const Script_Type_e a, const none<Script_Type_e>&& b) { return a >= Script_Type_e::_END_; }
        friend Bool_t operator!=(const none<Script_Type_e>& a, const Script_Type_e b) { return !(a == b); }
        friend Bool_t operator!=(const Script_Type_e a, const none<Script_Type_e>& b) { return !(a == b); }
        friend Bool_t operator!=(const none<Script_Type_e>&& a, const Script_Type_e b) { return !(a == b); }
        friend Bool_t operator!=(const Script_Type_e a, const none<Script_Type_e>&& b) { return !(a == b); }
    };

    template <>
    class maybe<Script_Type_e>
    {
    public:
        using value_type = Script_Type_e;

    private:
        Script_Type_e value;

    public:
        maybe() : value(none<Script_Type_e>()()) {}
        maybe(Script_Type_e value) : value(value) {}
        maybe(const none<Script_Type_e> other) : value(other()) {}
        maybe(const maybe<Script_Type_e>& other) : value(other.value) {}
        maybe(maybe<Script_Type_e>&& other) noexcept : value(std::exchange(other.value, none<Script_Type_e>()())) {}

        maybe<Script_Type_e>& operator=(const maybe<Script_Type_e>& other)
        {
            if (this != std::addressof(other)) {
                value = other.value;
            }
            return *this;
        }
        maybe<Script_Type_e>& operator=(maybe<Script_Type_e>&& other)
        {
            if (this != std::addressof(other)) {
                value = std::exchange(other.value, none<Script_Type_e>()());
            }
            return *this;
        }

        Script_Type_e operator()() { return value; }
        Script_Type_e operator()() const { return value; }

        Bool_t operator==(const maybe<Script_Type_e>& other) { return value == other(); }
        Bool_t operator==(const maybe<Script_Type_e>& other) const { return value == other(); }
        Bool_t operator!=(const maybe<Script_Type_e>& other) { return !operator==(other); }
        Bool_t operator!=(const maybe<Script_Type_e>& other) const { return !operator==(other); }

        explicit operator Bool_t() { return value != none<Script_Type_e>(); }
        explicit operator Bool_t() const { return value != none<Script_Type_e>(); }

        template <typename TT>
        operator maybe<TT>() { return static_cast<TT>(value); }
        template <typename TT>
        operator maybe<TT>() const { return static_cast<TT>(value); }
    };

    template <>
    class some<Script_Type_e>
    {
    public:
        using value_type = Script_Type_e;

    private:
        Script_Type_e value;

    public:
        some() = delete;
        some(Script_Type_e value) : value(value) {}
        some(const some<Script_Type_e>& other) : value(other.value) {}
        some(some<Script_Type_e>&& other) noexcept : value(std::exchange(other.value, none<Script_Type_e>()())) {}

        some<Script_Type_e>& operator=(const some<Script_Type_e>& other)
        {
            if (this != std::addressof(other)) {
                value = other.value;
            }
            return *this;
        }
        some<Script_Type_e>& operator=(some<Script_Type_e>&& other) noexcept
        {
            if (this != std::addressof(other)) {
                value = std::exchange(other.value, none<Script_Type_e>()());
            }
            return *this;
        }

        Script_Type_e operator()() { return value; }
        Script_Type_e operator()() const { return value; }

        Bool_t operator==(const some<Script_Type_e>& other) { return value == other(); }
        Bool_t operator==(const some<Script_Type_e>& other) const { return value == other(); }
        Bool_t operator!=(const some<Script_Type_e>& other) { return !operator==(other); }
        Bool_t operator!=(const some<Script_Type_e>& other) const { return !operator==(other); }

        explicit operator Bool_t() { return value != none<Script_Type_e>(); }
        explicit operator Bool_t() const { return value != none<Script_Type_e>(); }

        template <typename TT>
        operator some<TT>() { return static_cast<TT>(value); }
        template <typename TT>
        operator some<TT>() const { return static_cast<TT>(value); }
    };

}
