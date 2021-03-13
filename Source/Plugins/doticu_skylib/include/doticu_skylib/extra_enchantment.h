/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_data.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Enchantment_t;

    class Extra_Enchantment_t : // ExtraEnchantment
        public Extra_Data_t     // 00
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::ENCHANTMENT,
        };

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                V_TABLE = 0x0152C480, // 229574
            };
            using Enum_t::Enum_t;
        };

    public:
        static some<Extra_Enchantment_t*>   Create();
        static some<Extra_Enchantment_t*>   Create(maybe<Enchantment_t*> enchantment, u16 max_charge, Bool_t do_remove_on_unequip);
        static some<Extra_Enchantment_t*>   Create(const Extra_Enchantment_t& other);
        static void                         Destroy(some<Extra_Enchantment_t*> x_enchantment);

    public:
        virtual ~Extra_Enchantment_t(); // 0

    public:
        maybe<Enchantment_t*>   enchantment;            // 10
        u16                     max_charge;             // 18
        Bool_t                  do_remove_on_unequip;   // 1A
        u8                      pad_1B;                 // 1B
        u32                     pad_1C;                 // 1C

    public:
        maybe<Enchantment_t*>   Enchantment();
        void                    Enchantment(maybe<Enchantment_t*> enchantment);

    public:
        void Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Extra_Enchantment_t) == 0x20);

}
