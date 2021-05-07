# Skylib
A static library for The Elder Scrolls V: Skyrim SE and SKSE plugins. Following in the footsteps of SKSE and CommonLibSSE, Skylib reveals native C++ data structures and functions, and additionaly provides new algorithms to create more stable and efficient plugins.

Skylib was created specifically to deal with the intricacies of the game engine in a stable and reliable manner, and less mysteriously too. An attempt has been made to introduce an intuitive API so that less time is spent puzzling and more time spent producing.

Skylib provides the common functionality behind my other works: NPC Lookup, SkyPal, and most recently NPC Party.

### Requirements
- Windows 7/10
- Visual Studio
- Windows 8.1 SDK
- Visual Studio 2015 (v140) Toolset
- SKSE 2.0.17+
- Skyrim SE 1.5.97

*The older SDK and Toolset match the original enviroment that the Skyrim SE executable and SKSE solution are built with.*

### Building
- You only need the following projects in the SKSE solution: common_vc14, skse64_common, and skse64. The SKSE solution is to remain separate from your own solution.
- Make sure to disable post-build events for SKSE and set it to compile as a static library.
- An example solution with an example plugin project is provided in this repository (see "/Example"). Even if you wish to build your own project from scratch, I suggest using the example as a reference.
- You will need to set the directory macros in both the Skylib project and the example project. Property pages (.props) are provided for both projects.
- For both SKylib's projects and your own, make sure that the correct toolset and target platform are selected.
- Build your solution.
- After the build you will want to move the .dll into your SKSE/Plugins folder, or change the provided post-build event to do it automatically for you.

### Beta
This library is currently in beta and is quite subject to change. This means that updating to a new version of Skylib may require you to make changes to your plugin's file in order to reflect any changes in Skylib.

### Thank You
- [SKSE Team](http://skse.silverlock.org/) for your C++ library, which has decompiled large portions of the engine and made it possible to work with.
- Ryan-rsm-McKenzie of [CommonLibSSE](https://github.com/Ryan-rsm-McKenzie/CommonLibSSE) for decompiling even more parts of the SkyrimSE engine.
- meh321 of [Address Library for SKSE Plugins](https://www.nexusmods.com/skyrimspecialedition/mods/32444) for making it easy to read the executable's offsets.
