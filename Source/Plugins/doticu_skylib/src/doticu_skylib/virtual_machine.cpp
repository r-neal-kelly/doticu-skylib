/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/virtual_arguments.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_game.h"
#include "doticu_skylib/virtual_machine.h"

namespace doticu_skylib { namespace Virtual {

    some<Machine_t*> Machine_t::Self()
    {
        static maybe<Machine_t*> self = Virtual::Game_t::Self()->machine;
        SKYLIB_ASSERT(self);
        return self();
    }

    Bool_t Machine_t::Call_Global(String_t class_name,
                                  String_t function_name,
                                  Arguments_i* arguments,
                                  Callback_i** vcallback)
    {
        Callback_i* default_vcallback;
        if (!vcallback || !*vcallback) {
            default_vcallback = new Callback_t();
            vcallback = &default_vcallback;
        }
        if (arguments) {
            return Call_Global(&class_name, &function_name, arguments, vcallback);
        } else {
            Arguments_t default_arguments;
            return Call_Global(&class_name, &function_name, &default_arguments, vcallback);
        }
    }

    Bool_t Machine_t::Call_Global(String_t class_name,
                                  String_t function_name,
                                  maybe<Arguments_i*> varguments,
                                  maybe<Callback_i*> vcallback)
    {
        some<Callback_i*> some_vcallback = vcallback ? vcallback() : new Callback_t();
        if (varguments) {
            return Call_Global(&class_name, &function_name, varguments(), &some_vcallback);
        } else {
            Arguments_t default_arguments;
            return Call_Global(&class_name, &function_name, &default_arguments, &some_vcallback);
        }
    }

    Bool_t Machine_t::Call_Global(String_t class_name,
                                  String_t function_name,
                                  Arguments_i&& varguments,
                                  maybe<Callback_i*> vcallback)
    {
        some<Callback_i*> some_vcallback = vcallback ? vcallback() : new Callback_t();
        return Call_Global(&class_name, &function_name, &varguments, &some_vcallback);
    }

    Bool_t Machine_t::Call_Method(Handle_t handle,
                                  String_t class_name,
                                  String_t function_name,
                                  Arguments_i* arguments,
                                  Callback_i** vcallback)
    {
        Callback_i* default_vcallback;
        if (!vcallback || !*vcallback) {
            default_vcallback = new Callback_t();
            vcallback = &default_vcallback;
        }
        if (arguments) {
            return Call_Method2(handle, &class_name, &function_name, arguments, vcallback);
        } else {
            Arguments_t default_arguments;
            return Call_Method2(handle, &class_name, &function_name, &default_arguments, vcallback);
        }
    }

    Bool_t Machine_t::Call_Method(Handle_t handle,
                                  String_t class_name,
                                  String_t function_name,
                                  maybe<Arguments_i*> maybe_varguments,
                                  maybe<Callback_i*> maybe_vcallback)
    {
        Callback_i* vcallback;
        if (maybe_vcallback) {
            vcallback = maybe_vcallback();
        } else {
            vcallback = new Callback_t();
        }

        if (maybe_varguments) {
            return Call_Method2(handle, &class_name, &function_name, maybe_varguments(), &vcallback);
        } else {
            Arguments_t default_varguments;
            return Call_Method2(handle, &class_name, &function_name, &default_varguments, &vcallback);
        }
    }

    Bool_t Machine_t::Call_Method(Handle_t handle,
                                  String_t class_name,
                                  String_t function_name,
                                  Arguments_i&& varguments,
                                  maybe<Callback_i*> maybe_vcallback)
    {
        Callback_i* vcallback;
        if (maybe_vcallback) {
            vcallback = maybe_vcallback();
        } else {
            vcallback = new Callback_t();
        }

        return Call_Method2(handle, &class_name, &function_name, &varguments, &vcallback);
    }

    void Machine_t::Send_Event(Handle_t handle,
                               String_t event_name,
                               maybe<Arguments_i*> maybe_varguments)
    {
        if (maybe_varguments) {
            return Send_Event(handle, &event_name, maybe_varguments());
        } else {
            Arguments_t default_varguments;
            return Send_Event(handle, &event_name, &default_varguments);
        }
    }

}}
