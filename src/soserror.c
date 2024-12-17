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

#include "soserror.h"

#define MESSAGE_BUFFER_SZ	0xFFF

static TCHAR s_messageBuffer[MESSAGE_BUFFER_SZ + 1];

const TCHAR* SosGetErrorMessage(HRESULT _ErrorCode)
{
	DWORD cbChars = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_FROM_HMODULE,
		NULL,
		_ErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		s_messageBuffer,
		MESSAGE_BUFFER_SZ + 1, NULL);
	return cbChars == 0 ? _T("FormatMessage failed.") : s_messageBuffer;
}

const wchar_t* SosGetSystemErrorMessage(DWORD dwErrorCode)
{
	return GetErrorMessageCore(dwErrorCode, true);
}

const wchar_t* SosGetApplicationErrorMessage(HRESULT _ErrorCode)
{
	return GetErrorMessageCore(_ErrorCode, false);
}