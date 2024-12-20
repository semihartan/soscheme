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

#include "util.h"
#include "soserror.h"
#include "log.h"

bool SosIsGuidEmpty(const GUID* pGuid)
{
	assert(pGuid != NULL);
	uint64_t data4 = *(uint64_t*)pGuid->Data4;

	return pGuid->Data1 == 0 && pGuid->Data2 == 0 && pGuid->Data3 == 0 && data4 == 0;
}

void SosPrintGuid(const GUID* const pGuid)
{
	printf("{%08lX-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}", 
		pGuid->Data1, 
		pGuid->Data2, pGuid->Data3, 
		pGuid->Data4[0], pGuid->Data4[1], pGuid->Data4[2], pGuid->Data4[3], pGuid->Data4[4], pGuid->Data4[5], pGuid->Data4[6], pGuid->Data4[7]);
}

#define GUID_SZ					sizeof(GUID)
#define GUID_WO_BRACES_SZ		(GUID_SZ * 2 + 4) // GUID name without curly braces
#define GUID_BUFFER_SZ			(GUID_WO_BRACES_SZ + 2 + 1)	// GUID_WO_BRACES_SZ + { + } + '\0' chars for a GUID string.

#pragma warning(disable:4431)

const TCHAR* SosConvertGuidToString(const GUID* const _guid)
{
	static OLECHAR guidStringBuffer[GUID_BUFFER_SZ];
	// Convert the GUID into string. 
	// No need to check the return value cuz we provide a buffer of required size. 
	(void)StringFromGUID2(_guid, guidStringBuffer, GUID_BUFFER_SZ);
	// Trim the curly braces.
	wmemcpy(guidStringBuffer, (const wchar_t*)(guidStringBuffer + 1), GUID_WO_BRACES_SZ);
	guidStringBuffer[GUID_WO_BRACES_SZ] = L'\0';

#if !defined(UNICODE) && !defined(_UNICODE)
	SOS_RETURN_IF(
		0 < WideCharToMultiByte(CP_ACP, 0, guidStringBuffer, -1, (LPSTR)guidStringBuffer, GUID_BUFFER_SZ * sizeof(WCHAR), NULL, NULL),
		NULL,
		SOS_LOG_ERROR("WideCharToMultiByte failed."); 
	);
#endif // !defined(UNICODE) && !defined(_UNICODE)

	return (const TCHAR*)guidStringBuffer;
}

const TCHAR* GetExecutableFilePath()
{
	static TCHAR s_moduleFilePathBuffer[MAX_PATH + 1];
	HMODULE hInstanceHandle = NULL;
	const TCHAR* executableFilePath = NULL;

	SOS_RETURN_IF_NULL(hInstanceHandle = GetModuleHandleA(NULL),
		NULL,
		SOS_LOG_ERROR("GetModuleHandleA failed: %s.", SOS_LAST_ERROR_MESSAGE);
		);

#pragma warning(push)
#pragma warning(disable:4996)

	if(GetModuleFileName(hInstanceHandle, s_moduleFilePathBuffer, MAX_PATH + 1) <= 0)
	{
		SOS_LOG_ERROR("GetModuleFileNameA failed: %s.", SOS_LAST_ERROR_MESSAGE);
		executableFilePath = _tpgmptr;	
	}
	executableFilePath = s_moduleFilePathBuffer;
#pragma warning(pop)
	return executableFilePath;
}

