; // ***** soscheme.mc *****
; // This is the header section.

MessageIdTypedef=HRESULT

SeverityNames=(Success=0:SOS_SEVERITY_SUCCESS
Informational=0x1:SOS_SEVERITY_INFORMATIONAL
Warning=0x2:SOS_SEVERITY_WARNING
Error=0x3:SOS_SEVERITY_ERROR
)

FacilityNames=(FACILITY_ITF=0x4)

LanguageNames=(English=0x409:MSG00409)

; // The following are message definitions.

MessageId=0x1
Severity=Error
Facility=FACILITY_ITF
SymbolicName=SOS_E_QUERY_SCHEMES
Language=English
Failed to query the overlay schemes available on the system.
.

MessageId=0x2
Severity=Error
Facility=FACILITY_ITF
SymbolicName=SOS_E_REGOPEN
Language=English
Failed to open the registry key.
.

MessageId=0x3
Severity=Error
Facility=FACILITY_ITF
SymbolicName=SOS_E_REGGET
Language=English
Failed to get the registry key value.
.

MessageId=0x4
Severity=Error
Facility=FACILITY_ITF
SymbolicName=SOS_E_GET_SCHEME
Language=English
Failed to get the active scheme.
.

MessageId=0x5
Severity=Error
Facility=FACILITY_ITF
SymbolicName=SOS_E_SET_SCHEME
Language=English
Failed to set the active scheme.
.

MessageId=0x6
Severity=Error
Facility=FACILITY_ITF
SymbolicName=SOS_E_SCHEMEATTR
Language=English
Failed to set the scheme attribute.
.

MessageId=0x7
Severity=Error
Facility=FACILITY_ITF
SymbolicName=SOS_E_UNINITIALIZED
Language=English
OverlayScheme_init was not called.
.

MessageId=0x8
Severity=Error
Facility=FACILITY_ITF
SymbolicName=SOS_E_INVALID
Language=English
Invalid scheme or alias.
.

MessageId=0x9
Severity=Error
Facility=FACILITY_ITF
SymbolicName=SOS_E_WIN32
Language=English
An internal system error ocurred. Look at the log file for more details.
.

MessageId=0xA
Severity=Error
Facility=FACILITY_ITF
SymbolicName=SOS_E_INVALID_DIR
Language=English
The system cannot find the path specified, or the path is not a directory.
.

MessageId=0xB
Severity=Error
Facility=FACILITY_ITF
SymbolicName=SOS_E_CREATE_DIR
Language=English
Couldn't create the directory or file.
.
