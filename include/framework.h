#pragma once

#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include "targetver.h"

#include "resource.h"

// #define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>

#include <powerbase.h>
#include <powersetting.h>
#include <shellapi.h>
#include <shlwapi.h>
#include <Objbase.h>

// C RunTime Header Files
#include <fcntl.h>
#include <io.h>

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <errno.h>
#include <assert.h>
#include <string.h> 
#include <time.h> 

#include <malloc.h>
#include <memory.h>

// #define _CRT_NON_CONFORMING_WCSTOK
#include <wchar.h>
#include <tchar.h>

#endif