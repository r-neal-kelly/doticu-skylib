/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/keyword.h"

namespace doticu_skylib {

    class Location_Reference_Type_t : public Keyword_t
    {
    public:
        enum
        {
            FORM_TYPE   = Form_Type_e::LOCATION_REFERENCE_TYPE,
            kTypeID     = FORM_TYPE,
        };

    public:
        virtual ~Location_Reference_Type_t(); // 0
    };
    STATIC_ASSERT(sizeof(Keyword_t) == 0x28);

}
