/*
#pragma once

#ifndef OVERLAY_SCHEME_H
#define OVERLAY_SCHEME_H

#include <pch.h>

#define OS_NAME_BUF_SZ 	256

SOS_BEGIN

typedef struct OverlayScheme_s
{
	WCHAR friendlyName[OS_NAME_BUF_SZ];
	WCHAR description[OS_NAME_BUF_SZ];
	const WCHAR* alias;
	GUID guid;
}OverlayScheme_t;

SOS_API HRESULT SosOverlayScheme_Init();

SOS_API HRESULT SosOverlayScheme_GetSchemes(OverlayScheme_t** _overlaySchemes, size_t* _count);

SOS_API HRESULT SosOverlayScheme_GetActiveScheme(OverlayScheme_t** _activeScheme);

SOS_API HRESULT SosOverlayScheme_SetActiveScheme(const OverlayScheme_t* _scheme);

SOS_API HRESULT SosOverlayScheme_SetActiveSchemeByGuid(const GUID* _guid);

SOS_API HRESULT SosOverlayScheme_SetActiveSchemeByAlias(const wchar_t* _schemeMoniker);

SOS_END

#endif // !OVERLAY_SCHEME_H
