//
// Created by heiyt_R9000P on 2024/3/5.
//

#include "heiyt_task.h"
#include "ADC_Control.h"
#include "a_heiyt_task_lvgl/change_things.h"

extern bool is_button_p;
extern bool is_button2_p;
extern osThreadId_t lvgl_taskHandle;
extern osThreadId_t uart_taskHandle;
extern osThreadId_t system_low_taskHandle;
extern osThreadId_t system_fast_taskHandle;
//按钮事件不能停止，要不然无法唤醒
extern osTimerId_t sleep_timerHandle;
extern osMutexId_t lvgl_mutexHandle;
extern osEventFlagsId_t power_eventHandle;

volatile uint32_t sleepTime = 10000;
volatile uint32_t light = 90;

bool is_sleep = false;

void enter_sleep();
void wake_up();

void start_lvgl_task(void *argument)
{
    /* USER CODE BEGIN start_lvgl_task */
    /* Infinite loop */
    while(1)
    {
        osMutexAcquire(lvgl_mutexHandle, 12);
        lv_timer_handler();
        osDelay(6);
        osMutexRelease(lvgl_mutexHandle);
    }
    /* USER CODE END start_lvgl_task */
}

void start_uart_task(void *argument)
{
    /* USER CODE BEGIN start_uart_task */

    /* Infinite loop */
    while(1)
    {
        if (uart_get) {
            uart_get = false;
            BLE_Task();
            refresh_time_BLE();
            refresh_time_BLE_2();
        }
        osDelay(100);
    }
    /* USER CODE END start_uart_task */
}

void start_system_fast_task(void *argument)
{
    /* USER CODE BEGIN start_system_task */
    /* Infinite loop */
    while(1)
    {
        //电量读取以及低电量关机
        ADC_READ();
        osDelay(50);
    }
    /* USER CODE END start_system_task */
}

void start_system_low_task(void *argument)
{
    /* USER CODE BEGIN start_system_low_task */
    /* Infinite loop */
   while(1)
    {
        if (HAL_GPIO_ReadPin(POWER_GOOD_GPIO_Port, POWER_GOOD_Pin)) {
            osEventFlagsSet(power_eventHandle, 0x01);
        }
        if (HAL_GPIO_ReadPin(CHRG_GPIO_Port, CHRG_Pin) == 0) {
            osEventFlagsSet(power_eventHandle, 0x02);
        }
        if (HAL_GPIO_ReadPin(STDBY_GPIO_Port, STDBY_Pin) == 0) {
            osEventFlagsSet(power_eventHandle, 0x04);
        }
        if (BLE_Is_Connect()) {
            osEventFlagsSet(power_eventHandle, 0x08);
        }
        osDelay(1000);
    }
    /* USER CODE END start_system_low_task */
}

void start_button_task(void *argument)
{
    /* USER CODE BEGIN start_button_task */
    /* Infinite loop */
    while(1)
    {
        if (is_button_p || is_button2_p) {
            is_button_p = false;
            is_button2_p = false;
            osTimerStart(sleep_timerHandle, pdMS_TO_TICKS(sleepTime));
            Touch_Enter_AutoSleep(sleepTime/1000);
            if (is_sleep) {
                is_sleep = false;
                wake_up();
            }
        }
        osDelay(20);
    }
    /* USER CODE END start_button_task */
}

void sleep_Callback(void *argument)
{
    /* USER CODE BEGIN sleep_Callback */
    enter_sleep();
    /* USER CODE END sleep_Callback */
}

void enter_sleep() { //唤醒有关任务不能关闭。。。
    is_sleep = true;
    HAL_SPI_DMAPause(&hspi1);
    vTaskSuspend(lvgl_taskHandle);
    vTaskSuspend(uart_taskHandle);
    vTaskSuspend(system_low_taskHandle);
    vTaskSuspend(system_fast_taskHandle);
    osTimerStop(sleep_timerHandle);
    LCD_BLK_Close();
    __HAL_RCC_GPIOA_CLK_DISABLE();
    __HAL_RCC_GPIOB_CLK_DISABLE();
    __HAL_RCC_GPIOC_CLK_DISABLE();
    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON,PWR_STOPENTRY_WFI);
}

void wake_up() {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    HAL_SPI_DMAResume(&hspi1);
    vTaskResume(lvgl_taskHandle);
    vTaskResume(uart_taskHandle);
    vTaskResume(system_low_taskHandle);
    vTaskResume(system_fast_taskHandle);
    LCD_BLK_Open();
    LCD_BLK_Set(light);
}

void PreSleepProcessing(uint32_t ulExpectedIdleTime)
{
/* place for user code */
    __HAL_RCC_GPIOA_CLK_DISABLE();
    __HAL_RCC_GPIOB_CLK_DISABLE();
    __HAL_RCC_GPIOC_CLK_DISABLE();
}

void PostSleepProcessing(uint32_t ulExpectedIdleTime)
{
/* place for user code */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
}