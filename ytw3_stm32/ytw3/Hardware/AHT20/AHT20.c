#include "AHT20.h"

extern I2C_HandleTypeDef hi2c3;

void Delay_N10us(uint32_t t)//延时函数
{
    uint32_t k;
    while(t--)
    {
        for (k = 0; k < 2; k++);//110
    }
}

void SensorDelay_us(uint32_t t)//延时函数
{
    for(t = t-2; t>0; t--)
    {
        Delay_N10us(1);
    }
}
uint8_t AHT20_Read_Status() {
    uint8_t byte_first;
    HAL_I2C_Master_Receive(&hi2c3, AHT20_ADDRESS, &byte_first, 1, HAL_I2C_ERROR_TIMEOUT);
    return byte_first;
}

uint8_t AHT20_Read_Cal_Enable(void)  //查询cal enable位有没有使能
{
    uint8_t val = 0;//ret = 0,
    val = AHT20_Read_Status();
    if ((val & 0x68) == 0x08) {
        return 1;
    } else {
        return 0;
    }
}

void AHT20_SendAC() {
    uint8_t ac_buff[3] = {0xac, 0x33, 0x00};
    HAL_I2C_Master_Transmit(&hi2c3, AHT20_ADDRESS, ac_buff, 3, HAL_I2C_ERROR_TIMEOUT);
}
//CRC校验类型：CRC8/MAXIM
//多项式：X8+X5+X4+1
//Poly：0011 0001  0x31
//高位放到后面就变成 1000 1100 0x8c
//C现实代码：
uint8_t Calc_CRC8(uint8_t *message,uint8_t Num)
{
    uint8_t i;
    uint8_t byte;
    uint8_t crc=0xFF;
    for(byte=0; byte<Num; byte++)
    {
        crc^=(message[byte]);
        for(i=8;i>0;--i)
        {
            if(crc&0x80) crc=(crc<<1)^0x31;
            else crc=(crc<<1);
        }
    }
    return crc;
}

void AHT20_Read_CTdata(uint32_t *ct) //没有CRC校验，直接读取AHT20的温度和湿度数据
{
    volatile uint8_t  Byte_1th=0;
    volatile uint8_t  Byte_2th=0;
    volatile uint8_t  Byte_3th=0;
    volatile uint8_t  Byte_4th=0;
    volatile uint8_t  Byte_5th=0;
    volatile uint8_t  Byte_6th=0;
    uint8_t byte_buff[6];
    uint32_t RetuData = 0;
    uint16_t cnt = 0;
    AHT20_SendAC();//向AHT10发送AC命令
    HAL_Delay(80);//延时80ms左右
    cnt = 0;
    while(((AHT20_Read_Status()&0x80)==0x80))//直到状态bit[7]为0，表示为空闲状态，若为1，表示忙状态
    {
        SensorDelay_us(1508);
        if(cnt++>=100)
        {
            break;
        }
    }
    HAL_I2C_Master_Receive(&hi2c3, AHT20_ADDRESS, byte_buff, 6, HAL_I2C_ERROR_TIMEOUT);
    Byte_1th = byte_buff[0];
    Byte_2th = byte_buff[1];
    Byte_3th = byte_buff[2];
    Byte_4th = byte_buff[3];
    Byte_5th = byte_buff[4];
    Byte_6th = byte_buff[5];
    RetuData = (RetuData|Byte_2th)<<8;
    RetuData = (RetuData|Byte_3th)<<8;
    RetuData = (RetuData|Byte_4th);
    RetuData =RetuData >>4;
    ct[0] = RetuData;//湿度
    RetuData = 0;
    RetuData = (RetuData|Byte_4th)<<8;
    RetuData = (RetuData|Byte_5th)<<8;
    RetuData = (RetuData|Byte_6th);
    RetuData = RetuData&0xfffff;
    ct[1] =RetuData; //温度
}

void AHT20_Init()   //初始化AHT20
{
    uint8_t transmit_buff[3] = {0xa8, 0x00, 0x00};
    HAL_I2C_Master_Transmit(&hi2c3, AHT20_ADDRESS, transmit_buff, 3, HAL_I2C_ERROR_TIMEOUT);
    HAL_Delay(10);//延时10ms左右

    uint8_t transmit_buff_2[3] = {0xbe, 0x08, 0x00};
    HAL_I2C_Master_Transmit(&hi2c3, AHT20_ADDRESS, transmit_buff_2, 3, HAL_I2C_ERROR_TIMEOUT);
    HAL_Delay(10);//延时10ms左右
}
void JH_Reset_REG(uint8_t addr)
{
    uint8_t Byte_first,Byte_second,Byte_third,Byte_fourth;
    HAL_I2C_Master_Transmit(&hi2c3, AHT20_ADDRESS, &addr, 1, HAL_I2C_ERROR_TIMEOUT);
    HAL_I2C_Master_Transmit(&hi2c3, AHT20_ADDRESS, 0x00, 1, HAL_I2C_ERROR_TIMEOUT);
    HAL_I2C_Master_Transmit(&hi2c3, AHT20_ADDRESS, 0x00, 1, HAL_I2C_ERROR_TIMEOUT);
    HAL_Delay(5);//延时5ms左右
    HAL_I2C_Master_Receive(&hi2c3, AHT20_ADDRESS, &Byte_first, 1, HAL_I2C_ERROR_TIMEOUT);
    HAL_I2C_Master_Receive(&hi2c3, AHT20_ADDRESS, &Byte_second, 1, HAL_I2C_ERROR_TIMEOUT);
    HAL_I2C_Master_Receive(&hi2c3, AHT20_ADDRESS, &Byte_third, 1, HAL_I2C_ERROR_TIMEOUT);
    HAL_Delay(10);//延时10ms左右
    Byte_fourth = addr | 0xB0;
    HAL_I2C_Master_Transmit(&hi2c3, AHT20_ADDRESS,&Byte_fourth, 1, HAL_I2C_ERROR_TIMEOUT);
    HAL_I2C_Master_Transmit(&hi2c3, AHT20_ADDRESS,&Byte_second, 1, HAL_I2C_ERROR_TIMEOUT);
    HAL_I2C_Master_Transmit(&hi2c3, AHT20_ADDRESS,&Byte_third, 1, HAL_I2C_ERROR_TIMEOUT);
    Byte_second=0x00;
    Byte_third =0x00;
}
void AHT20_Start_Init()
{
    JH_Reset_REG(0x1b);
    JH_Reset_REG(0x1c);
    JH_Reset_REG(0x1e);
}

