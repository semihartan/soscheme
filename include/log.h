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

#ifndef SOS_LOG_H
#define SOS_LOG_H

#if defined(SOS_STATIC_LIB) || defined(SOS_SHARED_LIB)
#	define SOS_LOG(msg, ...)			(void)0 
#	define SOS_LOG_ERROR(msg, ...)		(void)0 
#else

#include <pch.h>

#define SOS_LOG(msg, ...)			SosLog(_T(__FILE__), _T(__FUNCTION__), __LINE__, msg, __VA_ARGS__)

// Don't put a new-line char at the end.
#define SOS_LOG_ERROR(msg, ...)		SOS_LOG(_T("[Error] ") _T(msg) _T("\n"), __VA_ARGS__)

void SosLog(const TCHAR* _File, const TCHAR* _Function, uint32_t _Line, const TCHAR* _Format, ...);

#endif

#endif                                                                                                                                                                                                                                                                                                                                        