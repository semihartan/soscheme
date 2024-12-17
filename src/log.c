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

#include "log.h"

#define LOG_FILE_NAME		L"soscheme.log"

void SosLog(const wchar_t* _File, const wchar_t* _Function, uint32_t _Line, const wchar_t* _Format, ...)
{
	FILE* logFile = _wfopen(LOG_FILE_NAME, L"a, ccs=UTF-16LE");
	const wchar_t* fileName = wcsrchr(_File, L'\\');
	fwprintf(logFile, L"%s(%u), %s: ", ++fileName, _Line, _Function);
	va_list ap;
	va_start(ap, _Format);
	vfwprintf_s(logFile, _Format, ap);
	va_end(ap);
	fclose(logFile);
}