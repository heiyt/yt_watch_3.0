#ifndef _AHT20_H_
#define _AHT20_H_

#include "main.h"
#define AHT20_ADDRESS 0x00

uint8_t AHT20_Read_Status(void);//读取AHT20的状态寄存器
uint8_t AHT20_Read_Cal_Enable(void);  //查询cal enable位有没有使能
void AHT20_SendAC(void); //向AHT20发送AC命令
uint8_t Calc_CRC8(uint8_t *message,uint8_t Num);
void AHT20_Read_CTdata(uint32_t *ct); //没有CRC校验，直接读取AHT20的温度和湿度数据
void AHT20_Init();
void JH_Reset_REG(uint8_t addr);
void AHT20_Start_Init();

#endif


