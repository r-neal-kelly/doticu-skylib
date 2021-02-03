/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/atomic_count.h"
#include "doticu_skylib/movement_register_controller.h"

namespace doticu_skylib {

    class Movement_AI_Controller_t :            // MovementControllerAI
        public Atomic_Count_t,                  // 008
        public Movement_Register_Controller_i   // 000
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E41208, // 686945
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual         ~Movement_AI_Controller_t();    // 0

        // Movement_AI_Controller_t
        virtual void    _5(void);                       // 5
        virtual void    _6(void);                       // 6
        virtual void    _7(void);                       // 7
        virtual void    _8(void);                       // 8
        virtual void    _9(void);                       // 9

    public:
        u32     pad_014;            // 014
        Byte_t  data_010[0x108];    // 018
    };
    STATIC_ASSERT(sizeof(Movement_AI_Controller_t) == 0x120);

}
