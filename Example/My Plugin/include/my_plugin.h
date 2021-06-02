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

        virtual Bool_t  On_Query(some<const SKSEInterface*> skse, some<PluginInfo*> info) override;
        virtual Bool_t  On_Load(some<const SKSEInterface*> skse) override;
        virtual Bool_t  On_Register(some<Virtual::Machine_t*> machine) override;

        virtual void    On_After_Load_Data() override;
        virtual void    On_After_New_Game() override;
        virtual void    On_Before_Save_Game(const std::string& file_name) override;
        virtual void    On_After_Save_Game(const std::string& file_name) override;
        virtual void    On_Before_Load_Game(const std::string& file_name) override;
        virtual void    On_After_Load_Game(const std::string& file_name, Bool_t did_load_successfully) override;
        virtual void    On_Before_Delete_Game(const std::string& file_name) override;
        virtual void    On_Update(u32 time_stamp) override;
    };

    extern My_Plugin_t my_plugin;

}}
