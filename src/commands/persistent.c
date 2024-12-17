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

#include "persistent.h"

#include "oscheme.h"
#include "soserror.h"
#include "util.h"
#include "log.h"

#pragma comment(lib, "powrprof.lib")

static bool s_isPersistentSchemeSet = FALSE;
static const TCHAR* s_previousSchemeMoniker = NULL;
static const TCHAR* s_persistentSchemeMoniker = NULL;

static HANDLE s_hFileMappingObject = NULL;
static PVOID s_pSharedMemoryBuffer = NULL;
static void* s_effectiveModeChangeNotificationHandle = NULL;

static void __stdcall EffectiveModeChangeCallback(_In_ EFFECTIVE_POWER_MODE Mode, _In_opt_ VOID* Context);
static void DoCleanUp();

int ProcessCommandPersistent(int argc, const TCHAR* argv[])
{
	HRESULT hr;
	OverlayScheme_t* activeScheme = NULL;
	HANDLE hProcessKillEvent;

	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	SOS_HALT_IF_NULL(hProcessKillEvent = OpenEvent(EVENT_ALL_ACCESS,
		FALSE, SOS_PROCESS_KILL_EVENT_NAME),
		SOS_REPORT_WIN32_ERROR();
		SOS_LOG_ERROR("OpenEvent failed: %s.\n", SOS_LAST_ERROR_MESSAGE););

	SOS_HALT_IF_NULL(s_hFileMappingObject = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,   // read/write access
		FALSE,                 // do not inherit the name
		SOS_FILE_MAPPING_OBJECT_NAME),
		SOS_REPORT_WIN32_ERROR();
		SOS_LOG_ERROR("OpenFileMapping failed: %s.\n", SOS_LAST_ERROR_MESSAGE););
	 
	SOS_HALT_IF_NULL(s_pSharedMemoryBuffer = MapViewOfFile(
		s_hFileMappingObject, // handle to map object
		FILE_MAP_ALL_ACCESS,  // read/write permission
		0,
		0,
		SOS_SHARED_MEMORY_SIZE),
		SOS_REPORT_WIN32_ERROR();
		SOS_LOG_ERROR("MapViewOfFile failed: %s.", SOS_LAST_ERROR_MESSAGE);
		CloseHandle(s_hFileMappingObject););
	  
	SOS_HALT_IF_FAILED(hr = PowerRegisterForEffectivePowerModeNotifications(EFFECTIVE_POWER_MODE_V2, EffectiveModeChangeCallback, NULL, &s_effectiveModeChangeNotificationHandle),
		SOS_REPORT_WIN32_ERROR();
		SOS_LOG_ERROR("PowerRegisterForEffectivePowerModeNotifications failed: %s.",
		SOS_HRESULT_MESSAGE(hr));); 

	s_persistentSchemeMoniker = (const TCHAR*)s_pSharedMemoryBuffer;

	SOS_HALT_IF_FAILED(hr = SosOverlayScheme_GetActiveScheme(&activeScheme),
		SOS_REPORT_HR_ERROR();
		DoCleanUp(););
	s_previousSchemeMoniker = activeScheme->alias;
	
	SOS_HALT_IF_FAILED(hr = SosOverlayScheme_SetActiveSchemeByAlias(s_persistentSchemeMoniker),
		SOS_REPORT_HR_ERROR();
		DoCleanUp(););
	 
	s_isPersistentSchemeSet = TRUE;

	SOS_HALT_IF_NOT(WAIT_OBJECT_0 != WaitForSingleObject(hProcessKillEvent, INFINITE),
		SOS_REPORT_WIN32_ERROR();
		SOS_LOG_ERROR("WaitForSingleObject failed: %s.", SOS_LAST_ERROR_MESSAGE);
		DoCleanUp(););
	
	// Restore the previous active overlay scheme.
	s_isPersistentSchemeSet = FALSE; 
	SOS_HALT_IF_FAILED(hr = SosOverlayScheme_SetActiveSchemeByAlias(s_previousSchemeMoniker),
		SOS_REPORT_HR_ERROR();
	DoCleanUp(););
		
	DoCleanUp();
	return EXIT_SUCCESS;
}

static void __stdcall EffectiveModeChangeCallback(_In_ EFFECTIVE_POWER_MODE _Mode, _In_opt_ VOID* _Context)
{
	HRESULT hr;
	UNREFERENCED_PARAMETER(_Mode);
	UNREFERENCED_PARAMETER(_Context);
	if (!s_isPersistentSchemeSet)
		return;
	s_persistentSchemeMoniker = (const TCHAR*)s_pSharedMemoryBuffer;
	//printf("[DEBUG] persistent scheme: %s.\n", persistentSchemeMoniker);
	SOS_HALT_IF_FAILED(hr = SosOverlayScheme_SetActiveSchemeByAlias(s_persistentSchemeMoniker),
		SOS_REPORT_WIN32_ERROR();
		DoCleanUp(); );
}

static void DoCleanUp()
{
	HRESULT hr;
	SOS_HALT_IF_FAILED(hr = PowerUnregisterFromEffectivePowerModeNotifications(s_effectiveModeChangeNotificationHandle),
		SOS_REPORT_WIN32_ERROR();
		SOS_LOG_ERROR("PowerUnregisterFromEffectivePowerModeNotifications failed: %s.", SOS_HRESULT_MESSAGE(hr));
		);
	UnmapViewOfFile(s_pSharedMemoryBuffer); 
	CloseHandle(s_hFileMappingObject);
}