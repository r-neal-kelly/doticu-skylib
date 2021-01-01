/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    using Raw_Form_Type_t = u8;

    class Form_Type_Base_e : public Enum_Base_t<Raw_Form_Type_t>
    {
    public:
        enum : _BASE_TYPE_
        {
            FORM                    = 0x00,

            KEYWORD                 = 0x04, // KYWD
            LOCATION_REFERENCE_TYPE = 0X05, // LCRT

            GLOBAL                  = 0x09, // GLOB
            FACTION                 = 0x0B, // FACT

            RACE                    = 0x0E, // RACE

            SCRIPT                  = 0x13, // SCPT

            ACTIVATOR               = 0x18, // ACTI

            FLORA                   = 0x27, // FLOR

            ACTOR_BASE              = 0x2B, // NPC_
            LEVELED_ACTOR_BASE      = 0x2C, // LVLN

            CELL                    = 0x3C, // CELL
            REFERENCE               = 0x3D, // REFR
            ACTOR                   = 0x3E, // ACHR

            WORLDSPACE              = 0x47, // WRLD

            QUEST                   = 0x4D, // QUST

            FORM_LIST               = 0x5B, // FLST

            LOCATION                = 0x68, // LCTN

            _END_                   = 0x8A,
        };
    };

    class Form_Type_e :
        public Form_Type_Base_e,
        public Enum_t<Raw_Form_Type_t>
    {
    public:
        using Enum_t::Enum_t;
    };
    STATIC_ASSERT(sizeof(Form_Type_e) == 0x1);

    template <>
    class none<Form_Type_e>
    {
    public:
        using value_type = Form_Type_e;

    private:
        Form_Type_e value;

    public:
        none() : value(Form_Type_e::FORM) {}

        Form_Type_e operator()() { return value; }
        Form_Type_e operator()() const { return value; }

        friend Bool_t operator==(const none<Form_Type_e>& a, const Form_Type_e b) { return b <= Form_Type_e::FORM || b >= Form_Type_e::_END_; }
        friend Bool_t operator==(const Form_Type_e a, const none<Form_Type_e>& b) { return a <= Form_Type_e::FORM || a >= Form_Type_e::_END_; }
        friend Bool_t operator==(const none<Form_Type_e>&& a, const Form_Type_e b) { return b <= Form_Type_e::FORM || b >= Form_Type_e::_END_; }
        friend Bool_t operator==(const Form_Type_e a, const none<Form_Type_e>&& b) { return a <= Form_Type_e::FORM || a >= Form_Type_e::_END_; }
        friend Bool_t operator!=(const none<Form_Type_e>& a, const Form_Type_e b) { return !(a == b); }
        friend Bool_t operator!=(const Form_Type_e a, const none<Form_Type_e>& b) { return !(a == b); }
        friend Bool_t operator!=(const none<Form_Type_e>&& a, const Form_Type_e b) { return !(a == b); }
        friend Bool_t operator!=(const Form_Type_e a, const none<Form_Type_e>&& b) { return !(a == b); }
    };

    template <>
    class maybe<Form_Type_e>
    {
    public:
        using value_type = Form_Type_e;

    private:
        Form_Type_e value;

    public:
        maybe() : value(none<Form_Type_e>()()) {}
        maybe(Form_Type_e value) : value(value) {}
        maybe(const none<Form_Type_e> other) : value(other()) {}
        maybe(const maybe<Form_Type_e>& other) : value(other.value) {}
        maybe(maybe<Form_Type_e>&& other) noexcept : value(std::exchange(other.value, none<Form_Type_e>()())) {}

        maybe<Form_Type_e>& operator=(const maybe<Form_Type_e>& other)
        {
            if (this != std::addressof(other)) {
                value = other.value;
            }
            return *this;
        }
        maybe<Form_Type_e>& operator=(maybe<Form_Type_e>&& other)
        {
            if (this != std::addressof(other)) {
                value = std::exchange(other.value, none<Form_Type_e>()());
            }
            return *this;
        }

        Form_Type_e operator()() { return value; }
        Form_Type_e operator()() const { return value; }

        Bool_t operator==(const maybe<Form_Type_e>& other) { return value == other(); }
        Bool_t operator==(const maybe<Form_Type_e>& other) const { return value == other(); }
        Bool_t operator!=(const maybe<Form_Type_e>& other) { return !operator==(other); }
        Bool_t operator!=(const maybe<Form_Type_e>& other) const { return !operator==(other); }

        explicit operator Bool_t() { return value != none<Form_Type_e>(); }
        explicit operator Bool_t() const { return value != none<Form_Type_e>(); }

        template <typename TT>
        operator maybe<TT>() { return static_cast<TT>(value); }
        template <typename TT>
        operator maybe<TT>() const { return static_cast<TT>(value); }
    };

    template <>
    class some<Form_Type_e>
    {
    public:
        using value_type = Form_Type_e;

    private:
        Form_Type_e value;

    public:
        some() = delete;
        some(Form_Type_e value) : value(value) {}
        some(const some<Form_Type_e>& other) : value(other.value) {}
        some(some<Form_Type_e>&& other) noexcept : value(std::exchange(other.value, none<Form_Type_e>()())) {}

        some<Form_Type_e>& operator=(const some<Form_Type_e>& other)
        {
            if (this != std::addressof(other)) {
                value = other.value;
            }
            return *this;
        }
        some<Form_Type_e>& operator=(some<Form_Type_e>&& other) noexcept
        {
            if (this != std::addressof(other)) {
                value = std::exchange(other.value, none<Form_Type_e>()());
            }
            return *this;
        }

        Form_Type_e operator()() { return value; }
        Form_Type_e operator()() const { return value; }

        Bool_t operator==(const some<Form_Type_e>& other) { return value == other(); }
        Bool_t operator==(const some<Form_Type_e>& other) const { return value == other(); }
        Bool_t operator!=(const some<Form_Type_e>& other) { return !operator==(other); }
        Bool_t operator!=(const some<Form_Type_e>& other) const { return !operator==(other); }

        explicit operator Bool_t() { return value != none<Form_Type_e>(); }
        explicit operator Bool_t() const { return value != none<Form_Type_e>(); }

        template <typename TT>
        operator some<TT>() { return static_cast<TT>(value); }
        template <typename TT>
        operator some<TT>() const { return static_cast<TT>(value); }
    };

}
