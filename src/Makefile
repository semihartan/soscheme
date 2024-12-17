ROOT = ..
LIBS = "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "shlwapi.lib" "odbccp32.lib" "powrprof.lib"

!include "$(ROOT)\target.mak"
!include "$(ROOT)\dirs.mak"

!message Output Path: $(OUT_PATH)

!if "$(SOS_SOURCE_BROWSING)" == ""
SOS_SOURCE_BROWSING = 0
!endif

DEBUG_CFLAGS=/JMC /D_DEBUG /DDEBUG /RTC1 /Od /MDd /ZI
DEBUG_LDLAGS=/incremental
RELEASE_CFLAGS=/DNDEBUG /GL  /Gy /O2 /Oi /MD /Zi
RELEASE_LDLAGS=/opt:ref /opt:icf /ltcg:incremental

SHARED_CFLAGS=/Fd:$(OBJDIR)\vc.pdb /DSOS_SHARED_LIB /D_WINDOWS /D_USRDLL
SHARED_LDFLAGS=/subsystem:windows /DLL /IMPLIB:$(OUT_DIR)\$(OUT_NAME).lib $(LIBS)

STATIC_CFLAGS=/Fd:$(OUT_DIR)\$(OUT_NAME).pdb /DSOS_STATIC_LIB /D_LIB
STATIC_LDFLAGS=/machine:$(SOS_TARGET_ARCH) /nologo

EXECUTABLE_CFLAGS=/Fd:$(OBJDIR)\vc.pdb /DSOS_EXECUTABLE /D_CONSOLE
EXECUTABLE_LDFLAGS=/subsystem:console $(LIBS)

CFLAGS=/W4 /I$(INCDIR)\ /I$(RESDIR)\ /D_UNICODE /DUNICODE /DWIN32_LEAN_AND_MEAN /D_WIN32_WINNT=0x0A00 \
/permissive- /ifcOutput $(OBJDIR)\ /GS /Zc:wchar_t /Gm- \
/sdl /Zc:inline /fp:precise /errorReport:prompt /WX- /Zc:forScope \
/Gd /FC /EHsc /nologo /diagnostics:column /TC

LDFLAGS=/manifest:embed /nxcompat /pdb:$(OUT_DIR)\$(OUT_NAME).pdb /dynamicbase \
/debug /machine:$(SOS_TARGET_ARCH) \
/manifestuac:"level='requireAdministrator' uiAccess='false'" \
/ltcgout:"$(OBJDIR)\$(OUT_NAME).iobj" \
/errorreport:prompt /ilk:"$(OBJDIR)\$(OUT_NAME).ilk" /nologo /tlbid:1 

##############################################################################
#	Object File Definitions
##############################################################################

OBJS_STATIC_LIB = \
$(OBJDIR)\mod.obj \
$(OBJDIR)\oscheme.obj \
$(OBJDIR)\soserror.obj \
$(OBJDIR)\sosstring.obj \
$(OBJDIR)\upowr.obj \
$(OBJDIR)\util.obj

OBJS_SHARED_LIB = \
$(OBJDIR)\dllmain.obj \
$(OBJS_STATIC_LIB)

OBJS_EXE = \
$(OBJDIR)\commands\change.obj \
$(OBJDIR)\commands\persistent.obj \
$(OBJDIR)\commands\schemes.obj \
$(OBJDIR)\commands\set.obj \
$(OBJDIR)\commands\start.obj \
$(OBJDIR)\commands\stop.obj \
$(OBJDIR)\commands\help.obj \
$(OBJDIR)\commands\install.obj \
$(OBJDIR)\main.obj \
$(OBJDIR)\log.obj \
$(OBJS_STATIC_LIB)

##############################################################################


##############################################################################
#    Conditionals
##############################################################################

!if $(SOS_DEBUG)==1
CFLAGS=$(CFLAGS) $(DEBUG_CFLAGS)
LDFLAGS=$(LDFLAGS) $(DEBUG_LDLAGS)
!else
CFLAGS=$(CFLAGS) $(RELEASE_CFLAGS) 
LDFLAGS=$(LDFLAGS) $(RELEASE_LDLAGS)
!endif

