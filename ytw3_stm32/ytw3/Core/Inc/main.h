/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lvgl.h"
#include "porting/lv_port_disp.h"
#include "porting/lv_port_indev.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BLE_ROLE_Pin GPIO_PIN_13
#define BLE_ROLE_GPIO_Port GPIOC
#define BLE_SLEEP_Pin GPIO_PIN_14
#define BLE_SLEEP_GPIO_Port GPIOC
#define BLE_ATEN_Pin GPIO_PIN_15
#define BLE_ATEN_GPIO_Port GPIOC
#define BUTTON2_Pin GPIO_PIN_0
#define BUTTON2_GPIO_Port GPIOA
#define BUTTON2_EXTI_IRQn EXTI0_IRQn
#define BLE_STA_Pin GPIO_PIN_4
#define BLE_STA_GPIO_Port GPIOA
#define BUTTON_Pin GPIO_PIN_5
#define BUTTON_GPIO_Port GPIOA
#define BUTTON_EXTI_IRQn EXTI9_5_IRQn
#define STDBY_Pin GPIO_PIN_6
#define STDBY_GPIO_Port GPIOA
#define CHRG_Pin GPIO_PIN_7
#define CHRG_GPIO_Port GPIOA
#define POWER_GOOD_Pin GPIO_PIN_0
#define POWER_GOOD_GPIO_Port GPIOB
#define POWER_ENABLE_Pin GPIO_PIN_2
#define POWER_ENABLE_GPIO_Port GPIOB
#define M41T62_INT_Pin GPIO_PIN_10
#define M41T62_INT_GPIO_Port GPIOB
#define M41T62_INT_EXTI_IRQn EXTI15_10_IRQn
#define CHRGB12_Pin GPIO_PIN_12
#define CHRGB12_GPIO_Port GPIOB
#define STDBYB13_Pin GPIO_PIN_13
#define STDBYB13_GPIO_Port GPIOB
#define LCD_DC_Pin GPIO_PIN_15
#define LCD_DC_GPIO_Port GPIOB
#define LCD_RST_Pin GPIO_PIN_9
#define LCD_RST_GPIO_Port GPIOA
#define USB_PULL_UP_Pin GPIO_PIN_10
#define USB_PULL_UP_GPIO_Port GPIOA
#define LCD_CS_Pin GPIO_PIN_15
#define LCD_CS_GPIO_Port GPIOA
#define T_RST_Pin GPIO_PIN_8
#define T_RST_GPIO_Port GPIOB
#define T_IQR_Pin GPIO_PIN_9
#define T_IQR_GPIO_Port GPIOB
#define T_IQR_EXTI_IRQn EXTI9_5_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
