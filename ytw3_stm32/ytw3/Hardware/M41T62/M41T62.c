#include "M41T62.h"

extern I2C_HandleTypeDef hi2c3;

//M41T62д�뺯��
static void M41T62_Write_Byte(uint8_t reg, uint8_t dat)
{
    HAL_I2C_Mem_Write(&hi2c3, M41T62_WRITE_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, &dat, 1,HAL_I2C_ERROR_TIMEOUT);
//    HAL_I2C_Mem_Write_DMA(&hi2c3, M41T62_WRITE_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, &dat, 1);
}

//M41T62��ȡ����
static unsigned char M41T62_Read_Byte(uint8_t reg)
{
	unsigned char dat;//��ȡ��������
    HAL_I2C_Mem_Read(&hi2c3, M41T62_READ_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, &dat, 1,HAL_I2C_ERROR_TIMEOUT);
//    HAL_I2C_Mem_Read_DMA(&hi2c3, M41T62_READ_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, &dat, 1);
    return dat;
}

//M41T62д�����ɺ���
static void M41T62_Write_N_Byte(uint8_t *dat, uint8_t reg, uint8_t num)
{
    HAL_I2C_Mem_Write(&hi2c3, M41T62_WRITE_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, dat, num,HAL_I2C_ERROR_TIMEOUT);
//    HAL_I2C_Mem_Write_DMA(&hi2c3, M41T62_WRITE_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, dat, num);
}


//M41T62��ȡ�����ֽں���
static void M41T62_Read_N_Byte(uint8_t *dat, uint8_t reg, uint8_t num)
{
    HAL_I2C_Mem_Read(&hi2c3, M41T62_READ_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, dat, num,HAL_I2C_ERROR_TIMEOUT);
//    HAL_I2C_Mem_Read_DMA(&hi2c3, M41T62_READ_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, dat, num);
}

//M41T62ʱ���ȡ
void M41T62_Read_Time(uint8_t *dat)
{
	M41T62_Read_N_Byte(dat, M41T62_SECOND, 7);//��ַ�Զ�����
}

//M41T62ʱ��д��
void M41T62_Write_Time(uint8_t *dat)
{
	M41T62_Write_N_Byte(dat, M41T62_SECOND, 7);
}

//M41T62��ȡʵʱʱ�亯��
void M41T62_Get_Real_Time(M41T62_Typedef *time)
{
	uint8_t buf[7];
	
	M41T62_Read_Time(buf);
	time->year = buf[6];
	time->mon  = buf[5] & 0x1F;
	time->day  = buf[4];
	time->week = buf[3] & 0x07;
	time->hour = buf[2];
	time->min  = buf[1] & 0x7F;
	time->sec  = buf[0] & 0x7F;
}

//M41T62����ʵʱʱ�亯��
void M41T62_Set_Real_Time(M41T62_Typedef *time)
{
	uint8_t buf[7];
	
	M41T62_Read_Time(buf);
	buf[5] &= 0xE0;
	buf[3] &= 0xF8;
	buf[1] &= 0x80;
	buf[0] &= 0x80;
	buf[6] = time->year;
	buf[5] |= time->mon;
	buf[4] = time->day;
	buf[3] |= time->week;
	buf[2] = time->hour;
	buf[1] |= time->min;
	buf[0] |= time->sec;
	M41T62_Write_Time(buf);
	M41T62_Write_Byte(M41T62_WATCH_DOG, 0x00);
}

//M41T62�������Ӻ���
void M41T62_Set_Alarm(M41T62_Typedef *time)
{
	uint8_t alarm_mon;
	M41T62_Typedef Alarm_Buff;
	
	alarm_mon = M41T62_Read_Byte(M41T62_ALARM_1_MONTH);
	alarm_mon &= 0xC0;
	Alarm_Buff = *time;
	Alarm_Buff.alarm_mon |= alarm_mon;
	Alarm_Buff.alarm_day &= ~0xC0;
	Alarm_Buff.alarm_hour &= ~0x80;
	Alarm_Buff.alarm_min &= ~0x80;
	Alarm_Buff.alarm_sec &= ~0x80;
	if(Alarm_Buff.alarm_mode == ALARM_MODE_EVERY_SECOND)
	{
		Alarm_Buff.alarm_day |= 0xC0;
		Alarm_Buff.alarm_hour |= 0x80;
		Alarm_Buff.alarm_min |= 0x80;
		Alarm_Buff.alarm_sec |= 0x80;
	}
	else if(Alarm_Buff.alarm_mode == ALARM_MODE_EVERY_MINUTE)
	{
		Alarm_Buff.alarm_day |= 0xC0;
		Alarm_Buff.alarm_hour |= 0x80;
		Alarm_Buff.alarm_min |= 0x80;
	}
	else if(Alarm_Buff.alarm_mode == ALARM_MODE_EVERY_HOUR)
	{
		Alarm_Buff.alarm_day |= 0xC0;
		Alarm_Buff.alarm_hour |= 0x80;
	}
	else if(Alarm_Buff.alarm_mode == ALARM_MODE_EVERY_DAY)
	{
		Alarm_Buff.alarm_day |= 0xC0;
	}
	else if(Alarm_Buff.alarm_mode == ALARM_MODE_EVERY_MONTH)
	{
		Alarm_Buff.alarm_day |= 0x40;
	}
	else if(Alarm_Buff.alarm_mode == ALARM_MODE_EVERY_YEAR)
	{
	}
	M41T62_Write_N_Byte((uint8_t *)&Alarm_Buff.alarm_mon, M41T62_ALARM_1_MONTH, 5);
}

