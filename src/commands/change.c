#include <pch.h>

#include "change.h"

#include "oscheme.h"
#include "soserror.h"
#include "log.h"
#include "util.h"

int ProcessCommandChange(int argc, const char* argv[])
{
	HRESULT hr = S_OK;
	HANDLE s_hFileMappingObject = NULL;
	PVOID s_pSharedMemoryBuffer = NULL; 

	UNREFERENCED_PARAMETER(argc);
	
	SOS_HALT_IF_NULL(s_hFileMappingObject = OpenFileMappingA(
		FILE_MAP_ALL_ACCESS,	// read/write access
		FALSE,					// no need to inherit the handle
		SOS_FILE_MAPPING_OBJECT_NAME),
		SOS_REPORT_HR_ERROR(SOS_E_WIN32);
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

	strcpy_s((char*)s_pSharedMemoryBuffer, SOS_SHARED_MEMORY_SIZE, argv[2]);

	SOS_HALT_IF_FAILED(hr = SosOverlayScheme_SetActiveSchemeByAlias(argv[2]),
		SOS_REPORT_APP_ERROR();
		CloseHandle(s_hFileMappingObject););
	 
	UnmapViewOfFile(s_pSharedMemoryBuffer); 
	CloseHandle(s_hFileMappingObject);
	return EXIT_SUCCESS;
}
