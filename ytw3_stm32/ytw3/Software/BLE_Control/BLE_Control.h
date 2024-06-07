//
// Created by heiyt_R9000P on 2024/3/2.
//

#ifndef YTW3_0_BLE_CONTROL_H
#define YTW3_0_BLE_CONTROL_H

#include "main.h"
#include "TIME_Control.h"

#define RECEIVE_UART_LENGTH 20

extern bool uart_get;

void BLE_Init();
void BLE_Enter_Sleep();
void BLE_Wake_Up();
void BLE_AT_Enable();
void BLE_AT_Disable();
void BLE_Enter_Master();
void BLE_Enter_Slave();
bool BLE_Is_Connect();
void BLE_Send_AT(char *at_command,uint8_t size);
void BLE_Send(uint8_t *data,uint16_t size);
void BLE_Task();

#endif //YTW3_0_BLE_CONTROL_H
