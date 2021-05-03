/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/armor_set.h"
#include "doticu_skylib/math.h"

namespace doticu_skylib {

    Armor_Set_t::Armor_Set_t() :
        aura(none<Armor_t*>()),
        body(none<Armor_t*>()),
        feet(none<Armor_t*>()),
        finger(none<Armor_t*>()),
        forearm(none<Armor_t*>()),
        forehead(none<Armor_t*>()),
        hands(none<Armor_t*>()),
        head(none<Armor_t*>()),
        neck(none<Armor_t*>())
    {
    }

    Armor_Set_t::Armor_Set_t(const Armor_Set_t& other) :
        aura(other.aura),
        body(other.body),
        feet(other.feet),
        finger(other.finger),
        forearm(other.forearm),
        forehead(other.forehead),
        hands(other.hands),
        head(other.head),
        neck(other.neck)
    {
    }

    Armor_Set_t::Armor_Set_t(Armor_Set_t&& other) noexcept :
        aura(std::move(other.aura)),
        body(std::move(other.body)),
        feet(std::move(other.feet)),
        finger(std::move(other.finger)),
        forearm(std::move(other.forearm)),
        forehead(std::move(other.forehead)),
        hands(std::move(other.hands)),
        head(std::move(other.head)),
        neck(std::move(other.neck))
    {
    }

    Armor_Set_t& Armor_Set_t::operator =(const Armor_Set_t& other)
    {
        if (std::addressof(other) != this) {
            this->aura = other.aura;
            this->body = other.body;
            this->feet = other.feet;
            this->finger = other.finger;
            this->forearm = other.forearm;
            this->forehead = other.forehead;
            this->hands = other.hands;
            this->head = other.head;
            this->neck = other.neck;
        }
        return *this;
    }

    Armor_Set_t& Armor_Set_t::operator =(Armor_Set_t&& other) noexcept
    {
        if (std::addressof(other) != this) {
            this->aura = std::move(other.aura);
            this->body = std::move(other.body);
            this->feet = std::move(other.feet);
            this->finger = std::move(other.finger);
            this->forearm = std::move(other.forearm);
            this->forehead = std::move(other.forehead);
            this->hands = std::move(other.hands);
            this->head = std::move(other.head);
            this->neck = std::move(other.neck);
        }
        return *this;
    }

    Armor_Set_t::~Armor_Set_t()
    {
    }

    maybe<Armor_t*> Armor_Set_t::Aura(u8 probability_percent) const
    {
        return Math_t::Random_Bool(probability_percent) ? this->aura : none<Armor_t*>();
    }

    maybe<Armor_t*> Armor_Set_t::Body(u8 probability_percent) const
    {
        return Math_t::Random_Bool(probability_percent) ? this->body : none<Armor_t*>();
    }

    maybe<Armor_t*> Armor_Set_t::Feet(u8 probability_percent) const
    {
        return Math_t::Random_Bool(probability_percent) ? this->feet : none<Armor_t*>();
    }

    maybe<Armor_t*> Armor_Set_t::Finger(u8 probability_percent) const
    {
        return Math_t::Random_Bool(probability_percent) ? this->finger : none<Armor_t*>();
    }

    maybe<Armor_t*> Armor_Set_t::Forearm(u8 probability_percent) const
    {
        return Math_t::Random_Bool(probability_percent) ? this->forearm : none<Armor_t*>();
    }

    maybe<Armor_t*> Armor_Set_t::Forehead(u8 probability_percent) const
    {
        return Math_t::Random_Bool(probability_percent) ? this->forehead : none<Armor_t*>();
    }

    maybe<Armor_t*> Armor_Set_t::Hands(u8 probability_percent) const
    {
        return Math_t::Random_Bool(probability_percent) ? this->hands : none<Armor_t*>();
    }

    maybe<Armor_t*> Armor_Set_t::Head(u8 probability_percent) const
    {
        return Math_t::Random_Bool(probability_percent) ? this->head : none<Armor_t*>();
    }

    maybe<Armor_t*> Armor_Set_t::Neck(u8 probability_percent) const
    {
        return Math_t::Random_Bool(probability_percent) ? this->neck : none<Armor_t*>();
    }

}
