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

#include "start.h" 

#include "oscheme.h"
#include "soserror.h"
#include "util.h"
#include "log.h"

#define MSG_APPLICATION_RUNNING     "One instance of the application already exists.\n"

static TCHAR s_commandLineBuffer[MAX_PATH];
static char s_commandLineBuffer[MAX_PATH];

static HANDLE s_hProcessKillEvent = NULL;
static HANDLE s_hFileMappingObject = NULL;

static STARTUPINFOA s_startupInfo;
static PROCESS_INFORMATION s_processInfo;

//"start <scheme>			Set the overlay scheme persistently.\n");
int ProcessCommandStart(int argc, const TCHAR* argv[])
{
    HRESULT hr;
    PVOID pSharedMemoryBuffer;
    const TCHAR* persistentSchemeMoniker = argv[1];
    HMODULE hInstanceHandle;
    const TCHAR* executableFilePath = NULL;

    UNREFERENCED_PARAMETER(argc);
    
    // The event handle must be inherited. Read the notes below!!
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;

    s_hProcessKillEvent = CreateEventA(&sa, FALSE, FALSE, SOS_PROCESS_KILL_EVENT_NAME);
   
    SOS_HALT_IF_NULL(s_hProcessKillEvent = CreateEventA(&sa, FALSE, FALSE, SOS_PROCESS_KILL_EVENT_NAME),
        SOS_REPORT_HR_ERROR(SOS_E_WIN32);
        SOS_LOG_ERROR("CreateEventA failed: %s.", SOS_LAST_ERROR_MESSAGE);
        );
    
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        fputs(MSG_APPLICATION_RUNNING, stderr);
        return EXIT_SUCCESS;
    }
    // When the hFile parameter is INVALID_HANDLE_VALUE, the system allocates a file mapping object
    // backed by the system swap file.
    SOS_HALT_IF_NULL(s_hFileMappingObject = CreateFileMapping(
        INVALID_HANDLE_VALUE,
        &sa,
        PAGE_READWRITE,
        0,
        SOS_SHARED_MEMORY_SIZE,
        SOS_FILE_MAPPING_OBJECT_NAME),
        SOS_REPORT_HR_ERROR(SOS_E_WIN32);
        SOS_LOG_ERROR("CreateFileMapping failed: %s.", SOS_LAST_ERROR_MESSAGE);
        );

    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        fputs(MSG_APPLICATION_RUNNING, stderr);
        return EXIT_SUCCESS;
    }
     

    SOS_HALT_IF_NULL(pSharedMemoryBuffer = MapViewOfFile(
        s_hFileMappingObject, // handle to map object
        FILE_MAP_ALL_ACCESS,  // read/write permission
        0,
        0,
        SOS_SHARED_MEMORY_SIZE),
        SOS_REPORT_HR_ERROR(SOS_E_WIN32);
        SOS_LOG_ERROR("MapViewOfFile failed: %s.", SOS_LAST_ERROR_MESSAGE);
        CloseHandle(s_hFileMappingObject);
        ); 

    _tcscpy_s((TCHAR*)pSharedMemoryBuffer, SOS_SHARED_MEMORY_SIZE, persistentSchemeMoniker);
    
    SOS_HALT_IF_NULL(hInstanceHandle = GetModuleHandleA(NULL),
        SOS_REPORT_HR_ERROR(SOS_E_WIN32);
        SOS_LOG_ERROR("GetModuleHandleA failed: %s.", SOS_LAST_ERROR_MESSAGE);
        );

    SOS_HALT_IF((retSize = GetModuleFileNameA(hInstanceHandle, s_moduleFilePathBuffer, MAX_PATH)) <= 0,
    _stprintf_s(s_commandLineBuffer, MAX_PATH, _T("soscheme persistent %s"), persistentSchemeMoniker);
        SOS_LOG_ERROR("GetModuleFileNameA failed: %s.", SOS_LAST_ERROR_MESSAGE);
        _get_pgmptr(&pgmptr);
        executableFilePath = pgmptr;
        );
     
    sprintf_s(s_commandLineBuffer, MAX_PATH, "soscheme persistent %s", persistentSchemeMoniker);

    /*
    * An important point.
    * These parameters only have effect when you ask for the CreateProcess function to create a new 
    * console for the newly created child process. Otherwise, they have no effect.
    */
    s_startupInfo.cb = sizeof(s_startupInfo);
    s_startupInfo.lpDesktop = _T("WinSta0\\Default");
    s_startupInfo.lpTitle = _T("soscheme (Persistancy Mode)");
    s_startupInfo.dwFlags = STARTF_USESHOWWINDOW;
    s_startupInfo.wShowWindow = SW_HIDE; 

    // When creating a new child process, it is crucial to specify the bInheriteHandles parameter as 
    // TRUE. Otherwise, the child process cannot retrieve the event handle and this causes a subtle bug 
    // in the chiild process causing it being suspended forever.
    SOS_HALT_IF_NOT(CreateProcess(executableFilePath, _T("soscheme persistent"), NULL, NULL,
        TRUE, // Inherit the handles.
        CREATE_NEW_CONSOLE, // Allocate a new console object for the child.
        NULL, NULL, &s_startupInfo, &s_processInfo),
        SOS_REPORT_HR_ERROR(SOS_E_WIN32);
        SOS_LOG_ERROR("CreateProcessA failed: %s.", SOS_LAST_ERROR_MESSAGE););
    
    CloseHandle(s_processInfo.hProcess);
    CloseHandle(s_processInfo.hThread);

    UnmapViewOfFile(pSharedMemoryBuffer);
    CloseHandle(s_hFileMappingObject);
    return EXIT_SUCCESS;
}