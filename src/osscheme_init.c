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

HRESULT SosOverlayScheme_Init()
{
#define SUBKEY_BUFFER_SZ		MAX_PATH
	static TCHAR szSubKeyBuffer[SUBKEY_BUFFER_SZ];
	static TCHAR szKeyValueBuffer[OS_NAME_BUF_SZ];
	static TCHAR friendlyName[OS_NAME_BUF_SZ];
	static TCHAR description[OS_NAME_BUF_SZ];

	GUID* overlaySchemeGuids = NULL;
	DWORD overlaySchemeCount = 0;
	HKEY hkPowerScheme;
	HKEY hkPowerSchemes;
	HRESULT hr;
	
	if (s_isInitialized)
		return S_OK;
	/*
	* !NOT RELEVANT ANYMORE! This execution path is a part of our main logic. It is a critical path, meaning that if something
	* fails at any point in it, we should stop immediately.
	*/
	SOS_RETURN_IFN_SUCCESS(hr = PowerGetOverlaySchemes(&overlaySchemeGuids, &overlaySchemeCount, 0),
		SOS_E_QUERY_SCHEMES,
		SOS_LOG_ERROR("PowerGetOverlaySchemes failed."););

	SOS_RETURN_IFN_SUCCESS(hr = RegOpenKeyEx(HKEY_LOCAL_MACHINE, POWER_SCHEMES_KEY, 0, KEY_READ, &hkPowerSchemes),
		SOS_E_REGOPEN,
		SOS_LOG_ERROR("RegOpenKeyEx(key=%s) failed: %s.", POWER_SCHEMES_KEY, SOS_LAST_ERROR_MESSAGE););

	for (size_t i = 0; i < overlaySchemeCount; ++i)
	{
		GUID* pOverlaySchemeGuid = overlaySchemeGuids + i;

		
		_stprintf_s(szSubKeyBuffer, SUBKEY_BUFFER_SZ, _T("%s\\"), SosConvertGuidToString(pOverlaySchemeGuid));

		SOS_RETURN_IFN_SUCCESS(hr = RegOpenKeyEx(hkPowerSchemes, szSubKeyBuffer, 0, KEY_READ, &hkPowerScheme),
			SOS_E_REGOPEN,
			SOS_LOG_ERROR("RegOpenKeyEx(key=%s) failed: %s.", szSubKeyBuffer, SOS_LAST_ERROR_MESSAGE););

		// Begin: Get the friendly name.
		SOS_RETURN_IFN_SUCCESS(hr = GetPowerSchemeAttribute(hkPowerScheme, _T("FriendlyName"), szKeyValueBuffer), 
			SOS_E_SCHEMEATTR);

		TCHAR seps[] = _T(",");
		TCHAR* ctx = NULL;
		_tcstok_s(szKeyValueBuffer, seps, &ctx);	// Skip to the rightmost item.
		_tcstok_s(NULL, seps, &ctx);	// Skip to the rightmost item.
		_tcscpy_s(friendlyName, OS_NAME_BUF_SZ, _tcstok_s(NULL, seps, &ctx));
		// End: Get the friendly name.

		// Begin: Get the description.
		SOS_RETURN_IF_NOT(
			SOS_IF_ERROR_SUCCESS(hr = GetPowerSchemeAttribute(hkPowerScheme, _T("Description"), szKeyValueBuffer)),
			SOS_E_SCHEMEATTR);

		ctx = NULL;
		_tcstok_s(szKeyValueBuffer, seps, &ctx);	// Skip to the rightmost item.
		_tcstok_s(NULL, seps, &ctx);	// Skip to the rightmost item.
		_tcscpy_s(description, OS_NAME_BUF_SZ, _tcstok_s(NULL, seps, &ctx));
		// End: Get the description.

		if (sosstring_ContainsStrings(friendlyName, 2, PERFORMANCE_KEYWORDS))
		{
			_tcscpy_s(s_overlaySchemes[2].friendlyName, OS_NAME_BUF_SZ, friendlyName);
			_tcscpy_s(s_overlaySchemes[2].description, OS_NAME_BUF_SZ, description);
			s_overlaySchemes[2].alias = _T("performance");
			memcpy_s(&s_overlaySchemes[2].guid, sizeof(GUID), pOverlaySchemeGuid, sizeof(GUID));
		}

		if (sosstring_ContainsStrings(friendlyName, 4, POWER_SAVER_KEYWORDS))
		{
			_tcscpy_s(s_overlaySchemes[0].friendlyName, OS_NAME_BUF_SZ, friendlyName);
			_tcscpy_s(s_overlaySchemes[0].description, OS_NAME_BUF_SZ, description);
			s_overlaySchemes[0].alias = _T("powersaver");
			memcpy_s(&s_overlaySchemes[0].guid, sizeof(GUID), pOverlaySchemeGuid, sizeof(GUID));
		}
		RegCloseKey(hkPowerScheme);
	}
	RegCloseKey(hkPowerSchemes);
	s_isInitialized = true;
	return S_OK;
}