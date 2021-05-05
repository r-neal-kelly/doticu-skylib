# Skylib
A static library for SKSE plugins, designed to help you interact with the game engine behind The Elder Scrolls V: Skyrim SE. Following in the footsteps of SKSE and CommonLibSSE, Skylib reveals native C++ data structures and functions, and additionaly provides new algorithms you can use to create more stable and efficient plugins.

Skylib was created specifically to make dealing with the intricacies of the game engine more stable and reliable, and hopefully less mysterious too. An attempt has been made to introduce an intuitive API so that less time is spent puzzling and more time spent producing.

### Requirements
- Windows 7/10
- Visual Studio
- Windows 8.1 SDK
- Visual Studio 2015 (v140) Toolset
- SKSE 2.0.17+
- Skyrim SE 1.5.97

*The older SDK and Toolset match the original enviroment that the Skyrim SE executable and SKSE solution are built with.*

### Build
- You only need the following projects in the SKSE solution: common_vc14, skse64_common, and skse64. The SKSE solution is to remain separate from your own solution.
- Add the Skylib project to your own plugin's solution.
- In the Skylib project, use the included macro "skse" in the "doticu_skylib" property page to set the location of your SKSE solution.
- For all projects, including SKSE's, Skylib's, and any other except the plugin's direct project:
   - Set as a static library.
   - Set target platform to 8.1.
   - Set toolset to Visual Studio 2015 v140
   - Disable any post build events you don't want, especially on the skse64 project.
- For you plugin's project, set the same target platform and toolset, but set it to a dynamic library instead of a static one.
- Interface directly with SKSE or alternatively, with the `SKSE_Plugin_t` in `skse_plugin.h`.
- Build your solution.

### Beta
This library is currently in beta and is quite subject to change. This means that updating to a new version of Skylib may require you to make changes to your plugin's file in order to reflect any changes in Skylib.

### Plugin Example
```
// my_plugin.h

#include "doticu_skylib/skse_plugin.h"

class My_Plugin_t :
    public SKSE_Plugin_t
{
public:
    My_Plugin_t();

public:
    virtual         ~My_Plugin_t();
    virtual Bool_t  On_Register(some<V::Machine_t*> machine) override;
    virtual void    On_Message(some<SKSE_Message_t*> message) override;
};

extern My_Plugin_t my_plugin;

// my_plugin.cpp

#include "doticu_skylib/version.h"
#include "my_plugin.h"

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

Bool_t My_Plugin_t::On_Register(some<V::Machine_t*> machine)
{
    // Register_Papyrus_Functions_And_Methods(machine);
    // see doticu_skylib/virtual_macros.h
    return true;
}

void My_Plugin_t::On_Message(some<SKSE_Message_t*> message)
{
    if (message->type == SKSEMessagingInterface::kMessage_SaveGame) {
        // Before_Save();
    } else if (message->type == SKSEMessagingInterface::kMessage_PreLoadGame) {
        // Before_Load();
    } else if (message->type == SKSEMessagingInterface::kMessage_PostLoadGame && message->data) {
        // After_Load();
    } else if (message->type == SKSEMessagingInterface::kMessage_NewGame) {
        // New_Game();
    } else if (message->type == SKSEMessagingInterface::kMessage_DataLoaded) {
        // Access_Forms_And_Other_Data();
    }
}

extern My_Plugin_t my_plugin; // instantiates the log

SKYLIB_EXPORT_SKSE_PLUGIN(my_plugin); // interfaces with user-installed SKSE dll
```

### Thank You
- [SKSE Team](http://skse.silverlock.org/) for your C++ library, which has decompiled large portions of the engine and made it possible to work with.
- Ryan-rsm-McKenzie of [CommonLibSSE](https://github.com/Ryan-rsm-McKenzie/CommonLibSSE) for decompiling even more parts of the SkyrimSE engine.
- meh321 of [Address Library for SKSE Plugins](https://www.nexusmods.com/skyrimspecialedition/mods/32444) for making it easy to read the executable's offsets.
