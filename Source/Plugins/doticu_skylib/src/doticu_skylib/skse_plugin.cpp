/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <ShlObj.h>
#include <thread>

#include "doticu_skylib/game.h"
#include "doticu_skylib/player.h"
#include "doticu_skylib/skse_plugin.h"
#include "doticu_skylib/ui.h"

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
        skse_version_method(skse_version_method),

        has_update_loop(false),
        update_locker(this->update_lock, std::defer_lock)
    {
        SKYLIB_ASSERT_SOME(plugin_name);

        SKYLIB_ASSERT(skyrim_version_method == Operator_e::EQUAL_TO ||
                      skyrim_version_method == Operator_e::GREATER_THAN_OR_EQUAL_TO ||
                      skyrim_version_method == Operator_e::NONE);

        SKYLIB_ASSERT(skse_version_method == Operator_e::EQUAL_TO ||
                      skse_version_method == Operator_e::GREATER_THAN_OR_EQUAL_TO ||
                      skse_version_method == Operator_e::NONE);

        this->log.OpenRelative(
            CSIDL_MYDOCUMENTS,
            (std::string("\\My Games\\Skyrim Special Edition\\SKSE\\") + this->plugin_name() + ".log").c_str()
        );
    }

    SKSE_Plugin_t::~SKSE_Plugin_t()
    {
    }

    Bool_t SKSE_Plugin_t::On_Query(some<const SKSEInterface*> skse, some<PluginInfo*> info)
    {
        auto Operate = [](Version_t<u16> version, Operator_e method, Version_t<u16> target)->Bool_t
        {
            if (method == Operator_e::GREATER_THAN_OR_EQUAL_TO) {
                return version >= target;
            } else {
                return version == target;
            }
        };

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
        this->skse = skse();
        this->papyrus = static_cast<const SKSEPapyrusInterface*>(skse->QueryInterface(kInterface_Papyrus));
        this->messaging = static_cast<const SKSEMessagingInterface*>(skse->QueryInterface(kInterface_Messaging));
        this->plugin_handle = skse->GetPluginHandle();

        SKYLIB_ASSERT(this->papyrus && this->messaging);

        return true;
    }

    Bool_t SKSE_Plugin_t::On_Register(some<Virtual::Machine_t*> machine)
    {
        return true;
    }

    void SKSE_Plugin_t::On_SKSE_Message(some<SKSE_Message_t*> message)
    {
        static auto Clean_File_Name = [](maybe<const char*> original)->std::string
        {
            if (original) {
                std::string result = original();

                if (CString_t::Ends_With(original(), ".ess", true)) {
                    result.erase(result.length() - 4);
                }

                return std::move(result);
            } else {
                return "";
            }
        };

        if (message->type == SKSEMessagingInterface::kMessage_SaveGame) {
            if (!this->update_locker.owns_lock()) {
                this->update_locker.lock();
            }

            this->cached_file_name = Clean_File_Name(static_cast<const char*>(message->data));
            On_Before_Save_Game(this->cached_file_name);

            std::thread(
                [this]()->void
                {
                    some<UI_t*> ui = UI_t::Self();
                    u32 time = ui->game_timer.total_time;
                    while (time == ui->game_timer.total_time) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(16));
                    }

                    this->On_After_Save_Game(this->cached_file_name);

                    if (this->update_locker.owns_lock()) {
                        this->update_locker.unlock();
                    }
                }
            ).detach();

        } else if (message->type == SKSEMessagingInterface::kMessage_PreLoadGame) {
            if (!this->update_locker.owns_lock()) {
                this->update_locker.lock();
            }

            this->cached_file_name = Clean_File_Name(static_cast<const char*>(message->data));
            On_Before_Load_Game(this->cached_file_name);

        } else if (message->type == SKSEMessagingInterface::kMessage_PostLoadGame) {
            On_After_Load_Game(this->cached_file_name, message->data ? true : false);

            if (this->update_locker.owns_lock()) {
                this->update_locker.unlock();
            }

        } else if (message->type == SKSEMessagingInterface::kMessage_NewGame) {
            std::lock_guard<std::mutex> update_locker(this->update_lock);

            On_After_New_Game();

        } else if (message->type == SKSEMessagingInterface::kMessage_DeleteGame) {
            std::string file_name = Clean_File_Name(static_cast<const char*>(message->data));
            std::thread(
                [this, file_name]()->void
                {
                    std::lock_guard<std::mutex> update_locker(this->update_lock);
                    On_Before_Delete_Game(file_name);
                }
            ).detach();

        } else if (message->type == SKSEMessagingInterface::kMessage_DataLoaded) {
            std::lock_guard<std::mutex> update_locker(this->update_lock);

            On_After_Load_Data();

        }
    }

    void SKSE_Plugin_t::Start_Updating(std::chrono::milliseconds interval)
    {
        SKYLIB_ASSERT(interval.count() > 0);

        if (!this->has_update_loop.exchange(true)) {
            std::thread(
                [this, interval]()->void
                {
                    Player_t& player = *Player_t::Self();
                    UI_t& ui = *UI_t::Self();
                    u32 time = 0;
                    while (true) {
                        {
                            std::lock_guard<std::mutex> update_locker(this->update_lock);

                            if (time != ui.game_timer.total_time) {
                                time = ui.game_timer.total_time;
                                if (player.Is_Attached()) {
                                    On_Update(time);
                                }
                            }
                        }
                        std::this_thread::sleep_for(interval);
                    }
                }
            ).detach();
        }
    }

}
