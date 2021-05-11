/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <ShlObj.h>
#include <thread>

#include "doticu_skylib/game.h"
#include "doticu_skylib/skse_plugin.h"
#include "doticu_skylib/ui.h"

namespace doticu_skylib {

    void SKSE_Plugin_t::On_SKSE_Message(SKSE_Plugin_t& plugin, some<SKSE_Message_t*> message)
    {
        if (message->type == SKSEMessagingInterface::kMessage_SaveGame) {
            std::thread(
                [&plugin]()->void
                {
                    UI_t& ui = UI_t::Self();
                    u32 time = ui.game_timer.total_time;
                    while (ui.game_timer.total_time == time) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(16));
                    }
                    plugin.On_After_Save_Game();
                }
            ).detach();
            plugin.On_Before_Save_Game();

        } else if (message->type == SKSEMessagingInterface::kMessage_PreLoadGame) {
            if (message->data) {
                plugin.On_Before_Load_Game(static_cast<const char*>(message->data), message->dataLen);
            } else {
                plugin.On_Before_Load_Game("", 0);
            }

        } else if (message->type == SKSEMessagingInterface::kMessage_PostLoadGame) {
            plugin.On_After_Load_Game(message->data ? true : false);

        } else if (message->type == SKSEMessagingInterface::kMessage_NewGame) {
            plugin.On_After_New_Game();

        } else if (message->type == SKSEMessagingInterface::kMessage_DeleteGame) {
            if (message->data) {
                plugin.On_Before_Delete_Game(static_cast<const char*>(message->data), message->dataLen);
            } else {
                plugin.On_Before_Delete_Game("", 0);
            }

        } else if (message->type == SKSEMessagingInterface::kMessage_DataLoaded) {
            plugin.On_After_Load_Data(Game_t::Self());

        }
    }

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
