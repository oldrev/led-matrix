#pragma once


void Indicator_Init();
void Indicator_TurnOn(uint8_t index);
void Indicator_TurnOff(uint8_t index);
void Indicator_BlinkAndDelay(uint8_t index, int ms);
void Indicator_TurnOnInPeriod(uint8_t index, int ms);
void Indicator_Drive();
