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

#pragma comment(lib, "powrprof.lib")

typedef BOOL(WINAPI GUIDFromString_ft)(_In_ LPCSTR szGuid, _Out_ LPGUID pGuid);


typedef int (ProcessCommandProc_t)(int argc, const char* argv[]);
 
static struct {
    const char* command_name;
    ProcessCommandProc_t* callback;
} command_callback_table[] = {
     "schemes", ProcessCommandSchemes,
     "set", ProcessCommandSet,
     "start", ProcessCommandStart,
     "change", ProcessCommandChange,
     "stop", ProcessCommandStop,
     "persistent", ProcessCommandPersistent,
};
 
static void PrintUsage();

/**
 * setoscheme is a command line tool for managing power overlay schemes on Windows 10/11.
 * It allows to query and set temporary/permanent schemes available on the system.
 * soscheme.exe <command> <args>
 * schemes								Display all available overlay schemes.
 * set <scheme>							Set the active scheme to <scheme>. <scheme> is 
 *										the alias or GUID of the scheme.
 * start <scheme>						Set the scheme persistently.
 * stop				    				Reset the scheme to the previous one.
 * install                              Installs itself into the desired location and 
 *                                      modifies the PATH var accordingly.
 * internal args:
 * soscheme persistent start <scheme>
 * soscheme persistent stop
 */

int main(int argc, char* argv[])
{
#pragma warning(push)
#pragma warning(disable: 4996)
    OSVERSIONINFO osvi;

    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    GetVersionEx(&osvi);

#pragma warning(pop)

    HRESULT hr = S_OK;
   
    SOS_HALT_IF(FAILED(hr = SosOverlayScheme_Init()));

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