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