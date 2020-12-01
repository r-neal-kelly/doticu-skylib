/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

namespace doticu_skylib {

    class Form_Data_c // BaseFormComponent
    {
    public:
        virtual ~Form_Data_c(); // 0

        virtual void _01(void); // 1
        virtual void _02(void); // 2
        virtual void _03(void); // 3
    };
    STATIC_ASSERT(sizeof(Form_Data_c) == 0x8);

}
