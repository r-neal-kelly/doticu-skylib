/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/utils.h"
#include "doticu_skylib/virtual_arguments.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_machine.h"

namespace doticu_skylib { namespace Virtual {

    Machine_t* Machine_t::Self() // use address library here
    {
        static Machine_t* machine =
            reinterpret_cast<Machine_t*>((*g_skyrimVM)->GetClassRegistry());
        SKYLIB_ASSERT(machine);
        return machine;
    }

    Bool_t Machine_t::Call_Global(String_t class_name,
                                  String_t function_name,
                                  Arguments_i* arguments,
                                  Callback_i** vcallback)
    {
        if (!vcallback || !*vcallback) {
            Callback_i* default_vcallback = new Callback_t();
            vcallback = &default_vcallback;
        }
        if (arguments) {
            return Call_Global(&class_name, &function_name, arguments, vcallback);
        } else {
            Arguments_t default_arguments;
            return Call_Global(&class_name, &function_name, &default_arguments, vcallback);
        }
    }

    Bool_t Machine_t::Call_Method(Handle_t handle,
                                  String_t class_name,
                                  String_t function_name,
                                  Arguments_i* arguments,
                                  Callback_i** vcallback)
    {
        if (!vcallback || !*vcallback) {
            Callback_i* default_vcallback = new Callback_t();
            vcallback = &default_vcallback;
        }
        if (arguments) {
            return Call_Method2(handle, &class_name, &function_name, arguments, vcallback);
        } else {
            Arguments_t default_arguments;
            return Call_Method2(handle, &class_name, &function_name, &default_arguments, vcallback);
        }
    }

}}
