/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/console_log.h"
#include "doticu_skylib/game.h"

namespace doticu_skylib {

    some<Console_Log_t*> Console_Log_t::Self()
    {
        static auto self = *reinterpret_cast
            <Console_Log_t**>
            (Game_t::Base_Address() + Offset_e::SELF);

        SKYLIB_ASSERT(self);
        return self;
    }

    void Console_Log_t::Print(const char* formatted_string, ...)
    {
        static auto print = reinterpret_cast
            <void(*)(Console_Log_t*, const char*, std::va_list)>
            (Game_t::Base_Address() + Offset_e::PRINT);

        std::va_list arguments;
        va_start(arguments, formatted_string);
        print(this, formatted_string, arguments);
        va_end(arguments);
    }

}
