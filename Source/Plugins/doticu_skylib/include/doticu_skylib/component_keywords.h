/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Keyword_t;

    class Keywords_c : public Form_Data_c // BGSKeywordForm
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E10F28, // 513855
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual             ~Keywords_c();                          // 0

        virtual Bool_t      Has(const Keyword_t* keyword) const;    // 4
        virtual Keyword_t*  Default_Keyword() const;                // 5

        Keyword_t** keywords;       // 08
        u32         keyword_count;  // 10
        u32         pad_14;         // 14
    };
    STATIC_ASSERT(sizeof(Keywords_c) == 0x18);

}
