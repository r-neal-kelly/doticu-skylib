/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/atomic_count.h"
#include "doticu_skylib/enum.h"
#include "doticu_skylib/movement_register_controller.h"

namespace doticu_skylib {

    class Movement_Register_Controller_i // IMovementControllerRegisterInterface
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E41238, // 686946
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual         ~Movement_Register_Controller_i();  // 0

        virtual void    _1(void);                           // 1
        virtual void    _2(void);                           // 2
        virtual void    _3(void);                           // 3
        virtual void    _4(void);                           // 4
    };
    STATIC_ASSERT(sizeof(Movement_Register_Controller_i) == 0x8);

}
