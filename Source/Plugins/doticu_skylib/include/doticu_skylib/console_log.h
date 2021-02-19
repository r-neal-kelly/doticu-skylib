/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/string.h"

namespace doticu_skylib {

    class Console_Log_t // ConsoleLog
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                SELF    = 0x02F000F0, // 515064
                PRINT   = 0x0085C2C0, // 50180
            };
            using Enum_t::Enum_t;
        };

    public:
        static some<Console_Log_t*> Self();

    public:
        u8                  pad_000;                // 000
        char                last_message[0x400];    // 001
        u8                  pad_401;                // 401
        u16                 pad_402;                // 402
        u32                 pad_404;                // 404
        Dynamic_String_t    buffer;                 // 408

    public:
        void Print(const char* formatted_string, ...);
    };
    STATIC_ASSERT(sizeof(Console_Log_t) == 0x418);

}
