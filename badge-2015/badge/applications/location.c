#include "location.h"

void draw_birds_eye() {
    uint8_t s = 24;
    uint16_t mindex = 0; 
    gfx_color_t red = GFX_COLOR(183,52,1);
    gfx_color_t path = GFX_COLOR(204,197,161);
    gfx_color_t road = GFX_COLOR(178,178,178);
    gfx_color_t dark = GFX_COLOR(48,48,48);
    gfx_color_t orange = GFX_COLOR(212,109,7);
    gfx_color_t stair = GFX_COLOR(109,109,109);
    gfx_color_t blue = GFX_COLOR(54,50,215);
    gfx_color_t purple = GFX_COLOR(151,56,255);


    gfx_color_t map[] = { 
        dark,path,path,path,path,path,path,path,path,path,dark,red,red,red,
        red,path,red,path,orange,orange,orange,orange,orange,path,dark,red,red,red,
        path,path,red,red,orange,orange,orange,orange,orange,path,path,red,red,red,
        dark,path,red,path,stair,orange,orange,orange,orange,path,dark,dark,dark,dark,
        dark,path,red,path,stair,dark,path,dark,dark,path,red,red,stair,stair,
        dark,path,path,path,stair,dark,path,path,path,path,path,path,stair,stair,
        dark,dark,dark,stair,stair,stair,path,dark,orange,orange,path,stair,path,path,
        dark,dark,dark,stair,dark,stair,path,orange,orange,orange,path,stair,red,red,
        dark,stair,stair,stair,stair,stair,path,orange,orange,orange,path,stair,red,red,
        stair,dark,dark,dark,path,path,path,dark,orange,orange,path,stair,red,red,
    };
    for (uint16_t y = 0; y < gfx_get_height(); y=y+s) {
        for (uint16_t x = 0; x < gfx_get_width(); x=x+s) {
            gfx_draw_filled_rect(x, y, s, s, map[mindex]);
            mindex++;
        }
    }

    gfx_draw_string_aligned("N| Outside", 0+2, (9*s)+3, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    gfx_draw_pixel(12, 224, GFX_COLOR_WHITE);
    gfx_draw_pixel(12, 225, GFX_COLOR_WHITE);
    gfx_draw_pixel(11, 225, GFX_COLOR_WHITE);

    gfx_draw_string_aligned("MA", 3, s+2, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    gfx_draw_string_aligned("SC", 2*s+4, 2*s+2, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    gfx_draw_string_aligned("LP", 10*s+16, 4*s+2, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    gfx_draw_string_aligned("LIB", 11*s+18, s+2, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    gfx_draw_string_aligned("Student\nUnion", 5*s+18, 1*s+6, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    gfx_draw_string_aligned("Browning\nAusted", 7*s+3, 7*s+2, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    gfx_draw_string_aligned("G\ny\nm", 12*s+10, 7*s+6, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
}

// void draw_uinon_lvl4() {
//     uint8_t s = 24;
//     uint16_t mindex = 0; 
//     gfx_color_t red = GFX_COLOR(183,52,1);
//     gfx_color_t path = GFX_COLOR(178,178,178);
//     gfx_color_t dark = GFX_COLOR(48,48,48);
//     gfx_color_t orange = GFX_COLOR(212,109,7);
//     gfx_color_t stair = GFX_COLOR(109,109,109);
//     gfx_color_t blue = GFX_COLOR(54,50,215);
//     gfx_color_t purple = GFX_COLOR(151,56,255);


//     gfx_color_t map[] = { 
//         dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,
//         dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,
//         dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,
//         dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,
//         dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,
//         dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,
//         dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,
//         dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,
//         dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,
//         dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,dark,
//     };
//     for (uint16_t y = 0; y < gfx_get_height(); y=y+s) {
//         for (uint16_t x = 0; x < gfx_get_width(); x=x+s) {
//             gfx_draw_filled_rect(x, y, s, s, map[mindex]);
//             mindex++;
//         }
//     }
// }

void draw_union_lvl3() {
    uint8_t s = 24;
    uint16_t mindex = 0; 
    gfx_color_t red = GFX_COLOR(183,52,1);
    gfx_color_t path = GFX_COLOR(178,178,178);
    gfx_color_t dark = GFX_COLOR(48,48,48);
    gfx_color_t orange = GFX_COLOR(212,109,7);
    gfx_color_t stair = GFX_COLOR(109,109,109);
    gfx_color_t blue = GFX_COLOR(54,50,215);
    gfx_color_t purple = GFX_COLOR(151,56,255);


    gfx_color_t map[] = { 
        red,path,path,path,path,path,path,path,path,path,path,path,dark,dark,
        dark,orange,orange,path,dark,orange,dark,dark,dark,dark,stair,path,dark,dark,
        orange,orange,orange,path,dark,dark,dark,dark,dark,dark,stair,path,dark,dark,
        orange,orange,orange,path,path,path,path,path,path,path,path,path,path,path,
        orange,orange,orange,path,path,path,path,path,path,path,dark,dark,dark,stair,
        orange,orange,orange,path,path,path,path,path,path,path,dark,dark,stair,stair,
        orange,orange,orange,path,red,stair,dark,dark,dark,path,dark,dark,dark,dark,
        orange,orange,orange,path,stair,stair,dark,dark,dark,path,orange,dark,dark,dark,
        dark,dark,dark,path,dark,dark,dark,dark,dark,path,dark,dark,dark,dark,
        dark,dark,dark,orange,orange,dark,dark,dark,dark,orange,orange,dark,dark,dark,dark
    };
    for (uint16_t y = 0; y < gfx_get_height(); y=y+s) {
        for (uint16_t x = 0; x < gfx_get_width(); x=x+s) {
            gfx_draw_filled_rect(x, y, s, s, map[mindex]);
            mindex++;
        }
    }
    gfx_draw_filled_rect(3*s, 0, s, s/2, blue);
    gfx_draw_filled_rect(12*s,4*s, s, s/2, blue);

    // gfx_draw_filled_circle((4*s)+12,  (3*s)+12, 6, dark, GFX_WHOLE);
    // gfx_draw_filled_circle((4*s)+12,  (5*s)+12, 6, dark, GFX_WHOLE);

    gfx_draw_horizontal_line(0, 2*s, 3*s, GFX_COLOR_BLACK);
    gfx_draw_horizontal_line(0, 4*s, 3*s, GFX_COLOR_BLACK);
    gfx_draw_horizontal_line(0, 6*s, 3*s, GFX_COLOR_BLACK);


    gfx_draw_string_aligned("RR", 3*s+4, -3, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    gfx_draw_string_aligned("RR", 12*s+4, (4*s)-3, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    gfx_draw_string_aligned("Mezzanine", 5*s, (4*s)+3, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    gfx_draw_string_aligned("N| 3rd", 0+2, (9*s)+3, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    gfx_draw_pixel(12, 224, GFX_COLOR_WHITE);
    gfx_draw_pixel(12, 225, GFX_COLOR_WHITE);
    gfx_draw_pixel(11, 225, GFX_COLOR_WHITE);

    gfx_draw_string_aligned("VAULT", s+4, 1*s-2, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    gfx_draw_string_aligned("312", s+10, 1*s+8, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);

    gfx_draw_string_aligned("HCV", 5*s+1, 1*s-2, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    gfx_draw_string_aligned("305", 5*s+1, 1*s+8, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);

    gfx_draw_string_aligned("BR1", 10*s+1, 7*s-2, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    gfx_draw_string_aligned("321", 10*s+1, 7*s+8, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);

    gfx_draw_string_aligned("LPV", 3*s+10, 9*s-2, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    gfx_draw_string_aligned("316", 3*s+10, 9*s+8, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);

    gfx_draw_string_aligned("CONOPS", 9*s+1, 9*s-2, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    gfx_draw_string_aligned("Senate", 9*s+1, 9*s+8, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);

    gfx_draw_string_aligned("Track 3", 4, (2*s)+4, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    gfx_draw_string_aligned("Track 2", 4, (4*s)+4, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    gfx_draw_string_aligned("Track 1", 4, (6*s)+4, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);

    gfx_draw_string_aligned("C", s+10, (2*s)+18, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    gfx_draw_string_aligned("B", s+10, (4*s)+18, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    gfx_draw_string_aligned("A", s+10, (6*s)+18, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);

}



void draw_union_lvl2() {
    uint8_t s = 24;
    uint16_t mindex = 0; 

    gfx_color_t red = GFX_COLOR(183,52,1);
    gfx_color_t path = GFX_COLOR(178,178,178);
    gfx_color_t dark = GFX_COLOR(48,48,48);
    gfx_color_t orange = GFX_COLOR(212,109,7);
    gfx_color_t stair = GFX_COLOR(109,109,109);
    gfx_color_t blue = GFX_COLOR(54,50,215);
    gfx_color_t purple = GFX_COLOR(151,56,255);

    gfx_color_t map[] = { 
        red,orange,orange,orange,dark,dark,dark,path,path,dark,dark,dark,dark,dark,
        dark,path,dark,dark,dark,dark,dark,path,path,stair,dark,dark,dark,dark,
        dark,path,dark,dark,dark,dark,dark,path,path,stair,dark,dark,dark,dark,
        dark,path,path,dark,dark,dark,dark,path,path,dark,dark,dark,dark,dark,
        dark,dark,path,path,path,path,path,path,path,orange,orange,dark,dark,stair,
        dark,dark,dark,path,path,path,path,path,path,path,path,path,stair,stair,
        dark,dark,dark,dark,red,stair,path,path,path,dark,dark,dark,dark,dark,
        dark,dark,dark,dark,stair,stair,path,path,path,dark,dark,dark,dark,dark,
        dark,dark,dark,dark,dark,dark,path,path,path,dark,dark,dark,dark,dark,
        dark,dark,dark,dark,dark,dark,path,path,path,dark,dark,dark,dark,dark,
    };

    for (uint16_t y = 0; y < gfx_get_height(); y=y+s) {
        for (uint16_t x = 0; x < gfx_get_width(); x=x+s) {
            gfx_draw_filled_rect(x, y, s, s, map[mindex]);
            mindex++;
        }
    }

    gfx_draw_string_aligned("N| 2nd", 0+2, (9*s)+3, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    gfx_draw_pixel(12, 224, GFX_COLOR_WHITE);
    gfx_draw_pixel(12, 225, GFX_COLOR_WHITE);
    gfx_draw_pixel(11, 225, GFX_COLOR_WHITE);

    gfx_draw_string_aligned("Track 4", s+4, -3, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    gfx_draw_string_aligned("WCT", s+12, 8, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);

    gfx_draw_string_aligned("HHV", 9*s+8, 4*s-3, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    gfx_draw_string_aligned("235", 9*s+8, 4*s+8, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);

    gfx_draw_string_aligned("Austed", 6*s+12, 9*s-3, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);

    gfx_draw_filled_triangle(6*s+25+ 5, 230, 6*s+25+ 15, 230, 6*s+25 + 10, 230+5, GFX_COLOR_WHITE);



}
bool first_location = true;;
int lvl = 0;
int current_lvl = 0;
int zone = 0;
void draw_current_location() {
    // parse the location
    uint16_t x = 0;
    uint16_t y = 0;
    //current_location

    char *array[4];
    uint8_t i = 0;
    array[i] = strtok(&current_location,",");
    while(array[i] != NULL) {
        array[++i] = strtok(NULL, ",");
    }    

    if (esp_received_location) {
        current_lvl = atoi(array[1]);
        zone = atoi(array[2]);
        esp_received_location = false;
    }

    if (first_location) {
    if (current_lvl == 2) {
        lvl = 0;
    } else if (current_lvl == 3) {
        lvl = 1;
    } else {
        lvl = 2;
    }
    first_location = false;
   }
    
    if (zone == 235) {
        x = 9 *24;
        y = 4 *24;
    }
    if (zone == 236) {
        x = 11 *24;
        y = 2 *24;
    }
    if (zone == 200) {
        x = 7 *24 +6;
        y = 1 *24;
    }
    if (zone == 201) {
        x = 6 *24 + 14;
        y = 4 *24;
    }
    if (zone == 202) {
        x = 6 *24 +14;
        y = 7 *24 +6;
    }
    if (zone == 203) {
        x = 4 *24 +14;
        y = 4 *24 +6;
    }
    if (zone == 208) {
        x = 24;
        y = 0;
    }
    if (zone == 328) {
        x = 12*24;
        y = 2*24+6;
    }
    if (zone == 300) {
        x = 6*24;
        y = 3*24+6;
    }
    if (zone == 301) {
        x = 10*24;
        y = 2*24+6;
    }
    if (zone == 302) {
        x = 3*24;
        y = 3*24+6;
    }
    if (zone == 305) {
        x = 5*24-2;
        y = 18;
    }
    if (zone == 307) {
        x = 3*24-2;
        y = 15;
    }
    if (zone == 312) {
        x = 1*24-2;
        y = 15;
    }
    if (zone == 321) {
        x = 10*24-2;
        y = 6*24+2;
    }
    if (zone == 320) {
        x = 9*24+2;
        y = 8*24+2;
    }
    if (zone == 316) {
        x = 3*24+2;
        y = 8*24+2;
    }

    if (zone == 313) {
        x = 24+2;
        y = 2*24+2;
    }
    if (zone == 314) {
        x = 24+2;
        y = 4*24+2;
    }
    if (zone == 315) {
        x = 24+2;
        y = 6*24+2;
    }

   
    //0; //current_location;
    void (*lvls[3])() = {
        draw_union_lvl2, draw_union_lvl3, draw_birds_eye
    };

    //gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(), GFX_COLOR_RED);

    // check for current location
    lvls[lvl]();

    //gfx_draw_string_aligned(current_location, 20, 20, &small_sysfont, GFX_COLOR_BLACK, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    if (zone != 0 && current_lvl - 2 == lvl) {
        gfx_draw_string_aligned(SYMFONT_HUMAN, x, y, &symbol_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_RED, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    }
}


void location_application() {
    gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(), GFX_COLOR(48,48,48));
    gfx_draw_string_aligned("Getting Current Location...", gfx_get_width()/2, gfx_get_height()/2, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
    
    // esp8266_enter_standby();
    // delay_ms(2);
    // esp8266_exit_standby();
    wifi_ready = false;
    esp8266_wifi_command("sc_wifievents.bounce()\r\n");
    //esp8266_wifi_command("wifi.sta.disconnect()\r\n");
    //delay_ms(2);
    //esp8266_wifi_command("wifi.sta.connect()\r\n");
    while (!wifi_ready && !wifi_error) {
        esp8266_check_buffer();
    }

    esp8266_wifi_command("require(\"httpprint\"):download(\"137.190.2.245\", 80, \"/api/v1/wifi\", 0)\r\n");
    // while(!esp_received_location && !wifi_error){
    //     esp8266_check_buffer();
    // }

    uint8_t s = 24;
    draw_current_location();

	struct keyboard_event input;
    while(mma8451_orientation() != 6) {
        esp8266_check_buffer();
        keyboard_get_key_state(&input);
        if (esp_received_location) {
            draw_current_location();
            esp_received_location = false;
        }
        if (input.type == KEYBOARD_RELEASE) {
            if (input.keycode == KEYBOARD_B) {
                break;               
            } else if (input.keycode == KEYBOARD_UP) {
                lvl++;
                if (lvl > 2 ) {
                    lvl = 2;
                }
                draw_current_location();
                //lvls[lvl]();
                //gfx_draw_string_aligned(SYMFONT_HUMAN, 3*s+4, 4*s, &symbol_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_RED, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
                //gfx_draw_string_aligned(current_location, gfx_get_width()/2, 15, &tiny_sysfont, GFX_COLOR_BLACK, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
            } else if (input.keycode == KEYBOARD_DOWN) {
                lvl--;
                if (lvl < 0 ) {
                    lvl = 0;
                }
                draw_current_location();
                //lvls[lvl]();
                //gfx_draw_string_aligned(SYMFONT_HUMAN, 3*s+4, 4*s, &symbol_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_RED, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
                //gfx_draw_string_aligned(current_location, gfx_get_width()/2, 15, &tiny_sysfont, GFX_COLOR_BLACK, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
            }
        }
        if(mma8451_clear_interrupt() && is_low_power()) {
            exit_low_power();
        }
    }
}