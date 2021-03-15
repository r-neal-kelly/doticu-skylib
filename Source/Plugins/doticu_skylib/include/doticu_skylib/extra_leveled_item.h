/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_data.h"
#include "doticu_skylib/form_id.h"

namespace doticu_skylib {

    class Leveled_Item_t;

    class Extra_Leveled_Item_t :    // ExtraLeveledItem
        public Extra_Data_t         // 00
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::LEVELED_ITEM,
        };

        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                V_TABLE = 0x0152C1C0, // 229552
            };
            using Enum_t::Enum_t;
        };

    public:
        static some<Extra_Leveled_Item_t*>  Create(some<Leveled_Item_t*> leveled_item);
        static void                         Destroy(some<Extra_Leveled_Item_t*> x_leveled_item);

    public:
        virtual ~Extra_Leveled_Item_t(); // 0

    public:
        maybe<Form_ID_t>    leveled_item_form_id;   // 10
        u32                 pad_14;                 // 14
    };
    STATIC_ASSERT(sizeof(Extra_Leveled_Item_t) == 0x18);

}
