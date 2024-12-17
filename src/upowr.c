/*
* MIT License
*
* Copyright (c) 2024 Semih Artan
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

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

