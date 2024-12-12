ROOT = .
!include "$(ROOT)\target.mak"

all:
	cd "$(MAKEDIR)"
	@echo $(MAKE)
	@echo Entering src..
	cd "$(MAKEDIR)\src"
	@echo Calling src\makefile..
    @$(MAKE) /NOLOGO $(MAKEFLAGS)
	@echo Entering src..
	cd "$(MAKEDIR)\src"
	@echo Setting SOS_SHARED_LIB...
    set SOS_SHARED_LIB=1
	@echo "SOS_SHARED_LIB=$(SOS_SHARED_LIB)"
	@echo Calling src\makefile..
    @$(MAKE) /NOLOGO $(MAKEFLAGS)
	cd "$(MAKEDIR)"
	
clean:
	cd "$(MAKEDIR)\src"
    @$(MAKE) /NOLOGO /$(MAKEFLAGS) clean
	cd "$(MAKEDIR)"
	