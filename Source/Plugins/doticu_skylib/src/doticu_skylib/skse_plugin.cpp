/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <ShlObj.h>

#include "doticu_skylib/skse_plugin.h"

namespace doticu_skylib {

    SKSE_Plugin_t::SKSE_Plugin_t(const some<const char*> plugin_name,
                                 const maybe<Version_t<u16>> skyrim_version_target,
                                 const Operator_e skyrim_version_method,
                                 const maybe<Version_t<u16>> skse_version_target,
                                 const Operator_e skse_version_method) :
        skse(nullptr),
        papyrus(nullptr),
        messaging(nullptr),

        plugin_name(plugin_name),
        plugin_handle(0),

        skyrim_version_target(skyrim_version_target),
        skyrim_version_method(skyrim_version_method),
        skse_version_target(skse_version_target),
        skse_version_method(skse_version_method)
    {
        SKYLIB_ASSERT_SOME(plugin_name);

        SKYLIB_ASSERT(skyrim_version_method == Operator_e::EQUAL_TO ||
                      skyrim_version_method == Operator_e::GREATER_THAN_OR_EQUAL_TO ||
                      skyrim_version_method == Operator_e::NONE);

        SKYLIB_ASSERT(skse_version_method == Operator_e::EQUAL_TO ||
                      skse_version_method == Operator_e::GREATER_THAN_OR_EQUAL_TO ||
                      skse_version_method == Operator_e::NONE);
    }

    SKSE_Plugin_t::~SKSE_Plugin_t()
    {
        this->skse = nullptr;
        this->papyrus = nullptr;
        this->messaging = nullptr;
        this->plugin_handle = 0;
    }

    Bool_t SKSE_Plugin_t::On_Query(some<const SKSEInterface*> skse, some<PluginInfo*> info)
    {
        info->infoVersion = PluginInfo::kInfoVersion;
        info->name = plugin_name();
        info->version = 1;

        if (this->skyrim_version_target.Has_Value() &&
            this->skyrim_version_method != Operator_e::NONE &&
            !Operate(Version_t<u16>::From_MM_mm_ppp_b(skse->runtimeVersion),
                     this->skyrim_version_method,
                     this->skyrim_version_target.Value())) {
            return false;
        } else if (this->skse_version_target.Has_Value() &&
                   this->skse_version_method != Operator_e::NONE &&
                   !Operate(Version_t<u16>::From_MM_mm_ppp_b(skse->skseVersion),
                            this->skse_version_method,
                            this->skse_version_target.Value())) {
            return false;
        } else {
            return true;
        }
    }

    Bool_t SKSE_Plugin_t::On_Load(some<const SKSEInterface*> skse)
    {
        this->log.OpenRelative(
            CSIDL_MYDOCUMENTS,
            (std::string("\\My Games\\Skyrim Special Edition\\SKSE\\") + this->plugin_name() + ".log").c_str()
        );

        this->skse = skse();
        this->papyrus = static_cast<const SKSEPapyrusInterface*>(skse->QueryInterface(kInterface_Papyrus));
        this->messaging = static_cast<const SKSEMessagingInterface*>(skse->QueryInterface(kInterface_Messaging));
        this->plugin_handle = skse->GetPluginHandle();

        SKYLIB_ASSERT(this->papyrus && this->messaging);

        return true;
    }

    Bool_t SKSE_Plugin_t::Operate(Version_t<u16> version, Operator_e method, Version_t<u16> target)
    {
        if (method == Operator_e::GREATER_THAN_OR_EQUAL_TO) {
            return version >= target;
        } else {
            return version == target;
        }
    }

}
