#pragma once

#ifndef MODULE_H
#define MODULE_H	1

// Just a declaration of that we depend on the pch.h
#include <pch.h>

HMODULE LoadModuleIfNeeded(LPCSTR _szModuleName);

PVOID LoadProcedure(LPCSTR _szModuleName, LPCSTR _szProcName);

#endif 