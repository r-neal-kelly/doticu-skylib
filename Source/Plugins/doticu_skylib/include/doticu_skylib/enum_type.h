/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/cstring.h"
#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe_enum.h"
#include "doticu_skylib/traits.h"

namespace doticu_skylib {

    template <typename T, enable_if_enumable_t<T> = true>
    class Enum_Type_Data_t
    {
    public:
        using value_type = T;

    public:
        static some<const char*> Enum_Type_Data_t::To_String(some<const char* const*> strings,
                                                             some<const char*> none_string,
                                                             Bool_t(*Is_Valid_f)(value_type),
                                                             value_type value)
        {
            SKYLIB_ASSERT_SOME(strings);

            if (Is_Valid_f(value)) {
                return strings[value];
            } else {
                return none_string;
            }
        }

        static value_type Enum_Type_Data_t::From_String(some<const char* const*> strings,
                                                        value_type _NONE_,
                                                        value_type _TOTAL_,
                                                        maybe<const char*> string,
                                                        Bool_t do_trim = false)
        {
            if (string) {
                if (do_trim) {
                    for (size_t idx = 0, end = _TOTAL_; idx < end; idx += 1) {
                        if (CString_t::Is_Same_Trimmed(strings[idx], string(), true)) {
                            return static_cast<value_type>(idx);
                        }
                    }
                    return _NONE_;
                } else {
                    for (size_t idx = 0, end = _TOTAL_; idx < end; idx += 1) {
                        if (CString_t::Is_Same(strings[idx], string(), true)) {
                            return static_cast<value_type>(idx);
                        }
                    }
                    return _NONE_;
                }
            } else {
                return _NONE_;
            }
        }
    };

    template <typename T>
    using enable_if_enum_type_data_t = std::enable_if_t<
        std::is_convertible<T, Enum_Type_Data_t<typename T::value_type>>::value,
        Bool_t
    >;
    template <typename T, typename _ = void>
    struct is_enum_type_data :
        public std::false_type
    {
    };
    template <typename T>
    struct is_enum_type_data<T, std::conditional_t<false, enable_if_enum_type_data_t<T>, void>> :
        public std::true_type
    {
    };

    template <typename Data_t, enable_if_enum_type_data_t<Data_t> = true>
    class Enum_Type_t :
        public Data_t
    {
    public:
        using data_type = typename Data_t;
        using value_type = typename Data_t::value_type;

    public:
        static some<const char*> To_String(maybe<Enum_Type_t> value)
        {
            return Data_t::To_String(value());
        }

        static maybe<Enum_Type_t> From_String(maybe<const char*> string)
        {
            return Data_t::From_String(string);
        }

    protected:
        Atomic_Number_t<value_type> value;

    public:
        Enum_Type_t() :
            value(Data_t::_NONE_)
        {
        }

        Enum_Type_t(value_type value) :
            value(Data_t::Is_Valid(value) ? value : Data_t::_NONE_)
        {
        }

        Enum_Type_t(const none<const char*>& string) :
            Enum_Type_t(Data_t::_NONE_)
        {
        }

        Enum_Type_t(none<const char*>&& string) noexcept :
            Enum_Type_t(Data_t::_NONE_)
        {
        }

        Enum_Type_t(const maybe<const char*>& string) :
            Enum_Type_t(From_String(string)())
        {
        }

        Enum_Type_t(maybe<const char*>&& string) noexcept :
            Enum_Type_t(From_String(string)())
        {
        }

        Enum_Type_t(const std::string& string) :
            Enum_Type_t(string.c_str())
        {
        }

        Enum_Type_t(std::string&& string) noexcept :
            Enum_Type_t(string.c_str())
        {
        }

        Enum_Type_t(const Enum_Type_t& other) :
            value(other.value)
        {
        }

        Enum_Type_t(Enum_Type_t&& other) noexcept :
            value(std::exchange(other.value, Data_t::_NONE_))
        {
        }

        Enum_Type_t& operator =(const Enum_Type_t& other)
        {
            if (this != std::addressof(other)) {
                this->value = other.value;
            }
            return *this;
        }

        Enum_Type_t& operator =(Enum_Type_t&& other) noexcept
        {
            if (this != std::addressof(other)) {
                this->value = std::exchange(other.value, Data_t::_NONE_);
            }
            return *this;
        }

        ~Enum_Type_t()
        {
            this->value = Data_t::_NONE_;
        }

    public:
        some<const char*> As_String() const
        {
            return Data_t::To_String(*this);
        }

    public:
        explicit operator Bool_t() const
        {
            return Data_t::Is_Valid(this->value);
        }

        operator value_type() const
        {
            return static_cast<Bool_t>(*this) ? this->value : Data_t::_NONE_;
        }

        operator some<const char*>() const
        {
            return As_String();
        }

    public:
        Bool_t operator !() const
        {
            return !static_cast<Bool_t>(*this);
        }

        value_type operator ()() const
        {
            return static_cast<value_type>(*this);
        }
    };

    template <typename T>
    class none<Enum_Type_t<T>> :
        public none_enum<Enum_Type_t<T>>
    {
    public:
        using none_enum::none_enum;
    };

    template <typename T>
    class maybe<Enum_Type_t<T>> :
        public maybe_enum<Enum_Type_t<T>>
    {
    public:
        using maybe_enum::maybe_enum;
    };

    template <typename T>
    class some<Enum_Type_t<T>> :
        public some_enum<Enum_Type_t<T>>
    {
    public:
        using some_enum::some_enum;
    };

    template <typename T>
    using enable_if_enum_type_t = std::enable_if_t<
        std::is_convertible<T, Enum_Type_t<typename T::data_type>>::value,
        Bool_t
    >;
    template <typename T, typename _ = void>
    struct is_enum_type :
        public std::false_type
    {
    };
    template <typename T>
    struct is_enum_type<T, std::conditional_t<false, enable_if_enum_type_t<T>, void>> :
        public std::true_type
    {
    };

}
