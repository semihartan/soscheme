 // ***** soscheme.mc *****
 // This is the header section.
 // The following are message definitions.
//
//  Values are 32 bit values laid out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +-+-+-+-+-+---------------------+-------------------------------+
//  |S|R|C|N|r|    Facility         |               Code            |
//  +-+-+-+-+-+---------------------+-------------------------------+
//
//  where
//
//      S - Severity - indicates success/fail
//
//          0 - Success
//          1 - Fail (COERROR)
//
//      R - reserved portion of the facility code, corresponds to NT's
//              second severity bit.
//
//      C - reserved portion of the facility code, corresponds to NT's
//              C field.
//
//      N - reserved portion of the facility code. Used to indicate a
//              mapped NT status value.
//
//      r - reserved portion of the facility code. Reserved for internal
//              use. Used to indicate HRESULT values that are not status
//              values, but are instead message ids for display strings.
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//
#define SOS_SEVERITY_SUCCESS             0x0
#define SOS_SEVERITY_INFORMATIONAL       0x1
#define SOS_SEVERITY_WARNING             0x2
#define SOS_SEVERITY_ERROR               0x3


//
// MessageId: SOS_E_QUERY_SCHEMES
//
// MessageText:
//
// Failed to query the overlay schemes available on the system.
//
#define SOS_E_QUERY_SCHEMES              ((HRESULT)0xE0040001L)

//
// MessageId: SOS_E_REGOPEN
//
// MessageText:
//
// Failed to open the registry key.
//
#define SOS_E_REGOPEN                    ((HRESULT)0xE0040002L)

//
// MessageId: SOS_E_REGGET
//
// MessageText:
//
// Failed to get the registry key value.
//
#define SOS_E_REGGET                     ((HRESULT)0xE0040003L)

//
// MessageId: SOS_E_GET_SCHEME
//
// MessageText:
//
// Failed to get the active scheme.
//
#define SOS_E_GET_SCHEME                 ((HRESULT)0xE0040004L)

//
// MessageId: SOS_E_SET_SCHEME
//
// MessageText:
//
// Failed to set the active scheme.
//
#define SOS_E_SET_SCHEME                 ((HRESULT)0xE0040005L)

//
// MessageId: SOS_E_SCHEMEATTR
//
// MessageText:
//
// Failed to set the scheme attribute.
//
#define SOS_E_SCHEMEATTR                 ((HRESULT)0xE0040006L)

//
// MessageId: SOS_E_UNINITIALIZED
//
// MessageText:
//
// OverlayScheme_init was not called.
//
#define SOS_E_UNINITIALIZED              ((HRESULT)0xE0040007L)

//
// MessageId: SOS_E_INVALID
//
// MessageText:
//
// Invalid scheme or alias.
//
#define SOS_E_INVALID                    ((HRESULT)0xE0040008L)

//
// MessageId: SOS_E_WIN32
//
// MessageText:
//
// An internal system error ocurred. Look at the log file for more details.
//
#define SOS_E_WIN32                      ((HRESULT)0xE0040009L)

//
// MessageId: SOS_E_INVALID_DIR
//
// MessageText:
//
// The system cannot find the path specified, or the path is not a directory.
//
#define SOS_E_INVALID_DIR                ((HRESULT)0xE004000AL)

//
// MessageId: SOS_E_CREATE_DIR
//
// MessageText:
//
// Couldn't create the directory or file.
//
#define SOS_E_CREATE_DIR                 ((HRESULT)0xE004000BL)