uint8_t Alarm_Mode_Buff = 0;

//M41T62��ȡ���Ӻ���
void M41T62_Get_Alarm(M41T62_Typedef *time)
{
	uint8_t Alarm_Buff[5];
	
	M41T62_Read_N_Byte(Alarm_Buff, M41T62_ALARM_1_MONTH, 5);//��ַ�Զ�����
	time->alarm_mon = Alarm_Buff[0] & ~0xE0;
	time->alarm_day = Alarm_Buff[1] & ~0xC0;
	time->alarm_hour = Alarm_Buff[2] & ~0x80;
	time->alarm_min = Alarm_Buff[3] & ~0x80;
	time->alarm_sec = Alarm_Buff[4] & ~0x80;
	Alarm_Mode_Buff = 0;
	Alarm_Mode_Buff |= (Alarm_Buff[1] & 0x40) >> 2;
	Alarm_Mode_Buff |= (Alarm_Buff[1] & 0x80) >> 4;
	Alarm_Mode_Buff |= (Alarm_Buff[2] & 0x80) >> 5;
	Alarm_Mode_Buff |= (Alarm_Buff[3] & 0x80) >> 6;
	Alarm_Mode_Buff |= (Alarm_Buff[4] & 0x80) >> 7;
	Alarm_Mode_Buff = ~Alarm_Mode_Buff;
	switch(Alarm_Mode_Buff)
	{
		case 0x1F:
			time->alarm_mode = ALARM_MODE_EVERY_SECOND;
			break;
		case 0x1E:
			time->alarm_mode = ALARM_MODE_EVERY_MINUTE;
			break;
		case 0x1C:
			time->alarm_mode = ALARM_MODE_EVERY_HOUR;
			break;
		case 0x18:
			time->alarm_mode = ALARM_MODE_EVERY_DAY;
			break;
		case 0x10:
			time->alarm_mode = ALARM_MODE_EVERY_MONTH;
			break;
		case 0x00:
			time->alarm_mode = ALARM_MODE_EVERY_YEAR;
			break;
		default:
			time->alarm_mode = ALARM_MODE_EVERY_DAY;
		break;
	}
}

//M41T62������ӱ�־λ
void M41T62_Clear_Alarm_Flag(void)
{
	M41T62_Read_Byte(M41T62_FLAG);//��ȡ��ǰ״̬
}

//M41T62���ӿ�������
void M41T62_Open_Alarm(void)
{
	uint8_t temp;//�м����
	
	M41T62_Clear_Alarm_Flag();
	temp = M41T62_Read_Byte(M41T62_ALARM_1_MONTH);//��ȡ��ǰ����
	M41T62_Write_Byte(M41T62_ALARM_1_MONTH, temp | 0x80);//���������ж�ʹ��
}

//DS3231���ӹرպ���
void M41T62_Close_Alarm(void)
{
	uint8_t temp;//�м����
	
	temp = M41T62_Read_Byte(M41T62_ALARM_1_MONTH);//��ȡ��ǰ����
	M41T62_Write_Byte(M41T62_ALARM_1_MONTH, (temp & (~0x80)));//���������ж�ʹ��
	M41T62_Clear_Alarm_Flag();
}

//M41T62���ӿ�������
void M41T62_Alarm_Init(void)
{
	uint8_t temp;//�м����
	
	temp = M41T62_Read_Byte(M41T62_CHECK);//��ȡ��ǰ����
	M41T62_Write_Byte(M41T62_CHECK, (temp | 0x80));//�������������ƽ
	
	M41T62_Clear_Alarm_Flag();
	/* �˴���� EXTI */
}

//M41T62��ʼ������
void M41T62_Init(M41T62_Typedef *time)
{
	uint8_t temp = 0;
	
//	temp = M41T62_Read_Byte(M41T62_FLAG) & 0x04;//��ȡ����ʧЧλ
//	if(temp != 0)//������ʧЧ
//	{
//		temp = M41T62_Read_Byte(M41T62_SECOND);
//		M41T62_Write_Byte(M41T62_SECOND, temp | 0x80);//��λֹͣλ
//
//		HAL_Delay(1000);
//
//		temp = M41T62_Read_Byte(M41T62_SECOND);
//		M41T62_Write_Byte(M41T62_SECOND, temp & 0x7F);//����ֹͣλ,������������
//
//		temp = M41T62_Read_Byte(M41T62_FLAG);
//		M41T62_Write_Byte(M41T62_SECOND, temp & 0xBF);//��������ʧЧλ
//	}

	temp = M41T62_Read_Byte(M41T62_ALARM_1_MONTH) & 0xBF;
	M41T62_Write_Byte(M41T62_ALARM_1_MONTH, temp);//�رշ������

	temp = M41T62_Read_Byte(M41T62_CHECK);
	temp &= 0xC0;
	temp |= 0x2C;//��У׼,ÿ��12*10s
	M41T62_Write_Byte(M41T62_CHECK, temp);//У׼���

	M41T62_Get_Alarm(time);//��ȡ����
//    M41T62_Get_Real_Time(time);//��ȡʱ��
//    time->year = 0x24;
//    time->mon = 0x01;
//    time->day = 0x01;
//    time->hour = 0x00;
//    time->min = 0x00;
//    time->sec = 0x00;
//    time->week = 0x00;
//    M41T62_Set_Real_Time(time);//��������ʱ��
	M41T62_Alarm_Init();//���ӳ�ʼ��
}