!if defined(SOS_SHARED_LIB)
CFLAGS=$(CFLAGS) $(SHARED_CFLAGS)
LD=link
LDFLAGS=$(LDFLAGS) $(SHARED_LDFLAGS)
OBJS=$(OBJS_SHARED_LIB)
!elseif defined(SOS_STATIC_LIB)
CFLAGS=$(CFLAGS) $(STATIC_CFLAGS)
LD=lib
LDFLAGS=$(STATIC_LDFLAGS)
OBJS=$(OBJS_STATIC_LIB)
!else
CFLAGS=$(CFLAGS) $(EXECUTABLE_CFLAGS)
LD=link
LDFLAGS=$(LDFLAGS) $(EXECUTABLE_LDFLAGS)
OBJS=$(OBJS_EXE)
!endif

PCH_FLAGS=

!if defined(USE_PCH)
OBJS=$(OBJDIR)\pch.obj $(OBJS)
CFLAGS=$(CFLAGS) /Fp$(OBJDIR)\$(OUT_NAME).pch
PCH_FLAGS= /Yupch.h
!endif

##############################################################################

.SUFFIXES: .c .h .obj

!ifdef SOS_ANALYZE
.c{$(OBJDIR)}.obj:
    $(CC) $(CFLAGS) /Fo$(OBJDIR)\ $(PCH_FLAGS) /c $<

{commands\}.c{$(OBJDIR)\commands\}.obj:
    $(CC) $(CFLAGS) /Fo$(OBJDIR)\commands\ $(PCH_FLAGS) /c $<
!else
.c{$(OBJDIR)}.obj:
	@echo  Compiling $<...
    $(CC) $(CFLAGS) /Fo$(OBJDIR)\ $(PCH_FLAGS) /c $<

{commands\}.c{$(OBJDIR)\commands\}.obj:
	@echo  Compiling $<...
    $(CC) $(CFLAGS) /Fo$(OBJDIR)\commands\ $(PCH_FLAGS) /c $<
!endif

##############################################################################

all: dirs \
    $(OUT_PATH) \
!IF $(SOS_SOURCE_BROWSING)==1
    $(OBJDIR)\$(OUT_NAME).bsc \
!endif

##############################################################################

clean:
    -del *~ 2>nul
    -del $(OUT_PATH) 2>nul
    -del $(OUT_PATH:dll=lib) 2>nul
    -del $(OUT_DIR)\$(OUT_NAME).pdb 2>nul
    -del $(OUT_DIR)\$(OUT_NAME).exp 2>nul
    -del $(INCDIR)\soserrors.h 2>nul
    -del $(RESDIR)\soserrors.rc 2>nul
    -del $(RESDIR)\$(OUT_NAME).res 2>nul
    -rmdir /q /s ..\obj 2>nul
    
shadowclean:
    -del *~ 2>nul 
    -del $(OBJS_SHARED_LIB) 2>nul
    -rmdir /q /s obj 2>nul

##############################################################################

dirs:
    @if not exist "$(BINDIR)" mkdir "$(BINDIR)" && echo.   Created $(BINDIR)
    @if not exist "$(LIBDIR)" mkdir "$(LIBDIR)" && echo.   Created $(LIBDIR)
    @if not exist "$(OBJDIR)" mkdir "$(OBJDIR)" && echo.   Created $(OBJDIR)
    @if not exist "$(OBJDIR)\commands" mkdir "$(OBJDIR)\commands" && echo.   Created $(OBJDIR)\commands

$(INCDIR)\soserror.h: $(INCDIR)\soserrors.h

$(INCDIR)\soserrors.h: $(RESDIR)\soserrors.mc
	mc -c -o -h $(INCDIR)\ -r $(RESDIR)\ $**

$(OBJDIR)\$(OUT_NAME).bsc : $(OBJS)
    bscmake /v /n /o $@ $(OBJS:.obj=.sbr)

