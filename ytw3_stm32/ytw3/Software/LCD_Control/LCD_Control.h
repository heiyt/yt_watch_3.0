//
// Created by heiyt_R9000P on 2024/3/2.
//

#ifndef YTW3_0_LCD_CONTROL_H
#define YTW3_0_LCD_CONTROL_H

#include "main.h"
#include "CST816.h"

extern TIM_HandleTypeDef htim1;

void LCD_BLK_Open();
void LCD_BLK_Set(uint16_t light);
void LCD_BLK_Close();
void Touch_Reset();
void Touch_WakeUp();
void Touch_Enter_AutoSleep(uint8_t time);
void Touch_Enter_Sleep();


#endif //YTW3_0_LCD_CONTROL_H
