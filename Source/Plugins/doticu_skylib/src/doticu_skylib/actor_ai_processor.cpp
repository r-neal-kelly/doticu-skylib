/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor_ai_processor.h"
#include "doticu_skylib/game.h"

namespace doticu_skylib {

    some<Actor_AI_Processor_t*> Actor_AI_Processor_t::Self()
    {
        static auto self = reinterpret_cast
            <Actor_AI_Processor_t**>
            (Game_t::Base_Address() + Offset_e::SELF);

        SKYLIB_ASSERT(self && *self);

        return *self;
    }

    void Actor_AI_Processor_t::Stop_Combat_And_Alarm(some<Actor_t*> actor, Bool_t stop_combat_only)
    {
        static auto stop_combat_and_alarm = reinterpret_cast
            <void(*)(Actor_AI_Processor_t*, Actor_t*, Bool_t)>
            (Game_t::Base_Address() + Offset_e::STOP_COMBAT_AND_ALARM);

        SKYLIB_ASSERT_SOME(actor);

        return stop_combat_and_alarm(this, actor(), stop_combat_only);
    }

}
