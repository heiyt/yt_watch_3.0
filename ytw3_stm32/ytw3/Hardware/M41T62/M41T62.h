#ifndef _M41T62_H_
#define _M41T62_H_

#include "main.h"

#ifdef __cplusplus
 extern "C" {
#endif 

#define M41T62_WRITE_ADDRESS		0xD0//����д��ַ
#define M41T62_READ_ADDRESS			0xD1//��������ַ

/* �Ĵ����� */
#define M41T62_SECOND						0x01//��
#define M41T62_MINUTE						0x02//��
#define M41T62_HOUR							0x03//ʱ
#define M41T62_WEEK							0x04//����
#define M41T62_DAY							0x05//��
#define M41T62_MONTH						0x06//��
#define M41T62_YEAR							0x07//��
#define M41T62_CHECK						0x08//У׼
#define M41T62_WATCH_DOG				0x09//���Ź�
#define M41T62_ALARM_1_MONTH		0x0A//�����·�
#define M41T62_ALARM_1_DAY			0x0B//����1����
#define M41T62_ALARM_1_HOUR			0x0C//����1ʱλ
#define M41T62_ALARM_1_MINUTE		0x0D//����1����
#define M41T62_ALARM_1_SECOND		0x0E//����1����
#define M41T62_FLAG							0x0F//��־

#define ALARM_MODE_EVERY_SECOND	0x00
#define ALARM_MODE_EVERY_MINUTE	0x01
#define ALARM_MODE_EVERY_HOUR		0x02
#define ALARM_MODE_EVERY_DAY		0x03
#define ALARM_MODE_EVERY_MONTH	0x04
#define ALARM_MODE_EVERY_YEAR		0x05

//ʱ��ṹ��
typedef struct {
	int16_t  year; //��
	int8_t mon;  //��
	int8_t day;  //��
	int8_t hour; //ʱ
	int8_t min;  //��
	int8_t sec;  //��
	int8_t week; //����
	int8_t alarm_mon;
	int8_t alarm_day;
	int8_t alarm_hour;
	int8_t alarm_min;
	int8_t alarm_sec;
	int8_t alarm_mode;
}M41T62_Typedef;

void M41T62_Init(M41T62_Typedef *time);
void M41T62_Get_Real_Time(M41T62_Typedef *time);
void M41T62_Set_Real_Time(M41T62_Typedef *time);
void M41T62_Set_Alarm(M41T62_Typedef *time);
void M41T62_Clear_Alarm_Flag(void);
void M41T62_Get_Alarm(M41T62_Typedef *time);
void M41T62_Close_Alarm(void);
void M41T62_Open_Alarm(void);

#ifdef __cplusplus
}
#endif

#endif
