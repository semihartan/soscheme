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


/**
 * @brief 
 * Here are some styles for handling errors in C or any low-level language.
 * 
 * When designing a good error handling system, the first question to ask ourselves must be that if we report
 * a possible failure reason to user, can the user actuall resolve the issue by using this info? It means that
 * is the failure due to the user's misuse of the interface? Or the failure is due to an internal inconvinience.
 * If the failure is due to the user, then we should report some kind of diagnostics data. It can be a simple 
 * boolean flag or a specific error code, which provides a detailed error info eventually.
 * 
 * * We can return a descriptive integer error code from our functions. This is the ultimate choice. It provides 
 * the users of the interface with detailed error codes directly.
 * 
 * * The other option is to return a boolean flag that indicates either a failure or a success.
 * In this scheme, to provide more detailed error info, we set a thread-local global error variable,
 * and let the user examine the error itself.
 * 
 * However, not always we should return a detailed error info, if don't need to do so. If we need to do, then 
 * a function can fail due to more than one reason, we should then set a global error variable or just return 
 * it from the function.
 * 
 * If a function can fail due to only **one** reason, then returning just a boolean flag is enough. In that case,
 * we also should document that reason, although it may seem to be obvious. What does a failure mean?
 * 
 * 
 * Some conventions for handling errors:
 * * If a function can fail due to more than two reasons, e.g., fail to allocate memory,
 * fail to read a reg key etc, and it can be useful to report a specific reason, return an OSError_t enumeration.
 *
 * * If a function can fail due to only one reason, then just return a boolean to report if it was failed or not.
 *
 * * Don't report any failure message unless we are in a critical path, which is the main execution flow of our
 * program. Just return the appropriate error code or a boolean value.
 * 
 * No need to abstract Win32 error codes because our code will run only on Windows.
 */
#pragma once

#ifndef SOS_ERROR_H
#define SOS_ERROR_H	1

#include <pch.h>

// Autogenerated!
#include "soserrors.h"

/**
 * @brief 
 * We have several options:
 * 
 * [USE THIS!!]
 * * The first option is we can define error codes using MAKE_HRESULT macro, which means 
 * that all the error codes will be of type HRESULT. There is no custom error type we can
 * return from functions. We will return only HRESULT as most system APIs do.
 *     * **Advantages**:
 *     * This might seem to be reasonable since this software is built for only Windows.
 *     * We can use FormatMessage to get the error messages.
 *     * **Disadvantages**:
 *     * The debugger/IDe cannot resolve the symbolic names for the error codes. [RESOLVED! Use .natvis files]
 * 
 * * The second option is we can define a custom error type like SosResult_t, and define 
 * error codes in this enumeration. We define a custom error code for all type of error 
 * codes that cause from both the C runtime and the system.
 *
 *     - **Advantages**:
 *     - The debuggers can show us meaningful symbolic names corresponding the numerical 
 *     values of our error codes. This is useful.
 *     - **Disadvantages**:
 *     - It also has the disadvantage that we must define a custom error code for every 
 *     possible error from both the C runtime and the system in someway. This is cumbersome.
 *
 * * The third option is to mix the previous two options. Create an enum, and define only 
 * error codes that aren't covered in the range of system error codes (For example, don't 
 * define an error code like SOS_S_OK, use S_OK instead.). Return this enum type from functions.
 *
 *     - **Advantages**:
 *     - We can use FormatMessage for system-defined ones.
 *     - We don't need to define custom error codes for every possible error code.
 *     - The debugger can show symbolic names for both HRESULTs and our custom enum constants.
 *  
 *     - **Disadvantages**:
 *     - We target both C and C++, and C++ has strict type-checking rules. It doesn't allow us
 *     to return an HRESULT from a function whose return type is our enum type. This invalidates
 *     all the advantages listed above.
 * 
 * When we define error codes as macros which expands to HRESULT constants,
 * the debugger has no idea of what a custom HRESULT value refers to (it cannot map 
 * custom values to symbolic names).
 * 
 * To overcome this, we can define error codes in an enum. But this also has its 
 * disadvantages: should we define our codes for the system error codes?, or should
 * we define only error codes that are not present in system error code set, and define
 * 
 * 
 * Moreover we target both C and C++, C++ has strict type-checking rules.
 */ 
  
// Auxiliary error data.
extern void* AuxErrorData;

/**
 * @brief Retrieves the error message for applicataion-defined or system-defined error code, formatted using FormatMessageW.
 * @return The descriptive error message.
 */
const TCHAR* SosGetErrorMessage(HRESULT _ErrorCode);

/**
 * @brief Retrieves the error message for applicataion-defined error code, formatted using FormatMessageW.
 * @return The descriptive application error message.
 */
const wchar_t* SosGetApplicationErrorMessage(HRESULT _ErrorCode);

#endif // SOS_ERROR_H