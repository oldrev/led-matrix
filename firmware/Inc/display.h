#pragma once

#define PALETTE_CAPACITY 16
#define PALETTE_SIZE     8

typedef struct {
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;
} Display_Color;


typedef struct {
    uint16_t LedCount;      // 总灯珠
    uint16_t XMax;          // 每行像素数
    uint16_t YMax;          // 行数
    uint16_t XSkip;          // 行内跳过的
    uint16_t YSkip;          // 列之间跳过的
    Display_Color Palette[PALETTE_SIZE]; // 色盘
} DisplaySettings;

typedef struct {
    uint8_t*            Pixels;
    DisplaySettings*    Settings;
    WS2812_Device       Device;
} Display;


int Display_Init(Display* display, DisplaySettings* settings, SPI_HandleTypeDef* spi);

int Display_Update(Display* display);

int Display_SetPixel(Display* display, uint16_t pos, uint8_t colorIndex);

int Display_SetPixelXY(Display* display, uint16_t x, uint16_t y, uint8_t colorIndex);

int Display_Fill(Display* display, uint8_t colorIndex);