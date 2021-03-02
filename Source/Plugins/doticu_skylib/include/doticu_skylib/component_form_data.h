/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Actor_Base_t;
    class Form_t;

    class Form_Data_c // BaseFormComponent
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E10DE0, // 513847
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual         ~Form_Data_c(); // 0
        virtual void    _01(void);      // 1
        virtual void    _02(void);      // 2
        virtual void    _03(void);      // 3

    public:
        Bool_t                  Component_Is_Actor_Base();
        Bool_t                  Component_Is_Form();

        maybe<Actor_Base_t*>    Component_As_Actor_Base();
        maybe<Form_t*>          Component_As_Form();

    public:
        Bool_t  Component_Flag_Form_Change(u32 flag);
        void    Component_Unflag_Form_Change(u32 flag);
    };
    STATIC_ASSERT(sizeof(Form_Data_c) == 0x8);

}
