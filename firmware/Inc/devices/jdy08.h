#pragma once

#define JDY08_RX_CAPACITY 32
#define JDY08_BLE_PACKAGE_SIZE 20

typedef struct {
    UART_HandleTypeDef* Uart;
    DMA_HandleTypeDef*  Dma;
    uint8_t             RXBuffer[JDY08_RX_CAPACITY];
    volatile uint16_t   RXSize;
    volatile uint8_t    IsReceived;
    volatile uint8_t    Mode;
    char                Mac[13];
} JDY08_Device;

enum {
    JDY08_AT_MODE = 0,
    JDY08_TRANS_MODE = 1,
};


int JDY08_Init(UART_HandleTypeDef* uart, DMA_HandleTypeDef* dma);
int JDY08_SendAT(const char* cmd);
int JDY08_SendATAndWaitOK(const char* cmd);

int JDY08_BeginDataRX();

int JDY08_OnReceived();

int JDY08_EnsureBroadcastingName(int* resetRequired);
int JDY08_EnsurePower(int* resetRequired);
int JDY08_EnsureWeixinEnabled(int* resetRequired);
int JDY08_EnsureClass(int* resetRequired);
int JDY08_EnsureAdvertisement(int* resetRequired);

const char* JDY08_GetMac();

int JDY08_Reset();
int JDY08_IsConnected();

int JDY08_Transmit(const void* buf, uint16_t bufSize);