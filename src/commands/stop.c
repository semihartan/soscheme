#include <pch.h>

#include "stop.h"

#include "oscheme.h"
#include "soserror.h" 
#include "log.h" 


int ProcessCommandStop(int argc, const char* argv[])
{
	HANDLE hProcessKillEvent; 

	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	SOS_HALT_IF_NULL(hProcessKillEvent = OpenEventA(EVENT_ALL_ACCESS, FALSE, SOS_PROCESS_KILL_EVENT_NAME),
		SOS_REPORT_HR_ERROR(SOS_E_WIN32);
		SOS_LOG_ERROR("OpenEventA failed: %s.", SOS_LAST_ERROR_MESSAGE););

	SOS_HALT_IF_FALSE(SetEvent(hProcessKillEvent),
		SOS_REPORT_HR_ERROR(SOS_E_WIN32);
		SOS_LOG_ERROR("SetEvent failed: %s.", SOS_LAST_ERROR_MESSAGE););
    return 0;
}