#pragma once

#ifndef UTIL_H
#define UTIL_H

#include <pch.h>

bool SosIsGuidEmpty(const GUID* const pGuid);

void SosPrintGuid(const GUID* const pGuid);

/**
 * @brief Converts a Guid to its string representation. The returned string doesn't include the leading 
 * and trailing braces, and is allocated statically. Therefore, don't free it. This also implies that 
 * you have to duplicate it if you need to work on it.
 * @param pGuid 
 * @return The string representation of pGuid.
 */
const wchar_t* SosConvertGuidToString(const GUID* const pGuid);


#endif