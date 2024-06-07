// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: ytw3_0

#include "../ui.h"

void ui_lightPanel_screen_init(void)
{
    ui_lightPanel = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_lightPanel, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM);     /// Flags
    lv_obj_add_event_cb(ui_lightPanel, scr_unloaded_delete_cb, LV_EVENT_SCREEN_UNLOADED, &ui_lightPanel);
    lv_obj_set_style_radius(ui_lightPanel, 35, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel1 = lv_obj_create(ui_lightPanel);
    lv_obj_set_width(ui_Panel1, 50);
    lv_obj_set_height(ui_Panel1, 35);
    lv_obj_set_x(ui_Panel1, 95);
    lv_obj_set_y(ui_Panel1, -80);
    lv_obj_set_align(ui_Panel1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label10 = lv_label_create(ui_lightPanel);
    lv_obj_set_width(ui_Label10, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label10, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label10, 95);
    lv_obj_set_y(ui_Label10, -80);
    lv_obj_set_align(ui_Label10, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label10, "90");
    lv_obj_set_style_text_font(ui_Label10, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label16 = lv_label_create(ui_lightPanel);
    lv_obj_set_width(ui_Label16, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label16, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label16, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label16, "");
    lv_obj_set_style_text_font(ui_Label16, &ui_font_shoudian48, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_lightPanel, ui_event_lightPanel, LV_EVENT_ALL, NULL);

}
