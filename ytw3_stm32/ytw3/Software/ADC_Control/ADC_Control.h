//
// Created by heiyt_R9000P on 2024/2/26.
//

#ifndef YTW3_0_ADC_CONTROL_H
#define YTW3_0_ADC_CONTROL_H

#include "main.h"
#include "stdbool.h"
#include "algorithm.h"
#include <stdio.h>

extern int16_t battery_power;
extern uint16_t cpu_temperature;

//本机的adc
void ADC_READ();

#endif //YTW3_0_ADC_CONTROL_H
