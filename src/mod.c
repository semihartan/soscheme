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

#include "mod.h"
 
HMODULE LoadModuleIfNeeded(LPCSTR _szModuleName)
{
	HMODULE hMod = GetModuleHandleA(_szModuleName);
	if (!hMod)
	{
		hMod = LoadLibraryA(_szModuleName);
		if (!hMod)
		{
			fprintf(stderr, "Failed to load the module %s\n", _szModuleName);
			SetLastError(ERROR_MOD_NOT_FOUND);
			return hMod;
		}
	}
	return hMod;
}

PVOID LoadProcedure(LPCSTR _szModuleName, LPCSTR _szProcName)
{
	PVOID procAddress = NULL;
	HMODULE hMod = LoadModuleIfNeeded(_szModuleName);
	procAddress = GetProcAddress(hMod, _szProcName);
	if (!procAddress)
	{
		if ((ULONGLONG)_szProcName & 0xFFFFFFFF00000000)
			fprintf(stderr, "Failed to get the address of procecure %hs\n", _szProcName);
		else
			fprintf(stderr, "Failed to get the address of procedure at ordinal number %u\n", (USHORT)_szProcName);
	}
	return procAddress;
}