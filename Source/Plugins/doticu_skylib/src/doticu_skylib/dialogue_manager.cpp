/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/atomic.inl"
#include "doticu_skylib/dialogue_manager.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/reference.h"

namespace doticu_skylib {

    some<Dialogue_Manager_t*> Dialogue_Manager_t::Self()
    {
        static auto self = reinterpret_cast
            <Dialogue_Manager_t**>
            (Game_t::Base_Address() + Offset_e::SELF);

        SKYLIB_ASSERT(self && *self);

        return *self;
    }

    maybe<Reference_t*> Dialogue_Manager_t::Current_Speaker()
    {
        return Reference_t::From_Handle(Atomic_t::Access(this->current_speaker));
    }

    maybe<Dialogue_Info_t*> Dialogue_Manager_t::Current_Dialogue_Info()
    {
        return static_cast<Dialogue_Info_t*>
            (Atomic_t::Access(reinterpret_cast<const volatile void*&>(this->current_info)));
    }

}
