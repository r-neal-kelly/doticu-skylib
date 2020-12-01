/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

#include "doticu_skylib/form_id.h"

namespace doticu_skylib {

    class Actor_t;
    class Cell_t;

    class Loaded_Actor_t
    {
    public:
        Actor_t*    actor;
        Cell_t*     cell;

        Loaded_Actor_t();
        Loaded_Actor_t(Actor_t* actor, Cell_t* cell);
        Loaded_Actor_t(Form_ID_t actor_form_id, Form_ID_t cell_form_id);
        Loaded_Actor_t(const Loaded_Actor_t& other);
        Loaded_Actor_t(Loaded_Actor_t&& other) noexcept;
        ~Loaded_Actor_t();

        Loaded_Actor_t& operator=(const Loaded_Actor_t& other);
        Loaded_Actor_t& operator=(Loaded_Actor_t&& other) noexcept;
        Bool_t operator==(const Loaded_Actor_t& other);
        Bool_t operator!=(const Loaded_Actor_t& other);

        Bool_t Is_Valid();

        operator Bool_t();
    };
    STATIC_ASSERT(sizeof(Loaded_Actor_t) == 0x10);

}
