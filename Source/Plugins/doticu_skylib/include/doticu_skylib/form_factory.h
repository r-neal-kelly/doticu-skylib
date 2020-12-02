/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "doticu_skylib/form_type.h"

namespace doticu_skylib {

    class Form_t;

    class Form_Factory_i
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : Word_t
            {
                IS_CREATED  = 0x01EC3CB3,
                FACTORIES   = 0x01EC3CE0,
            };
            using Enum_t::Enum_t;
        };

    public:
        static Form_Factory_i* Form_Factory(Form_Type_e form_type);

    public:
        virtual ~Form_Factory_i(); // 00
        virtual Form_t* Create(); // 01
    };

}
