#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "devices/devices.h"
#include "display.h"

#define PIXEL_MAX_CAPACITY 500
#define LED_MAX_CAPACITY 1000

/**
 * 初始化显示端口
 **/
int Display_Init(Display* display, DisplaySettings* settings, SPI_HandleTypeDef* spi)
{
    memset(display, 0, sizeof(Display));
    display->Settings = settings;
    uint16_t pixelCount = display->Settings->XMax * display->Settings->YMax;
    if (pixelCount > PIXEL_MAX_CAPACITY || display->Settings->LedCount > LED_MAX_CAPACITY) {
        return -1;
    }

    // 初始化显示像素缓冲区
    display->Pixels = (uint8_t*)malloc(pixelCount); // 浪费了一倍的空间无所谓了，省的位运算好麻烦
    Display_Fill(display, 0);

    // 初始化 WS2812，分配显存
    display->Device.Spi = spi;
    display->Device.FrameBufferSize = display->Settings->LedCount;
    display->Device.FrameBuffer = (WS2812_Pixel*)malloc(display->Device.FrameBufferSize * 9);

    WS2812_Init(&display->Device);

    return 0;
}

int Display_Update(Display* display)
{
    WS2812_FillBlack(&display->Device);
    // 把像素缓冲区转换为显存
    uint16_t ledIndex = 0;
    for (uint16_t y = 0; y < display->Settings->YMax; y++) {
        for (uint16_t x = 0; x < display->Settings->XMax; x++) {
            // 单数行的像素是相反的
            uint16_t pixelIndex = y * display->Settings->XMax + (y % 2 == 0 ? x : (display->Settings->XMax - 1 - x));
            const Display_Color* color = &display->Settings->Palette[display->Pixels[pixelIndex]];
            WS2812_SetPixel(&display->Device, ledIndex, color->Red, color->Green, color->Blue);
            ledIndex++;

            ledIndex += display->Settings->XSkip; //行内跳过的灯珠
        }
        ledIndex += display->Settings->YSkip; //每行跳的灯珠数
    }

    if (!WS2812_IsAvailable(&display->Device)) {
        return 0;
    }

    WS2812_Send(&display->Device);
    return 0;
}

int Display_SetPixel(Display* display, uint16_t pos, uint8_t colorIndex)
{
    display->Pixels[pos] = colorIndex;
    return 0;
}

int Display_SetPixelXY(Display* display, uint16_t x, uint16_t y, uint8_t colorIndex)
{
    display->Pixels[display->Settings->XMax * y + x] = colorIndex;
    return 0;
}

int Display_Fill(Display* display, uint8_t colorIndex)
{
    uint16_t pixelCount = display->Settings->XMax * display->Settings->YMax;
    memset(display->Pixels, colorIndex, pixelCount);
    const Display_Color* color = &display->Settings->Palette[colorIndex];
    WS2812_Fill(&display->Device, color->Red, color->Green, color->Blue);
    return 0;
}