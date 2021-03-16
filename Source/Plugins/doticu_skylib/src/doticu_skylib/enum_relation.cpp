/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/cstring.h"
#include "doticu_skylib/enum_relation.h"
#include "doticu_skylib/game.h"

namespace doticu_skylib {

    some<const char* const*> Relation_e::Strings()
    {
        static const char* const strings[_TOTAL_] =
        {
            SKYLIB_ENUM_TO_STRING(LOVER),
            SKYLIB_ENUM_TO_STRING(ALLY),
            SKYLIB_ENUM_TO_STRING(CONFIDANT),
            SKYLIB_ENUM_TO_STRING(FRIEND),
            SKYLIB_ENUM_TO_STRING(ACQUAINTANCE),
            SKYLIB_ENUM_TO_STRING(RIVAL),
            SKYLIB_ENUM_TO_STRING(FOE),
            SKYLIB_ENUM_TO_STRING(ENEMY),
            SKYLIB_ENUM_TO_STRING(ARCHNEMESIS),
        };

        return strings;
    }

    some<const char*> Relation_e::To_String(maybe<Relation_e> relation)
    {
        if (relation) {
            return Strings()[relation()];
        } else {
            return "NONE";
        }
    }

    maybe<Relation_e> Relation_e::From_String(maybe<const char*> relation)
    {
        if (relation) {
            some<const char* const*> strings = Strings();
            for (size_t idx = 0, end = _TOTAL_; idx < end; idx += 1) {
                some<const char*> string = strings[idx];
                if (CString_t::Is_Same(string(), relation(), true)) {
                    return static_cast<Relation_e::value_type>(idx);
                }
            }
            return _NONE_;
        } else {
            return _NONE_;
        }
    }

    some<Relation_e> Relation_e::Between(some<Form_t*> form_a, some<Form_t*> form_b)
    {
        static auto get = reinterpret_cast
            <u32(*)(Form_t*, Form_t*)>
            (Game_t::Base_Address() + Offset_e::GET);

        SKYLIB_ASSERT_SOME(form_a);
        SKYLIB_ASSERT_SOME(form_b);

        maybe<Relation_e> relation = get(form_a(), form_b());
        if (relation) {
            return relation();
        } else {
            return _DEFAULT_;
        }
    }

    void Relation_e::Between(some<Form_t*> form_a, some<Form_t*> form_b, some<Relation_e> relation)
    {
        static auto set = reinterpret_cast
            <void(*)(Form_t*, Form_t*, u32)>
            (Game_t::Base_Address() + Offset_e::SET);

        SKYLIB_ASSERT_SOME(form_a);
        SKYLIB_ASSERT_SOME(form_b);
        SKYLIB_ASSERT_SOME(relation);

        set(form_a(), form_b(), relation());
    }

    Relation_e::Relation_e() :
        Enum_t(_NONE_)
    {
    }

    Relation_e::Relation_e(enum_type value) :
        Enum_t(value < _TOTAL_ ? value : _NONE_)
    {
    }

    Relation_e::Relation_e(value_type value) :
        Relation_e(static_cast<enum_type>(value))
    {
    }

    Relation_e::Relation_e(const Relation_e& other) :
        Enum_t(other.value)
    {
    }

    Relation_e::Relation_e(Relation_e&& other) noexcept :
        Enum_t(std::move(other.value))
    {
    }

    Relation_e& Relation_e::operator =(const Relation_e& other)
    {
        if (this != std::addressof(other)) {
            this->value = other.value;
        }
        return *this;
    }

    Relation_e& Relation_e::operator =(Relation_e&& other) noexcept
    {
        if (this != std::addressof(other)) {
            this->value = std::move(other.value);
        }
        return *this;
    }

    Relation_e::~Relation_e()
    {
        this->value = _NONE_;
    }

    some<const char*> Relation_e::As_String()
    {
        return To_String(*this);
    }

    Relation_e::operator Bool_t() const
    {
        return this->value < _TOTAL_;
    }

    Relation_e::operator value_type() const
    {
        return static_cast<Bool_t>(*this) ? this->value : _NONE_;
    }

    Bool_t Relation_e::operator !() const
    {
        return !static_cast<Bool_t>(*this);
    }

    Relation_e::value_type Relation_e::operator ()() const
    {
        return static_cast<value_type>(*this);
    }

}
