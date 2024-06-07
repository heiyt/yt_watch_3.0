//
// Created by heiyt_R9000P on 2024/3/2.
//

#include "system.h"
#include "TIME_Control.h"
#include "BLE_Control.h"
#include "LCD_Control.h"
#include "a_heiyt_task_lvgl/change_things.h"

lv_timer_t *lv_Timer_1, *lv_Timer_2, *lv_Timer_3;

void YTW_System_Open_Before_ui() {
    /*user code*/
    //启动供电，启动usb，启动屏幕背光，开启需要的中断
    HAL_GPIO_WritePin(POWER_ENABLE_GPIO_Port, POWER_ENABLE_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(USB_PULL_UP_GPIO_Port, USB_PULL_UP_Pin, GPIO_PIN_SET);
    LCD_BLK_Open();
    LCD_BLK_Set(light);
    BLE_Init();
    Time_Open();
}

void YTW_System_Open_After_ui() {
    lv_Timer_3 = lv_timer_create(refresh_time_control_panel, 200, NULL);
}

void YTW_System_Close() {
    HAL_GPIO_WritePin(USB_PULL_UP_GPIO_Port, USB_PULL_UP_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(POWER_ENABLE_GPIO_Port, POWER_ENABLE_Pin, GPIO_PIN_RESET);
}