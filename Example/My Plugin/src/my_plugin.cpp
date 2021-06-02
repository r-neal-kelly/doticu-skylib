/*
    my_plugin.cpp
*/

#include "doticu_skylib/actor.h"        // for Actor_t::Log_Name_And_Type;
#include "doticu_skylib/const_actors.h" // for Const::Actor::Player;
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
        SKYLIB_LOG("My Plugin now has a log."); // see Documents/My Games/Skyrim Special Edition/SKSE/My Plugin.log
    }

    My_Plugin_t::~My_Plugin_t()
    {
    }

    Bool_t My_Plugin_t::On_Query(some<const SKSEInterface*> skse, some<PluginInfo*> info)
    {
        SKYLIB_LOG("My Plugin can override On_Query or just let SKSE_Plugin_t handle it.");

        return SKSE_Plugin_t::On_Query(skse, info);
    }

    Bool_t My_Plugin_t::On_Load(some<const SKSEInterface*> skse)
    {
        SKYLIB_LOG("My Plugin can also override On_Load or just let SKSE_Plugin_t handle it.");

        if (SKSE_Plugin_t::On_Load(skse)) {
            SKYLIB_LOG("My Plugin has loaded and can begin instantiating its data.");
            return true;
        } else {
            SKYLIB_LOG("My Plugin has failed to load and will not receive any further events.");
            return false;
        }
    }

    Bool_t My_Plugin_t::On_Register(some<Virtual::Machine_t*> machine)
    {
        SKYLIB_LOG("My Plugin can now register its own native Papyrus functions and methods."); // see doticu_skylib/virtual_macros.h

        return true;
    }

    void My_Plugin_t::On_After_Load_Data()
    {
        SKYLIB_LOG("My Plugin can now access forms like:");
        Const::Actor::Player()->Log_Name_And_Type(SKYLIB_TAB);

        SKYLIB_LOG("My Plugin can now start its own game loop.");
        Start_Updating(std::chrono::milliseconds(5000));
    }

    void My_Plugin_t::On_After_New_Game()
    {
        SKYLIB_LOG("My Plugin can now start as a new game, and should unload its existing data.");
    }

    void My_Plugin_t::On_Before_Save_Game(const std::string& file_name)
    {
        SKYLIB_LOG("My Plugin can now store data in the save-game file and it will persist.");
    }

    void My_Plugin_t::On_After_Save_Game(const std::string& file_name)
    {
        SKYLIB_LOG("My Plugin now knows that the game is done saving, and may continue executing.");
    }

    void My_Plugin_t::On_Before_Load_Game(const std::string& file_name)
    {
        SKYLIB_LOG("My Plugin can now unload its data relating to the current save-game instance.");
    }

    void My_Plugin_t::On_After_Load_Game(const std::string& file_name, Bool_t did_load_successfully)
    {
        if (did_load_successfully) {
            SKYLIB_LOG("My Plugin can now load its data relating to the current save-game instance.");
        } else {
            SKYLIB_LOG("My Plugin can now do what it needs to do, if anything, since the game failed to load a save game.");
        }
    }

    void My_Plugin_t::On_Before_Delete_Game(const std::string& file_name)
    {
        SKYLIB_LOG("My Plugin can now delete any files that were created along with Skyrim's and SKSE's files.");
    }

    void My_Plugin_t::On_Update(u32 time_stamp)
    {
        SKYLIB_LOG("My Plugin is updating with time_stamp: %u", time_stamp);
    }

    My_Plugin_t my_plugin;

}}

SKYLIB_EXPORT_SKSE_PLUGIN(doticu_skylib::My_Plugin::my_plugin);
