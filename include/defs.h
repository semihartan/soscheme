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

#ifndef DEFS_H
#define DEFS_H

#define SOS_FILE_MAPPING_OBJECT_NAME _T("Global\\soscheme_FileMappingObject")
#define SOS_PROCESS_KILL_EVENT_NAME _T("Global\\soscheme_ProcessKillEvent")

#define SOS_SHARED_MEMORY_SIZE	(256 * sizeof(TCHAR))

#if defined(SOS_SHARED_LIB)
#   define SOS_API          __declspec(dllexport)
#else
#   define SOS_API          __declspec(dllimport)
#endif

#define SOS_INLINE       __inline

#ifdef __cplusplus 
#   define SOS_BEGIN       extern "C" {
#   define SOS_END         }
#else
#   define SOS_BEGIN       
#   define SOS_END         
#endif


#if defined(UNICODE) || defined(_UNICODE)
#   ifndef _T
#       define __T(x)       L##x    
#       define _T(x)      __T(x)
#   endif
#   define fprintf(a, b, ...)	    fwprintf(a, _T(b), __VA_ARGS__)
#   define fputs(a, b)	            fputws(_T(a), b)
#   define puts(a)	                fputws(_T(a) _T("\n"), stdout)
#   define printf(a, ...)	        wprintf(_T(a), __VA_ARGS__)
#   define printe(a, ...)	        fwprintf(stderr, _T(a) _T("\n"), __VA_ARGS__)
#else
#   ifndef _T
#       define _T(x)       x
#   endif
#   define fprintf(a, b, ...)	    fprintf(a, b, __VA_ARGS__)
#   define fputs(a, b)	            fputs(a, b) 
#   define printf(a, ...)	        printf(a, __VA_ARGS__)
#   define printe(a, ...)	        fprintf(stderr, a _T("\n"), __VA_ARGS__)
#endif

#ifdef NDEBUG
#   define SOS_ASSERT(expr, ret, ...)    SOS_RETURN_IF_NOT(expr, ret, __VA_ARGS__)
#else
#   define SOS_ASSERT(expr, ret, ...)    assert(expr)
#endif

#define SOS_LAST_ERROR_MESSAGE              SosGetSystemErrorMessage(GetLastError())
#define SOS_HR_ERROR_MESSAGE(hr)            SosGetSystemErrorMessage(hr)
#define SOS_APP_ERROR_MESSAGE(hr)           SosGetApplicationErrorMessage(hr)
#define SOS_ERROR_MESSAGE           "An error ocurred.\nError: %s"
#define SOS_REPORT_LAST_ERROR()     printe(SOS_ERROR_MESSAGE, SOS_LAST_ERROR_MESSAGE)
#define SOS_REPORT_HR_ERROR(hr)     printe(SOS_ERROR_MESSAGE, SOS_HR_ERROR_MESSAGE(hr))
#define SOS_REPORT_APP_ERROR()      printe(SOS_ERROR_MESSAGE, SOS_APP_ERROR_MESSAGE(hr))

#define SOS_IF_ERROR_SUCCESS(x)	(ERROR_SUCCESS == (x))
#define SO_IF_TRUE(x)	        (TRUE == (x))

#define _SOS_HANDLE_ERROR(cond, stm, ret, ...)	    \
do {                                                \
    if (!(cond)) {		                            \
        __VA_ARGS__                     	        \
        stm ret;				                    \
    }                                               \
} while (0)

#define SOS_RETURN_IF_NOT(cond, ret, ...)   _SOS_HANDLE_ERROR(cond, return, (ret), __VA_ARGS__)

#define SOS_RETURN_IF(cond, ret, ...)            SOS_RETURN_IF_NOT(!(cond), (ret), __VA_ARGS__)
#define SOS_RETURN_IF_NULL(cond, ret, ...)       SOS_RETURN_IF_NOT(NULL != (cond), (ret), __VA_ARGS__)
#define SOS_RETURN_IF_FALSE(cond, ret, ...)      SOS_RETURN_IF_NOT((cond), (ret), __VA_ARGS__)
#define SOS_RETURN_IF_FAILED(cond, ret, ...)     SOS_RETURN_IF(FAILED((cond)), (ret), __VA_ARGS__)

#define SOS_HALT_IF_NOT(cond, ...)          _SOS_HANDLE_ERROR(cond, exit, (EXIT_FAILURE), __VA_ARGS__)

#define SOS_HALT_IF(cond, ...)              SOS_HALT_IF_NOT(!(cond), __VA_ARGS__)
#define SOS_HALT_IF_NULL(cond, ...)         SOS_HALT_IF_NOT(NULL != (cond), __VA_ARGS__)
#define SOS_HALT_IF_FALSE(cond, ...)        SOS_HALT_IF_NOT((cond), __VA_ARGS__)
#define SOS_HALT_IF_FAILED(cond, ...)       SOS_HALT_IF(FAILED((cond)), __VA_ARGS__)

#define SOS_GOTO_IF_NOT(cond, label, ...)       _SOS_HANDLE_ERROR(cond, goto, label, __VA_ARGS__)
#define SOS_GOTO_IF(cond, label, ...)            SOS_GOTO_IF_NOT(!(cond), label, __VA_ARGS__)
#define SOS_GOTO_IF_NULL(cond, label, ...)       SOS_GOTO_IF_NOT(NULL != (cond), label, __VA_ARGS__)
#define SOS_GOTO_IF_FALSE(cond, label, ...)      SOS_GOTO_IF_NOT((cond), label, __VA_ARGS__)
#define SOS_GOTO_IF_FAILED(cond, label, ...)     SOS_GOTO_IF(FAILED((cond)), label, __VA_ARGS__)
#endif 