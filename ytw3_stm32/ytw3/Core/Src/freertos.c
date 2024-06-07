/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for button_task */
osThreadId_t button_taskHandle;
const osThreadAttr_t button_task_attributes = {
  .name = "button_task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal3,
};
/* Definitions for uart_task */
osThreadId_t uart_taskHandle;
const osThreadAttr_t uart_task_attributes = {
  .name = "uart_task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow6,
};
/* Definitions for system_low_task */
osThreadId_t system_low_taskHandle;
const osThreadAttr_t system_low_task_attributes = {
  .name = "system_low_task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow2,
};
/* Definitions for lvgl_task */
osThreadId_t lvgl_taskHandle;
uint32_t lvgl_taskBuffer[ 6144 ];
osStaticThreadDef_t lvgl_taskControlBlock;
const osThreadAttr_t lvgl_task_attributes = {
  .name = "lvgl_task",
  .cb_mem = &lvgl_taskControlBlock,
  .cb_size = sizeof(lvgl_taskControlBlock),
  .stack_mem = &lvgl_taskBuffer[0],
  .stack_size = sizeof(lvgl_taskBuffer),
  .priority = (osPriority_t) osPriorityNormal5,
};
/* Definitions for system_fast_task */
osThreadId_t system_fast_taskHandle;
const osThreadAttr_t system_fast_task_attributes = {
  .name = "system_fast_task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow4,
};
/* Definitions for sleep_timer */
osTimerId_t sleep_timerHandle;
const osTimerAttr_t sleep_timer_attributes = {
  .name = "sleep_timer"
};
/* Definitions for lvgl_mutex */
osMutexId_t lvgl_mutexHandle;
const osMutexAttr_t lvgl_mutex_attributes = {
  .name = "lvgl_mutex"
};
/* Definitions for power_event */
osEventFlagsId_t power_eventHandle;
const osEventFlagsAttr_t power_event_attributes = {
  .name = "power_event"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void start_button_task(void *argument);
void start_uart_task(void *argument);
void start_system_low_task(void *argument);
void start_lvgl_task(void *argument);
void start_system_fast_task(void *argument);
void sleep_Callback(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationTickHook(void);

/* USER CODE BEGIN 3 */
void vApplicationTickHook( void )
{
   /* This function will be called by each tick interrupt if
   configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h. User code can be
   added here, but the tick hook is called from an interrupt context, so
   code must not attempt to block, and only the interrupt safe FreeRTOS API
   functions can be used (those that end in FromISR()). */
    lv_tick_inc(1);
}
/* USER CODE END 3 */

/* USER CODE BEGIN PREPOSTSLEEP */
__weak void PreSleepProcessing(uint32_t ulExpectedIdleTime)
{
/* place for user code */
}

__weak void PostSleepProcessing(uint32_t ulExpectedIdleTime)
{
/* place for user code */
}
/* USER CODE END PREPOSTSLEEP */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of lvgl_mutex */
  lvgl_mutexHandle = osMutexNew(&lvgl_mutex_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* creation of sleep_timer */
  sleep_timerHandle = osTimerNew(sleep_Callback, osTimerPeriodic, NULL, &sleep_timer_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
    osTimerStart(sleep_timerHandle, pdMS_TO_TICKS(10000));
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of button_task */
  button_taskHandle = osThreadNew(start_button_task, NULL, &button_task_attributes);

  /* creation of uart_task */
  uart_taskHandle = osThreadNew(start_uart_task, NULL, &uart_task_attributes);

  /* creation of system_low_task */
  system_low_taskHandle = osThreadNew(start_system_low_task, NULL, &system_low_task_attributes);

  /* creation of lvgl_task */
  lvgl_taskHandle = osThreadNew(start_lvgl_task, NULL, &lvgl_task_attributes);

  /* creation of system_fast_task */
  system_fast_taskHandle = osThreadNew(start_system_fast_task, NULL, &system_fast_task_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* creation of power_event */
  power_eventHandle = osEventFlagsNew(&power_event_attributes);

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_start_button_task */
/**
* @brief Function implementing the button_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_start_button_task */
__weak void start_button_task(void *argument)
{
  /* USER CODE BEGIN start_button_task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END start_button_task */
}

/* USER CODE BEGIN Header_start_uart_task */
/**
* @brief Function implementing the uart_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_start_uart_task */
__weak void start_uart_task(void *argument)
{
  /* USER CODE BEGIN start_uart_task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END start_uart_task */
}

/* USER CODE BEGIN Header_start_system_low_task */
/**
* @brief Function implementing the system_low_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_start_system_low_task */
__weak void start_system_low_task(void *argument)
{
  /* USER CODE BEGIN start_system_low_task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END start_system_low_task */
}

/* USER CODE BEGIN Header_start_lvgl_task */
/**
* @brief Function implementing the lvgl_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_start_lvgl_task */
__weak void start_lvgl_task(void *argument)
{
  /* USER CODE BEGIN start_lvgl_task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END start_lvgl_task */
}

/* USER CODE BEGIN Header_start_system_fast_task */
/**
* @brief Function implementing the system_fast_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_start_system_fast_task */
__weak void start_system_fast_task(void *argument)
{
  /* USER CODE BEGIN start_system_fast_task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END start_system_fast_task */
}

/* sleep_Callback function */
__weak void sleep_Callback(void *argument)
{
  /* USER CODE BEGIN sleep_Callback */

  /* USER CODE END sleep_Callback */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

