/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/enum_virtual_relation.h"

namespace doticu_skylib {

    Bool_t Virtual_Relation_e::Is_Valid(enum_type value)
    {
        return value <= LOVER && value >= ARCHNEMESIS;
    }

    Bool_t Virtual_Relation_e::Is_Valid(value_type value)
    {
        return Is_Valid(static_cast<enum_type>(value));
    }

    maybe<Relation_e> Virtual_Relation_e::To_Relation(Virtual_Relation_e::enum_type v_relation)
    {
        return To_Relation(maybe<Virtual_Relation_e>(v_relation));
    }

    maybe<Relation_e> Virtual_Relation_e::To_Relation(Virtual_Relation_e::value_type v_relation)
    {
        return To_Relation(maybe<Virtual_Relation_e>(v_relation));
    }

    maybe<Relation_e> Virtual_Relation_e::To_Relation(Virtual_Relation_e v_relation)
    {
        return To_Relation(maybe<Virtual_Relation_e>(v_relation));
    }

    maybe<Relation_e> Virtual_Relation_e::To_Relation(maybe<Virtual_Relation_e> v_relation)
    {
        if (v_relation) {
            return To_Relation(some<Virtual_Relation_e>(v_relation()));
        } else {
            return Relation_e::_NONE_;
        }
    }

    some<Relation_e> Virtual_Relation_e::To_Relation(some<Virtual_Relation_e> v_relation)
    {
        SKYLIB_ASSERT_SOME(v_relation);

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
    }

    maybe<Virtual_Relation_e> Virtual_Relation_e::From_Relation(Relation_e::enum_type relation)
    {
        return From_Relation(maybe<Relation_e>(relation));
    }

    maybe<Virtual_Relation_e> Virtual_Relation_e::From_Relation(Relation_e::value_type relation)
    {
        return From_Relation(maybe<Relation_e>(relation));
    }

    maybe<Virtual_Relation_e> Virtual_Relation_e::From_Relation(Relation_e relation)
    {
        return From_Relation(maybe<Relation_e>(relation));
    }

    maybe<Virtual_Relation_e> Virtual_Relation_e::From_Relation(maybe<Relation_e> relation)
    {
        if (relation) {
            return From_Relation(some<Relation_e>(relation()));
        } else {
            return Virtual_Relation_e::_NONE_;
        }
    }

    some<Virtual_Relation_e> Virtual_Relation_e::From_Relation(some<Relation_e> relation)
    {
        SKYLIB_ASSERT_SOME(relation);

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
        Enum_t(Is_Valid(value) ? value : _NONE_)
    {
    }

    Virtual_Relation_e::Virtual_Relation_e(value_type value) :
        Virtual_Relation_e(static_cast<enum_type>(value))
    {
    }

    Virtual_Relation_e::Virtual_Relation_e(const Virtual_Relation_e& other) :
        Enum_t(other)
    {
    }

    Virtual_Relation_e::Virtual_Relation_e(Virtual_Relation_e&& other) noexcept :
        Enum_t(std::move(other))
    {
    }

    Virtual_Relation_e& Virtual_Relation_e::operator =(const Virtual_Relation_e& other)
    {
        return static_cast<Virtual_Relation_e&>(Enum_t::operator =(other));
    }

    Virtual_Relation_e& Virtual_Relation_e::operator =(Virtual_Relation_e&& other) noexcept
    {
        return static_cast<Virtual_Relation_e&>(Enum_t::operator =(std::move(other)));
    }

    Virtual_Relation_e::~Virtual_Relation_e()
    {
        this->value = _NONE_;
    }

    maybe<Relation_e> Virtual_Relation_e::As_Relation() const
    {
        return To_Relation(*this);
    }

    some<const char*> Virtual_Relation_e::As_String() const
    {
        return To_String(*this);
    }

    Virtual_Relation_e::operator Bool_t() const
    {
        return Is_Valid(this->value);
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
