#define GUIDSARRAY_BUFFERSZ 256

DWORD WINAPI PowerGetOverlaySchemes(
    GUID** OverlaySchemes, // A pointer that receives a pointer to an array of GUIDs.
    PDWORD lpSchemeCount,   // A pointer to DWORD that receives the number of schemes.
    BYTE undocumented) // It is undocumented now. But it is probably either reserved or unused parameter.
{
  RPC_STATUS status; 
  SIZE_T requiredBytes;
  HLOCAL guidArray;
  int schemesCount;
  RPC_BINDING_HANDLE rpcHandle; 
  CLIENT_CALL_RETURN callReturn;
  BYTE guidsBuffer[GUIDSARRAY_BUFFERSZ]; 
 
  rpcHandle = 0i64;
  schemesCount = 0;
  if ( !OverlaySchemes || !lpSchemeCount)
    return ERROR_INVALID_PARAMETER;
  status = PowerRpcGetHandle(&rpcHandle);
  if ( !status )
  {
    callReturn.Simple = S_OK;
    callReturn.Pointer = NdrClientCall3((MIDL_STUBLESS_PROXY_INFO *)&pProxyInfo, 0x12, 0, rpcHandle, guidsBuffer, &schemesCount, undocumented).Pointer;
    status = (RPC_STATUS)callReturn.Pointer;
    if ( !LODWORD(callReturn.Pointer) )
    { 
      if ( schemesCount )
      {
        requiredBytes = (sizeof(GUID) * schemesCount);
        guidArray = LocalAlloc(LPTR, requiredBytes); 
        if ( !guidArray )
          return ERROR_OUTOFMEMORY;
        memcpy_0(guidArray, guidsBuffer, requiredBytes);
        *OverlaySchemes = guidArray; 
      }
      *lpSchemeCount = schemesCount;
    }
  }
  return status;
}