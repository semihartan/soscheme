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

#include "stop.h"

#include "oscheme.h"
#include "soserror.h" 
#include "log.h" 

//stop                    Reset the overlay scheme to the previous scheme.
int ProcessCommandStop(int argc, const TCHAR* argv[])
{
	HANDLE hProcessKillEvent; 

	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	SOS_HALT_IF_NULL(hProcessKillEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, SOS_PROCESS_KILL_EVENT_NAME),

		SOS_HALT_IF(ERROR_FILE_NOT_FOUND == GetLastError(),
			printe("You have to set a permanent scheme before using \"soscheme start\""););
		SOS_REPORT_WIN32_ERROR();
		SOS_LOG_ERROR("OpenEvent failed: %s.", SOS_LAST_ERROR_MESSAGE););

	SOS_HALT_IF_FALSE(SetEvent(hProcessKillEvent),
		SOS_REPORT_WIN32_ERROR();
		SOS_LOG_ERROR("SetEvent failed: %s.", SOS_LAST_ERROR_MESSAGE););
    return 0;
}