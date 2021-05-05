### Build Requirements
- Windows 7/10
- Visual Studio
- Windows 8.1 SDK
- Visual Studio 2015 (v140) Toolset
- SKSE 2.0.19+ (some earlier versions may work)

*The older SDK and Toolset match the original enviroment that the Skyrim SE executable and SKSE solution are built with.*

### Build Instructions
- You only need the following projects in the SKSE solution: common_vc14, skse64_common, and skse64.
- In your plugin's solution, use the included macro "skse" in the "doticu_skylib" property page of the Skylib project to set the location of your SKSE solution.
- For all projects:
   - Set as a static library.
   - Set target platform to 8.1.
   - Set toolset to Visual Studio 2015 v140
   - Disable any post build events you don't want, especially on the skse64 project.
- Build your solution.

### Thank You
- [SKSE Team](http://skse.silverlock.org/) for your c++ library, which has decompiled large portions of the engine and made it possible to work with.
- Ryan-rsm-McKenzie of [CommonLibSSE](https://github.com/Ryan-rsm-McKenzie/CommonLibSSE) for decompiling even more parts of the SkyrimSE engine.
- meh321 of [Address Library for SKSE Plugins](https://www.nexusmods.com/skyrimspecialedition/mods/32444) for making it easy to read the executable's offsets.
