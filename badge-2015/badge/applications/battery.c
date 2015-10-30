#include "battery.h"

void battery_application() {
    draw_background();



    gfx_draw_string_aligned("Power Info", gfx_get_width() / 2, 2, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);

    uint8_t battery = max1704x_bat();
    char batlvl[5];
    if (battery > 100) {
        battery = 100;
    }
    //battery = 19;
    uint16_t x =  75;
    uint16_t y = 40;

    gfx_draw_rect(x, y,  164, 54, GFX_COLOR_WHITE);
    gfx_draw_filled_rect(x+164, y+15, 3, 20, GFX_COLOR_WHITE);

    if (battery < 20) {
        gfx_draw_filled_rect(x+2, y+2, battery/6 * 10, 50, GFX_COLOR_RED);
    } else {
        gfx_draw_filled_rect(x+2, y+2, battery/6 * 10, 50, GFX_COLOR_GREEN);
    }


    snprintf(batlvl, sizeof(batlvl), "%d%%", battery);
    if (battery > 20) {
        gfx_draw_string_aligned(batlvl, gfx_get_width() /2, 50, &large_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
    } else {
        gfx_draw_string_aligned(batlvl, gfx_get_width() /2, 50, &large_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
    }

    char atime[32];
    snprintf(atime, sizeof(atime), "Seconds Awake:    %lu", get_time_awake());
    gfx_draw_string_aligned(atime, 70, 100, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);

    char stime[32];
    snprintf(stime, sizeof(stime), "Seconds Sleeping: %lu", get_time_sleep());
    gfx_draw_string_aligned(stime, 70, 120, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);

    gfx_draw_filled_circle(gfx_get_width() /2,  80+80+10+10, 25, GFX_COLOR_WHITE, GFX_WHOLE);
    gfx_draw_string_aligned(SYMFONT_MOON, gfx_get_width() /2, 152+10, &symbol_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR(200, 101, 18), TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
    gfx_draw_string_aligned("Enter Sleep Mode", gfx_get_width() / 2, 152+15+30+15, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);


	struct keyboard_event input;
    while(mma8451_orientation() != 6) {
        esp8266_check_buffer();
        if(mma8451_clear_interrupt() && is_low_power()) {
            exit_low_power();
        }

        keyboard_get_key_state(&input);
        if (input.type == KEYBOARD_RELEASE) {
            if (input.keycode == KEYBOARD_B) {
                break;
            } else if (input.keycode == KEYBOARD_A) {
                esp8266_enter_standby();
                enter_low_power();
                break;
            }
        }
    }
}