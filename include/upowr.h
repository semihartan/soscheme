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