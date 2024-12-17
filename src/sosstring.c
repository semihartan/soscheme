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

#include "sosstring.h"
#include "soserror.h" 


//sosstring_t sosstring_new(const wchar_t* _CStr)
//{
//	size_t strLen = wcslen(_CStr);
//	const char* cstr = malloc(sizeof(*cstr) * (strLen + 1) + sizeof(size_t));
//	*(size_t*)cstr = strLen;
//	cstr += sizeof(size_t);
//	wcscpy_s(cstr, strLen + 1, _CStr);
//	return cstr;
//}

const wchar_t* sosstring_ContainsStrings(const wchar_t* _String, int _CountStrings, ...)
{
	va_list ap;
	wchar_t* ret = NULL;

	SOS_RETURN_IF_NULL(ret = _wcsdup(_String), ret);

	wchar_t* strLowerCase = _wcslwr(ret);
	va_start(ap, _CountStrings);
	for (size_t i = 0; i < _CountStrings; i++)
	{
		const wchar_t* str = va_arg(ap, wchar_t*);

		SOS_RETURN_IF_NULL(ret = _wcsdup(str), ret);
		
		wchar_t* lowerCase = _wcslwr(ret);
		if ((ret = wcsstr(strLowerCase, lowerCase), free(lowerCase), ret))
			break;
	}
	free(strLowerCase);
	return ret;
}