#pragma once

#ifndef UPOWR_H
#define UPOWR_H

typedef DWORD (WINAPI PowerGetActualOverlayScheme_ft)(_Out_ GUID* SchemeGuid);
typedef DWORD (WINAPI PowerSetActiveOverlayScheme_ft)(_Out_ const GUID* SchemeGuid);
typedef DWORD (WINAPI PowerGetEffectiveOverlayScheme_ft)(_In_ GUID* SchemeGuid);
typedef DWORD (WINAPI PowerGetOverlaySchemes_ft)(_Out_ GUID** OverlaySchemes, PDWORD lpSchemeCount, BYTE reserved);

DWORD WINAPI PowerGetActualOverlayScheme(_Out_ GUID* SchemeGuid);

DWORD WINAPI PowerGetEffectiveOverlayScheme(_Out_ GUID* SchemeGuid);

DWORD WINAPI PowerSetActiveOverlayScheme(const GUID* SchemeGuid);

DWORD WINAPI PowerGetOverlaySchemes(_Out_ GUID** OverlaySchemes, PDWORD lpSchemeCount, BYTE reserved);

#endif