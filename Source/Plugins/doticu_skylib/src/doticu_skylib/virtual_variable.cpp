/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.h"

#include "doticu_skylib/virtual_variable.inl"

namespace doticu_skylib { namespace Virtual {

    Variable_u::Variable_u() :
        ptr(nullptr)
    {
    }

    Variable_u::Variable_u(const Variable_u& other) :
        ptr(other.ptr)
    {
    }

    Variable_u::Variable_u(Variable_u&& other) noexcept :
        ptr(std::exchange(other.ptr, nullptr))
    {
    }

    Variable_u& Variable_u::operator =(const Variable_u& other)
    {
        if (this != std::addressof(other)) {
            this->ptr = other.ptr;
        }
        return *this;
    }

    Variable_u& Variable_u::operator =(Variable_u&& other) noexcept
    {
        if (this != std::addressof(other)) {
            this->ptr = std::exchange(other.ptr, nullptr);
        }
        return *this;
    }

    Variable_u::~Variable_u()
    {
        this->ptr = nullptr;
    }

    Variable_t::Variable_t() :
        type(Type_e()), data(Variable_u())
    {
    }

    Variable_t::Variable_t(const Variable_t& other)
    {
        if (this != &other) {
            Copy(other);
        }
    }

    Variable_t& Variable_t::operator=(const Variable_t& other)
    {
        if (this != &other) {
            Copy(other);
        }
        return *this;
    }

    Variable_t::~Variable_t()
    {
        Destroy();
    }

    void Variable_t::Destroy()
    {
        static auto destroy = reinterpret_cast
            <void (*)(Variable_t*)>
            (Game_t::Base_Address() + static_cast<Word_t>(Offset_e::DESTROY));

        destroy(this);
        type = Type_e();
        data = Variable_u();
    }

    void Variable_t::Copy(const Variable_t& other)
    {
        static auto copy = reinterpret_cast
            <void (*)(Variable_t*, const Variable_t&)>
            (Game_t::Base_Address() + static_cast<Word_t>(Offset_e::COPY));

        Destroy();
        copy(this, other);
    }

}}
