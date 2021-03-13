/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Extra_Charge_t :  // ExtraCharge
        public Extra_Data_t // 00
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::CHARGE,
        };

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                V_TABLE = 0x0152C0C0, // 229544
            };
            using Enum_t::Enum_t;
        };

    public:
        static some<Extra_Charge_t*>    Create();
        static some<Extra_Charge_t*>    Create(Float_t charge);
        static some<Extra_Charge_t*>    Create(const Extra_Charge_t& other);
        static void                     Destroy(some<Extra_Charge_t*> x_charge);

    public:
        virtual ~Extra_Charge_t(); // 0

    public:
        Float_t charge; // 10
        u32     pad_14; // 14

    public:
        Float_t Charge();
        void    Charge(Float_t charge);

    public:
        void Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Extra_Charge_t) == 0x18);

}
