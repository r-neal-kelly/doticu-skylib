/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_type.h"

namespace doticu_skylib {

    class Data_x
    {
    public:
        template <typename Type_t>
        static Type_t*  Create();
        static void     Destroy(Data_x* xdata);

    public:
        virtual         ~Data_x();                          // 0

        virtual u8      Get_Type();                         // 1
        virtual Bool_t  Isnt_Equal(const Data_x* other);    // 2

        Data_x* next;

        Extra_Type_e Type();
    };
    STATIC_ASSERT(sizeof(Data_x) == 0x10);

}
