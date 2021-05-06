/*
    my_plugin.h
*/

#pragma once

#include "doticu_skylib/skse_plugin.h"

namespace doticu_skylib { namespace My_Plugin {

    class My_Plugin_t :
        public SKSE_Plugin_t
    {
    public:
        My_Plugin_t();

    public:
        virtual         ~My_Plugin_t();
        virtual Bool_t  On_Load(some<const SKSEInterface*> skse) override;
        virtual Bool_t  On_Register(some<Virtual::Machine_t*> machine) override;
        virtual void    On_Message(some<SKSE_Message_t*> message) override;
    };

    extern My_Plugin_t my_plugin = My_Plugin_t();

}}
