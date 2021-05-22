/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/virtual_latent_id.h"
#include "doticu_skylib/virtual_machine.h"
#include "doticu_skylib/virtual_variable.h"

namespace doticu_skylib { namespace Virtual {

    Latent_ID_t::Latent_ID_t(maybe<Stack_ID_t> stack_id) :
        stack_id(stack_id)
    {
    }

    Latent_ID_t::Latent_ID_t(Latent_ID_t&& other) noexcept :
        stack_id(std::exchange(other.stack_id, none<Stack_ID_t>()))
    {
    }

    Latent_ID_t& Latent_ID_t::operator =(Latent_ID_t&& other) noexcept
    {
        if (this != std::addressof(other)) {
            this->stack_id = std::exchange(other.stack_id, none<Stack_ID_t>());
        }
        return *this;
    }

    Latent_ID_t::~Latent_ID_t()
    {
        if (this->stack_id) {
            Return(Variable_t());
        }
    }

    void Latent_ID_t::Return(Variable_t& variable) const
    {
        SKYLIB_ASSERT(this->stack_id);
        Machine_t::Self()->Return_Latent_Function(stack_id(), variable);
        this->stack_id = none<Stack_ID_t>();
    }

    void Latent_ID_t::Return(Variable_t&& variable) const
    {
        Return(variable);
    }

    Latent_ID_t::operator Bool_t() const
    {
        return this->stack_id != none<Stack_ID_t>();
    }

}}
