//
// Created by heiyt_R9000P on 2024/3/2.
//

#ifndef YTW3_0_SYSTEM_H
#define YTW3_0_SYSTEM_H

#include "main.h"

extern volatile uint32_t light;

extern lv_timer_t *lv_Timer_1, *lv_Timer_2, *lv_Timer_3;

void YTW_System_Open_Before_ui();
void YTW_System_Open_After_ui();
void YTW_System_Close();

#endif //YTW3_0_SYSTEM_H
