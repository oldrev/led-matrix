#pragma once

#include "messages.h"

#define COMM_REMOTE_HEADER_MAGIC    0x66
#define COMM_REMOTE_PACKAGE_HEADER_SIZE     8
#define COMM_PACKAGE_CAPACITY       512
#define COMM_PACKAGE_BODY_CAPACITY  (COMM_PACKAGE_CAPACITY - COMM_REMOTE_PACKAGE_HEADER_SIZE)     

typedef struct {
    uint16_t Size;
    uint8_t MsgPack[COMM_PACKAGE_CAPACITY];
} Comm_CmdMsg;

typedef struct {
    uint8_t  Magic;
    uint32_t ID;
    uint8_t Type;
    uint16_t Size;
} Comm_RemoteHeader;

typedef struct {
    uint8_t             Package[COMM_PACKAGE_BODY_CAPACITY];
    volatile uint16_t   Size;
    volatile uint16_t   ReceivedSize;
    volatile uint32_t   ReceivedOn;
} Comm_PackageBuffer;


typedef struct {
    osMessageQId       Queue;
    Comm_PackageBuffer Buffer;
    uint8_t            TXBuffer[COMM_PACKAGE_CAPACITY];
} Comm;

int Comm_Init(osMessageQId queue);

int Comm_BeginPackage();
int Comm_ReceiveFrame(const void* frameBuffer, uint16_t frameSize);
void Comm_ParsePackageHeader(const void* buf, Comm_RemoteHeader* header);
void Comm_PackPackageHeader(const Comm_RemoteHeader* header, void* buf);
int Comm_SendPackage(uint8_t packageType, const void* body, uint16_t bodySize);
int Comm_ReplyPackage(uint32_t packageId, uint8_t packageType, const void* body, uint16_t bodySize);