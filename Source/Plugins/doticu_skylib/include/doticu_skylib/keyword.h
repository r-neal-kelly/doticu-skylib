/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/form.h"
#include "doticu_skylib/script_type.h"

namespace doticu_skylib {

    class Keyword_t : public Form_t
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::KEYWORD,
            kTypeID     = SCRIPT_TYPE,
        };

    public:
        static Int_t Compare_Any_Names(Keyword_t** a, Keyword_t** b);

    public:
        virtual ~Keyword_t(); // 0

        String_t editor_id; // 20

        String_t Any_Name();
    };
    STATIC_ASSERT(sizeof(Keyword_t) == 0x28);

}
