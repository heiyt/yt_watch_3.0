//
// Created by heiyt_R9000P on 2024/3/12.
//

#include "change_things.h"

char show_shiShi[1], show_shiGe[1], show_fenShi[1], show_fenGe[1], show_miaoShi[1], show_miaoGe[1];
char show_year_mon_day[10];
char show_control_panel[8];

volatile int8_t week_s;
volatile int16_t year_s;
volatile int8_t month_s;
volatile int8_t day_s;
volatile int8_t hour_s;
volatile int8_t min_s;
volatile int8_t sec_s;
volatile int16_t miaoZhen;
volatile int16_t fenZhen;
volatile int16_t shiZhen;

void refresh_time_control_panel() {
    Time_Get();
    sprintf(&show_control_panel[0], "%d", m41t62_time.hour / 16);
    sprintf(&show_control_panel[1], "%d", m41t62_time.hour % 16);
    sprintf(&show_control_panel[3], "%d", m41t62_time.min / 16);
    sprintf(&show_control_panel[4], "%d", m41t62_time.min % 16);
    sprintf(&show_control_panel[6], "%d", m41t62_time.sec / 16);
    sprintf(&show_control_panel[7], "%d", m41t62_time.sec % 16);
    show_control_panel[2] = ':';
    show_control_panel[5] = ':';
    lv_label_set_text(ui_Label41, show_control_panel);
}

//需要检查数据是否改变，这样刷新才更快
void refresh_time() {
    Time_Get();
    if (sec_s != m41t62_time.sec) {
        sec_s = m41t62_time.sec;
        sprintf(show_miaoShi, "%d", m41t62_time.sec / 16);
        sprintf(show_miaoGe, "%d", m41t62_time.sec % 16);
        lv_label_set_text(ui_miaoShi, show_miaoShi);
        lv_label_set_text(ui_miaoGe, show_miaoGe);
        if (min_s != m41t62_time.min) {
            min_s = m41t62_time.min;
            sprintf(show_fenShi, "%d", m41t62_time.min / 16);
            sprintf(show_fenGe, "%d", m41t62_time.min % 16);
            lv_label_set_text(ui_fenShi, show_fenShi);
            lv_label_set_text(ui_fenGe, show_fenGe);
            if (hour_s != m41t62_time.hour) {
                hour_s = m41t62_time.hour;
                sprintf(show_shiShi, "%d", m41t62_time.hour / 16);
                sprintf(show_shiGe, "%d", m41t62_time.hour % 16);
                lv_label_set_text(ui_shiShi, show_shiShi);
                lv_label_set_text(ui_shiGe, show_shiGe);
                if (day_s != m41t62_time.day) {
                    day_s = m41t62_time.day;
                    sprintf(&show_year_mon_day[8], "%d", m41t62_time.day / 16);
                    sprintf(&show_year_mon_day[9], "%d", m41t62_time.day % 16);
                    if (month_s != m41t62_time.mon) {
                        month_s = m41t62_time.mon;
                        sprintf(&show_year_mon_day[5], "%d", m41t62_time.mon / 16);
                        sprintf(&show_year_mon_day[6], "%d", m41t62_time.mon % 16);
                        if (year_s != m41t62_time.year) {
                            year_s = m41t62_time.year;
                            sprintf(&show_year_mon_day[0], "%d", 2);
                            sprintf(&show_year_mon_day[1], "%d", 0);
                            sprintf(&show_year_mon_day[2], "%d", m41t62_time.year / 16 % 16);
                            sprintf(&show_year_mon_day[3], "%d", m41t62_time.year % 16);
                        }
                    }
                    if (week_s != m41t62_time.week) {
                        week_s = m41t62_time.week;
                        switch (m41t62_time.week) {
                            case 0x01: lv_label_set_text(ui_Label5, "SUN"); break;
                            case 0x02: lv_label_set_text(ui_Label5, "MON"); break;
                            case 0x03: lv_label_set_text(ui_Label5, "TUE"); break;
                            case 0x04: lv_label_set_text(ui_Label5, "WED"); break;
                            case 0x05: lv_label_set_text(ui_Label5, "THU"); break;
                            case 0x06: lv_label_set_text(ui_Label5, "FRI"); break;
                            case 0x07: lv_label_set_text(ui_Label5, "SAT"); break;
                        }
                    }
                    show_year_mon_day[4] = '/';
                    show_year_mon_day[7] = '/';
                    lv_label_set_text(ui_Label4, show_year_mon_day);
                }
            }
        }
    }
}

