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

#include "change.h"

#include "oscheme.h"
#include "soserror.h"
#include "log.h"
#include "util.h"

//change <scheme>         Change the persistent overlay scheme.
int ProcessCommandChange(int argc, const TCHAR* argv[])
{
	HRESULT hr = S_OK;
	HANDLE s_hFileMappingObject = NULL;
	PVOID s_pSharedMemoryBuffer = NULL; 

	UNREFERENCED_PARAMETER(argc);
	
	if (argc != 2)
		return EXIT_INVALID_SYNTAX;

	s_hFileMappingObject = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,	// read/write access
		FALSE,					// no need to inherit the handle
		SOS_FILE_MAPPING_OBJECT_NAME),
		SOS_REPORT_HR_ERROR(SOS_E_WIN32);
		SOS_REPORT_WIN32_ERROR();
		SOS_LOG_ERROR("OpenFileMappingA failed: %s.", SOS_LAST_ERROR_MESSAGE););

	SOS_HALT_IF_NULL(s_pSharedMemoryBuffer = MapViewOfFile(
		s_hFileMappingObject,	// handle to map object
		FILE_MAP_ALL_ACCESS,	// read/write permission
		0,
		0,
		SOS_SHARED_MEMORY_SIZE),
		SOS_REPORT_HR_ERROR(SOS_E_WIN32);
		SOS_LOG_ERROR("MapViewOfFile failed: %s.\n", SOS_LAST_ERROR_MESSAGE);
		CloseHandle(s_hFileMappingObject););

	_tcscpy_s((TCHAR*)s_pSharedMemoryBuffer, SOS_SHARED_MEMORY_SIZE, argv[1]);

	SOS_HALT_IF_FAILED(hr = SosOverlayScheme_SetActiveSchemeByAlias(argv[2]),
		SOS_REPORT_APP_ERROR();
		CloseHandle(s_hFileMappingObject););
	 
	UnmapViewOfFile(s_pSharedMemoryBuffer); 
	CloseHandle(s_hFileMappingObject);
	return EXIT_SUCCESS;
}
