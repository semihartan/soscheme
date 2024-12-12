#include <pch.h>

#include "upowr.h"
#include "mod.h"

DWORD WINAPI PowerGetActualOverlayScheme(_Out_ GUID* SchemeGuid)
{
	static PowerGetActualOverlayScheme_ft* PowerGetActualOverlayScheme = NULL;
	if (!PowerGetActualOverlayScheme)
		PowerGetActualOverlayScheme = (PowerGetActualOverlayScheme_ft*)LoadProcedure("powrprof.dll", "PowerGetActualOverlayScheme");

	return PowerGetActualOverlayScheme(SchemeGuid);
}

DWORD WINAPI PowerGetEffectiveOverlayScheme(_Out_ GUID* SchemeGuid)
{
	static PowerGetEffectiveOverlayScheme_ft* PowerGetEffectiveOverlayScheme = NULL;
	if (!PowerGetEffectiveOverlayScheme)
		PowerGetEffectiveOverlayScheme = (PowerGetEffectiveOverlayScheme_ft*)LoadProcedure("powrprof.dll", "PowerGetEffectiveOverlayScheme");

	return PowerGetEffectiveOverlayScheme(SchemeGuid);
}

DWORD WINAPI PowerSetActiveOverlayScheme(const GUID* SchemeGuid)
{
	static PowerSetActiveOverlayScheme_ft *PowerSetActiveOverlayScheme = NULL;
	if (!PowerSetActiveOverlayScheme) 
		PowerSetActiveOverlayScheme = (PowerSetActiveOverlayScheme_ft*)LoadProcedure("powrprof.dll", "PowerSetActiveOverlayScheme");
	
	return PowerSetActiveOverlayScheme(SchemeGuid);
}

DWORD WINAPI PowerGetOverlaySchemes(GUID** OverlaySchemes, PDWORD lpSchemeCount, BYTE reserved)
{
	static PowerGetOverlaySchemes_ft *PowerGetOverlaySchemes = NULL;
	if (!PowerGetOverlaySchemes)
		PowerGetOverlaySchemes = (PowerGetOverlaySchemes_ft*)LoadProcedure("powrprof.dll", "PowerGetOverlaySchemes");

	return PowerGetOverlaySchemes(OverlaySchemes, lpSchemeCount, reserved);
}

