#include <stdint.h>
#include <string.h>

#include "devices/devices.h"
#include "devices/ws2812.h"
#include "main.h"

#define BIT7 (1 << 7)

#define WS2812_LOW 0b100
#define WS2812_HIGH 0b110

inline static void ColorChannelToBits(uint8_t byte, uint8_t* triple);
inline static void WS2812_ToPixel(uint8_t red, uint8_t green, uint8_t blue, WS2812_Pixel* pixel);

/*
 WS2812 芯片复位需要发送持续 50us 以上的低电平，这里 SPI 2.25M 的频率，换算下来
 50 / ((1 / 2250000) * 1000 * 1000) / 8 为 14.0625 保险起见发送 20 个字节
*/
#define RESET_BUFFER_SIZE 20
const uint8_t RESET_BUFFER[RESET_BUFFER_SIZE] = { 0 };

void WS2812_Init(WS2812_Device* ws2812)
{
    WS2812_FillBlack(ws2812);

    while (HAL_SPI_GetState(ws2812->Spi) != HAL_SPI_STATE_READY) {
    }
    WS2812_Reset(ws2812);
    while (HAL_SPI_GetState(ws2812->Spi) != HAL_SPI_STATE_READY) {
    }
    WS2812_Send(ws2812);
    while (HAL_SPI_GetState(ws2812->Spi) != HAL_SPI_STATE_READY) {
    }
}

void WS2812_Reset(WS2812_Device* ws2812)
{
    HAL_StatusTypeDef result = HAL_SPI_Transmit_DMA(ws2812->Spi, (uint8_t*)RESET_BUFFER, RESET_BUFFER_SIZE);
    if (result != HAL_OK) {
        Error_Handler();
    }
}

void WS2812_Send(WS2812_Device* ws2812)
{
    if (HAL_SPI_Transmit_DMA(ws2812->Spi, (uint8_t*)ws2812->FrameBuffer, ws2812->FrameBufferSize * 9) != HAL_OK) {
        Error_Handler();
    }
}

inline uint8_t WS2812_IsAvailable(WS2812_Device* ws2812)
{
    return HAL_SPI_GetState(ws2812->Spi) == HAL_SPI_STATE_READY;
}

inline void WS2812_ToPixel(uint8_t red, uint8_t green, uint8_t blue, WS2812_Pixel* pixel)
{
    ColorChannelToBits(red, pixel->Red);
    ColorChannelToBits(green, pixel->Green);
    ColorChannelToBits(blue, pixel->Blue);
}

inline void WS2812_SetPixel(WS2812_Device* ws2812, uint16_t index, uint8_t red, uint8_t green, uint8_t blue)
{
    WS2812_ToPixel(red, green, blue, &ws2812->FrameBuffer[index]);
}

void WS2812_Fill(WS2812_Device* ws2812, uint8_t red, uint8_t green, uint8_t blue)
{
    for (uint16_t i = 0; i < ws2812->FrameBufferSize; i++) {
        WS2812_ToPixel(red, green, blue, &ws2812->FrameBuffer[i]);
    }
}

void WS2812_FillBlack(WS2812_Device* ws2812) { WS2812_Fill(ws2812, 0, 0, 0); }

void WS2812_FillWhite(WS2812_Device* ws2812) { WS2812_Fill(ws2812, 0xFF, 0xFF, 0xFF); }

/**
 * 8位单通道颜色值转换为24位
 */
inline void ColorChannelToBits(uint8_t byte, uint8_t* triple)
{
    uint32_t encoding = 0;
    for (size_t i = 0; i < 8; i++) {
        encoding = encoding << 3;
        if (byte & BIT7) {
            encoding |= WS2812_HIGH;
        } else {
            encoding |= WS2812_LOW;
        }
        byte = byte << 1;
    }
    triple[0] = ((encoding >> 16) & 0xff);
    triple[1] = ((encoding >> 8) & 0xff);
    triple[2] = (encoding & 0xff);
}