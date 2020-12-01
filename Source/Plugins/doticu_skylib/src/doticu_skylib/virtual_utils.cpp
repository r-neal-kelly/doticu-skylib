/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/collections.h"

#include "doticu_skylib/virtual_arguments.h"
#include "doticu_skylib/virtual_machine.h"
#include "doticu_skylib/virtual_utils.h"
#include "doticu_skylib/virtual_variable.h"

namespace doticu_skylib { namespace Virtual {

    void Utils_t::Wait(Float_t seconds, Callback_i* vcallback)
    {
        struct Arguments : public Arguments_t {
            Float_t seconds;
            Arguments(Float_t seconds) :
                seconds(seconds)
            {
            }
            Bool_t operator()(Buffer_t<Variable_t>* arguments)
            {
                arguments->Resize(1);
                arguments->At(0)->Float(seconds);
                return true;
            }
        } arguments(seconds);

        Machine_t::Self()->Call_Global(
            "Utility",
            "WaitMenuMode",
            &arguments,
            &vcallback
        );
    }

    void Utils_t::Wait_Out_Of_Menu(Float_t seconds, Callback_i* vcallback)
    {
        struct Arguments : public Arguments_t {
            Float_t seconds;
            Arguments(Float_t seconds) :
                seconds(seconds)
            {
            }
            Bool_t operator()(Buffer_t<Variable_t>* arguments)
            {
                arguments->Resize(1);
                arguments->At(0)->Float(seconds);
                return true;
            }
        } arguments(seconds);

        Machine_t::Self()->Call_Global(
            "Utility",
            "Wait",
            &arguments,
            &vcallback
        );
    }

}}
