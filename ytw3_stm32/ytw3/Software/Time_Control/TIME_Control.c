//
// Created by heiyt_R9000P on 2024/3/2.
//

#include "TIME_Control.h"

M41T62_Typedef m41t62_time;

void Time_Open() {
    M41T62_Init(&m41t62_time);
}

void Time_Get() {
    M41T62_Get_Real_Time(&m41t62_time);
}

void Time_Set_Num(int16_t year, int8_t mon, int8_t day, int8_t hour, int8_t min, int8_t sec, int8_t week) {
    m41t62_time.year = year;
    m41t62_time.mon = mon;
    m41t62_time.day = day;
    m41t62_time.hour = hour;
    m41t62_time.min = min;
    m41t62_time.sec = sec;
    M41T62_Set_Real_Time(&m41t62_time);
}

void Time_Set_Struct() {
    M41T62_Set_Real_Time(&m41t62_time);
}