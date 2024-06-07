//
// Created by heiyt_R9000P on 2024/4/6.
//

#include "../ui.h"

void ui_calendarPanel_screen_init(void) {
    //get now time
    ui_calendarPanel = lv_obj_create(NULL);
    lv_obj_set_flex_flow(ui_calendarPanel, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_calendarPanel, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_AROUND);

    ui_calendar = lv_calendar_create(ui_calendarPanel);
    lv_obj_clear_flag(ui_calendar, LV_OBJ_FLAG_SCROLLABLE);
    ui_calendar_header = lv_calendar_header_arrow_create(ui_calendar);
    lv_obj_set_size(ui_calendar_header, 280, 50);

    lv_obj_set_size(ui_calendar, 280, 240);
    lv_obj_set_style_radius(ui_calendar, 35, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_calendar_set_showed_date(ui_calendar, 2024, 4);
    lv_calendar_set_today_date(ui_calendar, 2024, 4, 15);

    lv_obj_add_event_cb(ui_calendarPanel, ui_event_calendarPanel, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_calendar, ui_event_calendar, LV_EVENT_ALL, NULL);
}
