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

#include <pch.h>

#include "help.h"


int ProcessCommandHelp(int argc, const TCHAR* argv[])
{
    UNREFERENCED_PARAMETER(argc);
    UNREFERENCED_PARAMETER(argv);
    printf("soscheme © 2024 Semih Artan\n\n");
    printf("Description: soscheme is a command line tool for managing power overlay \n"
           "schemes on Windows 10/11. It allows to query and set temporary/permanent\n"
           "schemes available on the system.\n\n\n");
    printf("Usage: soscheme.exe <command> <args>\n\n");
    printf("--help, -h              Prints this help message.\n");
    printf("schemes                 Display all available overlay schemes.\n");
    printf("set <scheme>            Set the overlay scheme to <scheme>. <scheme> is\n"
           "                        the name of the scheme.\n");
    printf("start <scheme>          Set the overlay scheme persistently.\n");
    printf("change <scheme>         Change the persistent overlay scheme.\n");
    printf("stop                    Reset the overlay scheme to the previous scheme.\n");
    printf("install <path>          Installs itself into the desired location and\n");
    printf("                        modifies the PATH var accordingly.\n");
    printf("                                                            ");
    return EXIT_SUCCESS;
}
