/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/interface.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/unique.h"

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
        void Force_First_Person(maybe<Virtual::Callback_i*> v_callback = nullptr);              // ForceFirstPerson
        void Force_First_Person(maybe<unique<doticu_skylib::Callback_i<>>> callback = nullptr); // ForceFirstPerson

        void Force_Third_Person(maybe<Virtual::Callback_i*> v_callback = nullptr);              // ForceThirdPerson
        void Force_Third_Person(maybe<unique<doticu_skylib::Callback_i<>>> callback = nullptr); // ForceThirdPerson
    };

}}
