#pragma once

#include <stdint.h>
#include <cmsis_os.h>

#include "stm32f1xx_hal_conf.h"
#include "main.h"

#include "indicator.h"
#include "ws2812.h"
#include "jdy08.h"


int JDY08_Init();