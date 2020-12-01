/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/loaded_actor.h"

namespace doticu_skylib {

    Loaded_Actor_t::Loaded_Actor_t() :
        actor(nullptr), cell(nullptr)
    {
    }

    Loaded_Actor_t::Loaded_Actor_t(Actor_t* actor, Cell_t* cell) :
        actor(actor), cell(cell)
    {
        if (!actor || !cell) {
            actor = nullptr;
            cell = nullptr;
        }
    }

    Loaded_Actor_t::Loaded_Actor_t(Form_ID_t actor_form_id, Form_ID_t cell_form_id) :
        Loaded_Actor_t(static_cast<Actor_t*>(Game_t::Form(actor_form_id)),
                       static_cast<Cell_t*>(Game_t::Form(cell_form_id)))
    {
    }

    Loaded_Actor_t::Loaded_Actor_t(const Loaded_Actor_t& other) :
        Loaded_Actor_t(other.actor, other.cell)
    {
    }

    Loaded_Actor_t::Loaded_Actor_t(Loaded_Actor_t&& other) noexcept :
        actor(std::exchange(other.actor, nullptr)),
        cell(std::exchange(other.cell, nullptr))
    {
        if (!actor || !cell) {
            actor = nullptr;
            cell = nullptr;
        }
    }

    Loaded_Actor_t::~Loaded_Actor_t()
    {
        actor = nullptr;
        cell = nullptr;
    }

    Loaded_Actor_t& Loaded_Actor_t::operator=(const Loaded_Actor_t& other)
    {
        if (this != &other) {
            if (other.actor && other.cell) {
                actor = other.actor;
                cell = other.cell;
            } else {
                actor = nullptr;
                cell = nullptr;
            }
        }
        return *this;
    }

    Loaded_Actor_t& Loaded_Actor_t::operator=(Loaded_Actor_t&& other) noexcept
    {
        if (this != &other) {
            actor = std::exchange(other.actor, nullptr);
            cell = std::exchange(other.cell, nullptr);
            if (!actor || !cell) {
                actor = nullptr;
                cell = nullptr;
            }
        }
        return *this;
    }

    Bool_t Loaded_Actor_t::operator==(const Loaded_Actor_t& other)
    {
        return actor == other.actor && cell == other.cell;
    }

    Bool_t Loaded_Actor_t::operator!=(const Loaded_Actor_t& other)
    {
        return !operator==(other);
    }

    Bool_t Loaded_Actor_t::Is_Valid()
    {
        return actor && cell && actor->Is_Valid() && cell->Is_Valid();
    }

    Loaded_Actor_t::operator Bool_t()
    {
        return Is_Valid();
    }

}
