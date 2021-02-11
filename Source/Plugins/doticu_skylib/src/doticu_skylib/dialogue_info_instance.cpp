/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/dialogue_info_instance.h"
#include "doticu_skylib/game.h"

namespace doticu_skylib {

    Dialogue_Info_Instance_t::Dialogue_Info_Instance_t(some<Quest_t*> quest,
                                                       some<Dialogue_Topic_t*> topic,
                                                       some<Dialogue_Info_t*> info,
                                                       maybe<Actor_t*> speaker)
    {
        static auto ctor = reinterpret_cast
            <Dialogue_Info_Instance_t&(*)(Dialogue_Info_Instance_t*, Quest_t*, Dialogue_Topic_t*, Dialogue_Info_t*, Actor_t*)>
            (Game_t::Base_Address() + Offset_e::CTOR);

        SKYLIB_ASSERT_SOME(quest);
        SKYLIB_ASSERT_SOME(topic);
        SKYLIB_ASSERT_SOME(info);

        ctor(this, quest(), topic(), info(), speaker());
    }

}
