#include <string.h>

#include "devices/devices.h"
#include "display.h"

#include "settings.h"

const AppSettings APP_SETTINGS_DEFAULT = { .DisplaySettings = { .LedCount = 500, // 总灯珠
                                               .XMax = 11, // 每行像素数
                                               .YMax = 20, // 行数
                                               .XSkip = 1, // 行内跳过的
                                               .YSkip = 2, // 列之间跳过的
                                               .Palette = {
                                                   { 0x00, 0x00, 0x00 }, // 纯黑
                                                   { 0x80, 0x80, 0x80 }, // 白/灰
                                                   { 0x80, 0x00, 0x00 }, // 红
                                                   { 0x00, 0x80, 0x00 }, // 绿
                                                   { 0x00, 0x00, 0x80 }, // 蓝
                                                   { 0x80, 0x80, 0x00 }, // 黄
                                                   { 0x00, 0x80, 0x80 }, // 青
                                                   { 0x80, 0x00, 0x80 }, // 粉红
                                               } } };