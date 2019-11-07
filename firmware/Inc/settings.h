#pragma once

#include "display.h"

typedef struct {
    uint16_t            Version;        // 固件版本
    DisplaySettings     DisplaySettings; // 显示设置
} AppSettings;


void Settings_Init();
const __IO AppSettings* Settings_Get();
int Settings_IsFirstBoot();
void Settings_Restore();
void Settings_Save(const AppSettings* settings);