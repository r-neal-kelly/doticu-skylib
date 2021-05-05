#### Build Requirements
- Windows 7/10
- Visual Studio
- Windows 8.1 SDK
- Visual Studio 2015 (v140) Toolset
- SKSE 2.0.19+ (some earlier versions may work)

#### Build Instructions
- The older SDK and Toolset match the original enviroment that the Skyrim SE engine is built with, as well as SKSE's environment. We use it to remain as compatibile as possible.
- Use the included macro "skse" in the doticu_skylib property page to set the location of your SKSE installation.
- Make sure that you have the correct target platform and toolset selected in the project's properties.
- Must be built as a static library.

#### Thank You
- [SKSE Team](http://skse.silverlock.org/) for your c++ library, which has decompiled large portions of the engine and made it possible to work with.
- Ryan-rsm-McKenzie of [CommonLibSSE](https://github.com/Ryan-rsm-McKenzie/CommonLibSSE) for decompiling even more parts of the SkyrimSE engine.
- meh321 of [Address Library for SKSE Plugins](https://www.nexusmods.com/skyrimspecialedition/mods/32444) for making it easy to read the executable's offsets.
