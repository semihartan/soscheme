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

#if !defined(SOS_STATIC_LIB) && !defined(SOS_SHARED_LIB)

#include "log.h"

#define LOG_FILE_NAME		_T("soscheme.log")

void SosLog(const TCHAR* _File, const TCHAR* _Function, uint32_t _Line, const TCHAR* _Format, ...)
{
	static TCHAR timeBuffer[26];
	const wchar_t* fileName = wcsrchr(_File, L'\\');
	fwprintf(logFile, L"%s(%u), %s: ", ++fileName, _Line, _Function);
	FILE* logFile = _tfopen(LOG_FILE_NAME, _T("a, ccs=UTF-16LE"));
	const TCHAR* fileName = _tcsrchr(_File, _T('\\'));
	va_list ap;
	va_start(ap, _Format);
	_vftprintf_s(logFile, _Format, ap);
	va_end(ap);
	fclose(logFile);
}

#endif