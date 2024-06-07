// 0x68 << 1 = 0xD0
#define MBI160_ADDRESS 0xD0

#include "BMI160.h"

#define AM_DEVICES_BMI160_CMD 0x7e
#define AM_DEVICES_BMI160_INT_MOTION_3 0x62
#define AM_DEVICES_BMI160_INT_MOTION_2 0x61
#define AM_DEVICES_BMI160_INT_MOTION_1 0x60
#define AM_DEVICES_BMI160_INT_MOTION_0 0x5F
#define AM_DEVICES_BMI160_INT_MAP_1 0x56
#define AM_DEVICES_BMI160_INT_MAP_0 0x55
#define AM_DEVICES_BMI160_INT_LATCH 0x54
#define AM_DEVICES_BMI160_INT_OUT_CTRL 0x53
#define AM_DEVICES_BMI160_INT_EN_2 0x52
#define AM_DEVICES_BMI160_INT_EN_1 0x51
#define AM_DEVICES_BMI160_INT_EN_0 0x50
#define AM_DEVICES_BMI160_PMU_STATUS 0x03
#define AM_DEVICES_BMI160_ERR_REG 0x02

extern I2C_HandleTypeDef hi2c3;

// 写指令 buffer
uint8_t I2C_Buffer_Write[16] = {0};

void BMI160_Write_Reg(uint8_t reg,  uint8_t val)
{
    I2C_Buffer_Write[0] = reg ; ;
    I2C_Buffer_Write[1] = val;
    HAL_I2C_Master_Transmit(&hi2c3, MBI160_ADDRESS, I2C_Buffer_Write, 2, 1000);
    HAL_Delay(50);

}


void BMI160_Read_Reg(uint8_t reg, uint16_t data_len)
{
    I2C_Buffer_Write[0] = reg;
    I2C_Buffer_Write[1] = 0x0c;

    HAL_I2C_Master_Transmit(&hi2c3, MBI160_ADDRESS, I2C_Buffer_Write, 1, 1000);

    HAL_Delay(5);
    memset(I2C_Buffer_Write, 0, sizeof(I2C_Buffer_Write));
    HAL_I2C_Master_Receive(&hi2c3, MBI160_ADDRESS, I2C_Buffer_Write, data_len, 1000);
}


// 初始化一下BMI160 若有晃动，移动，INT1 发出中断信号
void init_bmi160()
{
    uint8_t ui8Attempts = 20;
    uint8_t ui8Status = 0;

    // 重启 BMI160
    BMI160_Write_Reg(AM_DEVICES_BMI160_CMD, 0xB6);

    while (ui8Status != 0x24 && ui8Attempts--)
    {
        // BMI160 陀螺仪 通用模式
        BMI160_Write_Reg(AM_DEVICES_BMI160_CMD, 0x15);

        // BMI160 加速器 low power
        BMI160_Write_Reg(AM_DEVICES_BMI160_CMD, 0x12);
        BMI160_Read_Reg(AM_DEVICES_BMI160_PMU_STATUS, 1);
        ui8Status =	I2C_Buffer_Write[0];

#if GYROSCOPE_DEBUG
        printf ("PMU_STATUS=%02Xr\n", I2C_Buffer_Write[0]);
#endif
    }

    BMI160_Read_Reg(AM_DEVICES_BMI160_ERR_REG, 1);
#if GYROSCOPE_DEBUG
    printf ("_ERR_REG=%02X\r\n", I2C_Buffer_Write[0]);
#endif


    BMI160_Write_Reg(AM_DEVICES_BMI160_INT_MOTION_0, 0x00);
    BMI160_Write_Reg(AM_DEVICES_BMI160_INT_MOTION_1, 0x14);
    //BMI160_Write_Reg(AM_DEVICES_BMI160_INT_MOTION_2, 0xFF);
    BMI160_Write_Reg(AM_DEVICES_BMI160_INT_MOTION_3, 0x02);


    BMI160_Write_Reg(AM_DEVICES_BMI160_INT_OUT_CTRL, 0x0A);

    //BMI160_Write_Reg(AM_DEVICES_BMI160_INT_MAP_2, 0x07);
    //BMI160_Write_Reg(AM_DEVICES_BMI160_INT_MAP_1, 0x07);
    BMI160_Write_Reg(AM_DEVICES_BMI160_INT_MAP_0, 0x07);

    // INT_EN_0
    BMI160_Write_Reg(AM_DEVICES_BMI160_INT_EN_0, 0x07);
    BMI160_Write_Reg(AM_DEVICES_BMI160_INT_EN_1, 0x07);
    BMI160_Write_Reg(AM_DEVICES_BMI160_INT_EN_2, 0x07);

}
//// 定义变量
//int acc_x = 0, acc_y = 0, acc_z = 0;

// 读取I2c数据。
void i2c_read_data(int *gyr_x, int *gyr_y, int *gyr_z)
{

    HAL_Delay(100);

    I2C_Buffer_Write[0] = 0x0c;
    I2C_Buffer_Write[1] = 0x0c;

    HAL_I2C_Master_Transmit(&hi2c3, MBI160_ADDRESS, I2C_Buffer_Write, 1, 1000);

    HAL_Delay(5);
    memset(I2C_Buffer_Write, 0, sizeof(I2C_Buffer_Write));
    HAL_I2C_Master_Receive(&hi2c3, MBI160_ADDRESS, I2C_Buffer_Write, 6, 1000);

    *gyr_x  = I2C_Buffer_Write[0] | (I2C_Buffer_Write[1] << 8);
    if(*gyr_x > 0x7fff)
    {
        *gyr_x = -(0xffff - *gyr_x);
    }
    *gyr_x = (*gyr_x * 2000) / 0x8000;

    *gyr_y  = I2C_Buffer_Write[2] | (I2C_Buffer_Write[3] << 8);
    if(*gyr_y > 0x7fff)
    {
        *gyr_y = -(0xffff - *gyr_y);
    }

    *gyr_y = (*gyr_y * 2000) / 0x8000;

    *gyr_z  = I2C_Buffer_Write[4] | (I2C_Buffer_Write[5] << 8);
    if(*gyr_z > 0x7fff)
    {
        *gyr_z = -(0xffff - *gyr_z);
    }
    *gyr_z = (*gyr_z * 2000) / 0x8000;

#if GYROSCOPE_DEBUG
    printf("read i2c=\r\n %02x, %02x, %02x, %02x, %02x, %02x\r\n",
           I2C_Buffer_Write[0], I2C_Buffer_Write[1], I2C_Buffer_Write[2],
           I2C_Buffer_Write[3], I2C_Buffer_Write[4], I2C_Buffer_Write[5]);
    printf("gyr_x=%d, gyr_y=%d, gyr_z=%d\r\n", gyr_x, gyr_y, gyr_z);
#endif

    if (abs(*gyr_z) + abs(*gyr_x) + abs(*gyr_y) >= 5)
    {
#if GYROSCOPE_DEBUG
        printf("warnning REMOVE \r\n");
#endif
    }
}
