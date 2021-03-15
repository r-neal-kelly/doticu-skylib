/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Reference_t;
    class Reference_Interaction_t;

    class Extra_Reference_Interaction_t :   // ExtraInteraction
        public Extra_Data_t                 // 00
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::REFERENCE_INTERACTION,
        };

        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                V_TABLE = 0x0152F540, // 229909
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Extra_Reference_Interaction_t(); // 0

    public:
        maybe<Reference_Interaction_t*> reference_interaction; // 10

    public:
        maybe<Reference_t*> Interactor_A();
        maybe<Reference_t*> Interactor_B();
    };
    STATIC_ASSERT(sizeof(Extra_Reference_Interaction_t) == 0x18);

}
