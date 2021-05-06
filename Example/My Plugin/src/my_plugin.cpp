/*
    my_plugin.cpp
*/

#include "doticu_skylib/actor.h"        // for Actor_t::Log_Name_And_Type;
#include "doticu_skylib/const_actors.h" // for Const::Actor::PLayer;
#include "doticu_skylib/version.h"      // for Version_t<u16>;

#include "my_plugin.h"

namespace doticu_skylib { namespace My_Plugin {

    My_Plugin_t::My_Plugin_t() :
        SKSE_Plugin_t("My Plugin",                          // Name of dll and log
                      Version_t<u16>(1, 5, 97),             // Skyrim
                      Operator_e::EQUAL_TO,                 // only 1.5.97
                      Version_t<u16>(2, 0, 17),             // SKSE
                      Operator_e::GREATER_THAN_OR_EQUAL_TO) // 2.0.17+
    {
    }

    My_Plugin_t::~My_Plugin_t()
    {
    }

    Bool_t My_Plugin_t::On_Load(some<const SKSEInterface*> skse)
    {
        SKSE_Plugin_t::On_Load(skse);

        SKYLIB_LOG("My Plugin has now loaded and can begin interacting with its log and instantiating its data.");

        return true;
    }

    Bool_t My_Plugin_t::On_Register(some<Virtual::Machine_t*> machine)
    {
        return Register_Functions();
    }

    void My_Plugin_t::On_Message(some<SKSE_Message_t*> message)
    {
        if (message->type == SKSEMessagingInterface::kMessage_SaveGame) {
            Before_Save();
        } else if (message->type == SKSEMessagingInterface::kMessage_PreLoadGame) {
            Before_Load();
        } else if (message->type == SKSEMessagingInterface::kMessage_PostLoadGame && message->data) {
            After_Load();
        } else if (message->type == SKSEMessagingInterface::kMessage_NewGame) {
            New_Game();
        } else if (message->type == SKSEMessagingInterface::kMessage_DataLoaded) {
            Access_Data();
        }
    }

    Bool_t My_Plugin_t::Register_Functions()
    {
        SKYLIB_LOG("My Plugin can now register its Papyrus functions."); // see doticu_skylib/virtual_macros.h

        return true;
    }

    void My_Plugin_t::Access_Data()
    {
        SKYLIB_LOG("My Plugin can now access forms like:");
        Const::Actor::Player()->Log_Name_And_Type(SKYLIB_TAB);
    }

    void My_Plugin_t::New_Game()
    {
        SKYLIB_LOG("My Plugin can now start as a new game, and should unload its existing data.");
    }

    void My_Plugin_t::Before_Save()
    {
        SKYLIB_LOG("My Plugin can now store data in the save-game file and it will persist.");
    }

    void My_Plugin_t::Before_Load()
    {
        SKYLIB_LOG("My Plugin can now unload its data relating to the current save-game instance.");
    }

    void My_Plugin_t::After_Load()
    {
        SKYLIB_LOG("My Plugin can now load its data relating to the current save-game instance.");
    }

    extern My_Plugin_t my_plugin;

}}

SKYLIB_EXPORT_SKSE_PLUGIN(doticu_skylib::My_Plugin::my_plugin);
