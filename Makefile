ROOT = .

PROJECT_NAME=soscheme
OUT_NAME=$(PROJECT_NAME)

!message Project Name: $(PROJECT_NAME)

!if "$(USE_PCH)"==""
USE_PCH=1
!message Using Precompiled Header...
!endif

SOS_SHARED_LIB=$(SOS_SHARED_LIB)
SOS_STATIC_LIB=$(SOS_STATIC_LIB)
SOS_TARGET_ARCH=$(SOS_TARGET_ARCH)
SOS_CONFIG=$(SOS_CONFIG)

!include "$(ROOT)\target.mak"
!include "$(ROOT)\dirs.mak"

!message    SOS_SHARED_LIB=$(SOS_SHARED_LIB)
!message    SOS_STATIC_LIB=$(SOS_STATIC_LIB)
!message    SOS_TARGET_ARCH=$(SOS_TARGET_ARCH)
!message    SOS_CONFIG=$(SOS_CONFIG)

all:
    cd "$(MAKEDIR)"
	set PROJECT_NAME=$(PROJECT_NAME)
	set OUT_NAME=$(OUT_NAME)
	set USE_PCH=$(USE_PCH)
	@echo "    $(MAKE)"
	@echo "    Entering src.."
	cd "$(MAKEDIR)\src"
!if "$(SOS_SHARED_LIB)"=="1"
	@echo "    Building shared lib.."
	@echo "    Calling src\makefile.."
!elseif "$(SOS_STATIC_LIB)"=="1"
	@echo "    Building static lib.."
	@echo "    Calling src\makefile.."
!else
	@echo "    Building executable.."
	@echo "    Calling src\makefile.."
!endif
    @$(MAKE) /NOLOGO $(MAKEFLAGS)
	@echo "    Exiting src.."
	cd "$(MAKEDIR)"
	
clean:
	cd "$(MAKEDIR)"
	cd "$(MAKEDIR)\src"
	set PROJECT_NAME=$(PROJECT_NAME)
	set OUT_NAME=$(OUT_NAME)
	set USE_PCH=$(USE_PCH)
    @$(MAKE) /NOLOGO $(MAKEFLAGS) clean
	cd "$(MAKEDIR)"