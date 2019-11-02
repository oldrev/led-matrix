#pragma once

typedef struct {
    uint8_t Red[3];
    uint8_t Green[3];
    uint8_t Blue[3];
} WS2812_Pixel;

typedef struct {
    SPI_HandleTypeDef* Spi;
    WS2812_Pixel* FrameBuffer;
    uint16_t FrameBufferSize;
} WS2812_Device;

void WS2812_Init(WS2812_Device* ws2812);

void WS2812_Reset(WS2812_Device* ws2812);

void WS2812_Send(WS2812_Device* ws2812);

uint8_t WS2812_IsAvailable(WS2812_Device* ws2812);

void WS2812_SetPixel(WS2812_Device* ws2812, uint16_t index, uint8_t red, uint8_t green, uint8_t blue);

void WS2812_Fill(WS2812_Device* ws2812, uint8_t red, uint8_t green, uint8_t blue);

void WS2812_FillBlack(WS2812_Device* ws2812);

void WS2812_FillWhite(WS2812_Device* ws2812);