ROOT = ..
LIBS = "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib" "powrprof.lib"

!include "$(ROOT)\target.mak"

!IF "$(SOS_SOURCE_BROWSING)" == ""
SOS_SOURCE_BROWSING = 0
!ENDIF

CFLAGS=/W4 /I$(INCDIR)\ /I$(RESDIR)\ /D_UNICODE /DUNICODE \
/permissive- /ifcOutput $(OBJDIR)\ /GS /Zc:wchar_t /Gm- \
/sdl /Fd:$(OBJDIR)\vc143.pdb /Zc:inline /fp:precise /errorReport:prompt /WX- /Zc:forScope \
/Gd /FC /EHsc /nologo /Fp$(OBJDIR)\soscheme.pch /diagnostics:column

LDFLAGS=/manifest /nxcompat /pdb:$(BINDIR)\soscheme.pdb /dynamicbase \
/debug /machine:$(SOS_TARGET_PROCESSOR) \
/manifestuac:"level='requireAdministrator' uiAccess='false'" \
/ManifestFile:"$(OBJDIR)\soscheme.manifest" /ltcgout:"$(OBJDIR)\soscheme.iobj" \
/errorreport:prompt /ilk:"$(OBJDIR)\soscheme.ilk" /nologo /tlbid:1 

!IF $(SOS_DEBUG)==1
CFLAGS=$(CFLAGS) /JMC /D_DEBUG /DDEBUG /RTC1 /Od /MDd /ZI
LDFLAGS=$(LDFLAGS) /incremental
!ELSE
CFLAGS=$(CFLAGS) /DNDEBUG /GL  /Gy /O2 /Oi /MD /Zi 
LDFLAGS=$(LDFLAGS) /opt:ref /opt:icf /ltcg:incremental
!ENDIF

!IF $(SOS_SOURCE_BROWSING)==1
CFLAGS=$(CFLAGS) /FR
!ELSE
CFLAGS=$(CFLAGS) /DWIN32_LEAN_AND_MEAN /D_WIN32_WINNT=0x0A00 
!ENDIF

!if defined(SOS_WIN_7) && defined(SOS_CL_17_OR_NEWER)
CFLAGS=$(CFLAGS) /D_USING_V110_SDK71_
!elseif defined(SOS_ANALYZE)
CFLAGS=$(CFLAGS) /analyze
!endif

OBJS_SHARED = \
$(OBJDIR)\dllmain.obj \
$(OBJDIR)\mod.obj \
$(OBJDIR)\oscheme.obj \
$(OBJDIR)\soserror.obj \
$(OBJDIR)\sosstring.obj \
$(OBJDIR)\upowr.obj \
$(OBJDIR)\util.obj

OBJS_EXE = \
$(OBJDIR)\commands\change.obj \
$(OBJDIR)\commands\persistent.obj \
$(OBJDIR)\commands\schemes.obj \
$(OBJDIR)\commands\set.obj \
$(OBJDIR)\commands\start.obj \
$(OBJDIR)\commands\stop.obj \
$(OBJDIR)\main.obj \
$(OBJDIR)\log.obj \
$(OBJS_SHARED)

!if defined(SOS_SHARED_LIB)

SOS_EXT=dll
CFLAGS=$(CFLAGS) /DSOS_SHARED_LIB /D_WINDOWS /D_USRDLL
LDFLAGS=$(LDFLAGS) /subsystem:windows /DLL /IMPLIB:$(BINDIR)\soscheme.lib
OBJS=$(OBJDIR)\pch.obj $(OBJS_SHARED)

!else

SOS_EXT=exe
CFLAGS=$(CFLAGS) /D_CONSOLE
LDFLAGS=$(LDFLAGS) /subsystem:console 
OBJS=$(OBJDIR)\pch.obj $(OBJS_EXE)

!endif

.SUFFIXES: .c .h .obj

!ifdef SOS_ANALYZE

.c{$(OBJDIR)}.obj:
    $(CC) $(CFLAGS) /Fo$(OBJDIR)\ /Yupch.h /c $<

{commands\}.c{$(OBJDIR)\commands\}.obj:
    $(CC) $(CFLAGS) /Fo$(OBJDIR)\commands\ /Yupch.h /c $<

# {$(INCDIR)}.h:

!else

.c{$(OBJDIR)}.obj:
	@echo  Compiling $<...
    $(CC) $(CFLAGS) /Fo$(OBJDIR)\ /Yupch.h /c $<

{commands\}.c{$(OBJDIR)\commands\}.obj:
	@echo  Compiling $<...
    $(CC) $(CFLAGS) /Fo$(OBJDIR)\commands\ /Yupch.h /c $<

# {$(INCDIR)}.h:

!endif

##############################################################################

all: dirs \
    $(BINDIR)\soscheme.$(SOS_EXT) \
!IF $(SOS_SOURCE_BROWSING)==1
    $(OBJDIR)\soscheme.bsc \
!endif

##############################################################################

clean:
    -del *~ 2>nul
    -del $(BINDIR)\soscheme.pdb $(BINDIR)\soscheme.$(SOS_EXT) 2>nul
    -rmdir /q /s obj 2>nul

##############################################################################

dirs:
    @if not exist "$(BINDIR)" mkdir "$(BINDIR)" && echo.   Created $(BINDIR)
    @if not exist "$(OBJDIR)" mkdir "$(OBJDIR)" && echo.   Created $(OBJDIR)
    @if not exist "$(OBJDIR)\commands" mkdir "$(OBJDIR)\commands" && echo.   Created $(OBJDIR)\commands

$(INCDIR)\soserror.h: $(INCDIR)\soserrors.h

$(INCDIR)\soserrors.h: $(RESDIR)\soserrors.mc
	mc -c -o -h $(INCDIR)\ -r $(RESDIR)\ $<

$(OBJDIR)\soscheme.bsc : $(OBJS)
    bscmake /v /n /o $@ $(OBJS:.obj=.sbr)

$(RESDIR)\soscheme.res: $(RESDIR)\soscheme.rc $(RESDIR)\Resource.h
    rc /l 0x0409 /nologo /dUNICODE /d_UNICODE /I $(RESDIR)\ /I $(INCDIR)\ @< 

$(BINDIR)\soscheme.$(SOS_EXT): $(OBJS)
    link /out:$@ $(LDFLAGS) $(OBJS) $(LIBS) $(RESDIR)\soscheme.res

# $(INCDIR)\*.h:

$(OBJDIR)\pch.obj: $(INCDIR)\framework.h $(INCDIR)\pch.h
    @echo.  Creating precompiled header file...
    $(CC) $(CFLAGS) /Fo$(OBJDIR)\ /Ycpch.h /c pch.c 

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

$(OBJDIR)\mod.obj: \
mod.c \
$(INCDIR)\mod.h

$(OBJDIR)\oscheme.obj: \
oscheme.c \
$(INCDIR)\oscheme.h \
$(INCDIR)\util.h \
$(INCDIR)\upowr.h \
$(INCDIR)\sosstring.h \
$(INCDIR)\soserror.h 

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