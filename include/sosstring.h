#pragma once

#ifndef STRING_H
#define STRING_H	1

#include <pch.h>

SOS_BEGIN

#define SOSSTRING_MAGIC			'RTSSOS'
#define SOSSTRING_LEN(str)		*(size_t*)((char*)(str) - sizeof(size_t))

typedef const wchar_t* sosstring_t;

//sosstring_t sosstring_new(const wchar_t* _CStr);

const wchar_t* sosstring_ContainsStrings(const wchar_t* _String, int _CountStrings, ...);

SOS_END

#endif