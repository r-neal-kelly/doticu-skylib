/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/interface.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/unique.h"

namespace doticu_skylib {

    class Actor_t;
    class Reference_t;

}

namespace doticu_skylib { namespace Virtual {

    class Callback_i;
    class Machine_t;

    class Game_t
    {
    public:
        static constexpr const char* SCRIPT_NAME = "Game";

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                SELF = 0x01EC3B78, // 514315
            };
            using Enum_t::Enum_t;
        };

    public:
        static some<Game_t*> Self();

    public:
        Byte_t              base_classes[0x200];    // 0000
        maybe<Machine_t*>   machine;                // 0200

    public:
        static void Current_Crosshair_Reference(some<Virtual::Callback_i*> v_callback);                                 // GetCurrentCrosshairRef
        static void Current_Crosshair_Reference(some<unique<doticu_skylib::Callback_i<maybe<Reference_t*>>>> callback);

        static void Find_Closest_Actor(Float_t origin_x,
                                       Float_t origin_y,
                                       Float_t origin_z,
                                       Float_t radius,
                                       some<Virtual::Callback_i*> v_callback);                                          // FindClosestActor
        static void Find_Closest_Actor(Float_t origin_x,
                                       Float_t origin_y,
                                       Float_t origin_z,
                                       Float_t radius,
                                       some<unique<doticu_skylib::Callback_i<maybe<Actor_t*>>>> callback);

        static void Find_Closest_Actor_From(some<Reference_t*> origin,
                                            Float_t radius,
                                            some<Virtual::Callback_i*> v_callback);                                     // FindClosestActorFromRef
        static void Find_Closest_Actor_From(some<Reference_t*> origin,
                                            Float_t radius,
                                            some<unique<doticu_skylib::Callback_i<maybe<Actor_t*>>>> callback);

        static void Force_First_Person(maybe<Virtual::Callback_i*> v_callback);                                         // ForceFirstPerson
        static void Force_First_Person(maybe<unique<doticu_skylib::Callback_i<>>> callback);

        static void Force_Third_Person(maybe<Virtual::Callback_i*> v_callback);                                         // ForceThirdPerson
        static void Force_Third_Person(maybe<unique<doticu_skylib::Callback_i<>>> callback);
    };

}}
