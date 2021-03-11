/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/virtual_handle.h"
#include "doticu_skylib/virtual_object.h"

namespace doticu_skylib {

    class Actor_Base_t;

}

namespace doticu_skylib { namespace Virtual {

    class Actor_Base_t
    {
    protected:
        some<doticu_skylib::Actor_Base_t*>  scriptable;
        some<Object_t*>                     object;

    public:
        Actor_Base_t(some<doticu_skylib::Actor_Base_t*> actor_base);
        Actor_Base_t(const Actor_Base_t& other);
        Actor_Base_t(Actor_Base_t&& other) noexcept;
        Actor_Base_t& operator =(const Actor_Base_t& other);
        Actor_Base_t& operator = (Actor_Base_t&& other) noexcept;
        ~Actor_Base_t();

    public:
        Bool_t      Is_Valid();
        Handle_t    Handle();

    public:
        void    Is_Protected(maybe<Callback_i*> v_callback);                            // IsProtected
        void    Is_Protected(maybe<unique<Callback_ii<Bool_t>>> callback);
        void    Is_Protected(Bool_t value, maybe<Callback_i*> v_callback);              // SetProtected
        void    Is_Protected(Bool_t value, maybe<unique<Callback_ii<>>> callback);

        void    Is_Essential(maybe<Callback_i*> v_callback);                            // IsEssential
        void    Is_Essential(maybe<unique<Callback_ii<Bool_t>>> callback);
        void    Is_Essential(Bool_t value, maybe<Callback_i*> v_callback);              // SetEssential
        void    Is_Essential(Bool_t value, maybe<unique<Callback_ii<>>> callback);

        void    Is_Invulnerable(maybe<Callback_i*> v_callback);                         // IsInvulnerable
        void    Is_Invulnerable(maybe<unique<Callback_ii<Bool_t>>> callback);
        void    Is_Invulnerable(Bool_t value, maybe<Callback_i*> v_callback);           // SetInvulnerable
        void    Is_Invulnerable(Bool_t value, maybe<unique<Callback_ii<>>> callback);
    };
    STATIC_ASSERT(sizeof(Actor_Base_t) == 0x10);

}}
