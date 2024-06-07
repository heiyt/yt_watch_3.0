#ifndef __CST816_H
#define __CST816_H
#include "main.h"
#include "stdint.h"
#include <stdbool.h>

/* CST816 dev pin defination */

/* functions define */
#define TOUCH_RST_0 HAL_GPIO_WritePin(T_RST_GPIO_Port, T_RST_Pin, GPIO_PIN_RESET)
#define TOUCH_RST_1 HAL_GPIO_WritePin(T_RST_GPIO_Port, T_RST_Pin, GPIO_PIN_SET)

/* 设备地址 */
#define Device_Addr 	0x15

/* 触摸屏寄存器 */
#define GestureID 			0x01
#define FingerNum 			0x02
#define XposH 				0x03
#define XposL 				0x04
#define YposH 				0x05
#define YposL 				0x06
#define ChipID 				0xA7
#define SleepMode			0xE5
#define MotionMask 			0xEC
#define IrqPluseWidth 	0xED
#define NorScanPer 			0xEE
#define MotionSlAngle 	0xEF
#define LpAutoWakeTime 	0xF4
#define LpScanTH 				0xF5
#define LpScanWin 			0xF6
#define LpScanFreq 			0xF7
#define LpScanIdac 			0xF8
#define AutoSleepTime 	0xF9
#define IrqCtl 					0xFA
#define AutoReset 			0xFB
#define LongPressTime 	0xFC
#define IOCtl 					0xFD
#define DisAutoSleep 		0xFE

/* 触摸屏坐标结构体 */
typedef struct
{
    int16_t X_Pos;
    int16_t Y_Pos;
} CST816_Info;

/* 手势ID识别选项 */
typedef enum
{
    NOGESTURE = 	0x00,
    DOWNGLIDE = 	0x01,
    UPGLIDE = 		0x02,
    LEFTGLIDE = 	0x03,
    RIGHTGLIDE = 	0x04,
    CLICK = 			0x05,
    DOUBLECLICK = 0x0B,
    LONGPRESS = 	0x0C,
} GestureID_TypeDef;

/* 连续动作配置选项 */
typedef enum
{
    M_DISABLE = 	0x00,
    EnConLR = 		0x01,
    EnConUD = 		0x02,
    EnDClick = 		0x03,
    M_ALLENABLE = 0x07,
} MotionMask_TypeDef;

/* 中断低脉冲发射方式选项 */
typedef enum
{
    OnceWLP = 		0x00,
    EnMotion = 		0x10,
    EnChange = 		0x20,
    EnTouch = 		0x40,
    EnTest = 			0x80,
} IrqCtl_TypeDef;

extern bool is_touch_cst816;
extern CST816_Info CST816_Instance;

/* 触摸屏初始化相关函数 */
void CST816_RESET(void);
void CST816_Init(void);

/* 触摸屏操作函数 */
void CST816_Get_XY_AXIS(void);
uint8_t CST816_Get_ChipID(void);
uint8_t CST816_Get_FingerNum(void);

/* 触摸屏有关参数配置函数 */
void CST816_Config_MotionMask(uint8_t mode);
void CST816_Config_AutoSleepTime(uint8_t time);
void CST816_Config_MotionSlAngle(uint8_t x_right_y_up_angle);
void CST816_Config_NorScanPer(uint8_t Period);
void CST816_Config_IrqPluseWidth(uint8_t Width);
void CST816_Config_LpScanTH(uint8_t TH);
void CST816_Wakeup(void);
void CST816_Sleep(void);

#endif
