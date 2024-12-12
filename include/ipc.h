#pragma once

#ifndef IPC_H
#define IPC_H

#define IPCMESSAGE_MAGIC	'SOSIPCM'

typedef struct IPCMessage_s
{
	uint32_t magic;
    const char* persistentOverlayScheme;
}IPCMessage_t;

void IPCMessage_Init(void* _SharedMemoryBase);

const char* IPCMessage_GetPersistentSchemeMoniker(void* _SharedMemoryBase);

const char* IPCMessage_SetPersistentSchemeMoniker(void* _SharedMemoryBase, const char* _schemeMoniker);

#endif 