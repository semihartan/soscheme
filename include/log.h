#pragma once

#ifndef SOS_LOG_H
#define SOS_LOG_H

#include <pch.h>

#define SOS_SHARED_LIB

#if defined(SOS_STATIC_LIB) || defined(SOS_SHARED_LIB)
#	define SOS_LOG(msg, ...)			(void)0 
#	define SOS_LOG_ERROR(msg, ...)		(void)0 
#else
#	define SOS_LOG(msg, ...)			SosLog(__FILEW__, __FUNCTIONW__, __LINE__, msg, __VA_ARGS__)
#	define SOS_LOG_ERROR(msg, ...)		SOS_LOG(L"[Error] " _L(msg) _L("\n"), __VA_ARGS__)
#endif

void SosLog(const wchar_t* _File, const wchar_t* _Function, uint32_t _Line, const wchar_t* _Format, ...);

#endif                                                                                                                                                                                                                                                                                                                                        