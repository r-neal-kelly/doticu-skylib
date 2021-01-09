/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/form_id.h"

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Outfit_x : public Data_x // ExtraOutfitItem
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::OUTFIT,
        };

        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                V_TABLE = 0x0152C1E0,
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Outfit_x();

    public:
        Form_ID_t   outfit_form_id; // 10 (Outfit_t)
        u32         pad_14;         // 14
    };
    STATIC_ASSERT(sizeof(Outfit_x) == 0x18);

}
