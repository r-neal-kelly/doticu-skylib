/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Actor_Base_t;
    class Faction_t;
    class Form_t;

    class Form_Owner_t
    {
    protected:
        maybe<Form_t*>  form;   // 00

    public:
        Form_Owner_t();
        Form_Owner_t(Form_t* form);
        Form_Owner_t(Actor_Base_t* actor_base);
        Form_Owner_t(Faction_t* faction);
        Form_Owner_t(std::nullptr_t form);
        Form_Owner_t(none<Form_t*> form);
        Form_Owner_t(none<Actor_Base_t*> actor_base);
        Form_Owner_t(none<Faction_t*> faction);
        Form_Owner_t(maybe<Form_t*> form);
        Form_Owner_t(maybe<Actor_Base_t*> actor_base);
        Form_Owner_t(maybe<Faction_t*> faction);
        Form_Owner_t(some<Form_t*> form);
        Form_Owner_t(some<Actor_Base_t*> actor_base);
        Form_Owner_t(some<Faction_t*> faction);
        Form_Owner_t(const Form_Owner_t& other);
        Form_Owner_t(Form_Owner_t&& other) noexcept;
        Form_Owner_t& operator =(const Form_Owner_t& other);
        Form_Owner_t& operator =(Form_Owner_t&& other) noexcept;
        ~Form_Owner_t();

    public:
        Bool_t                  Is_Actor_Base() const;
        Bool_t                  Is_Faction() const;

        maybe<Form_t*>          As_Form() const;
        maybe<Actor_Base_t*>    As_Actor_Base() const;
        maybe<Faction_t*>       As_Faction() const;

    public:
        explicit operator Bool_t() const;

    public:
        maybe<Form_t*> operator ()() const;

    public:
        void    Log(std::string indent = "") const;
    };
    STATIC_ASSERT(sizeof(Form_Owner_t) == 0x8);

}
