# soscheme (Set Power Overlay Schemes)

## Description

**soscheme** is a simple tool that allows to set transient/persistent power overlay schemes, query and report them with JSON output.

## Motivation

I've created this tool because the system control software (*Armoury Crate*) on my laptop changes the Windows power overlay scheme each time I choose a different profile on it. Armoury Crate on my device has four profiles: Windows, Quite, Performance and Turbo. When I switch to either Performance and Turbo, it automatically sets Windows overlay scheme as `Best Performance`. This causes your system to consume more power than required.

Then I started searching the internet and scanning `Win32` API, and I have discovered that Windows Power API has a nice API for detecting overlay scheme changes. The function is `PowerRegisterForEffectivePowerModeNotifications`. Other APIs I have used, which are undocumented are `PowerSetActiveOverlayScheme` to set the active overlay scheme, `PowerGetActualOverlayScheme` to retrieve the active scheme, and finally `PowerGetOverlaySchemes` to query the available overlay schemes on the system.

The first two functions was documented in a Stackoverflow post, but the last one was undocumented. I have done a bit reverse-engineering on it, and documented its first two parameters. The functions signature is as follows:

```c
DWORD WINAPI PowerGetOverlaySchemes(
    GUID** OverlaySchemes, // A pointer that receives a pointer to an array of GUIDs.
    PDWORD lpSchemeCount,   // A pointer to DWORD that receives the number of schemes.
    BYTE undocumented) // It is undocumented now. But it is probably either reserved or unused parameter.
```

The file `include\upowr.dis.h` includes the entire reverse-engineered function.

## How to Build

To build the tool, make sure you have at least "Desktop development with C++ workload" installed by either installing Visual Studio IDE, or [Build Tools for Visual Studio](buildtools) as a standalone package. 

[buildtools]: (https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2022)