$(RESDIR)\$(OUT_NAME).res: $(RESDIR)\$(OUT_NAME).rc $(INCDIR)\soserrors.h $(RESDIR)\Resource.h
    $(RC) /l 0x0409 /nologo /dUNICODE /d_UNICODE /I $(RESDIR)\ /I $(INCDIR)\ $(RESDIR)\$(OUT_NAME).rc

$(OUT_PATH): $(OBJS) $(RESDIR)\$(OUT_NAME).res
    $(LD) /out:"$@" $(LDFLAGS) $**  

!if  defined(USE_PCH)
$(OBJDIR)\pch.obj: $(INCDIR)\framework.h $(INCDIR)\defs.h $(INCDIR)\pch.h
    @echo.  Creating precompiled header file...
    $(CC) $(CFLAGS) /Fo$(OBJDIR)\ /Ycpch.h /c pch.c 
!endif

$(OBJDIR)\commands\change.obj: \
commands\change.c \
$(INCDIR)\change.h \
$(INCDIR)\oscheme.h \
$(INCDIR)\soserror.h \
$(INCDIR)\util.h \
$(INCDIR)\log.h

$(OBJDIR)\commands\persistent.obj: \
commands\persistent.c \
$(INCDIR)\persistent.h \
$(INCDIR)\oscheme.h \
$(INCDIR)\soserror.h \
$(INCDIR)\util.h \
$(INCDIR)\log.h

$(OBJDIR)\commands\schemes.obj: \
commands\schemes.c \
$(INCDIR)\schemes.h \
$(INCDIR)\oscheme.h \
$(INCDIR)\soserror.h \
$(INCDIR)\util.h

$(OBJDIR)\commands\set.obj: \
commands\set.c \
$(INCDIR)\set.h \
$(INCDIR)\oscheme.h \
$(INCDIR)\soserror.h \
$(INCDIR)\util.h

$(OBJDIR)\commands\start.obj: \
commands\start.c \
$(INCDIR)\start.h \
$(INCDIR)\oscheme.h \
$(INCDIR)\soserror.h \
$(INCDIR)\util.h \
$(INCDIR)\log.h

$(OBJDIR)\commands\stop.obj: \
commands\stop.c \
$(INCDIR)\stop.h \
$(INCDIR)\oscheme.h \
$(INCDIR)\soserror.h \
$(INCDIR)\log.h

$(OBJDIR)\commands\help.obj: \
commands\help.c \
$(INCDIR)\help.h

$(OBJDIR)\commands\install.obj: \
commands\install.c \
$(INCDIR)\install.h \
$(INCDIR)\soserror.h \
$(INCDIR)\log.h \
$(INCDIR)\util.h 

$(OBJDIR)\mod.obj: \
mod.c \
$(INCDIR)\mod.h

$(OBJDIR)\oscheme.obj: \
oscheme.c \
$(INCDIR)\oscheme.h \
$(INCDIR)\util.h \
$(INCDIR)\upowr.h \
$(INCDIR)\sosstring.h \
$(INCDIR)\soserror.h \
$(INCDIR)\log.h

$(OBJDIR)\ssoserror.obj: \
soserror.c \
$(INCDIR)\soserror.h

$(OBJDIR)\sosstring.obj: \
sosstring.c \
$(INCDIR)\sosstring.h

$(OBJDIR)\log.obj: \
log.c \
$(INCDIR)\log.h

$(OBJDIR)\upowr.obj: \
upowr.c \
$(INCDIR)\upowr.h \
$(INCDIR)\util.h \
$(INCDIR)\mod.h

$(OBJDIR)\util.obj: \
util.c \
$(INCDIR)\util.h

$(OBJDIR)\main.obj: \
main.c \
$(INCDIR)\schemes.h \
$(INCDIR)\set.h \
$(INCDIR)\start.h \
$(INCDIR)\change.h \
$(INCDIR)\stop.h \
$(INCDIR)\persistent.h \
$(INCDIR)\oscheme.h \
$(INCDIR)\util.h

##############################################################################