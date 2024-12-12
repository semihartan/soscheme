#pragma once

#ifndef REGISTRY_HELPER_H
#define REGISTRY_HELPER_H	1

#include "pch.h"

HKEY RegOpen(LPCSTR _szModuleName);

PVOID LoadProcedure(LPCSTR _szModuleName, LPCSTR _szProcName);

#endif 