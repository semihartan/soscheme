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
#include "util.h"
#include "log.h"
#include "soserror.h"

#include "schemes.h"
#include "set.h"
#include "start.h"
#include "change.h"
#include "stop.h"
#include "persistent.h"
#include "help.h"
#include "install.h"

#pragma comment(lib, "powrprof.lib")

typedef BOOL(WINAPI GUIDFromString_ft)(_In_ LPCSTR szGuid, _Out_ LPGUID pGuid);


typedef int (ProcessCommandProc_t)(int argc, const TCHAR* argv[]);
 
static struct {
    const TCHAR* name;
    const TCHAR* alias;
    ProcessCommandProc_t* callback;
} commandCallbacks[] = {
     __T("--help"), __T("-h"), ProcessCommandHelp,
     __T("schemes"), __T(""), ProcessCommandSchemes,
     __T("set"),  __T(""), ProcessCommandSet,
     __T("start"),  __T(""), ProcessCommandStart,
     __T("change"),  __T(""), ProcessCommandChange,
     __T("stop"),  __T(""), ProcessCommandStop,
     __T("install"),  __T(""), ProcessCommandInstall,
     __T("persistent"),  __T(""), ProcessCommandPersistent,
};
 
/**
 * Description: setoscheme is a command line tool for managing power overlay schemes on Windows 10/11.
 * It allows to query and set temporary/permanent schemes available on the system.
 * Usage: soscheme.exe <command> <args>
 * --help, -h   						Prints this help message.
 * schemes								Display all available overlay schemes.
 * set <scheme>							Set the active scheme to <scheme>. <scheme> is 
 *										the alias or GUID of the scheme.
 * start <scheme>						Set the scheme persistently.
 * stop				    				Reset the scheme to the previous one.
 * install <path>                       Installs itself into the desired location and 
 *                                      modifies the PATH var accordingly.
 * internal args:
 * soscheme persistent
 */
int _tmain(int argc, const TCHAR* argv[])
{
#pragma warning(push)
#pragma warning(disable: 4996)
    OSVERSIONINFO osvi;

    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    GetVersionEx(&osvi);

#pragma warning(pop)

    HRESULT hr = S_OK;
   
    SOS_HALT_IF_FAILED(hr = SosOverlayScheme_Init(),
        SOS_REPORT_APP_ERROR(););

    if (argc == 1)
    {
        PrintUsage();
        return 0;
    }
    for (size_t i = 0; i < ARRAYSIZE(command_callback_table); i++)
    {
        if (strcmp(argv[1], command_callback_table[i].command_name) == 0)
        {
            return command_callback_table[i].callback(argc, argv);
        }
    }  
    return EXIT_SUCCESS;
}

static void PrintUsage()
{
    printf("soscheme.exe <command> <args>\n");
    printf("schemes                 Display all available overlay schemes.\n");
    printf("set <scheme>            Set the overlay scheme to <scheme>. <scheme> is\n"
        "                        the name of the scheme.\n");
    printf("start <scheme>			Set the overlay scheme persistently.\n");
    printf("change <scheme>         Change the persistent overlay scheme.\n");
    printf("stop                    Reset the overlay scheme to the previous scheme.\n");
}