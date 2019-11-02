#pragma once

#include "messages.h"

#define COMM_REMOTE_HEADER_MAGIC    0x66
#define COMM_REMOTE_PACKAGE_HEADER_SIZE     8
#define COMM_PACKAGE_CAPACITY       512

typedef struct {
    uint16_t Size;
    uint8_t MsgPack[512];
} Comm_CmdMsg;

typedef struct {
    uint8_t  Magic;
    uint32_t ID;
    uint8_t Type;
    uint16_t Size;
} Comm_RemoteHeader;

typedef struct {
    uint8_t             Package[COMM_PACKAGE_CAPACITY];
    volatile uint16_t   Size;
    volatile uint16_t   ReceivedSize;
    volatile uint32_t   ReceivedOn;
} Comm_PackageBuffer;


typedef struct {
    osMessageQId       Queue;
    Comm_PackageBuffer Buffer;
} Comm;

int Comm_Init(osMessageQId queue);

int Comm_BeginPackage();
int Comm_ReceiveFrame(const void* frameBuffer, uint16_t frameSize);
void Comm_ParsePackageHeader(const void* buf, Comm_RemoteHeader* header);