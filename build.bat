@echo off

set __SOS_SHARED_LIB=
set __SOS_STATIC_LIB=
set __SOS_PARSE_ERROR=
set __SOS_TARGET_ARCH=x64
set __SOS_HOST_ARCH=x64
set __SOS_CLEAN=
set __SOS_BUILD=1
set __SOS_REBUILD=
set __SOS_CONFIG=Release
set __SOS_HELP=
set __SOS_ALL=
set __SOS_BUILD_CONFIG=
set __SOS_BUILD_CONFIG_ARCH=
set __SOS_BUILD_CONFIG_OUT=
set __SOS_BUILD_CONFIG_TYPE=

set "__SOS_ALL_BUILD_CONFIGS=x86 exe Debug"
set "__SOS_ALL_BUILD_CONFIGS=%__SOS_ALL_BUILD_CONFIGS%; x86 exe Release"
set "__SOS_ALL_BUILD_CONFIGS=%__SOS_ALL_BUILD_CONFIGS%; x86 dll Debug"
set "__SOS_ALL_BUILD_CONFIGS=%__SOS_ALL_BUILD_CONFIGS%; x86 dll Release"
set "__SOS_ALL_BUILD_CONFIGS=%__SOS_ALL_BUILD_CONFIGS%; x86 lib Debug"
set "__SOS_ALL_BUILD_CONFIGS=%__SOS_ALL_BUILD_CONFIGS%; x86 lib Release"

set "__SOS_ALL_BUILD_CONFIGS=%__SOS_ALL_BUILD_CONFIGS%; x64 exe Debug"
set "__SOS_ALL_BUILD_CONFIGS=%__SOS_ALL_BUILD_CONFIGS%; x64 exe Release"
set "__SOS_ALL_BUILD_CONFIGS=%__SOS_ALL_BUILD_CONFIGS%; x64 dll Debug"
set "__SOS_ALL_BUILD_CONFIGS=%__SOS_ALL_BUILD_CONFIGS%; x64 dll Release"
set "__SOS_ALL_BUILD_CONFIGS=%__SOS_ALL_BUILD_CONFIGS%; x64 lib Debug"
set "__SOS_ALL_BUILD_CONFIGS=%__SOS_ALL_BUILD_CONFIGS%; x64 lib Release"

set "__SOS_ALL_BUILD_CONFIGS=%__SOS_ALL_BUILD_CONFIGS%; arm exe Debug"
set "__SOS_ALL_BUILD_CONFIGS=%__SOS_ALL_BUILD_CONFIGS%; arm exe Release"
set "__SOS_ALL_BUILD_CONFIGS=%__SOS_ALL_BUILD_CONFIGS%; arm dll Debug"
set "__SOS_ALL_BUILD_CONFIGS=%__SOS_ALL_BUILD_CONFIGS%; arm dll Release"
set "__SOS_ALL_BUILD_CONFIGS=%__SOS_ALL_BUILD_CONFIGS%; arm lib Debug"
set "__SOS_ALL_BUILD_CONFIGS=%__SOS_ALL_BUILD_CONFIGS%; arm lib Release"

set "__SOS_ALL_BUILD_CONFIGS=%__SOS_ALL_BUILD_CONFIGS%; arm64 exe Debug"
set "__SOS_ALL_BUILD_CONFIGS=%__SOS_ALL_BUILD_CONFIGS%; arm64 exe Release"
set "__SOS_ALL_BUILD_CONFIGS=%__SOS_ALL_BUILD_CONFIGS%; arm64 dll Debug"
set "__SOS_ALL_BUILD_CONFIGS=%__SOS_ALL_BUILD_CONFIGS%; arm64 dll Release"
set "__SOS_ALL_BUILD_CONFIGS=%__SOS_ALL_BUILD_CONFIGS%; arm64 lib Debug"
set "__SOS_ALL_BUILD_CONFIGS=%__SOS_ALL_BUILD_CONFIGS%; arm64 lib Release"

:check_installation
set __SOS_VSInstallationDir=
set "__SOS_VSWhere=C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe"

echo %__SOS_VSWhere%

