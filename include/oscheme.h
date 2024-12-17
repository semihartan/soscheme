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

#pragma once

#ifndef OVERLAY_SCHEME_H
#define OVERLAY_SCHEME_H

#include <pch.h>

#define OS_NAME_BUF_SZ 	256

SOS_BEGIN

typedef struct OverlayScheme_s
{
	TCHAR friendlyName[OS_NAME_BUF_SZ];
	TCHAR description[OS_NAME_BUF_SZ];
	const TCHAR* alias;
	GUID guid;
}OverlayScheme_t;

SOS_API HRESULT SosOverlayScheme_Init();

SOS_API HRESULT SosOverlayScheme_GetSchemes(OverlayScheme_t** _overlaySchemes, size_t* _count);

SOS_API HRESULT SosOverlayScheme_GetActiveScheme(OverlayScheme_t** _activeScheme);

SOS_API HRESULT SosOverlayScheme_SetActiveScheme(const OverlayScheme_t* _scheme);

SOS_API HRESULT SosOverlayScheme_SetActiveSchemeByGuid(const GUID* _guid);

SOS_API HRESULT SosOverlayScheme_SetActiveSchemeByAlias(const TCHAR* _schemeMoniker);

SOS_END

#endif // !OVERLAY_SCHEME_H
