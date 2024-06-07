//
// Created by heiyt_R9000P on 2024/3/2.
//

#include "BLE_Control.h"

uint8_t receive_uart[RECEIVE_UART_LENGTH];
bool uart_get = false;

extern UART_HandleTypeDef huart2;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart == &huart2) {
        uart_get = true;
    }
}
void BLE_Init() {
    BLE_Wake_Up();
    BLE_AT_Disable();
    BLE_Enter_Slave();
    HAL_UART_Receive_IT(&huart2, receive_uart, RECEIVE_UART_LENGTH);
}
void BLE_Send_AT(char *at_command,uint8_t size) {
    HAL_UART_Transmit(&huart2, (uint8_t *)at_command, size, HAL_MAX_DELAY);
}
void BLE_Send(uint8_t *data,uint16_t size){
    HAL_UART_Transmit(&huart2, data, size, HAL_MAX_DELAY);
}

void BLE_Task(){
    /*user code*/
    if (receive_uart[0] == 0x01) {
        if (!(receive_uart[1] > 0x23 || receive_uart[1] < 0x00)) {
            m41t62_time.hour = (int8_t)receive_uart[1];
        }
        if (!(receive_uart[2] > 0x59 || receive_uart[2] < 0x00)) {
            m41t62_time.min = (int8_t)receive_uart[2];
        }
        if (!(receive_uart[3] > 0x59 || receive_uart[3] < 0x00)) {
            m41t62_time.sec = (int8_t)receive_uart[3];
        }
        m41t62_time.year = (int16_t) (0x2000 + receive_uart[5]);
        if (!(receive_uart[6] > 0x12 || receive_uart[6] < 0x00)) {
            m41t62_time.mon = (int8_t) receive_uart[6];
        }
        if (!(receive_uart[7] > 0x31 || receive_uart[7] < 0x00)) {
            m41t62_time.day = (int8_t) receive_uart[7];
        }
        if (!(receive_uart[8] > 0x07 || receive_uart[8] < 0x00)) {
            m41t62_time.week = (int8_t) receive_uart[8];
        }
        Time_Set_Struct();
        BLE_Send("sync end", 8);
    }
    HAL_UART_Receive_IT(&huart2, receive_uart, RECEIVE_UART_LENGTH);
}

void BLE_Enter_Sleep(){
    HAL_GPIO_WritePin(BLE_SLEEP_GPIO_Port, BLE_SLEEP_Pin, GPIO_PIN_SET);
}
void BLE_Wake_Up() {
    HAL_GPIO_WritePin(BLE_SLEEP_GPIO_Port, BLE_SLEEP_Pin, GPIO_PIN_RESET);
}
void BLE_AT_Enable(){
    HAL_GPIO_WritePin(BLE_ATEN_GPIO_Port, BLE_ATEN_Pin, GPIO_PIN_RESET);
}
void BLE_AT_Disable(){
    HAL_GPIO_WritePin(BLE_ATEN_GPIO_Port, BLE_ATEN_Pin, GPIO_PIN_SET);
}
void BLE_Enter_Master(){
    HAL_GPIO_WritePin(BLE_ROLE_GPIO_Port, BLE_ROLE_Pin, GPIO_PIN_RESET);
}
void BLE_Enter_Slave(){
    HAL_GPIO_WritePin(BLE_ROLE_GPIO_Port, BLE_ROLE_Pin, GPIO_PIN_SET);
}
bool BLE_Is_Connect(){
    if(HAL_GPIO_ReadPin(BLE_STA_GPIO_Port, BLE_STA_Pin)){
        return true;
    } else {
        return false;
    }
}