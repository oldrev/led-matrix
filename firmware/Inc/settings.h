#pragma once

#include "display.h"

typedef struct {
    DisplaySettings     DisplaySettings; // 显示设置
} AppSettings;

/**
 * 默认设置
 **/
extern const AppSettings APP_SETTINGS_DEFAULT;