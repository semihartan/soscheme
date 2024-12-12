#include <pch.h>

#include "schemes.h"

#include "oscheme.h"
#include "soserror.h"
#include "util.h"

int ProcessCommandSchemes(int argc, const char* argv[])
{
	HRESULT hr = S_OK;
	size_t count = 0;
	OverlayScheme_t* overlaySchemes = NULL;
	OverlayScheme_t* activeScheme = NULL;

	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);
	
	SOS_HALT_IF_FAILED(hr = SosOverlayScheme_GetActiveScheme(&activeScheme),
		SOS_REPORT_APP_ERROR(););

	SOS_HALT_IF_FAILED(hr = SosOverlayScheme_GetSchemes(&overlaySchemes, &count),
		SOS_REPORT_APP_ERROR(););

	puts("[");
	for (size_t i = 0; i < count; i++)
	{
		OverlayScheme_t os = overlaySchemes[i];

		printf("\"%s\":\n{\n  ", os.alias);

		printf("  \"GUID\": ");
		SosPrintGuid(&overlaySchemes[i].guid);
		puts(",");
		bool isActive = memcmp(&overlaySchemes[i].guid, &os.guid, sizeof(GUID)) == 0;

		printf("  \"friendlyName\":  \"%s\",\n", os.friendlyName);
		printf("  \"description\":  \"%s\",\n", os.description);
		printf("  \"isActive\":  %s,\n", isActive ? _L("true") : _L("false"));
		puts("},");
	}
	puts("]");
	//LocalFree(activeScheme);
	free(overlaySchemes);
	return EXIT_SUCCESS;
}