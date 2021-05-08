/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/alias_reference.h"
#include "doticu_skylib/reference.h"
#include "doticu_skylib/scrap_array.inl"
#include "doticu_skylib/virtual_arguments.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_machine.inl"
#include "doticu_skylib/virtual_variable.inl"

namespace doticu_skylib {

    void Alias_Reference_t::Unfill(Vector_t<some<Alias_Reference_t*>>&& aliases, maybe<unique<Callback_i<>>> callback)
    {
        using Callback = maybe<unique<Callback_i<>>>;

        class Virtual_Callback :
            public Virtual::Callback_t
        {
        public:
            const Vector_t<some<Alias_Reference_t*>>    aliases;
            const size_t                                idx;
            const size_t                                end;
            Callback                                    callback;

        public:
            Virtual_Callback(const Vector_t<some<Alias_Reference_t*>>&& aliases,
                             const size_t idx,
                             const size_t end,
                             Callback callback) :
                aliases(std::move(aliases)),
                idx(idx),
                end(end),
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator ()(Virtual::Variable_t*) override
            {
                if (this->idx < this->end) {
                    SKYLIB_ASSERT_SOME(this->aliases[this->idx]);
                    this->aliases[this->idx]->Unfill(
                        new Virtual_Callback(std::move(this->aliases), this->idx + 1, this->end, std::move(this->callback))
                    );
                } else {
                    if (this->callback) {
                        (*this->callback)();
                    }
                }
            }
        };

        const size_t idx = 0;
        const size_t end = aliases.size();
        if (idx < end) {
            SKYLIB_ASSERT_SOME(aliases[0]);
            aliases[0]->Unfill(new Virtual_Callback(std::move(aliases), idx + 1, end, std::move(callback)));
        } else {
            if (callback) {
                (*callback)();
            }
        }
    }

    void Alias_Reference_t::Fill(some<Reference_t*> reference, maybe<Virtual::Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Virtual::Arguments_t
        {
        public:
            some<Reference_t*> reference;

        public:
            Virtual_Arguments(some<Reference_t*> reference) :
                reference(reference)
            {
            }

        public:
            virtual Bool_t operator()(Scrap_Array_t<Virtual::Variable_t>* args) override
            {
                args->Resize(1);
                args->At(0).As<Reference_t*>(reference());
                return true;
            }
        };

        SKYLIB_ASSERT_SOME(reference);

        Virtual::Machine_t::Ready_Scriptable<Alias_Reference_t*>(this);
        Virtual::Machine_t::Self()->Call_Method(
            this,
            SCRIPT_NAME,
            "ForceRefTo",
            Virtual_Arguments(reference),
            v_callback
        );
    }

    void Alias_Reference_t::Fill(some<Reference_t*> reference, maybe<unique<Callback_i<>>> callback)
    {
        using Callback = maybe<unique<Callback_i<>>>;

        class Virtual_Callback :
            public Virtual::Callback_t
        {
        public:
            Callback callback;

        public:
            Virtual_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator()(Virtual::Variable_t*) override
            {
                if (this->callback) {
                    (*this->callback)();
                }
            }
        };

        SKYLIB_ASSERT_SOME(reference);

        Fill(reference, new Virtual_Callback(std::move(callback)));
    }

    void Alias_Reference_t::Unfill(maybe<Virtual::Callback_i*> v_callback)
    {
        Virtual::Machine_t::Ready_Scriptable<Alias_Reference_t*>(this);
        Virtual::Machine_t::Self()->Call_Method(
            this,
            SCRIPT_NAME,
            "Clear",
            none<Virtual::Arguments_i*>(),
            v_callback
        );
    }

    void Alias_Reference_t::Unfill(maybe<unique<Callback_i<>>> callback)
    {
        using Callback = maybe<unique<Callback_i<>>>;

        class Virtual_Callback :
            public Virtual::Callback_t
        {
        public:
            Callback callback;

        public:
            Virtual_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator()(Virtual::Variable_t*) override
            {
                if (this->callback) {
                    (*this->callback)();
                }
            }
        };

        Unfill(new Virtual_Callback(std::move(callback)));
    }

    void Alias_Reference_t::To_Reference(some<Virtual::Callback_i*> v_callback)
    {
        SKYLIB_ASSERT_SOME(v_callback);

        Virtual::Machine_t::Ready_Scriptable<Alias_Reference_t*>(this);
        Virtual::Machine_t::Self()->Call_Method(
            this,
            SCRIPT_NAME,
            "GetReference",
            none<Virtual::Arguments_i*>(),
            v_callback()
        );
    }

    void Alias_Reference_t::To_Reference(some<unique<Callback_i<maybe<Reference_t*>>>> callback)
    {
        using Callback = some<unique<Callback_i<maybe<Reference_t*>>>>;

        class Virtual_Callback :
            public Virtual::Callback_t
        {
        public:
            Callback callback;

        public:
            Virtual_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator()(Virtual::Variable_t* result) override
            {
                (*this->callback)(result ? result->As<Reference_t*>() : nullptr);
            }
        };

        SKYLIB_ASSERT_SOME(callback);

        To_Reference(new Virtual_Callback(std::move(callback)));
    }

}
