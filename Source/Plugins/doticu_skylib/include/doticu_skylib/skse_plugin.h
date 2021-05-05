/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/PluginAPI.h"

#include "doticu_skylib/enum_operator.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/skse.h"
#include "doticu_skylib/version.h"

namespace doticu_skylib {

    namespace Virtual {

        class Machine_t;

    }

    class SKSE_Plugin_t
    {
    public:
        IDebugLog                               log;

        maybe<const SKSEInterface*>             skse;
        maybe<const SKSEPapyrusInterface*>      papyrus;
        maybe<const SKSEMessagingInterface*>    messaging;

        const some<const char*>                 plugin_name;
        PluginHandle                            plugin_handle;

        const maybe<Version_t<u16>>             skyrim_version_target;
        const Operator_e                        skyrim_version_method;
        const maybe<Version_t<u16>>             skse_version_target;
        const Operator_e                        skse_version_method;

    public:
        SKSE_Plugin_t(const some<const char*> plugin_name,
                      const maybe<Version_t<u16>> skyrim_version_target = none<Version_t<u16>>(),
                      const Operator_e skyrim_version_method = Operator_e::EQUAL_TO,
                      const maybe<Version_t<u16>> skse_version_target = none<Version_t<u16>>(),
                      const Operator_e skse_version_method = Operator_e::GREATER_THAN_OR_EQUAL_TO);

    public:
        virtual         ~SKSE_Plugin_t();
        virtual Bool_t  On_Query(some<const SKSEInterface*> skse, some<PluginInfo*> info);
        virtual Bool_t  On_Load(some<const SKSEInterface*> skse);
        virtual Bool_t  On_Register(some<Virtual::Machine_t*> machine);
        virtual void    On_Message(some<SKSE_Message_t*> message);

    private:
        Bool_t Operate(Version_t<u16> version, Operator_e method, Version_t<u16> target);
    };

    #define SKYLIB_EXPORT_SKSE_PLUGIN(_SKSE_PLUGIN)                                                     \
    extern "C" {                                                                                        \
                                                                                                        \
        _declspec(dllexport) doticu_skylib::Bool_t SKSEPlugin_Query(const SKSEInterface*, PluginInfo*); \
        _declspec(dllexport) doticu_skylib::Bool_t SKSEPlugin_Load(const SKSEInterface*);               \
                                                                                                        \
        doticu_skylib::Bool_t SKSEPlugin_Query(const SKSEInterface* skse, PluginInfo* info)             \
        {                                                                                               \
            SKYLIB_ASSERT(skse && info);                                                                \
            return _SKSE_PLUGIN.On_Query(skse, info);                                                   \
        }                                                                                               \
                                                                                                        \
        doticu_skylib::Bool_t SKSEPlugin_Load(const SKSEInterface* skse)                                \
        {                                                                                               \
            SKYLIB_ASSERT(skse);                                                                        \
            return                                                                                      \
                _SKSE_PLUGIN.On_Load(skse) &&                                                           \
                _SKSE_PLUGIN.papyrus->Register(                                                         \
                    [](doticu_skylib::SKSE_Registry_t* registry)->doticu_skylib::Bool_t                 \
                    {                                                                                   \
                        SKYLIB_ASSERT(registry);                                                        \
                        return _SKSE_PLUGIN.On_Register(                                                \
                            reinterpret_cast<doticu_skylib::Virtual::Machine_t*>(registry)              \
                        );                                                                              \
                    }                                                                                   \
                ) &&                                                                                    \
                _SKSE_PLUGIN.messaging->RegisterListener(                                               \
                    _SKSE_PLUGIN.plugin_handle,                                                         \
                    "SKSE",                                                                             \
                    [](doticu_skylib::SKSE_Message_t* message)->void                                    \
                    {                                                                                   \
                        if (message) {                                                                  \
                            _SKSE_PLUGIN.On_Message(message);                                           \
                        }                                                                               \
                    }                                                                                   \
                );                                                                                      \
        }                                                                                               \
                                                                                                        \
    }

}
