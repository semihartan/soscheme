# soscheme (Set Power Overlay Schemes)

## Description

**soscheme** is a simple tool that allows to set transient/persistent power overlay schemes, query and report them with JSON output.

## Motivation

I've created this tool because the system control software (*Armoury Crate*) on my laptop changes the Windows power overlay scheme each time I choose a different profile on it. Armoury Crate on my device has four profiles: Windows, Quite, Performance and Turbo. When I switch to either Performance and Turbo, it automatically sets Windows overlay scheme as `Best Performance`. This causes your system to consume more power than required.

Then I started searching the internet and scanning `Win32` API, and I have discovered that Windows Power API has a nice API for detecting overlay scheme changes. The function is `PowerRegisterForEffectivePowerModeNotifications`. Other APIs I have used, which are undocumented are PowerSetActiveOverlayScheme` to set the active overlay scheme, `PowerGetActualOverlayScheme` to retrieve the active scheme, and finally `PowerGetOverlaySchemes` to query the available overlay schemes on the system.

The first two functions was documented in a Stackoverflow post, but the last one was undocumented. I have done a bit reverse-engineering on it, and documented its first two parameters. The functions signature is as follows:

```c
DWORD WINAPI PowerGetOverlaySchemes(
    GUID** OverlaySchemes, // A pointer that receives a pointer to an array of GUIDs.
    PDWORD lpSchemeCount,   // A pointer to DWORD that receives the number of schemes.
    BYTE undocumented) // It is undocumented now. But it is probably either reserved or unused parameter.
```

The file `include\upowr.dis.h` includes the entire reverse-engineered function.

## How to Build

To build the tool, make sure you have at least **"Desktop development with C++ workload"** installed by either installing [Visual Studio IDE][vs], or [Build Tools for Visual Studio][buildtools] as a standalone package. 

[vs]: https://visualstudio.microsoft.com/downloads/
[buildtools]: https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2022

This project doesn't use MSBuild to build the software. It uses Microsoft's make program NMake. The makefile can build a static library, a dynamic library or an executable. Calling nmake as-is at the project's root directory builds a x64 executable retail build. To build libraries, you have to set a two command-line environment variables: `SOS_STATIC_LIB` and `SOS_SHARED_LIB`. To build a static library, you have to set `SOS_STATIC_LIB` to `1`, and leave `SOS_SHARED_LIB` as empty variable, and vice-versa for shared library.

To control the type of the build, Retail or Debug, you have to set the environment variable `SOS_CONFIG` to either `Debug` or `Release`.

To choose the target platform architecture, set the environment variable `SOS_TARGET_ARCH` to one of the architectures in the following list: `x86`, `x64`, `arm`, and `arm64`. 

Building different configs on the same command-prompt windows is therefore hard and cumbersome. So It also includes a high level build script to abstract these details.

The syntax for this high level build script is as follows.

```
Syntax:
    build.bat [build_type] [--arch=arch_type] [--lib=lib_type] [--config=config_type]
where :
    [build_type]: clean | build | rebuild
    [arch_type]: x86 | amd64 | arm | arm64
    [lib_type]: static | shared
    [config_type] : debug | release


For example:
    build.bat (Builds the default config)
    build.bat --arch=x64 --config=Debug
    build.bat clean --arch=x64 --config=Debug
    build.bat build --arch=x86 --config=Release
    build.bat rebuild --arch=arm --config=Debug --lib=static
```

You don't need to call this script from a Developer Command Prompt. It automatically search for a Visual Studio installation and setup a developer environment for the selected config by calling the script supplied by Visual Studio.

For example, to build the software as an ARM debug executable call the script as the following.

```
> build.bat --arch=arm --config=Debug
```

To build a x86 debug static library, invoke the script as below.

```
> build.bat --arch=x86 --config=Debug --lib=static
```