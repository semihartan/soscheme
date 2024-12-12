#include <pch.h>

#include "soserror.h"

#define MESSAGE_BUFFER_SZ	0xFFF

static WCHAR s_messageBuffer[MESSAGE_BUFFER_SZ + 1];

static const wchar_t* GetErrorMessageCore(HRESULT _ErrorCode, bool _isSystem)
{
	DWORD cbChars = FormatMessageW(_isSystem ?
		FORMAT_MESSAGE_FROM_HMODULE :
		FORMAT_MESSAGE_FROM_HMODULE,
		NULL,
		_ErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		s_messageBuffer,
		MESSAGE_BUFFER_SZ + 1, NULL);
	return cbChars == 0 ? L"FormatMessage failed." : s_messageBuffer;
}

const wchar_t* SosGetSystemErrorMessage(DWORD dwErrorCode)
{
	return GetErrorMessageCore(dwErrorCode, true);
}

const wchar_t* SosGetApplicationErrorMessage(HRESULT _ErrorCode)
{
	return GetErrorMessageCore(_ErrorCode, false);
}