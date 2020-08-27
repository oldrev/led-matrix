#include <string.h>
#include <stm32f1xx_hal_flash.h>
#include <stm32f1xx_hal_flash_ex.h>
#include "stm32f1xx_hal_conf.h"

#include "devices/devices.h"
#include "display.h"

#include "settings.h"

const AppSettings APP_SETTINGS_DEFAULT = { .DisplaySettings = { .LedCount = 600, // 总灯珠
                                               .XMax = 11, // 每行像素数
                                               .YMax = 18, // 行数
                                               .XSkip = 2, // 行内跳过的
                                               .YSkip = 0, // 行之间跳过的
                                               .Palette = {
                                                   { 0x00, 0x00, 0x00 }, // 纯黑
                                                   { 0x55, 0x55, 0x55 }, // 白/灰
                                                   { 0x55, 0x00, 0x00 }, // 红
                                                   { 0x00, 0x55, 0x00 }, // 绿
                                                   { 0x00, 0x00, 0x55 }, // 蓝
                                                   { 0x55, 0x55, 0x00 }, // 黄
                                                   { 0x00, 0x55, 0x55 }, // 青
                                                   { 0x55, 0x00, 0x55 }, // 粉红
                                               } } };

#define FLASH_MEMORY_SIZE (1024 * 64)

//保存设置的地址为最后1页
#define SETTINGS_FLASH_ADDRESS (0x08000000 + (FLASH_MEMORY_SIZE - (FLASH_PAGE_SIZE)))

const __IO AppSettings* SETTINGS_INVARIABLE = (const __IO AppSettings*)(SETTINGS_FLASH_ADDRESS);

/** 设置初始化 */
void Settings_Init() {}

const __IO AppSettings* Settings_Get() { return SETTINGS_INVARIABLE; }

/** 检查是否是第一次启动 */
int Settings_IsFirstBoot() { return SETTINGS_INVARIABLE->Version != FW_VERSION; }

/** 初始化默认设置 */
void Settings_Restore() { Settings_Save(&APP_SETTINGS_DEFAULT); }

/** 把设置立即写入 Flash 中 */
void Settings_Save(const AppSettings* settings)
{

    uint32_t addr = (uint32_t)SETTINGS_INVARIABLE;
    // 1、解锁FLASH
    if (HAL_FLASH_Unlock() != HAL_OK) {
        Error_Handler();
    }

    // 2、擦除FLASH
    //初始化FLASH_EraseInitTypeDef
    FLASH_EraseInitTypeDef erase;
    erase.TypeErase = FLASH_TYPEERASE_PAGES;
    erase.PageAddress = addr;
    erase.NbPages = 1;

    //擦除
    uint32_t pageError = 0;
    if (HAL_FLASHEx_Erase(&erase, &pageError) != HAL_OK) {
        Error_Handler();
    }

    //注意！ AppSettings 结构必须是按照 32 位对齐

    // 3. 写入 Flash， 按照 32 位一组进行
    uint32_t* buf = (uint32_t*)(settings);
    for (size_t i = 0; i < sizeof(AppSettings) / sizeof(uint32_t); i++) {
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr + (i * sizeof(uint32_t)), buf[i]) != HAL_OK) {
            Error_Handler();
        }
    }

    // 4、锁住FLASH
    if (HAL_FLASH_Lock() != HAL_OK) {
        Error_Handler();
    }
}