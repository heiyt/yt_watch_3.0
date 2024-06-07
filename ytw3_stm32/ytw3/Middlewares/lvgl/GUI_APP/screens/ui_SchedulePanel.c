//
// Created by heiyt_R9000P on 2024/4/8.
//

#include "../ui.h"

void ui_SchedulePanel_screen_init(void) {
    ui_SchedulePanel = lv_obj_create(NULL);
    lv_obj_set_flex_flow(ui_SchedulePanel, LV_FLEX_FLOW_COLUMN);
    lv_obj_add_event_cb(ui_SchedulePanel, scr_unloaded_delete_cb, LV_EVENT_SCREEN_UNLOADED, &ui_SchedulePanel);
    lv_obj_set_style_radius(ui_SchedulePanel, 35, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_SchedulePanel, ui_event_SchedulePanel, LV_EVENT_ALL, NULL);
}