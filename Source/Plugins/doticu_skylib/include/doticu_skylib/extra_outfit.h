/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_data.h"
#include "doticu_skylib/form_id.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Outfit_t;

    class Extra_Outfit_t :  // ExtraOutfitItem
        public Extra_Data_t // 00
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
                V_TABLE = 0x0152C1E0, // 229553
            };
            using Enum_t::Enum_t;
        };

    public:
        static some<Extra_Outfit_t*>    Create(some<Outfit_t*> outfit);
        static void                     Destroy(some<Extra_Outfit_t*> x_outfit);

    public:
        virtual ~Extra_Outfit_t(); // 0

    public:
        maybe<Form_ID_t>    outfit_form_id; // 10
        u32                 pad_14;         // 14
    };
    STATIC_ASSERT(sizeof(Extra_Outfit_t) == 0x18);

}
