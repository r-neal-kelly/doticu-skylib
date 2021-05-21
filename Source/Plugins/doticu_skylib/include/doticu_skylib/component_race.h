/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Race_t;

    class Race_c :          // TESRaceForm
        public Form_Data_c  // 00
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E15550, // 513946
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Race_c(); // 0

    public:
        maybe<Race_t*>  race; // 00
    };
    STATIC_ASSERT(sizeof(Race_c) == 0x10);

}
