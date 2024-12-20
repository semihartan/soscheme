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

#include "schemes.h"

#include "oscheme.h"
#include "soserror.h"
#include "util.h"

//"schemes                 Display all available overlay schemes.\n");
int ProcessCommandSchemes(int argc, const TCHAR* argv[])
{
	HRESULT hr = S_OK;
	size_t count = 0;
	OverlayScheme_t* overlaySchemes = NULL;
	OverlayScheme_t* activeScheme = NULL;

	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);
	
	SOS_HALT_IF_FAILED(hr = SosOverlayScheme_GetActiveScheme(&activeScheme),
		SOS_REPORT_HR_ERROR(););

	SOS_HALT_IF_FAILED(hr = SosOverlayScheme_GetSchemes(&overlaySchemes, &count),
		SOS_REPORT_HR_ERROR(););

	puts("[");
	for (size_t i = 0; i < count; i++)
	{
		OverlayScheme_t os = overlaySchemes[i];

		printf("{\n  \"name\": \"%s\",\n", os.alias);

		printf("  \"GUID\": \"%s\",\n", SosConvertGuidToString(&overlaySchemes[i].guid));
		bool isActive = memcmp(&overlaySchemes[i].guid, &os.guid, sizeof(GUID)) == 0;

		printf("  \"friendlyName\":  \"%s\",\n", os.friendlyName);
		printf("  \"description\":  \"%s\",\n", os.description);
		printf("  \"isActive\":  %s,\n", isActive ? _T("true") : _T("false"));
		puts("},");
	}
	puts("]");
	//LocalFree(activeScheme);
	free(overlaySchemes);
	return EXIT_SUCCESS;
}