INCDIR = $(ROOT)\include
LIBDIR = $(ROOT)\lib\$(SOS_CONFIG)\$(SOS_TARGET_ARCH)
BINDIR = $(ROOT)\bin\$(SOS_CONFIG)\$(SOS_TARGET_ARCH)
RESDIR = $(ROOT)\res

INCDIRS = $(ROOT)\include

LIBDIRS = \
$(ROOT)\lib\$(SOS_CONFIG)\x86 \
$(ROOT)\lib\$(SOS_CONFIG)\x64 \
$(ROOT)\lib\$(SOS_CONFIG)\arm \
$(ROOT)\lib\$(SOS_CONFIG)\arm64

BINDIRS = \
$(ROOT)\bin\$(SOS_CONFIG)\x86 \
$(ROOT)\bin\$(SOS_CONFIG)\x64 \
$(ROOT)\bin\$(SOS_CONFIG)\arm \
$(ROOT)\bin\$(SOS_CONFIG)\arm64

OBJDIRS = \
obj\$(SOS_CONFIG)\x86 \
obj\$(SOS_CONFIG)\x64 \
obj\$(SOS_CONFIG)\arm \
obj\$(SOS_CONFIG)\arm64 \

!if "$(SOS_SHARED_LIB)"=="1"
OUT_EXT=dll
OUT_DIR=$(BINDIR)
OBJDIR = $(ROOT)\obj\lib\shared\$(SOS_CONFIG)\$(SOS_TARGET_ARCH)
!elseif "$(SOS_STATIC_LIB)"=="1"
OUT_EXT=lib
OUT_DIR=$(LIBDIR)
OBJDIR = $(ROOT)\obj\lib\static\$(SOS_CONFIG)\$(SOS_TARGET_ARCH)
!else
OUT_EXT=exe
OUT_DIR=$(BINDIR)
OBJDIR = $(ROOT)\obj\bin\$(SOS_CONFIG)\$(SOS_TARGET_ARCH)
!endif
 
OUT_PATH=$(OUT_DIR)\$(OUT_NAME).$(OUT_EXT)