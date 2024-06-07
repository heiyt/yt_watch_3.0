// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: ytw3_0

#include "../ui.h"

void ui_SystemAboutPanel_screen_init(void)
{
    ui_SystemAboutPanel = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_SystemAboutPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_add_event_cb(ui_SystemAboutPanel, scr_unloaded_delete_cb, LV_EVENT_SCREEN_UNLOADED, &ui_SystemAboutPanel);
    lv_obj_set_style_radius(ui_SystemAboutPanel, 35, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label12 = lv_label_create(ui_SystemAboutPanel);
    lv_obj_set_width(ui_Label12, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label12, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label12, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label12, "Operation System : FreeRTOS\nUI : lvgl\ndesigned by heiyt\nSystem Version: 3.0.1 ");

    lv_obj_add_event_cb(ui_SystemAboutPanel, ui_event_SystemAboutPanel, LV_EVENT_ALL, NULL);

}
