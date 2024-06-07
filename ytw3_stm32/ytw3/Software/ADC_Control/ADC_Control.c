//
// Created by heiyt_R9000P on 2024/2/26.
//

#include "ADC_Control.h"
#include "system.h"
#include "ui_helpers.h"

extern ADC_HandleTypeDef hadc1;

uint16_t adc_count = 0;
uint32_t adc_value[3];
uint32_t vbat_list[101];
uint32_t cpu_temper_list[101];
uint32_t verfint_list[101];
uint16_t v_bat;
float v_cpuT;
char show_b[3];
char show_t[3];
int16_t battery_power;
uint16_t cpu_temperature;

void ADC_READ() {
    HAL_ADC_Start_DMA(&hadc1, adc_value, 3);
    vbat_list[adc_count] = adc_value[0];
    cpu_temper_list[adc_count] = adc_value[1];
    verfint_list[adc_count] = adc_value[2];
    adc_count++;
    if (adc_count >= 101) {
        adc_count = 0;
        BubbleSort(vbat_list, 101);
        BubbleSort(cpu_temper_list, 01);
        BubbleSort(verfint_list, 101);
        //battery powerS
        v_bat = 240 * vbat_list[50] / verfint_list[50]; //use the base v is better
        battery_power =(int16_t)((((5.16565079e-05 * v_bat - 8.01832126e-02) * v_bat + 4.66123209e+01) * v_bat - 1.20252730e+04) * v_bat + 1.16153974e+06);
        if (battery_power > 100) {
            battery_power = 100;
        }
        if (battery_power < 0) {
            YTW_System_Close();
        }
        //cpu temperature
        v_cpuT = (float)(cpu_temper_list[50] * 3.3 / 4096);
        cpu_temperature = (uint16_t)((v_cpuT - 0.76) / 0.0025 + 25);
        /*user show code*/
        sprintf(show_b, "%d", battery_power);
        sprintf(show_t, "%d", cpu_temperature);
        lv_label_set_text(ui_dianliang1, show_b);
        lv_label_set_text(ui_dianliang2, show_b);
    }
}