void refresh_time_2() {
    Time_Get();
    if (sec_s != m41t62_time.sec) {
        sec_s = m41t62_time.sec;
        miaoZhen = (int16_t) ((m41t62_time.sec / 16 * 10 + m41t62_time.sec % 16) * 60);
        lv_img_set_angle(ui_miaoZhen, miaoZhen);
        if (min_s != m41t62_time.min) {
            min_s = m41t62_time.min;
            fenZhen = (int16_t) ((m41t62_time.min / 16 * 10 + m41t62_time.min % 16) * 60);
            lv_img_set_angle(ui_fenZhen, fenZhen);
            if (hour_s != m41t62_time.hour) {
                hour_s = m41t62_time.hour;
                shiZhen = (int16_t) ((m41t62_time.hour / 16 * 10 + m41t62_time.hour % 16) * 150 +
                                     ((m41t62_time.min / 16 * 10 + m41t62_time.min % 16) / 4) * 10);
                lv_img_set_angle(ui_shiZhen, shiZhen);
                if (day_s != m41t62_time.day) {
                    day_s = m41t62_time.day;
                    sprintf(&show_year_mon_day[8], "%d", m41t62_time.day / 16);
                    sprintf(&show_year_mon_day[9], "%d", m41t62_time.day % 16);
                    if (month_s != m41t62_time.mon) {
                        month_s = m41t62_time.mon;
                        sprintf(&show_year_mon_day[5], "%d", m41t62_time.mon / 16);
                        sprintf(&show_year_mon_day[6], "%d", m41t62_time.mon % 16);
                        if (year_s != m41t62_time.year) {
                            year_s = m41t62_time.year;
                            sprintf(&show_year_mon_day[0], "%d", 2);
                            sprintf(&show_year_mon_day[1], "%d", 0);
                            sprintf(&show_year_mon_day[2], "%d", m41t62_time.year / 16 % 16);
                            sprintf(&show_year_mon_day[3], "%d", m41t62_time.year % 16);
                        }
                    }
                    if (week_s != m41t62_time.week) {
                        week_s = m41t62_time.week;
                        switch (m41t62_time.week) {
                            case 0x01: lv_label_set_text(ui_Label27, "SUN"); break;
                            case 0x02: lv_label_set_text(ui_Label27, "MON"); break;
                            case 0x03: lv_label_set_text(ui_Label27, "TUE"); break;
                            case 0x04: lv_label_set_text(ui_Label27, "WED"); break;
                            case 0x05: lv_label_set_text(ui_Label27, "THU"); break;
                            case 0x06: lv_label_set_text(ui_Label27, "FRI"); break;
                            case 0x07: lv_label_set_text(ui_Label27, "SAT"); break;
                        }
                    }
                    show_year_mon_day[4] = '/';
                    show_year_mon_day[7] = '/';
                    lv_label_set_text(ui_Label18, show_year_mon_day);
                }
            }
        }
    }
}