if exist "%__SOS_VSWhere%" (
    for /f "usebackq tokens=*" %%a in (`"%__SOS_VSWhere%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do ( 
		set "__SOS_VSInstallationDir=%%a"
	)
)

echo %__SOS_VSInstallationDir%

if "%__SOS_VSInstallationDir%"=="" (
	if exist "C:\Program Files\Microsoft Visual Studio\2022\Community" (
		set "__SOS_VSInstallationDir=C:\Program Files\Microsoft Visual Studio\2022\Community"
	) else (
		if exist "C:\Program Files\Microsoft Visual Studio\2019\Community" (
			set "__SOS_VSInstallationDir=C:\Program Files\Microsoft Visual Studio\2019\Community"
		) else (
			goto :missing
		)
	)
)
echo %__SOS_VSInstallationDir%

set "__SOS_VSDEVCMD=%__SOS_VSInstallationDir%\Common7\Tools\vsdevcmd.bat"

echo %__SOS_VSDEVCMD%

if "%__SOS_VSDEVCMD%"=="" (
	goto :missing
)

:parse_args
set __SOS_PARSE_ERROR=0
set "__SOS_ARGS_LIST=%*"
call :parse_loop
set "__SOS_ARGS_LIST="

:check_error
if "%SOS_DEBUG%" GEQ "1" (
	echo "__SOS_PARSE_ERROR=%__SOS_PARSE_ERROR%"
	echo "__SOS_HELP=%__SOS_HELP%"
)
if "%__SOS_PARSE_ERROR%" NEQ "0" goto :usage_error
if "%__SOS_HELP%" NEQ "" goto :usage

if "%__SOS_ALL%"=="" (
	goto :assemble_vscmdargs
)

:build_all

echo Building all...
echo:

set __SOS_BUILD=1
set __SOS_REBUILD=0
set __SOS_CLEAN=0

setlocal enabledelayedexpansion

:parse_configs_loop
for /f "tokens=1,* delims=;" %%A in ("!__SOS_ALL_BUILD_CONFIGS!") do (
	echo In parse_configs_loop 
	set __SOS_BUILD_CONFIG=%%A
	echo __SOS_BUILD_CONFIG=!__SOS_BUILD_CONFIG!
	
	call :parse_config_loop
	
	set __SOS_TARGET_ARCH=!__SOS_BUILD_CONFIG_ARCH!
	set __SOS_CONFIG=!__SOS_BUILD_CONFIG_TYPE!
	if /I "!__SOS_BUILD_CONFIG_OUT!"=="lib" (
		set __SOS_STATIC_LIB=1
		set __SOS_SHARED_LIB=
		echo Building static library...
	) else (
		if /I "!__SOS_BUILD_CONFIG_OUT!"=="dll" (
			set __SOS_STATIC_LIB=
			set __SOS_SHARED_LIB=1
			echo Building shared library...
		) else (
			set __SOS_STATIC_LIB=
			set __SOS_SHARED_LIB=
			echo Building executable...
		)
	)
	echo Target Architecture=!__SOS_TARGET_ARCH!
	echo Config=!__SOS_CONFIG!
	echo:
	call :assemble_vscmdargs
	
	set __SOS_ALL_BUILD_CONFIGS=%%B
	goto :parse_configs_loop
)

goto :parse_configs_end

:parse_config_loop
for /f "tokens=1,*" %%C in ("!__SOS_BUILD_CONFIG!") do (
	if /I "%%C"=="x86"     (set __SOS_BUILD_CONFIG_ARCH=%%C)
	if /I "%%C"=="x64"     (set __SOS_BUILD_CONFIG_ARCH=%%C)
	if /I "%%C"=="arm"     (set __SOS_BUILD_CONFIG_ARCH=%%C)
	if /I "%%C"=="arm64"   (set __SOS_BUILD_CONFIG_ARCH=%%C)

	if /I "%%C"=="exe"     (set __SOS_BUILD_CONFIG_OUT=%%C)
	if /I "%%C"=="dll"     (set __SOS_BUILD_CONFIG_OUT=%%C)
	if /I "%%C"=="lib"     (set __SOS_BUILD_CONFIG_OUT=%%C)

	if /I "%%C"=="debug"   (set __SOS_BUILD_CONFIG_TYPE=%%C)
	if /I "%%C"=="release" (set __SOS_BUILD_CONFIG_TYPE=%%C)

	set __SOS_BUILD_CONFIG=%%D
	goto :parse_config_loop
)

exit /B 0

:parse_configs_end
exit /B 0

endlocal

:convert_args_case
if /I "%__SOS_TARGET_ARCH%"=="x86" (
	set __SOS_TARGET_ARCH=x86
)
if /I "%__SOS_TARGET_ARCH%"=="x86" (
	set __SOS_TARGET_ARCH=win32
)
if /I "%__SOS_TARGET_ARCH%"=="x64" (
	set __SOS_TARGET_ARCH=amd64
)
if /I "%__SOS_TARGET_ARCH%"=="amd64" (
	set __SOS_TARGET_ARCH=amd64
)
if /I "%__SOS_TARGET_ARCH%"=="arm" (
	set __SOS_TARGET_ARCH=arm
)
if /I "%__SOS_TARGET_ARCH%"=="arm64" (
	set __SOS_TARGET_ARCH=arm64
)
if /I "%__SOS_HOST_ARCH%"=="x86" (
	set __SOS_HOST_ARCH=x86
)
if /I "%__SOS_HOST_ARCH%"=="win32" (
	set __SOS_HOST_ARCH=x86
)
if /I "%__SOS_HOST_ARCH%"=="x64" (
	set __SOS_HOST_ARCH=amd64
)
if /I "%__SOS_HOST_ARCH%"=="amd64" (
	set __SOS_HOST_ARCH=amd64
)
if /I "%__SOS_HOST_ARCH%"=="arm" (
	set __SOS_HOST_ARCH=arm
)
if /I "%__SOS_HOST_ARCH%"=="arm64" (
	set __SOS_HOST_ARCH=arm64
)

:assemble_vscmdargs
set "__SOS_VSDEVCMD_ARGS=-arch=%__SOS_TARGET_ARCH% -host_arch=%__SOS_HOST_ARCH% -no_logo"

if /I "%__SOS_TARGET_ARCH%"=="amd64" (
	set __SOS_TARGET_ARCH=x64
)

if defined VSCMD_ARG_TGT_ARCH (
	if /I "%VSCMD_ARG_TGT_ARCH%" NEQ "%__SOS_TARGET_ARCH%" (
		call "%__SOS_VSDEVCMD%" -no_logo /clean_env
		echo VsDevCmd is cleaned and now being initialized for target=%__SOS_TARGET_ARCH%, host=%__SOS_HOST_ARCH%
		call "%__SOS_VSDEVCMD%" %__SOS_VSDEVCMD_ARGS%
	)
) else (
	echo VsDevCmd is being initialized for target=%__SOS_TARGET_ARCH%, host=%__SOS_HOST_ARCH%
    call "%__SOS_VSDEVCMD%" %__SOS_VSDEVCMD_ARGS%
)

:call_nmake
if "%SOS_DEBUG%" GEQ "1" (
	echo __SOS_SHARED_LIB=%__SOS_SHARED_LIB%
	echo __SOS_STATIC_LIB=%__SOS_STATIC_LIB%
	echo __SOS_PARSE_ERROR=%__SOS_PARSE_ERROR%
	echo __SOS_TARGET_ARCH=%__SOS_TARGET_ARCH%
	echo __SOS_HOST_ARCH=%__SOS_HOST_ARCH%
	echo __SOS_CLEAN=%__SOS_CLEAN%
	echo __SOS_BUILD=%__SOS_BUILD%
	echo __SOS_REBUILD=%__SOS_REBUILD%
	echo __SOS_CONFIG=%__SOS_CONFIG%
)
set SOS_STATIC_LIB=%__SOS_STATIC_LIB%
set SOS_SHARED_LIB=%__SOS_SHARED_LIB%
set SOS_TARGET_ARCH=%__SOS_TARGET_ARCH%
set SOS_CONFIG=%__SOS_CONFIG%

if /I "%__SOS_REBUILD%"=="1" (
	nmake clean&& nmake
) else (
	if /I "%__SOS_CLEAN%"=="1" (
		nmake clean
	) else (
		if /I "%__SOS_BUILD%"=="1" (
			nmake
		)
	)
)
REM if !ERRORLEVEL! NEQ 0 (
REM	echo Build failed.
REM	echo Exiting...
REM	exit 1
REM )

exit /B 0

:parse_loop
for /F "tokens=1,* delims= " %%a in ("%__SOS_ARGS_LIST%") do (
    call :parse_argument %%a
@REM Reduce __SOS_ARGS_LIST	
    set "__SOS_ARGS_LIST=%%b"
    goto :parse_loop
)
:parse_end
exit /B 0

:parse_argument
@REM called by :parse_loop and expects the arguments to either be:
@REM 1. a single argument in %1
@REM 2. an argument pair from the command line specified as '%1=%2'

set __local_ARG_FOUND=0
@REM Architecture

if /I "%1"=="all" (
	set __SOS_ALL=1
	set __local_ARG_FOUND=1
	goto :parse_end
)
if /I "%1"=="-arch" (
	goto :parse_arch_opt
)
if /I "%1"=="--arch" (
	goto :parse_arch_opt
)
if /I "%1"=="/arch" (
	goto :parse_arch_opt
)
if /I "%1"=="-lib" (
	goto :parse_lib_opt
)
if /I "%1"=="--lib" (
	goto :parse_lib_opt
)
if /I "%1"=="/lib" (
	goto :parse_lib_opt
)
if /I "%1"=="-config" (
	goto :parse_config_opt
)
if /I "%1"=="--config" (
	goto :parse_config_opt
)
if /I "%1"=="/config" (
	goto :parse_config_opt
)
if /I "%1"=="help" (
    set __SOS_HELP=1
    set __local_ARG_FOUND=1
)
if /I "%1"=="/help" (
    set __SOS_HELP=1
    set __local_ARG_FOUND=1
)
if /I "%1"=="-help" (
    set __SOS_HELP=1
    set __local_ARG_FOUND=1
)
if /I "%1"=="--help" (
    set __SOS_HELP=1
    set __local_ARG_FOUND=1
)
if /I "%1"=="clean" (
    set __SOS_CLEAN=1
    set __SOS_BUILD=0
    set __SOS_REBUILD=0
    set __local_ARG_FOUND=1
)
if /I "%1"=="build" (
    set __SOS_CLEAN=0
    set __SOS_BUILD=1
    set __SOS_REBUILD=0
    set __local_ARG_FOUND=1
)
if /I "%1"=="rebuild" (
    set __SOS_CLEAN=0
    set __SOS_BUILD=0
    set __SOS_REBUILD=1
    set __local_ARG_FOUND=1
)
if /I "%1"=="/?" (
    set __SOS_HELP=1
    set __local_ARG_FOUND=1
)
if /I "%1"=="-?" (
    set __SOS_HELP=1
    set __local_ARG_FOUND=1
)

:parse_args_end
if "%SOS_DEBUG%" GEQ "1" (
	echo "__local_ARG_FOUND=%__local_ARG_FOUND%"
)
if "%__local_ARG_FOUND%" NEQ "1" (
	if "%SOS_DEBUG%" GEQ "1" (
		echo "No Argument found."
	)
    set /A __SOS_PARSE_ERROR=__SOS_PARSE_ERROR+1
)

set __local_ARG_FOUND=

exit /B 0

:parse_lib_opt
if /I "%2"=="static" (
	set __SOS_STATIC_LIB=1
	set __local_ARG_FOUND=1
) else (
	if /I "%2"=="shared" (
		set __SOS_SHARED_LIB=1
		set __local_ARG_FOUND=1
	) else (
		set __local_ARG_FOUND=0
		echo "Invalid Argument"
	)
)
goto :parse_args_end


:parse_config_opt
if /I "%2"=="debug" (
	set __SOS_CONFIG=Debug
	set __local_ARG_FOUND=1
) else (
	if /I "%2"=="release" (
		set __SOS_CONFIG=Release
		set __local_ARG_FOUND=1
	) else (
		set __local_ARG_FOUND=0
	)
)

goto :parse_args_end


:parse_arch_opt
if /I "%2"=="x86" (
	set __SOS_TARGET_ARCH=x86
	set __local_ARG_FOUND=1
) else (
	if /I "%2"=="x64" (
		set __SOS_TARGET_ARCH=x64
		set __local_ARG_FOUND=1
	) else (
		if /I "%2"=="arm" (
			set __SOS_TARGET_ARCH=arm
			set __local_ARG_FOUND=1
		) else (
			if /I "%2"=="arm64" (
				set __SOS_TARGET_ARCH=arm64
				set __local_ARG_FOUND=1
			) else (
					set __local_ARG_FOUND=0
				)
			)
		)
)
goto :parse_args_end	
	

:usage_error
echo [ERROR:%~nx0] Error in script usage. The correct usage is:
goto :usage

:usage
echo Syntax:
echo     %~nx0 [build_type] [--arch=arch_type] [--lib=lib_type] [--config=config_type]
echo where :
echo     [build_type]: clean ^| build ^| rebuild
echo     [arch_type]: x86 ^| amd64 ^| arm ^| arm64
echo     [lib_type]: static ^| shared
echo     [config_type] : debug ^| release
echo:
echo:
echo For example:
echo     %~nx0 
echo     %~nx0 --arch=x64 --config=Debug
echo     %~nx0 clean --arch=x64 --config=Debug
echo     %~nx0 build --arch=x86 --config=Release
echo     %~nx0 rebuild --arch=arm --config=Debug --lib=static
echo:
goto :missing
	
:missing
echo Please make sure either Visual Studio or C++ Build SKU is installed.	
	
:end
set SOS_STATIC_LIB=
set SOS_SHARED_LIB=
set SOS_TARGET_ARCH=
set SOS_CONFIG=
set __SOS_SHARED_LIB=
set __SOS_STATIC_LIB=
set __SOS_PARSE_ERROR=
set __SOS_TARGET_ARCH=
set __SOS_HOST_ARCH=
set __SOS_CLEAN=
set __SOS_BUILD=
set __SOS_REBUILD=