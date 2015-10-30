#include "credits.h"

void credits_application() {
    gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(), GFX_COLOR_BLACK);
    gfx_draw_string_aligned("Credits", gfx_get_width() / 2, 2, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
    //irqflags_t flags = cpu_irq_save();

    uint32_t song [] = {1046, 70, 987, 70, 783, 70, 698, 70, 783, 70, 698, 70, 622, 70, 587, 70, 622, 70, 587, 70, 523, 70, 466, 140, 349, 70, 392, 70, 466, 70, 523, 500};
    for (uint16_t n = 0; n < 30; n=n+2) {
        start_buzz(song[n]);
        delay_ms(song[n+1]);
    }
    stop_buzz();

    //cpu_irq_restore(flags);

    gfx_draw_string_aligned("Badge Team:", gfx_get_width() / 2, 30, &medium_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR(200, 101, 18), TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
    gfx_draw_string_aligned("Luke Jenkins\nJonathan Karras\nMike Spicer", (gfx_get_width() / 2)/2, 55, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
    gfx_draw_string_aligned("Klint Holmes\nDustin Woodard\nSeth Johnson", gfx_get_width() / 2+ (gfx_get_width() / 2)/2, 55, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);


    gfx_draw_string_aligned("Assembled by EMS Solutions", gfx_get_width() / 2, 130, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR(200, 101, 18), TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
    gfx_draw_string_aligned("Ogden, Utah", gfx_get_width() / 2, 147, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR(200, 101, 18), TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
    //gfx_draw_string_aligned("in Utah", gfx_get_width() / 2, 120, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR(200, 101, 18), TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
        //gfx_draw_string_aligned("Jonathan Karras", gfx_get_width() / 2, 80, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
    //gfx_draw_string_aligned("Dustin Woodard", gfx_get_width() / 2, 95, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);


    gfx_draw_string_aligned("Thanks:", gfx_get_width() / 2, 170, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR(100, 100, 100), TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
    gfx_draw_string_aligned("UtahSAINT Orginization, SparkFun,\nAdafruit, NodeMCU, Fontello" , gfx_get_width() / 2, 190, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR(100, 100, 100), TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
    gfx_draw_string_aligned("PASSWORD: GSTRV8GCN4NJS5EL" , gfx_get_width() / 2, 225, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR(100, 100, 100), TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);





	struct keyboard_event input;
    while(mma8451_orientation() != 6) {
        esp8266_check_buffer();

        keyboard_get_key_state(&input);
        if (input.type == KEYBOARD_RELEASE) {
            if (input.keycode == KEYBOARD_B) {
                break;
            }
        }
        if(mma8451_clear_interrupt() && is_low_power()) {
            exit_low_power();
        }
    }

}