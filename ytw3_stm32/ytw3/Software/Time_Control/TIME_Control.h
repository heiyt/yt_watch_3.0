//
// Created by heiyt_R9000P on 2024/3/2.
//

#ifndef YTW3_0_TIME_CONTROL_H
#define YTW3_0_TIME_CONTROL_H

#include "M41T62.h"
extern M41T62_Typedef m41t62_time;
void Time_Open();
void Time_Get();
void Time_Set_Num(int16_t year, int8_t mon, int8_t day, int8_t hour, int8_t min, int8_t sec, int8_t week);
void Time_Set_Struct();

#endif //YTW3_0_TIME_CONTROL_H
