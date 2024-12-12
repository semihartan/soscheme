//static BOOL 

static BOOL GetSchemeFriendlyName(HKEY hkPowerScheme, LPWSTR _lpFriendlyName, DWORD _dwBufferInCount, PDWORD _dwRequiredCount)
{
	

	/*if (IsGuidEmpty(_SchemeGuid))
	{
		if (_dwBufferInCount < 9)
		{
			fprintf(stderr, "Insufficient buffer size.\n");
			return FALSE;
		}
		wcscpy(_lpFriendlyName, L"Balanced");
		return TRUE;
	}*/

	

	swprintf(szTempBuffer, TEMP_BUFFER_SZ, L"%s\\", guidString);
	LSTATUS ls = RegOpenKeyW(hkPowerSchemes, szTempBuffer, &hkPowerScheme);
	if (ERROR_SUCCESS != ls)
	{
		fprintf(stderr, "Failed to opensub key %s.\n", szTempBuffer);
		return FALSE;
	}
	*_dwRequiredCount = _dwBufferInCount;
	
	return TRUE;
}