//蓝牙接收时间完成后自动刷新
void refresh_time_BLE() {
    Time_Get();
    sprintf(show_miaoShi, "%d", m41t62_time.sec / 16);
    sprintf(show_miaoGe, "%d", m41t62_time.sec % 16);
    lv_label_set_text(ui_miaoShi, show_miaoShi);
    lv_label_set_text(ui_miaoGe, show_miaoGe);
    sprintf(show_fenShi, "%d", m41t62_time.min / 16);
    sprintf(show_fenGe, "%d", m41t62_time.min % 16);
    lv_label_set_text(ui_fenShi, show_fenShi);
    lv_label_set_text(ui_fenGe, show_fenGe);
    sprintf(show_shiShi, "%d", m41t62_time.hour / 16);
    sprintf(show_shiGe, "%d", m41t62_time.hour % 16);
    lv_label_set_text(ui_shiShi, show_shiShi);
    lv_label_set_text(ui_shiGe, show_shiGe);
    sprintf(&show_year_mon_day[0], "%d", 2);
    sprintf(&show_year_mon_day[1], "%d", 0);
    sprintf(&show_year_mon_day[2], "%d", m41t62_time.year / 16 % 16);
    sprintf(&show_year_mon_day[3], "%d", m41t62_time.year % 16);
    sprintf(&show_year_mon_day[5], "%d", m41t62_time.mon / 16);
    sprintf(&show_year_mon_day[6], "%d", m41t62_time.mon % 16);
    sprintf(&show_year_mon_day[8], "%d", m41t62_time.day / 16);
    sprintf(&show_year_mon_day[9], "%d", m41t62_time.day % 16);
    show_year_mon_day[4] = '/';
    show_year_mon_day[7] = '/';
    lv_label_set_text(ui_Label4, show_year_mon_day);
    switch (m41t62_time.week) {
        case 0x01: lv_label_set_text(ui_Label5, "SUN"); break;
        case 0x02: lv_label_set_text(ui_Label5, "MON"); break;
        case 0x03: lv_label_set_text(ui_Label5, "TUE"); break;
        case 0x04: lv_label_set_text(ui_Label5, "WED"); break;
        case 0x05: lv_label_set_text(ui_Label5, "THU"); break;
        case 0x06: lv_label_set_text(ui_Label5, "FRI"); break;
        case 0x07: lv_label_set_text(ui_Label5, "SAT"); break;
    }
}

void refresh_time_BLE_2() {
    miaoZhen = (int16_t) ((m41t62_time.sec / 16 * 10 + m41t62_time.sec % 16) * 60);
    lv_img_set_angle(ui_miaoZhen, miaoZhen);
    fenZhen = (int16_t) ((m41t62_time.min / 16 * 10 + m41t62_time.min % 16) * 60);
    lv_img_set_angle(ui_fenZhen, fenZhen);
    shiZhen = (int16_t) ((m41t62_time.hour / 16 * 10 + m41t62_time.hour % 16) * 150 +
                         ((m41t62_time.min / 16 * 10 + m41t62_time.min % 16) / 4) * 10);
    lv_img_set_angle(ui_shiZhen, shiZhen);
    sprintf(&show_year_mon_day[0], "%d", 2);
    sprintf(&show_year_mon_day[1], "%d", 0);
    sprintf(&show_year_mon_day[2], "%d", m41t62_time.year / 16 % 16);
    sprintf(&show_year_mon_day[3], "%d", m41t62_time.year % 16);
    sprintf(&show_year_mon_day[5], "%d", m41t62_time.mon / 16);
    sprintf(&show_year_mon_day[6], "%d", m41t62_time.mon % 16);
    sprintf(&show_year_mon_day[8], "%d", m41t62_time.day / 16);
    sprintf(&show_year_mon_day[9], "%d", m41t62_time.day % 16);
    show_year_mon_day[4] = '/';
    show_year_mon_day[7] = '/';
    lv_label_set_text(ui_Label18, show_year_mon_day);
    switch (m41t62_time.week) {
        case 0x01: lv_label_set_text(ui_Label27, "SUN"); break;
        case 0x02: lv_label_set_text(ui_Label27, "MON"); break;
        case 0x03: lv_label_set_text(ui_Label27, "TUE"); break;
        case 0x04: lv_label_set_text(ui_Label27, "WED"); break;
        case 0x05: lv_label_set_text(ui_Label27, "THU"); break;
        case 0x06: lv_label_set_text(ui_Label27, "FRI"); break;
        case 0x07: lv_label_set_text(ui_Label27, "SAT"); break;
    }
}