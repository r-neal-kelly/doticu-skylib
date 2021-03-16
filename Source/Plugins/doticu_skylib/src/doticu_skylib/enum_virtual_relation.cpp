/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/enum_virtual_relation.h"

namespace doticu_skylib {

    maybe<Relation_e> Virtual_Relation_e::To_Relation(maybe<Virtual_Relation_e> v_relation)
    {
        if (v_relation) {
            if (v_relation == Virtual_Relation_e::LOVER)                return Relation_e::LOVER;
            else if (v_relation == Virtual_Relation_e::ALLY)            return Relation_e::ALLY;
            else if (v_relation == Virtual_Relation_e::CONFIDANT)       return Relation_e::CONFIDANT;
            else if (v_relation == Virtual_Relation_e::FRIEND)          return Relation_e::FRIEND;
            else if (v_relation == Virtual_Relation_e::ACQUAINTANCE)    return Relation_e::ACQUAINTANCE;
            else if (v_relation == Virtual_Relation_e::RIVAL)           return Relation_e::RIVAL;
            else if (v_relation == Virtual_Relation_e::FOE)             return Relation_e::FOE;
            else if (v_relation == Virtual_Relation_e::ENEMY)           return Relation_e::ENEMY;
            else if (v_relation == Virtual_Relation_e::ARCHNEMESIS)     return Relation_e::ARCHNEMESIS;
            else                                                        return Relation_e::_DEFAULT_;
        } else {
            return Relation_e::_NONE_;
        }
    }

    maybe<Virtual_Relation_e> Virtual_Relation_e::From_Relation(maybe<Relation_e> relation)
    {
        if (relation) {
            if (relation == Relation_e::LOVER)              return Virtual_Relation_e::LOVER;
            else if (relation == Relation_e::ALLY)          return Virtual_Relation_e::ALLY;
            else if (relation == Relation_e::CONFIDANT)     return Virtual_Relation_e::CONFIDANT;
            else if (relation == Relation_e::FRIEND)        return Virtual_Relation_e::FRIEND;
            else if (relation == Relation_e::ACQUAINTANCE)  return Virtual_Relation_e::ACQUAINTANCE;
            else if (relation == Relation_e::RIVAL)         return Virtual_Relation_e::RIVAL;
            else if (relation == Relation_e::FOE)           return Virtual_Relation_e::FOE;
            else if (relation == Relation_e::ENEMY)         return Virtual_Relation_e::ENEMY;
            else if (relation == Relation_e::ARCHNEMESIS)   return Virtual_Relation_e::ARCHNEMESIS;
            else                                            return Virtual_Relation_e::_DEFAULT_;
        } else {
            return Virtual_Relation_e::_NONE_;
        }
    }

    some<const char*> Virtual_Relation_e::To_String(maybe<Virtual_Relation_e> v_relation)
    {
        return Relation_e::To_String(To_Relation(v_relation));
    }

    maybe<Virtual_Relation_e> Virtual_Relation_e::From_String(maybe<const char*> v_relation)
    {
        return From_Relation(Relation_e::From_String(v_relation));
    }

    Virtual_Relation_e::Virtual_Relation_e() :
        Enum_t(_NONE_)
    {
    }

    Virtual_Relation_e::Virtual_Relation_e(enum_type value) :
        Enum_t(value <= LOVER && value >= ARCHNEMESIS ? value : _NONE_)
    {
    }

    Virtual_Relation_e::Virtual_Relation_e(value_type value) :
        Virtual_Relation_e(static_cast<enum_type>(value))
    {
    }

    Virtual_Relation_e::Virtual_Relation_e(const Virtual_Relation_e& other) :
        Enum_t(other.value)
    {
    }

    Virtual_Relation_e::Virtual_Relation_e(Virtual_Relation_e&& other) noexcept :
        Enum_t(std::move(other.value))
    {
    }

