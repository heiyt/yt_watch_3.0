// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: ytw3_0

#include "../ui.h"

void ui_addRemainsPanel_screen_init(void)
{
    ui_addRemainsPanel = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_addRemainsPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_flex_flow(ui_addRemainsPanel, LV_FLEX_FLOW_COLUMN_WRAP);
    lv_obj_set_flex_align(ui_addRemainsPanel, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_AROUND);
    lv_obj_set_style_radius(ui_addRemainsPanel, 35, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Container8 = lv_obj_create(ui_addRemainsPanel);
    lv_obj_remove_style_all(ui_Container8);
    lv_obj_set_width(ui_Container8, 260);
    lv_obj_set_height(ui_Container8, 70);
    lv_obj_set_align(ui_Container8, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_Container8, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_Container8, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_AROUND);
    lv_obj_clear_flag(ui_Container8, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_TextArea1 = lv_textarea_create(ui_Container8);
    lv_obj_set_width(ui_TextArea1, 180);
    lv_obj_set_height(ui_TextArea1, 70);
    lv_obj_set_align(ui_TextArea1, LV_ALIGN_CENTER);
    lv_textarea_set_placeholder_text(ui_TextArea1, "remain to do...");



    ui_Button11 = lv_btn_create(ui_Container8);
    lv_obj_set_width(ui_Button11, 50);
    lv_obj_set_height(ui_Button11, 50);
    lv_obj_set_x(ui_Button11, 99);
    lv_obj_set_y(ui_Button11, -80);
    lv_obj_set_align(ui_Button11, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_Button11, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_Button11, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_AROUND);
    lv_obj_clear_flag(ui_Button11, LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                      LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_scrollbar_mode(ui_Button11, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(ui_Button11, LV_DIR_TOP);
    lv_obj_set_style_radius(ui_Button11, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Button11, lv_color_hex(0x11BDDC), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Button11, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Button11, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Button11, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_Button11, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_Button11, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui_Button11, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui_Button11, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_Button11, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Button11, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label32 = lv_label_create(ui_Button11);
    lv_obj_set_width(ui_Label32, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label32, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label32, 206);
    lv_obj_set_y(ui_Label32, -47);
    lv_obj_set_align(ui_Label32, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label32, "");
    lv_obj_set_style_text_color(ui_Label32, lv_color_hex(0x8D9E87), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label32, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label32, &ui_font_gouzi48, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Keyboard1 = lv_keyboard_create(ui_addRemainsPanel);
    lv_obj_set_width(ui_Keyboard1, 270);
    lv_obj_set_height(ui_Keyboard1, 120);
    lv_obj_set_align(ui_Keyboard1, LV_ALIGN_CENTER);

    lv_obj_add_event_cb(ui_Button11, ui_event_Button11, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Keyboard1, ui_event_Button11, LV_EVENT_ALL, NULL);
    lv_keyboard_set_textarea(ui_Keyboard1, ui_TextArea1);
    lv_obj_add_event_cb(ui_addRemainsPanel, ui_event_addRemainsPanel, LV_EVENT_ALL, NULL);

}
