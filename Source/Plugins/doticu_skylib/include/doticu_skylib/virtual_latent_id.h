/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"
#include "doticu_skylib/virtual.h"
#include "doticu_skylib/virtual_stack_id.h"

namespace doticu_skylib { namespace Virtual {

    class Latent_ID_t
    {
    protected:
        mutable maybe<Stack_ID_t> stack_id;

    public:
        Latent_ID_t(maybe<Stack_ID_t> stack_id);
        Latent_ID_t(const Latent_ID_t& other)                   = delete;
        Latent_ID_t(Latent_ID_t&& other) noexcept;
        Latent_ID_t& operator=(const Latent_ID_t& other)        = delete;
        Latent_ID_t& operator=(Latent_ID_t&& other) noexcept;
        ~Latent_ID_t();

    public:
        void Return(Variable_t& variable) const;
        void Return(Variable_t&& variable) const;

    public:
        operator Bool_t() const;
    };

}}
