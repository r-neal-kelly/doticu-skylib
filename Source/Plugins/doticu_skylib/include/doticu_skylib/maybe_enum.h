/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"
#include "doticu_skylib/string.h"

namespace doticu_skylib {

    template <typename T>
    class none_enum;
    template <typename T>
    class maybe_enum;
    template <typename T>
    class some_enum;

    template <typename T>
    class none_enum
    {
    public:
        using value_type = T;

    protected:
        const value_type value;

    public:
        none_enum() :
            value(value_type::_NONE_)
        {
        }

        none_enum(const none_enum& other) :
            value(value_type::_NONE_)
        {
        }

        none_enum(none_enum&& other) noexcept :
            value(value_type::_NONE_)
        {
        }

        none_enum& operator =(const none_enum& other)
        {
            return *this;
        }

        none_enum& operator =(none_enum&& other) noexcept
        {
            return *this;
        }

        ~none_enum()
        {
        }

    public:
        explicit operator Bool_t() const
        {
            return false;
        }

    public:
        Bool_t operator !() const
        {
            return true;
        }

        value_type operator ()() const
        {
            return value_type::_NONE_;
        }
    };

    template <typename T>
    class maybe_enum
    {
    public:
        using value_type = T;

    protected:
        value_type value;

    public:
        maybe_enum() :
            value(value_type::_NONE_)
        {
        }

        maybe_enum(typename value_type::value_type value) :
            value(value)
        {
        }

        maybe_enum(const char* string) :
            value(string)
        {
        }

        maybe_enum(const none<const char*>& string) :
            value(string)
        {
        }

        maybe_enum(none<const char*>&& string) noexcept :
            value(string)
        {
        }

        maybe_enum(const maybe<const char*>& string) :
            value(string)
        {
        }

        maybe_enum(maybe<const char*>&& string) noexcept :
            value(string)
        {
        }

        maybe_enum(const some<const char*>& string) :
            value(string)
        {
        }

        maybe_enum(some<const char*>&& string) noexcept :
            value(string)
        {
        }

        maybe_enum(const String_t& string) :
            value(string)
        {
        }

        maybe_enum(String_t&& string) noexcept :
            value(string)
        {
        }

        maybe_enum(const std::string& string) :
            value(string)
        {
        }

        maybe_enum(std::string&& string) noexcept :
            value(string)
        {
        }

        maybe_enum(const value_type& value) :
            value(value)
        {
        }

        maybe_enum(value_type&& value) noexcept :
            value(std::exchange(value, value_type::_NONE_))
        {
        }

        maybe_enum(const none_enum<value_type>& other) :
            value(value_type::_NONE_)
        {
        }

        maybe_enum(none_enum<value_type>&& other) noexcept :
            value(value_type::_NONE_)
        {
        }

        maybe_enum(const maybe_enum& other) :
            value(other.value)
        {
        }

        maybe_enum(maybe_enum&& other) noexcept :
            value(std::exchange(other.value, value_type::_NONE_))
        {
        }

        maybe_enum(const some_enum<value_type>& other) :
            value(other.value)
        {
        }

        maybe_enum(some_enum<value_type>&& other) noexcept :
            value(std::exchange(other.value, value_type::_NONE_))
        {
        }

        maybe_enum& operator =(const maybe_enum& other)
        {
            if (this != std::addressof(other)) {
                this->value = other.value;
            }
            return *this;
        }

        maybe_enum& operator =(maybe_enum&& other) noexcept
        {
            if (this != std::addressof(other)) {
                this->value = std::exchange(other.value, value_type::_NONE_);
            }
            return *this;
        }

        ~maybe_enum()
        {
            this->value = value_type::_NONE_;
        }

    public:
        explicit operator Bool_t() const
        {
            return static_cast<Bool_t>(this->value);
        }

        template <typename TT>
        operator maybe<TT>()
        {
            return maybe<TT>(static_cast<TT&>(this->value));
        }

    public:
        Bool_t operator !() const
        {
            return !static_cast<Bool_t>(*this);
        }

        value_type operator ()() const
        {
            return this->value;
        }
    };

    template <typename T>
    class some_enum
    {
    public:
        friend class maybe_enum<T>;

    public:
        using value_type = T;

    protected:
        value_type value;

    public:
        some_enum() = delete;

        some_enum(typename value_type::value_type value) :
            value(value)
        {
        }

        some_enum(const char* string) :
            value(string)
        {
        }

        some_enum(const some<const char*>& string) :
            value(string)
        {
        }

        some_enum(some<const char*>&& string) noexcept :
            value(string)
        {
        }

        some_enum(const String_t& string) :
            value(string)
        {
        }

        some_enum(String_t&& string) noexcept :
            value(string)
        {
        }

        some_enum(const std::string& string) :
            value(string)
        {
        }

        some_enum(std::string&& string) noexcept :
            value(string)
        {
        }

        some_enum(const value_type& value) :
            value(value)
        {
        }

        some_enum(value_type&& value) noexcept :
            value(std::exchange(value, value_type::_NONE_))
        {
        }

        some_enum(const some_enum& other) :
            value(other.value)
        {
        }

        some_enum(some_enum&& other) noexcept :
            value(std::exchange(other.value, value_type::_NONE_))
        {
        }

        some_enum& operator =(const some_enum& other)
        {
            if (this != std::addressof(other)) {
                this->value = other.value;
            }
            return *this;
        }

        some_enum& operator =(some_enum&& other) noexcept
        {
            if (this != std::addressof(other)) {
                this->value = std::exchange(other.value, value_type::_NONE_);
            }
            return *this;
        }

        ~some_enum()
        {
            this->value = value_type::_NONE_;
        }

    public:
        explicit operator Bool_t() const
        {
            return static_cast<Bool_t>(this->value);
        }

        template <typename TT>
        operator some<TT>()
        {
            return some<TT>(static_cast<TT&>(this->value));
        }

    public:
        Bool_t operator !() const
        {
            return !static_cast<Bool_t>(*this);
        }

        value_type operator ()() const
        {
            return this->value;
        }
    };

}
