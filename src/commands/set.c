#include <pch.h>

#include "set.h"

#include "oscheme.h"
#include "soserror.h"
#include "util.h"

int ProcessCommandSet(int argc, const char* argv[])
{
	HRESULT hr;
	UNREFERENCED_PARAMETER(argc);

	const char* alias = argv[2];

	SOS_HALT_IF_FAILED(hr = SosOverlayScheme_SetActiveSchemeByAlias(alias),
		SOS_REPORT_APP_ERROR(););

	return EXIT_SUCCESS;
}