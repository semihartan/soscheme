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