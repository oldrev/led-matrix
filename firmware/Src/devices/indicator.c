#include "devices/devices.h"
#include "devices/indicator.h"

typedef struct {
    GPIO_TypeDef* Port;
    uint32_t Pin;
} Indiactor_GpioProfile;

const Indiactor_GpioProfile GPIO_PROFILES[] = { { .Port = DBG_LED_GPIO_Port, .Pin = DBG_LED_Pin } };

static volatile uint32_t g_indicatorTimers[sizeof(GPIO_PROFILES) / sizeof(Indiactor_GpioProfile)];

void Indicator_Init()
{
    for (size_t i = 0; i < sizeof(g_indicatorTimers) / sizeof(uint32_t); i++) {
        g_indicatorTimers[i] = 0;
        Indicator_TurnOff(i);
    }
}

void Indicator_TurnOn(uint8_t index)
{
    const Indiactor_GpioProfile* pprofile = &GPIO_PROFILES[index];
    HAL_GPIO_WritePin(pprofile->Port, pprofile->Pin, GPIO_PIN_RESET);
}

void Indicator_TurnOff(uint8_t index)
{
    const Indiactor_GpioProfile* pprofile = &GPIO_PROFILES[index];
    HAL_GPIO_WritePin(pprofile->Port, pprofile->Pin, GPIO_PIN_SET);
}

void Indicator_BlinkAndDelay(uint8_t index, int ms)
{
    const Indiactor_GpioProfile* pprofile = GPIO_PROFILES + index;
    HAL_GPIO_WritePin(pprofile->Port, pprofile->Pin, GPIO_PIN_RESET);
    HAL_Delay(ms);
    HAL_GPIO_WritePin(pprofile->Port, pprofile->Pin, GPIO_PIN_SET);
}

void Indicator_TurnOnInPeriod(uint8_t index, int ms)
{
    g_indicatorTimers[index] = HAL_GetTick() + ms;
    Indicator_TurnOn(index);
}

void Indicator_Drive()
{
    uint32_t now = HAL_GetTick();
    for (size_t i = 0; i < sizeof(g_indicatorTimers) / sizeof(uint32_t); i++) {
        if (now >= g_indicatorTimers[i]) {
            g_indicatorTimers[i] = 0;
            Indicator_TurnOff(i);
        }
    }
}