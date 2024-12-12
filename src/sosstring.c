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