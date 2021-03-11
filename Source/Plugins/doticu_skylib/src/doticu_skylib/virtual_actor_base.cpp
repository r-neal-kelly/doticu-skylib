/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/virtual_actor_base.h"
#include "doticu_skylib/virtual_arguments.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_machine.h"
#include "doticu_skylib/virtual_variable.h"

namespace doticu_skylib { namespace Virtual {

    Actor_Base_t::Actor_Base_t(some<doticu_skylib::Actor_Base_t*> actor_base) :
        scriptable(actor_base), object(Object_t::Find_Or_Create(actor_base(), false)())
    {
        SKYLIB_ASSERT(Is_Valid());
    }

    Actor_Base_t::Actor_Base_t(const Actor_Base_t& other) :
        scriptable(other.scriptable), object(other.object)
    {
        SKYLIB_ASSERT(Is_Valid());

        this->object->Increment_Lock();
    }

    Actor_Base_t::Actor_Base_t(Actor_Base_t&& other) noexcept :
        scriptable(std::move(other.scriptable)), object(std::move(other.object))
    {
        SKYLIB_ASSERT(Is_Valid());
    }

    Actor_Base_t& Actor_Base_t::operator =(const Actor_Base_t& other)
    {
        if (this != std::addressof(other)) {
            this->scriptable = other.scriptable;
            this->object = other.object;

            SKYLIB_ASSERT(Is_Valid());

            this->object->Increment_Lock();
        }
        return *this;
    }

    Actor_Base_t& Actor_Base_t::operator =(Actor_Base_t&& other) noexcept
    {
        if (this != std::addressof(other)) {
            this->scriptable = std::move(other.scriptable);
            this->object = std::move(other.object);

            SKYLIB_ASSERT(Is_Valid());
        }
        return *this;
    }

    Actor_Base_t::~Actor_Base_t()
    {
        if (Is_Valid()) {
            this->object->Decrement_Lock();
        }
    }

    Bool_t Actor_Base_t::Is_Valid()
    {
        return this->scriptable && this->object;
    }

    Handle_t Actor_Base_t::Handle()
    {
        SKYLIB_ASSERT(Is_Valid());

        return this->object->Handle();
    }

    void Actor_Base_t::Is_Protected(maybe<Callback_i*> v_callback)
    {
        Machine_t::Self()->Call_Method(
            Handle(),
            doticu_skylib::Actor_Base_t::SCRIPT_NAME,
            "IsProtected",
            none<Arguments_i*>(),
            v_callback
        );
    }

    void Actor_Base_t::Is_Protected(maybe<unique<Callback_ii<Bool_t>>> callback)
    {
        using Callback = maybe<unique<Callback_ii<Bool_t>>>;

        class Virtual_Callback :
            public Callback_t
        {
        public:
            Callback callback;

        public:
            Virtual_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator()(Variable_t* result) override
            {
                if (this->callback) {
                    (*this->callback)(result ? result->As<Bool_t>() : false);
                }
            }
        };

        Is_Protected(new Virtual_Callback(std::move(callback)));
    }

    void Actor_Base_t::Is_Protected(Bool_t value, maybe<Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Arguments_t
        {
        public:
            Bool_t value;

        public:
            Virtual_Arguments(Bool_t value) :
                value(value)
            {
            }

        public:
            virtual Bool_t operator()(Scrap_Array_t<Variable_t>* args) override
            {
                args->Resize(1);
                args->At(0).As<Bool_t>(this->value);
                return true;
            }
        };

        Machine_t::Self()->Call_Method(
            Handle(),
            doticu_skylib::Actor_Base_t::SCRIPT_NAME,
            "SetProtected",
            Virtual_Arguments(value),
            v_callback
        );
    }

    void Actor_Base_t::Is_Protected(Bool_t value, maybe<unique<Callback_ii<>>> callback)
    {
        using Callback = maybe<unique<Callback_ii<>>>;

        class Virtual_Callback :
            public Callback_t
        {
        public:
            Callback callback;

        public:
            Virtual_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator()(Variable_t*) override
            {
                if (this->callback) {
                    (*this->callback)();
                }
            }
        };

        Is_Protected(value, new Virtual_Callback(std::move(callback)));
    }

