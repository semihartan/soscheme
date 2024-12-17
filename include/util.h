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

const TCHAR* GetExecutableFilePath();

#endif