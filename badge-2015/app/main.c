/**
* SaintCON Badge 2015 
* 
*
*
*
*
**/

#include "main.h"

//    irqflags_t flags = cpu_irq_save();
//    cpu_irq_restore(flags);
/* Global variables */
bool send_bat = false;
volatile irparams_t  irparams;
bool acked[] = {false, false, false, false, false};

void draw_battery_level(uint8_t lvl) {
    uint16_t x = 290;
    uint16_t y = 6;
    if (lvl > 100) {
        lvl = 100;
    }
    gfx_draw_rect(x, y,  20, 8, GFX_COLOR_WHITE);
    gfx_draw_pixel(x+20, y+2, GFX_COLOR_WHITE);
    gfx_draw_pixel(x+20, y+3, GFX_COLOR_WHITE);
    gfx_draw_pixel(x+20, y+4, GFX_COLOR_WHITE);
    gfx_draw_pixel(x+20, y+5, GFX_COLOR_WHITE);
    if (lvl < 20) {
        gfx_draw_filled_rect(x+2, y+2, lvl/6, 4, GFX_COLOR_RED);
    } else {
        gfx_draw_filled_rect(x+2, y+2, lvl/6, 4, GFX_COLOR_GREEN);
    }
}

void draw_password_alert(char *password, uint8_t type) {
    if (!acked[type]) {

        start_buzz(600);
        delay_ms(50);
        stop_buzz();
        delay_ms(50);
        start_buzz(600);
        delay_ms(50);
        stop_buzz();
        gfx_draw_filled_rect(20, 65, 280, 95, GFX_COLOR(5, 5, 5));
        gfx_draw_filled_rect(15, 65, 280, 90, GFX_COLOR(20, 20, 20));

        gfx_draw_filled_circle(25, 75, 5, GFX_COLOR_RED, GFX_WHOLE);
        gfx_draw_string_aligned("B", 26, 66, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);

        
        gfx_draw_string_aligned("Hacker Challenge Password", gfx_get_width()/2, gfx_get_height()/2-40, &sysfont, GFX_COLOR(20, 20, 20), GFX_COLOR_SC_ORANGE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
        char passwd[64];
        snprintf(passwd, sizeof(passwd), "PASSWORD: %s", password);
        gfx_draw_string_aligned(passwd, gfx_get_width()/2, gfx_get_height()/2, &small_sysfont, GFX_COLOR(20, 20, 20), GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
        
        uint8_t first =  mma8451_orientation();
        struct keyboard_event input;
        while (true) {
            if  (mma8451_orientation() != first) {
                break;
            }
            esp8266_check_buffer();
            if(mma8451_clear_interrupt() && is_low_power()) {
                exit_low_power();
            }

            keyboard_get_key_state(&input);
            if (input.type == KEYBOARD_RELEASE) {
                if (input.keycode == KEYBOARD_B) {
                    acked[type] = true;
                    break;
                }
            }
        }
    }
}

uint16_t current_temp() {
        int16_t temperature;
        ntc_measure();

        while (!ntc_data_is_ready());

        temperature = ntc_get_temperature();
        temperature = temperature * 1.8 + 32;

        ntc_measure();

        return temperature;
}

void menu_mode(void) {

    // get all values that require i2c bus / interrups before disableing
    uint8_t battery = max1704x_bat();
    unsigned long ts = rtc_get_time();

    char temp[4];
    snprintf(temp, sizeof(temp), "%d", current_temp());

    // uint8_t rank[AT45DBX_SECTOR_SIZE];
    // at45dbx_read_sector_open(0x000A);
    // at45dbx_read_sector_to_ram(rank);
    // at45dbx_read_close();

    uint8_t score[AT45DBX_SECTOR_SIZE];
    at45dbx_read_sector_open(0x000B);
    at45dbx_read_sector_to_ram(score);
    at45dbx_read_close();

    
    

    //irqflags_t flags = cpu_irq_save();
    gfx_set_orientation(MENU_ORIENTATION);
    
    /* Fill the whole screen with the background color */
    //gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(), GFX_COLOR_BLACK);
   
    draw_background();

    gfx_draw_string_aligned("SCORE", gfx_get_width() / 2, 80, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
    if(score[0] != 0x00) {
        //char rank_string[128];
        //snprintf(rank_string, sizeof(rank_string), "%s - %s", rank, score);
        gfx_draw_string_aligned(score, gfx_get_width() / 2, 105, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_SC_ORANGE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
    } else {
        gfx_draw_string_aligned("No Data", gfx_get_width() / 2, 100, &medium_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
    }

    /* Write center-aligned text string to the top of the display */
    gfx_draw_string_aligned("SAINTCON 2015",    gfx_get_width() / 2, 2, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
    //gfx_draw_string_aligned("Down", gfx_get_width() / 2, 215, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);

    gfx_draw_filled_triangle((gfx_get_width()/2) - 10, 220, (gfx_get_width()/2) +10, 220, gfx_get_width()/2, 220+10, GFX_COLOR_WHITE);

    //gfx_draw_string_aligned("Hacker Challenge", 30, 100, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    //gfx_draw_string_aligned("#1 - 1337", 30, 115, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_LG_GRAY, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);

    //gfx_draw_string_aligned("Calendar", 30, 100, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    //gfx_draw_string_aligned("Next Event", 30, 115, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_LG_GRAY, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);

     gfx_draw_string_aligned(temp, 10, gfx_get_height() - 30, &medium_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_LG_GRAY, TEXT_POS_LEFT, TEXT_ALIGN_RIGHT);
     gfx_draw_circle(40, gfx_get_height() - 25, 2, GFX_COLOR_WHITE, GFX_WHOLE);
    

    struct calendar_date rtc_date;
    
    // might need to build in something for daylight savings time
    calendar_timestamp_to_date_tz(ts, -6, 0, &rtc_date);
    //calendar_timestamp_to_date(rtc_get_time(), &rtc_date);

    char rtc[15];
    char string_buf[15];

    uint8_t hour[] = {12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    char* day[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"}; 

    gfx_draw_string_aligned(day[rtc_date.dayofweek], 30, 30, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_LG_GRAY, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    
    snprintf(rtc, sizeof(rtc), "%d", rtc_date.date + 1);
    gfx_draw_string_aligned(rtc, 30, 50, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);

    snprintf(string_buf, sizeof(string_buf),"%d:%.2d", hour[rtc_date.hour], rtc_date.minute);
    gfx_draw_string_aligned(string_buf, 240, 35, &medium_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);

    draw_battery_level(battery);

    // restore interrupts 
    //cpu_irq_restore(flags);
}

//
// char attendee_name[64];
// char attendee_handel[64];
// char attendee_company[64];
char macAddress[18];
char uuid[13];
uint8_t display_conf = 0;

void name_mode(void) {
    //irqflags_t flags = cpu_irq_save();

    char attendee_name[64];
    char attendee_fname[AT45DBX_SECTOR_SIZE];
    char attendee_lname[AT45DBX_SECTOR_SIZE];
    char attendee_handle[AT45DBX_SECTOR_SIZE];
    char attendee_company[AT45DBX_SECTOR_SIZE];
    char ram_buf[AT45DBX_SECTOR_SIZE];

    gfx_set_orientation(NAME_ORIENTATION);
    draw_background();

    // char size_test[16];
    // snprintf(size_test, sizeof(size_test), "%d", sizeof(attendee_fname));
    // gfx_draw_string_aligned(size_test, 30, 50, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);


    if(at45dbx_mem_check() != true)   {
        //return false;
    }

    // at45dbx_read_sector_open(0x0001);
    // at45dbx_read_sector_to_ram(ram_buf);
    // at45dbx_read_close();

    at45dbx_read_sector_open(FNAME_SECTOR);
    at45dbx_read_sector_to_ram(attendee_fname);
    at45dbx_read_close();

    at45dbx_read_sector_open(LNAME_SECTOR);
    at45dbx_read_sector_to_ram(attendee_lname);
    at45dbx_read_close();

    at45dbx_read_sector_open(HANDLE_SECTOR);
    at45dbx_read_sector_to_ram(attendee_handle);
    at45dbx_read_close();

     at45dbx_read_sector_open(ORG_SECTOR);
    at45dbx_read_sector_to_ram(attendee_company);
    at45dbx_read_close();

    snprintf(attendee_name, sizeof(attendee_name), "%s %s", attendee_fname, attendee_lname);

    // char *array[7];
    // uint8_t i = 0;
    // array[i] = strtok(ram_buf,",");
    // while(array[i] != NULL) {
    //     array[++i] = strtok(NULL, ",");
    // }

    at45dbx_read_byte_open(0x0001);
    display_conf = at45dbx_read_byte();
    at45dbx_read_close();

    // strcpy(attendee_name, array[0]);
    // strcpy(attendee_handle, array[1]);
    // strcpy(attendee_company, array[2]);

    // strcpy(macAddress, array[3]);
    // strcpy(uuid, array[4]);

    //char ram_buf[AT45DBX_SECTOR_SIZE];
    at45dbx_read_sector_open(0x0000);
    at45dbx_read_sector_to_ram(ram_buf);
    at45dbx_read_close();

    uint8_t disp_name[160];
    uint8_t numlines = word_wrap(&disp_name, attendee_name, 17);

    uint8_t disp_org[160];
    uint8_t orglines = word_wrap(&disp_org, attendee_company, 23);
    switch (display_conf) {
        case 0:
            gfx_draw_string_aligned(disp_name, gfx_get_width() / 2, 10, &large_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
            gfx_draw_string_aligned(attendee_handle, gfx_get_width() / 2, 50 + (numlines * 20) , &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
            gfx_draw_string_aligned(disp_org, gfx_get_width() / 2, 200 - (orglines* 24), &medium_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
            break;
        case 1:
            gfx_draw_string_aligned(attendee_handle, gfx_get_width() / 2, 10, &large_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
            gfx_draw_string_aligned(attendee_name, gfx_get_width() / 2, 50, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
            gfx_draw_string_aligned(disp_org, gfx_get_width() / 2, 200 - (orglines * 24), &medium_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
             break;
        case 2:
            gfx_draw_string_aligned(attendee_name, gfx_get_width() / 2, 10, &large_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
            gfx_draw_string_aligned(attendee_handle, gfx_get_width() / 2, 50, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
            break;
        case 3:
            gfx_draw_string_aligned(attendee_handle, gfx_get_width() / 2, 10, &large_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
            gfx_draw_string_aligned(attendee_name, gfx_get_width() / 2, 50, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
            break;
        case 4:
            if (attendee_handle[0] != 0x0) {
                gfx_draw_string_aligned(attendee_handle, gfx_get_width() / 2, 10, &large_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
            } else {
                gfx_draw_string_aligned(disp_name, gfx_get_width() / 2, 10, &large_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
            }
            break;
    }

    
    //cpu_irq_restore(flags);

}



uint8_t columns = 4;
int column = 0;
uint8_t rows = 2;
int row = 0;
//
void draw_icons(void) {
    gfx_color_t color[2][4];
    for (uint8_t r = 0; r < rows; r++) {
        for (uint8_t x = 0; x < columns; x++ ) {
            if (column == x) {
                if (row == r) { 
                    color[r][x] = GFX_COLOR_SC_ORANGE;
                } else {
                    color[r][x] = GFX_COLOR(80,80,80);
                }
            } else {
                color[r][x] = GFX_COLOR(80,80,80);
            }
        }
    }

    gfx_draw_string_aligned(SYMFONT_SCHEDULE, 54, 60, &symbol_sysfont, GFX_COLOR_TRANSPARENT, color[0][0], TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
    gfx_draw_string_aligned(SYMFONT_CONTROLLER, 126, 60, &symbol_sysfont, GFX_COLOR_TRANSPARENT, color[0][1], TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
    gfx_draw_string_aligned(SYMFONT_LOCATION, 196, 60, &symbol_sysfont, GFX_COLOR_TRANSPARENT, color[0][2], TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
    gfx_draw_string_aligned(SYMFONT_HC, 269, 60, &symbol_sysfont, GFX_COLOR_TRANSPARENT, color[0][3], TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);

    gfx_draw_string_aligned(SYMFONT_NAMETAG, 54, 152, &symbol_sysfont, GFX_COLOR_TRANSPARENT, color[1][0], TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
    gfx_draw_string_aligned(SYMFONT_BATTERY, 126, 152, &symbol_sysfont, GFX_COLOR_TRANSPARENT, color[1][1], TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
    if (esp_received_pmsg || esp_received_bmsg) {
        gfx_draw_string_aligned(SYMFONT_MAIL, 196, 152, &symbol_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_RED, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
    } else {
        gfx_draw_string_aligned(SYMFONT_MAIL, 196, 152, &symbol_sysfont, GFX_COLOR_TRANSPARENT, color[1][2], TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
    }
    gfx_draw_string_aligned(SYMFONT_WIFI, 269, 152, &symbol_sysfont, GFX_COLOR_TRANSPARENT, color[1][3], TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
}

void draw_application_menu(void) {
    //irqflags_t flags = cpu_irq_save();

    gfx_set_orientation(MENU_ORIENTATION);
    draw_background();
    gfx_draw_string_aligned("Applications", gfx_get_width() / 2, 2, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);

    gfx_draw_filled_circle(53,  80, 30, GFX_COLOR_WHITE, GFX_WHOLE);
    gfx_draw_filled_circle(125, 80, 30, GFX_COLOR_WHITE, GFX_WHOLE);
    gfx_draw_filled_circle(195, 80, 30, GFX_COLOR_WHITE, GFX_WHOLE);
    gfx_draw_filled_circle(268, 80, 30, GFX_COLOR_WHITE, GFX_WHOLE);

    gfx_draw_filled_circle(53,  80+80+10, 30, GFX_COLOR_WHITE, GFX_WHOLE);
    gfx_draw_filled_circle(125, 80+80+10, 30, GFX_COLOR_WHITE, GFX_WHOLE);
    gfx_draw_filled_circle(195, 80+80+10, 30, GFX_COLOR_WHITE, GFX_WHOLE);
    gfx_draw_filled_circle(268, 80+80+10, 30, GFX_COLOR_WHITE, GFX_WHOLE);


    draw_icons();

    //cpu_irq_restore(flags);
}

//void (*applications[4][2])() = {credits_application, hackerchallenge_application};
void (*applications[2][4])() = {
        {schedule_application, game_application, location_application, hackerchallenge_application},
        {settings_application, battery_application, notifications_application, network_application}
};

void application_menu(void) {

    draw_application_menu();

    struct keyboard_event input;
    while(mma8451_orientation() != 6) {
        esp8266_check_buffer();

        keyboard_get_key_state(&input);
        if (input.type == KEYBOARD_RELEASE) {
            if (input.keycode == KEYBOARD_B) {
                menu_mode();
                break;

            } else if (input.keycode == KEYBOARD_A) {
                (*applications[row][column])();
                draw_application_menu();

            } else if (input.keycode == KEYBOARD_UP) {
                row--;
                if (row < 0 ) {
                    row = rows-1;
                }
                draw_icons();
            } else if (input.keycode == KEYBOARD_DOWN) {
                row++;
                if (row > rows-1) {
                    row = 0;
                }
                draw_icons();
            } else if (input.keycode == KEYBOARD_LEFT) {
                column--;
                if (column < 0 ) {
                    column = columns-1;
                }
                draw_icons();

            } else if (input.keycode == KEYBOARD_RIGHT) {
                column++;
                if (column > columns-1) {
                    column = 0;
                }
                draw_icons();
            }
        }
        // clear motion interrupt
        mma8451_clear_interrupt();
        
    }
}

void matrix_animation() {
    char m[] = {'S','A','I','N','T','C','O','N','2','0','1','5','!'};
    char l[2]; 
    uint16_t x = (rand() % 310);
    uint16_t y = (rand() % 60);
    if ( x > 50 && x < 280) {
        y += 55;
    } 

    uint8_t  n = (rand() % 4 + 8);
    for (int i = 0; i < n; i++) {
        if (i > 0 ) {  
            snprintf(l, sizeof(l), "%c", (rand() % 32 + 32));
            gfx_draw_string_aligned(l, x, y + ((i -1) * 16), &tiny_sysfont, GFX_COLOR_BLACK, GFX_COLOR_SC_ORANGE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
        }
        snprintf(l, sizeof(l), "%c", m[rand() % 12]);
        gfx_draw_string_aligned(l, x, y + (i * 16), &tiny_sysfont, GFX_COLOR_BLACK, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
        delay_ms(20);
    }
    gfx_draw_string_aligned("Loading...", gfx_get_width() / 2, gfx_get_height()/2, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
}

static void sleep_alarm(void) {
    
    // power up wifi and check for updates
    //max1704x_bat(); // check battery level
    //LED_On(LED0);

    // char ntp[ESP8266_BUFFER_SIZE];
    // esp8266_wifi_command(ESP_NTP_COMMAND);
    // esp8266_get_result("{", "stdin", '}', &ntp);
    // unsigned long timestamp = atol(ntp);
    // if (timestamp > 0 && rtc_get_time() + 3 < timestamp) {
    //     rtc_set_time(timestamp);
    // }
    send_bat = true;
    rtc_set_alarm_relative(60);
    move_counter++;
    if (move_counter > 2) {
        enter_low_power();
    }
    // if (move_counter > 9) {
    //     esp8266_enter_standby();
    // }
    //LED_Off(LED0);
}


bool badge_registerd(void) {
    uint8_t ram_buf[AT45DBX_SECTOR_SIZE];

    if(at45dbx_mem_check() != true)   {
        return false;
    }


    gfx_draw_string_aligned("Welcome to SAINTCON\n2015", gfx_get_width() / 2, 2, &medium_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);

    gfx_draw_string_aligned("Loading...", gfx_get_width() / 2, gfx_get_height()/2, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);

    // for (int m = 0; m < 36; m++) {
    //     matrix_animation();
    // }


    at45dbx_read_byte_open(0x0000);
    uint8_t registered = at45dbx_read_byte();
    at45dbx_read_close();

    uint16_t count = 0;
    while(!wifi_ready && !wifi_error) {
        if (count == 65000) {
            matrix_animation();
        } 
        esp8266_check_buffer();
        count++;
    }
    esp8266_wifi_command("=require(\"scmqtt\"):frombadge(\"color\", \"purple\")\r\n");
    if (registered != 0x01) {
        //LED_On(LED0);
        while(!esp_received_uuid);
        draw_background();
        gfx_draw_string_aligned("Registration Code", gfx_get_width() / 2, 2, &sysfont, GFX_COLOR_BLACK, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
        gfx_draw_string_aligned(esp_uuid, gfx_get_width() / 2, 50, &sysfont, GFX_COLOR_BLACK, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);

        while (!esp_received_fname && !esp_received_lname && !esp_received_org) {
            esp8266_check_buffer();
        }

    } else {
        //LED_On(LED0);
        return true;
    }

    
    for(uint16_t i=0;i<AT45DBX_SECTOR_SIZE;i++) {
        ram_buf[i]=0x00;
    }


    at45dbx_write_byte_open(0x0000);
    at45dbx_write_byte(0x01);
    at45dbx_write_close();

    at45dbx_write_byte_open(0x0001);
    at45dbx_write_byte(0x00);
    at45dbx_write_close();

    return true;
}

uint32_t ir_unlock_pattern[] = {0xdead,0xc0de};
uint8_t unlock_index = 0;
bool ir_unlock(uint16_t code) {
    if (code == ir_unlock_pattern[unlock_index]) {
        unlock_index++;
        if (unlock_index == 2) {
            return true;
        }
    }
    return false;
}



void send_temp(void) {
    char cmd[64];
    snprintf(cmd, sizeof(cmd), "=require(\"scmqtt\"):frombadge(\"temperature\", %d)\r\n", current_temp());
    esp8266_wifi_command(cmd);
 
}

int main(void) {
    board_init();
    pmic_init();
    sysclk_init();
    gfx_init();
    twi_init();
    adc_sensors_init();
    tsl2561t_init();
    cpu_irq_enable();
    irda_init();
    at45dbx_init();
    esp8266_init(&USARTE0);

    // splash the boot screen and play tones 
    gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(), GFX_COLOR_BLACK);
    //draw_background();
    //gfx_draw_string_aligned("Loading...", gfx_get_width() / 2, 90, &medium_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);


    
   
    start_buzz(400);
    delay_ms(100);
    stop_buzz();
    start_buzz(523);
    delay_ms(100);
    stop_buzz();
  
    uint32_t rtc_timestamp;
    sysclk_enable_module(SYSCLK_PORT_GEN, SYSCLK_RTC);
    while (RTC32.SYNCCTRL & RTC32_SYNCBUSY_bm) {
        // Wait for RTC32 sysclk to become stable
    }
    // If we have battery power and RTC is running, don't initialize RTC32
    if (rtc_vbat_system_check(false) != VBAT_STATUS_OK) {
        rtc_init();
        // Set current time to after production date
        rtc_timestamp = 1440543104 + 1;
        rtc_set_time(rtc_timestamp);
    }
    // Get current time
    rtc_timestamp = rtc_get_time();
    // Make sure RTC has not been set to a too early date .
    if (rtc_timestamp < FIRST_POSSIBLE_TIMESTAMP) {
        // Set time to 01.01.2011 00:00:00
        rtc_set_time(FIRST_POSSIBLE_TIMESTAMP);
    }

    if (!badge_registerd()) {

    }
    esp8266_wifi_command(ESP_NTP_COMMAND);

    rtc_set_callback((rtc_callback_t)&sleep_alarm);
    powermgmt_init(rtc_get_time()); // used to track how long this badge has been awake or sleeping 
    
    rtc_set_alarm_relative(60);

    

    //esp8266_wifi_command("require(\"httpprint\"):download(\"atticus.klintholmes.com\", 80, \"/demo.php\", 0)\r\n");


    decode_results  result;
    irparams.rcvstate = STATE_IDLE;
    struct keyboard_event input;

    mma8451_init();

    while (true) {

        name_mode();
        // reset sleep alarm on mode transition
        while(mma8451_orientation() != 4) {
            esp8266_check_buffer();
            if (send_bat) {
                uint8_t battery = max1704x_bat();
                if (battery > 100) {
                    battery = 100;
                }
                char cmd[64];
                snprintf(cmd, sizeof(cmd), "=require(\"scmqtt\"):frombadge(\"battery\", %d)\r\n", battery);
                //snprintf(cmd, sizeof(cmd), "=require(\"scmqtt\"):frombadge(\"battery\", %d)\r\n", battery);
                esp8266_wifi_command(cmd);
                send_temp();
                send_bat = false;
            }

            if (tsl2561t_light() > 1955 && !acked[2]) {
                draw_password_alert("ZF727LNNSW6AJA94", 2);
                name_mode();
            }

            if (current_temp() < 45 && !acked[0]) {
                draw_password_alert("IRVZJSGEYF16NHA7", 0);
                name_mode();
            }
            if (irparams.rcvstate == STATE_STOP) {
                decode(&result);

                //LED_Toggle(LED0);
                if (ir_unlock(result.value) && !acked[1]) {
                    draw_password_alert("T9PSUX5KUPJJE9MF", 1);
                    name_mode();
                }
                // char ircode[15];
                // snprintf(ircode, sizeof(ircode), "%04x", result.value);
                // gfx_draw_string_aligned(ircode,    3 , 44, &sysfont, GFX_COLOR_BLACK, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);

                irparams.rawlen = 0;
                irparams.rcvstate = STATE_IDLE;
                
            }

            // clear motion interruptesp8266_check_buffer();
            if(mma8451_clear_interrupt() && is_low_power()) {
                exit_low_power();
            }
        }
        //=require("scmqtt"):frombadge("battery", 42)\r\n
        //=require("httpprint"):download("atticus.klintholmes.com", 80, "/demo.php", 0)
        if (is_low_power()) {
            exit_low_power();
        }
        menu_mode();
        while(mma8451_orientation() != 6) {
            esp8266_check_buffer();
            if (send_bat) {
                uint8_t battery = max1704x_bat();
                if (battery > 100) {
                    battery = 100;
                }
                char cmd[64];
                snprintf(cmd, sizeof(cmd), "=require(\"scmqtt\"):frombadge(\"battery\", %d)\r\n", battery);
                esp8266_wifi_command(cmd);
                send_temp();
                send_bat = false;
            }

            if (tsl2561t_light() > 1955 && !acked[2]) {
                draw_password_alert("ZF727LNNSW6AJA94", 2);
                menu_mode();
            }
            if (current_temp() < 45 && !acked[0]) {
                draw_password_alert("IRVZJSGEYF16NHA7", 0);
                menu_mode();

            }
            if(mma8451_clear_interrupt() && is_low_power()) {
                exit_low_power();
            }

            keyboard_get_key_state(&input);
            if (input.type == KEYBOARD_RELEASE) {
                if (input.keycode == KEYBOARD_DOWN) {
                    application_menu();
                } else if (input.keycode == KEYBOARD_START) {
                    if (input.konami) {
                        credits_application();
                        menu_mode();
                    }
                }
            }
        }
    }
}

void upgrade_firmware() {
}