    void Actor_Base_t::Is_Essential(maybe<Callback_i*> v_callback)
    {
        Machine_t::Self()->Call_Method(
            Handle(),
            doticu_skylib::Actor_Base_t::SCRIPT_NAME,
            "IsEssential",
            none<Arguments_i*>(),
            v_callback
        );
    }

    void Actor_Base_t::Is_Essential(maybe<unique<Callback_ii<Bool_t>>> callback)
    {
        using Callback = maybe<unique<Callback_ii<Bool_t>>>;

        class Virtual_Callback :
            public Callback_t
        {
        public:
            Callback callback;

        public:
            Virtual_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator()(Variable_t* result) override
            {
                if (this->callback) {
                    (*this->callback)(result ? result->As<Bool_t>() : false);
                }
            }
        };

        Is_Essential(new Virtual_Callback(std::move(callback)));
    }

    void Actor_Base_t::Is_Essential(Bool_t value, maybe<Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Arguments_t
        {
        public:
            Bool_t value;

        public:
            Virtual_Arguments(Bool_t value) :
                value(value)
            {
            }

        public:
            virtual Bool_t operator()(Scrap_Array_t<Variable_t>* args) override
            {
                args->Resize(1);
                args->At(0).As<Bool_t>(this->value);
                return true;
            }
        };

        Machine_t::Self()->Call_Method(
            Handle(),
            doticu_skylib::Actor_Base_t::SCRIPT_NAME,
            "SetEssential",
            Virtual_Arguments(value),
            v_callback
        );
    }

    void Actor_Base_t::Is_Essential(Bool_t value, maybe<unique<Callback_ii<>>> callback)
    {
        using Callback = maybe<unique<Callback_ii<>>>;

        class Virtual_Callback :
            public Callback_t
        {
        public:
            Callback callback;

        public:
            Virtual_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator()(Variable_t*) override
            {
                if (this->callback) {
                    (*this->callback)();
                }
            }
        };

        Is_Essential(value, new Virtual_Callback(std::move(callback)));
    }

    void Actor_Base_t::Is_Invulnerable(maybe<Callback_i*> v_callback)
    {
        Machine_t::Self()->Call_Method(
            Handle(),
            doticu_skylib::Actor_Base_t::SCRIPT_NAME,
            "IsInvulnerable",
            none<Arguments_i*>(),
            v_callback
        );
    }

    void Actor_Base_t::Is_Invulnerable(maybe<unique<Callback_ii<Bool_t>>> callback)
    {
        using Callback = maybe<unique<Callback_ii<Bool_t>>>;

        class Virtual_Callback :
            public Callback_t
        {
        public:
            Callback callback;

        public:
            Virtual_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator()(Variable_t* result) override
            {
                if (this->callback) {
                    (*this->callback)(result ? result->As<Bool_t>() : false);
                }
            }
        };

        Is_Invulnerable(new Virtual_Callback(std::move(callback)));
    }

    void Actor_Base_t::Is_Invulnerable(Bool_t value, maybe<Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Arguments_t
        {
        public:
            Bool_t value;

        public:
            Virtual_Arguments(Bool_t value) :
                value(value)
            {
            }

        public:
            virtual Bool_t operator()(Scrap_Array_t<Variable_t>* args) override
            {
                args->Resize(1);
                args->At(0).As<Bool_t>(this->value);
                return true;
            }
        };

        Machine_t::Self()->Call_Method(
            Handle(),
            doticu_skylib::Actor_Base_t::SCRIPT_NAME,
            "SetInvulnerable",
            Virtual_Arguments(value),
            v_callback
        );
    }

    void Actor_Base_t::Is_Invulnerable(Bool_t value, maybe<unique<Callback_ii<>>> callback)
    {
        using Callback = maybe<unique<Callback_ii<>>>;

        class Virtual_Callback :
            public Callback_t
        {
        public:
            Callback callback;

        public:
            Virtual_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator()(Variable_t*) override
            {
                if (this->callback) {
                    (*this->callback)();
                }
            }
        };

        Is_Invulnerable(value, new Virtual_Callback(std::move(callback)));
    }

}}
