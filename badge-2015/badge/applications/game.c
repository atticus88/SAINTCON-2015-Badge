#include "game.h"

bool game_exit = false;
void draw_game_alert() {
    gfx_draw_filled_rect(20, 45, 280, 185, GFX_COLOR(5, 5, 5));
    gfx_draw_filled_rect(15, 45, 280, 180, GFX_COLOR(20, 20, 20));

    //gfx_draw_filled_circle(25, 75, 5, GFX_COLOR_RED, GFX_WHOLE);
    //gfx_draw_string_aligned("B", 26, 66, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);

    
    gfx_draw_string_aligned("Game Controller Mode", gfx_get_width()/2, gfx_get_height()/2-70, &sysfont, GFX_COLOR(20, 20, 20), GFX_COLOR(200, 101, 18), TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
    gfx_draw_string_aligned("To exit game controller mode\nyou will have to remove the\nbattery and/or USB.\n\nDo you you want to continue?", gfx_get_width()/2, gfx_get_height()/2-50, &small_sysfont, GFX_COLOR(20, 20, 20), GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
    
    gfx_draw_filled_rect(43, 180, 80, 39, GFX_COLOR(5, 5, 5));
    gfx_draw_filled_rect(40, 180, 80, 36, GFX_COLOR(200, 101, 18));
     gfx_draw_string_aligned("B: NO", 80, 185, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);

    gfx_draw_filled_rect(193, 180, 80, 39, GFX_COLOR(5, 5, 5));
    gfx_draw_filled_rect(190, 180, 80, 36, GFX_COLOR(200, 101, 18));
    gfx_draw_string_aligned("A: YES", 230, 185, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);

    struct keyboard_event input;
    while (true) {
        esp8266_check_buffer();
        if(mma8451_clear_interrupt() && is_low_power()) {
            exit_low_power();
        }

        keyboard_get_key_state(&input);
        if (input.type == KEYBOARD_RELEASE) {
            if (input.keycode == KEYBOARD_B) {
                game_exit = true;
                break;
            } else if (input.keycode == KEYBOARD_A) {
                game_exit = false;
                break;
            }
        }
    }
}

void game_application() {
    draw_background();

    draw_game_alert();
    if (!game_exit) {
        gfx_draw_filled_rect(5, 26, 310, 220, GFX_COLOR(8, 8, 8));

        gfx_draw_string_aligned("Game Controller Mode", gfx_get_width() / 2, 2, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);

        gfx_draw_string_aligned("Your badge will now show\nup as a HID Keyboard.", gfx_get_width() / 2, 30, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
        gfx_draw_string_aligned("Remove the battery and/or USB\nto exit this mode.", gfx_get_width() / 2, 80, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR(200, 101, 18), TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);

        gfx_draw_string_aligned("A => A\nB => B", (gfx_get_width() / 2)/2, 140, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
        gfx_draw_string_aligned("Select => Spance\nStart => Enter", gfx_get_width() / 2+ (gfx_get_width() / 2)/2, 140, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);

        gfx_draw_string_aligned("Arrow keys are mapped\nto arrow keys.", gfx_get_width() / 2, 190, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);


        udc_start();
    	struct keyboard_event input;
        
        while(true) {
            esp8266_check_buffer();
            keyboard_get_key_state(&input);
            if (input.type == KEYBOARD_RELEASE) {
                // if (input.keycode == KEYBOARD_SELECT) {
                //     udc_stop();
                //     break;
                // }
            }
            if(mma8451_clear_interrupt() && is_low_power()) {
                exit_low_power();
            }
        }
    }
}