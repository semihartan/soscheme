#include <pch.h>

#include "install.h"
#include "soserror.h"
#include "util.h"
#include "log.h"

#define DEFAULT_LOCATION	_T("C:\\Program Files\\soscheme")
#define NT_PATH_SEP			_T("\\")


int ProcessCommandInstall(int argc, const TCHAR* argv[])
{
	static TCHAR s_pathVariableBuffer[0xFFFF];
	static TCHAR s_filePathBuffer[MAX_PATH + 1];
	const TCHAR* installationLocation = DEFAULT_LOCATION;
	const TCHAR* executableFilePath = NULL;
	const TCHAR* destFilePath = NULL;
	HRESULT hr;
	HKEY hkEnvironment = NULL;
	DWORD dwBufferSz = sizeof(s_pathVariableBuffer);

	if (argc == 1)
	{
		if (PathIsDirectory(argv[0]))
			installationLocation = argv[0];
		else
		{
			SOS_REPORT_ERROR(ERROR_PATH_NOT_FOUND);
			return EXIT_FAILURE;
		}
	}
	else
	{
		if (!PathIsDirectory(DEFAULT_LOCATION))
			SOS_HALT_IF_FAILED(_tmkdir(DEFAULT_LOCATION),
				SOS_REPORT_ERROR(SOS_E_CREATE_DIR);
				SOS_LOG_ERROR("_tmkdir failed: %s.", SOS_ERRNO_MESSAGE);
				);
	}
	executableFilePath = GetExecutableFilePath();
	_tcscpy_s(s_filePathBuffer, _tcsnlen(installationLocation, MAX_PATH) + 1, installationLocation);
	_tcscat_s(s_filePathBuffer, MAX_PATH + 1, NT_PATH_SEP);
	_tcscat_s(s_filePathBuffer, MAX_PATH + 1, _tcsrchr(executableFilePath, _T('\\')) + 1);
	destFilePath = s_filePathBuffer;

	SOS_HALT_IF_FALSE(CopyFile(executableFilePath, destFilePath, FALSE),
		SOS_REPORT_WIN32_ERROR();
		SOS_LOG_ERROR("CopyFile failed: %s.\n", SOS_LAST_ERROR_MESSAGE);
		);

	SOS_HALT_IFN_SUCCESS(hr = RegOpenKeyEx(HKEY_CURRENT_USER, _T("Environment\\"), 0, KEY_QUERY_VALUE | KEY_SET_VALUE, &hkEnvironment),
		SOS_REPORT_WIN32_ERROR();
		SOS_LOG_ERROR("RegOpenKeyEx(key=%s) failed: %s.", _T("Environment\\"), SOS_HRESULT_MESSAGE(hr));
		);

	SOS_HALT_IFN_SUCCESS(hr = RegGetValue(hkEnvironment, NULL, _T("Path"), RRF_RT_REG_EXPAND_SZ | RRF_NOEXPAND, NULL, s_pathVariableBuffer, &dwBufferSz),
		SOS_REPORT_WIN32_ERROR();
		SOS_LOG_ERROR("RegGetValue(value=%s) failed: %s.", _T("Path"), SOS_HRESULT_MESSAGE(hr));
		);

	_tcscat_s(s_pathVariableBuffer, 0xFFFF, installationLocation);
	_tcscat_s(s_pathVariableBuffer, 0xFFFF, _T(";"));
	dwBufferSz = sizeof(s_pathVariableBuffer[0]) * (_tcsnlen(s_pathVariableBuffer, 0xFFFF) + 1);
	SOS_HALT_IFN_SUCCESS(hr = RegSetValueEx(hkEnvironment, _T("Path"), 0, REG_EXPAND_SZ, (const BYTE*)s_pathVariableBuffer, dwBufferSz),
		SOS_REPORT_WIN32_ERROR();
	SOS_LOG_ERROR("RegSetValue(value=%s) failed: %s.", _T("Path"), SOS_HRESULT_MESSAGE(hr));
		);
	return EXIT_SUCCESS;
}