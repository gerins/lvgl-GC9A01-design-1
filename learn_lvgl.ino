#include <TFT_eSPI.h>
#include <Ticker.h>
#include <lvgl.h>

// LVGL Logging
#if LV_USE_LOG != 0
void my_print(lv_log_level_t level, const char *buf) {
    LV_UNUSED(level);
    Serial.println(buf);
    Serial.flush();
}
#endif

// Screen specification
#define TFT_HOR_RES 240
#define TFT_VER_RES 240
#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

// My variable
Ticker lvglTicker;
lv_obj_t *rpmLabel;
const char *tempLogo = "\xEF\x8B\x88";
const char *lightingBoltLogo = "\xEF\x83\xA7";
const char *sunLogo = "\xEF\x86\x85";
const char *moonLogo = "\xEF\x86\x86";
const char *cloudMoonLogo = "\xEF\x9B\x83";
const char *mountainLogo = "\xEF\x9B\xBC";

// Put custom font here C:\Users\gerin\Documents\Arduino\libraries\lvgl\src\font
// And declare here
LV_FONT_DECLARE(digital_font_50)
LV_FONT_DECLARE(custom_symbol_16)

void setup() {
#if LV_USE_LOG != 0
    lv_log_register_print_cb(my_print);
    // Serial.begin(115200);
#endif

    // Init
    lv_init();
    lv_display_t *disp = lv_tft_espi_create(TFT_HOR_RES, TFT_VER_RES, draw_buf, sizeof(draw_buf));
    lvglTicker.attach_ms(1, []() { lv_tick_inc(1); });                                      // Set up a Ticker interrupt to call lv_tick_inc() every millisecond
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0xFF000000), LV_PART_MAIN);  // Set background color to black

    //================================== Start Code ==================================

    //================================== Volt Arc ==================================
    lv_obj_t *voltArc = CreateBaseArc(0xFFD89843, 230, 0, 16, 190, 260);
    int voltValue = 13;
    lv_arc_set_value(voltArc, voltValue);
    // Knob configuration
    lv_obj_remove_style(voltArc, NULL, LV_PART_KNOB);  // Remove knob
    // Symbol volt
    lv_obj_t *voltSymbol = lv_label_create(lv_scr_act());                  //
    lv_obj_align(voltSymbol, LV_ALIGN_CENTER, -108, 0);                    // Center position
    lv_obj_set_style_text_font(voltSymbol, &custom_symbol_16, 0);          // Change font style
    lv_obj_set_style_text_color(voltSymbol, lv_color_hex(0xFFD89843), 0);  // Change text color
    lv_label_set_text(voltSymbol, lightingBoltLogo);                       // Set logo symbol EF 83 A7
    // Volt Value
    lv_obj_t *labelVolt = lv_label_create(lv_scr_act());
    lv_label_set_text_fmt(labelVolt, "%s", "12");
    lv_obj_set_style_text_color(labelVolt, lv_color_hex(0xFFFFFFFF), 0);  // Change text color
    lv_arc_rotate_obj_to_angle(voltArc, labelVolt, -17);

    //================================== Temperature Arc ==================================
    lv_obj_t *tempArc = CreateBaseArc(0xFFD72749, 230, 0, 100, 280, 350);  // Indicator color
    // lv_obj_set_style_arc_color(tempArc, lv_color_hex(0xFFD72749), LV_PART_MAIN);  // Bucket color
    int tempValue = 50;
    lv_arc_set_value(tempArc, tempValue);
    // Knob configuration
    lv_obj_remove_style(tempArc, NULL, LV_PART_KNOB);                            // Remove knob
    lv_obj_set_style_bg_color(tempArc, lv_color_hex(0xFFFFFFFF), LV_PART_KNOB);  // Knob color
    lv_obj_set_style_pad_all(tempArc, 1, LV_PART_KNOB);                          // Set 5px padding around knob
    // Symbol
    lv_obj_t *tempSymbol = lv_label_create(lv_scr_act());                  //
    lv_obj_align(tempSymbol, LV_ALIGN_CENTER, 0, -108);                    // Center position
    lv_obj_set_style_text_font(tempSymbol, &custom_symbol_16, 0);          // Change font style
    lv_obj_set_style_text_color(tempSymbol, lv_color_hex(0xFFD72749), 0);  // Change text color
    lv_label_set_text(tempSymbol, tempLogo);                               // Set logo symbol
    // Temp Value
    lv_obj_t *labelTemp = lv_label_create(lv_scr_act());
    lv_label_set_text_fmt(labelTemp, "%d", 50);
    lv_obj_set_style_text_color(labelTemp, lv_color_hex(0xFFFFFFFF), 0);  // Change text color
    lv_arc_rotate_obj_to_angle(tempArc, labelTemp, -17);

    // Arc 3
    lv_obj_t *arc4 = CreateBaseArc(0xFF0AC94C, 230, 0, 100, 10, 80);
    lv_arc_set_value(arc4, 100);
    lv_obj_remove_style(arc4, NULL, LV_PART_KNOB);                              // Remove knob
    lv_obj_t *cloudMoonSymbol = lv_label_create(lv_scr_act());                  //
    lv_obj_align(cloudMoonSymbol, LV_ALIGN_CENTER, 108, 0);                     // Center position
    lv_obj_set_style_text_font(cloudMoonSymbol, &custom_symbol_16, 0);          // Change font style
    lv_obj_set_style_text_color(cloudMoonSymbol, lv_color_hex(0xFF0AC94C), 0);  // Change text color
    lv_label_set_text(cloudMoonSymbol, cloudMoonLogo);                          // Set logo symbol EF 83 A7

    // Arc 4
    lv_obj_t *arc3 = CreateBaseArc(0xFF18BB8D, 230, 0, 100, 100, 170);
    lv_arc_set_value(arc3, 100);
    lv_obj_remove_style(arc3, NULL, LV_PART_KNOB);                             // Remove knob
    lv_obj_t *mountainSymbol = lv_label_create(lv_scr_act());                  //
    lv_obj_align(mountainSymbol, LV_ALIGN_CENTER, 0, 106);                     // Center position
    lv_obj_set_style_text_font(mountainSymbol, &custom_symbol_16, 0);          // Change font style
    lv_obj_set_style_text_color(mountainSymbol, lv_color_hex(0xFF18BB8D), 0);  // Change text color
    lv_label_set_text(mountainSymbol, mountainLogo);                           // Set logo symbol EF 83 A7

    // RPM Label middle
    lv_obj_t *rpmLabel = lv_label_create(lv_scr_act());
    lv_obj_align(rpmLabel, LV_ALIGN_CENTER, 0, 0);                       // Center position
    lv_obj_set_style_text_font(rpmLabel, &digital_font_50, 0);           // Change font style
    lv_obj_set_style_text_color(rpmLabel, lv_color_hex(0xFFFFFFFF), 0);  // Change text color
    lv_label_set_text(rpmLabel, "5288");                                 // Set text

    // Clock
    lv_obj_t *clockLabel = lv_label_create(lv_scr_act());
    lv_obj_align(clockLabel, LV_ALIGN_CENTER, 0, -40);                     // Center position
    lv_obj_set_style_text_font(clockLabel, &lv_font_montserrat_14, 0);     // Change font style
    lv_obj_set_style_text_color(clockLabel, lv_color_hex(0xFFFFFFFF), 0);  // Change text color
    lv_label_set_text(clockLabel, "19:20");                                // Set text

    //================================== End Code ====================================

    Serial.println("Setup done");
}

void loop() {
    lv_task_handler();
    char buffer[5];  // 4 digits + null terminator
    std::snprintf(buffer, sizeof(buffer), "%04d", (millis() / 1000) / 60);
    lv_label_set_text(rpmLabel, buffer);  // Set text
}

lv_obj_t *CreateBaseArc(uint32_t indicatorColor, int size, int minRange, int maxrange, int minAngel, int maxAngel) {
    lv_obj_t *newArc = lv_arc_create(lv_scr_act());

    // Spec
    lv_arc_set_range(newArc, minRange, maxrange);      // Value range
    lv_arc_set_bg_angles(newArc, minAngel, maxAngel);  // Arc length

    // Style
    lv_obj_set_style_arc_width(newArc, 7, LV_PART_MAIN);
    lv_obj_set_style_arc_width(newArc, 7, LV_PART_INDICATOR);
    lv_obj_center(newArc);                // Middle position
    lv_obj_set_size(newArc, size, size);  // Set width and height
    lv_obj_clear_flag(newArc, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_arc_color(newArc, lv_color_hex(0xFF212421), LV_PART_MAIN);  // Grey
    lv_obj_set_style_arc_color(newArc, lv_color_hex(indicatorColor), LV_PART_INDICATOR);

    return newArc;
}
