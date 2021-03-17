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
                                  maybe<Arguments_i*> arguments,
                                  maybe<Callback_i*> callback)
    {
        some<Callback_i*> some_callback = callback ? callback() : new Callback_t();
        if (arguments) {
            return Do_Call_Global(class_name, function_name, *arguments, static_cast<Callback_i*&>(some_callback));
        } else {
            Arguments_t default_arguments;
            return Do_Call_Global(class_name, function_name, default_arguments, static_cast<Callback_i*&>(some_callback));
        }
    }

    Bool_t Machine_t::Call_Global(String_t class_name,
                                  String_t function_name,
                                  Arguments_i&& arguments,
                                  maybe<Callback_i*> callback)
    {
        some<Callback_i*> some_callback = callback ? callback() : new Callback_t();
        return Do_Call_Global(class_name, function_name, arguments, static_cast<Callback_i*&>(some_callback));
    }

    Bool_t Machine_t::Call_Method(Handle_t handle,
                                  String_t class_name,
                                  String_t function_name,
                                  maybe<Arguments_i*> arguments,
                                  maybe<Callback_i*> callback)
    {
        some<Callback_i*> some_callback = callback ? callback() : new Callback_t();
        if (arguments) {
            return Do_Call_Method_2(handle, class_name, function_name, *arguments, static_cast<Callback_i*&>(some_callback));
        } else {
            Arguments_t default_arguments;
            return Do_Call_Method_2(handle, class_name, function_name, default_arguments, static_cast<Callback_i*&>(some_callback));
        }
    }

    Bool_t Machine_t::Call_Method(Handle_t handle,
                                  String_t class_name,
                                  String_t function_name,
                                  Arguments_i&& arguments,
                                  maybe<Callback_i*> callback)
    {
        some<Callback_i*> some_callback = callback ? callback() : new Callback_t();
        return Do_Call_Method_2(handle, class_name, function_name, arguments, static_cast<Callback_i*&>(some_callback));
    }

    void Machine_t::Send_Event(Handle_t handle,
                               String_t event_name,
                               maybe<Arguments_i*> arguments)
    {
        if (arguments) {
            return Do_Send_Event(handle, event_name, *arguments);
        } else {
            Arguments_t default_arguments;
            return Do_Send_Event(handle, event_name, default_arguments);
        }
    }

    void Machine_t::Send_Event(Handle_t handle,
                               String_t event_name,
                               Arguments_i&& arguments)
    {
        return Do_Send_Event(handle, event_name, arguments);
    }

    void Machine_t::Return_Latent_Function(Stack_ID_t stack_id, const Variable_t& return_variable)
    {
        Do_Return_Latent_Function(stack_id, return_variable);
    }

    void Machine_t::Return_Latent_Function(Stack_ID_t stack_id, const Variable_t&& return_variable)
    {
        Do_Return_Latent_Function(stack_id, return_variable);
    }

}}
