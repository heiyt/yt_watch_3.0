//
// Created by heiyt_R9000P on 2024/3/2.
//

#include "LCD_Control.h"

void LCD_BLK_Open() {
    HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
}
void LCD_BLK_Set(uint16_t light) {
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, light);
}
void LCD_BLK_Close() {
    __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,0);
    HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);
}
void Touch_Reset(){
    CST816_RESET();
}
void Touch_WakeUp() {
    CST816_Wakeup();
}
void Touch_Enter_AutoSleep(uint8_t time){
    CST816_Config_AutoSleepTime(time);
}
void Touch_Enter_Sleep(){
    CST816_Sleep();
}