    Virtual_Relation_e& Virtual_Relation_e::operator =(const Virtual_Relation_e& other)
    {
        if (this != std::addressof(other)) {
            this->value = other.value;
        }
        return *this;
    }

    Virtual_Relation_e& Virtual_Relation_e::operator =(Virtual_Relation_e&& other) noexcept
    {
        if (this != std::addressof(other)) {
            this->value = std::move(other.value);
        }
        return *this;
    }

    Virtual_Relation_e::~Virtual_Relation_e()
    {
        this->value = _NONE_;
    }

    maybe<Relation_e> Virtual_Relation_e::As_Relation()
    {
        return To_Relation(*this);
    }

    some<const char*> Virtual_Relation_e::As_String()
    {
        return To_String(*this);
    }

    Virtual_Relation_e::operator Bool_t() const
    {
        return this->value <= LOVER && this->value >= ARCHNEMESIS;
    }

    Virtual_Relation_e::operator value_type() const
    {
        return static_cast<Bool_t>(*this) ? this->value : _NONE_;
    }

    Bool_t Virtual_Relation_e::operator !() const
    {
        return !static_cast<Bool_t>(*this);
    }

    Virtual_Relation_e::value_type Virtual_Relation_e::operator ()() const
    {
        return static_cast<value_type>(*this);
    }

    void Virtual_Relation_e::Log_Test(std::string indent)
    {
        SKYLIB_LOG(indent + "Virtual_Relation_e::Log_Test");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "%s == %s",
                   Virtual_Relation_e(Virtual_Relation_e::LOVER).As_String(),
                   From_Relation(Relation_e::LOVER)().As_String());
        SKYLIB_LOG(indent + SKYLIB_TAB + "%s == %s",
                   Virtual_Relation_e(Virtual_Relation_e::ALLY).As_String(),
                   From_Relation(Relation_e::ALLY)().As_String());
        SKYLIB_LOG(indent + SKYLIB_TAB + "%s == %s",
                   Virtual_Relation_e(Virtual_Relation_e::CONFIDANT).As_String(),
                   From_Relation(Relation_e::CONFIDANT)().As_String());
        SKYLIB_LOG(indent + SKYLIB_TAB + "%s == %s",
                   Virtual_Relation_e(Virtual_Relation_e::FRIEND).As_String(),
                   From_Relation(Relation_e::FRIEND)().As_String());
        SKYLIB_LOG(indent + SKYLIB_TAB + "%s == %s",
                   Virtual_Relation_e(Virtual_Relation_e::ACQUAINTANCE).As_String(),
                   From_Relation(Relation_e::ACQUAINTANCE)().As_String());
        SKYLIB_LOG(indent + SKYLIB_TAB + "%s == %s",
                   Virtual_Relation_e(Virtual_Relation_e::RIVAL).As_String(),
                   From_Relation(Relation_e::RIVAL)().As_String());
        SKYLIB_LOG(indent + SKYLIB_TAB + "%s == %s",
                   Virtual_Relation_e(Virtual_Relation_e::FOE).As_String(),
                   From_Relation(Relation_e::FOE)().As_String());
        SKYLIB_LOG(indent + SKYLIB_TAB + "%s == %s",
                   Virtual_Relation_e(Virtual_Relation_e::ENEMY).As_String(),
                   From_Relation(Relation_e::ENEMY)().As_String());
        SKYLIB_LOG(indent + SKYLIB_TAB + "%s == %s",
                   Virtual_Relation_e(Virtual_Relation_e::ARCHNEMESIS).As_String(),
                   From_Relation(Relation_e::ARCHNEMESIS)().As_String());
        SKYLIB_LOG(indent + SKYLIB_TAB + "%s == %s",
                   Virtual_Relation_e(Virtual_Relation_e::_NONE_).As_String(),
                   From_Relation(Relation_e::_NONE_)().As_String());

        SKYLIB_LOG(indent + "}");
    }

}
