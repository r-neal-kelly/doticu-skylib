/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Armor_t;

    class Armor_Set_t
    {
    public:
        maybe<Armor_t*> aura;
        maybe<Armor_t*> body;
        maybe<Armor_t*> feet;
        maybe<Armor_t*> finger;
        maybe<Armor_t*> forearm;
        maybe<Armor_t*> forehead;
        maybe<Armor_t*> hands;
        maybe<Armor_t*> head;
        maybe<Armor_t*> neck;

    public:
        Armor_Set_t();
        Armor_Set_t(const Armor_Set_t& other);
        Armor_Set_t(Armor_Set_t&& other) noexcept;
        Armor_Set_t& operator =(const Armor_Set_t& other);
        Armor_Set_t& operator =(Armor_Set_t&& other) noexcept;
        ~Armor_Set_t();

    public:
        maybe<Armor_t*> Aura(u8 probability_percent) const;
        maybe<Armor_t*> Body(u8 probability_percent) const;
        maybe<Armor_t*> Feet(u8 probability_percent) const;
        maybe<Armor_t*> Finger(u8 probability_percent) const;
        maybe<Armor_t*> Forearm(u8 probability_percent) const;
        maybe<Armor_t*> Forehead(u8 probability_percent) const;
        maybe<Armor_t*> Hands(u8 probability_percent) const;
        maybe<Armor_t*> Head(u8 probability_percent) const;
        maybe<Armor_t*> Neck(u8 probability_percent) const;
    };
    STATIC_ASSERT(sizeof(Armor_Set_t) == 0x48);

}
