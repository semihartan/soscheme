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

#include "oscheme.h"

#include "upowr.h"
#include "util.h"
#include "sosstring.h"
#include "soserror.h"
#include "log.h"
 
#define SCHEMES_COUNT	ARRAYSIZE(s_overlaySchemes)

#define BALANCED_SCHEME_INIT \
{ L"Balanced" }, \
{ L"Automatically balances performance with energy consumption on capable hardware." }, \
L"balanced", \
{ 0x00000000, 0x0000, 0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} }

#define POWER_SCHEMES_KEY	_T("SYSTEM\\CurrentControlSet\\Control\\Power\\User\\PowerSchemes\\")
#define PERFORMANCE_KEYWORDS _T("max"), _T("maximum")
#define POWER_SAVER_KEYWORDS _T("battery"), _T("saver"), _T("saving"),  _T("efficiency")

static bool s_isInitialized = false;

static OverlayScheme_t s_overlaySchemes[3] = { {0}, {BALANCED_SCHEME_INIT}, {0} };

static const TCHAR* s_powerSavingKeywords[] = { POWER_SAVER_KEYWORDS };
static const TCHAR* s_performanceKeywords[] = { PERFORMANCE_KEYWORDS };

static HRESULT GetPowerSchemeAttribute(HKEY _hkPowerScheme, const TCHAR* _AttrName, TCHAR* _Buffer);

static bool IsGuidValid(const GUID* _schemeGuid);
static bool IsSchemeValid(const OverlayScheme_t* _scheme);

#include "osscheme_init.c"

HRESULT SosOverlayScheme_GetSchemes(OverlayScheme_t** _overlaySchemes, size_t* _count)
{
	SOS_ASSERT(("The library is not initialized.", s_isInitialized), SOS_E_UNINITIALIZED);
	SOS_ASSERT(_overlaySchemes != NULL, 
		E_INVALIDARG, SOS_LOG_ERROR("Invalid parameter: _overlaySchemes==NULL.\n"););
	SOS_ASSERT(_count != NULL,
		E_INVALIDARG, SOS_LOG_ERROR("Invalid parameter: _count==NULL.\n"););
	
	SOS_RETURN_IF_NULL(*_overlaySchemes = (OverlayScheme_t*)malloc(sizeof(**_overlaySchemes) * SCHEMES_COUNT),
		E_OUTOFMEMORY,
		SOS_LOG_ERROR("malloc failed.\n"););

	memcpy_s(*_overlaySchemes, sizeof(**_overlaySchemes) * SCHEMES_COUNT, s_overlaySchemes, sizeof(**_overlaySchemes) * SCHEMES_COUNT);

	*_count = SCHEMES_COUNT;
	return S_OK;
}

HRESULT SosOverlayScheme_GetActiveScheme(OverlayScheme_t** _activeScheme)
{
	HRESULT hr;
	static GUID activeScheme;
	
	SOS_ASSERT(s_isInitialized, SOS_E_UNINITIALIZED);
	SOS_ASSERT(_activeScheme != NULL, SOS_E_INVALID);
	
	/*SOS_RETURN_IF_NULL(activeScheme = (GUID*)LocalAlloc(LPTR, sizeof(GUID)),
		E_OUTOFMEMORY,
		SOS_LOG_ERROR("LocalAlloc failed: %s.\n", SOS_LAST_ERROR_MESSAGE););*/

	SOS_RETURN_IFN_SUCCESS(hr = PowerGetActualOverlayScheme(&activeScheme),
		SOS_E_GET_SCHEME,
		SOS_LOG_ERROR("PowerGetActualOverlayScheme failed.\n"););

	for (size_t i = 0; i < SCHEMES_COUNT; i++)
	{ 
		if (memcmp(&s_overlaySchemes[i].guid, &activeScheme, sizeof(GUID)) == 0)
		{ 
			*_activeScheme = &s_overlaySchemes[i];
			break;
		}
	}
	return S_OK;
}

HRESULT SosOverlayScheme_SetActiveScheme(const OverlayScheme_t* _scheme)
{ 
	HRESULT hr;
	SOS_RETURN_IF_NOT(IsSchemeValid(_scheme), 
		SOS_E_INVALID,
		SOS_LOG_ERROR("The scheme is not valid.\n"););

	SOS_RETURN_IFN_SUCCESS(hr = PowerSetActiveOverlayScheme(&_scheme->guid), 
		SOS_E_SET_SCHEME,
		SOS_LOG_ERROR("PowerSetActiveOverlayScheme failed."););

	return S_OK;
}

HRESULT SosOverlayScheme_SetActiveSchemeByGuid(const GUID* _guid)
{
	HRESULT hr;

	SOS_RETURN_IF_NOT(IsGuidValid(_guid), 
		SOS_E_INVALID,
		SOS_LOG_ERROR("The scheme is not valid.\n"););

	SOS_RETURN_IFN_SUCCESS(hr = PowerSetActiveOverlayScheme(_guid),
		SOS_E_SET_SCHEME,
		SOS_LOG_ERROR("PowerSetActiveOverlayScheme failed."););

	return S_OK;
}
 
HRESULT SosOverlayScheme_SetActiveSchemeByAlias(const TCHAR* _alias)
{
	HRESULT hr;

	SOS_ASSERT(s_isInitialized, 
		SOS_E_UNINITIALIZED,
		SOS_LOG_ERROR("SosOverlayScheme_init was not called.\n"););
	for (size_t i = 0; i < SCHEMES_COUNT; i++)
	{
		const GUID* schemeGuid = &s_overlaySchemes[i].guid;

		if (_tcscmp(s_overlaySchemes[i].alias, _alias) == 0)
		{
			SOS_RETURN_IFN_SUCCESS(hr = PowerSetActiveOverlayScheme(schemeGuid),
				SOS_E_SET_SCHEME,
				SOS_LOG_ERROR("PowerSetActiveOverlayScheme failed."););
			return S_OK;
		}
	}
	return SOS_E_INVALID;
}

// BEGIN: HELPER FUNCTIONS
static bool IsGuidValid(const GUID* _schemeGuid)
{
	SOS_ASSERT(s_isInitialized, 
		SOS_E_UNINITIALIZED,
		SOS_LOG_ERROR("SosOverlayScheme_init was not called.\n"););
	for (size_t i = 0; i < SCHEMES_COUNT; i++)
	{
		if (memcmp(&s_overlaySchemes[i].guid, _schemeGuid, sizeof(GUID)) == 0)
		{
			return true;
		}
	}
	return false;
}

static bool IsSchemeValid(const OverlayScheme_t* _scheme)
{
	return IsGuidValid(&_scheme->guid);
}

static HRESULT GetPowerSchemeAttribute(HKEY _hkPowerScheme, const TCHAR* _AttrName, TCHAR* _Buffer)
{
	HRESULT hr;
	DWORD pcbData = OS_NAME_BUF_SZ;
	SOS_RETURN_IFN_SUCCESS(hr = RegGetValue(_hkPowerScheme, NULL, _AttrName, RRF_RT_REG_SZ, NULL, _Buffer, &pcbData),
		SOS_E_REGGET,
		SOS_LOG_ERROR("RegGetValue(value=%s) failed: %s.", _AttrName, SOS_LAST_ERROR_MESSAGE);
	);
	return S_OK;
}
// END: HELPER FUNCTIONS