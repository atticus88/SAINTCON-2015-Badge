#include "keyboard.h"

void bsod(void) {
    gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(), GFX_COLOR_BLUE);
    gfx_draw_string_aligned("Badge Error",  gfx_get_width() / 2, 2, &sysfont, GFX_COLOR_LG_GRAY, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
    gfx_draw_string_aligned("An error has occurred.",   gfx_get_width() / 2, 22, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
}


void badge_test(void) {
    
        gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(), GFX_COLOR_BLUE);
        gfx_draw_string_aligned("Badge Test",   gfx_get_width() / 2, 2, &sysfont, GFX_COLOR_LG_GRAY, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
        
        gfx_draw_string_aligned("MMA8451 : ",  3, 22, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
        if (mma8451_read(0x0D) != 0x1A) {
         gfx_draw_string_aligned("MMA8451 : Not Found.",  3, 22, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
        } else {
         gfx_draw_string_aligned("MMA8451 : Found.",  3, 22, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
        }

        gfx_draw_string_aligned("MAX1704X: ", 3, 44, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
        if (max1704x_version() == 3) { // version of chip
            gfx_draw_string_aligned("MAX1704X: Found.", 3, 44, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
            char bat_lvl[15];
            snprintf(bat_lvl, sizeof(bat_lvl), "%2i %%", max1704x_bat());
            gfx_draw_string_aligned(bat_lvl,    180, 44, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
        } else {
            gfx_draw_string_aligned("MAX1704X: Not Found.", 3, 44, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
        }

        gfx_draw_string_aligned("TSL2561T: ", 3, 66, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
        if (tsl2561t_version() == 10) {
            gfx_draw_string_aligned("TSL2561T: Found.", 3, 66, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
            char lux[8];
            char light_id[16];
            dtostrf(tsl2561t_light(), 4, 2, lux);
            snprintf(light_id, sizeof(light_id), "%s Lux", lux);
            gfx_draw_string_aligned(light_id,   180, 66, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
        } else {
            gfx_draw_string_aligned("TSL2561T: Not Found.", 3, 66, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
        }

        gfx_draw_string_aligned("AT45DB16: ", 3, 88, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
        if (test_flash_memory()) {
            gfx_draw_string_aligned("AT45DB16: Found.", 3, 88, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
        } else {
            gfx_draw_string_aligned("AT45DB16: Not Found.", 3, 88, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
        }

        // char tmp[64];
         gfx_draw_string_aligned("ESP12   : SKIPPED.", 3, 110, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
        // if (esp8266_get_version(&tmp)) {
        //       gfx_draw_string_aligned("ESP12   : Found.", 3, 110, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
        // } else {
        //        gfx_draw_string_aligned("ESP12   : Not Found.", 3, 110, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
        // }
   
        gfx_draw_string_aligned("ATAES132: SKIPPED.", 3, 132, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
        gfx_draw_string_aligned("ATECC508: SKIPPED.", 3, 154, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);

        if (mma_interupt_test()) {
            gfx_draw_string_aligned("PASS.",  180, 22, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
        } else {
            gfx_draw_string_aligned("FAIL.",  180, 22, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
        }


        //esp_send_test();
        //ir_send_test();
        //rtc_test();
        ntc_test();
        ir_test();
        
        delay_ms(2000);
        //button_test();
}

void button_test(void) {
    int press_count = 0;
    struct keyboard_event input;
    gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(), GFX_COLOR_BLACK);
    gfx_draw_string_aligned("Keyboard Test", gfx_get_width() / 2, 50, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
    while (press_count < 8) {
        keyboard_get_key_state(&input);
        if (input.type == KEYBOARD_RELEASE) {
            if (input.keycode == KEYBOARD_B) {
                gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(), GFX_COLOR_BLACK);
                gfx_draw_string_aligned("B", gfx_get_width() / 2, 50, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
                press_count++;
            } else if (input.keycode == KEYBOARD_A) {
                gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(), GFX_COLOR_BLACK);
                gfx_draw_string_aligned("A", gfx_get_width() / 2, 50, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);        
                press_count++;
            } else if (input.keycode == KEYBOARD_SELECT) {
                gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(), GFX_COLOR_BLACK);
                gfx_draw_string_aligned("SELECT", gfx_get_width() / 2, 50, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);   
                press_count++;
            } else if (input.keycode == KEYBOARD_START) {
                gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(), GFX_COLOR_BLACK);
                gfx_draw_string_aligned("START", gfx_get_width() / 2, 50, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);    
                press_count++;
            } else if (input.keycode == KEYBOARD_UP) {
                gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(), GFX_COLOR_BLACK);
                gfx_draw_string_aligned("UP", gfx_get_width() / 2, 50, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);   
                press_count++;
            } else if (input.keycode == KEYBOARD_DOWN) {
                gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(), GFX_COLOR_BLACK);
                gfx_draw_string_aligned("DOWN", gfx_get_width() / 2, 50, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT); 
                press_count++;
            } else if (input.keycode == KEYBOARD_LEFT) {
                gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(), GFX_COLOR_BLACK);
                gfx_draw_string_aligned("LEFT", gfx_get_width() / 2, 50, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT); 
                press_count++;
            } else if (input.keycode == KEYBOARD_RIGHT) {
                gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(), GFX_COLOR_BLACK);
                gfx_draw_string_aligned("RIGHT", gfx_get_width() / 2, 50, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);    
                press_count++;
            }
        }
    }
}

bool mma_interupt_test(void) {
    while (!motion_int && !lndprt_int);
    return true;
}

void ntc_test(void) {
   // while (true) {
        char temperature_string[30];
        int16_t temperature;

        ntc_measure();

        while (!ntc_data_is_ready());
        //LED_On(LED0);
        // Read the temperature once the ADC reading is done
        temperature = ntc_get_temperature();
        temperature = temperature * 1.8 + 32;

        snprintf(temperature_string, sizeof(temperature_string), "NTCTEMP : Found.  %d", temperature);
        gfx_draw_string_aligned(temperature_string, 3, 176, &sysfont, GFX_COLOR_BLUE, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);

        // Call a new reading while doing the rest of the calculations
        ntc_measure();
       // delay_ms(600);
  //  }
}

// this will test reading and writing to the flash return false on errors 
bool test_flash_memory(void) {

    uint8_t ram_buf[AT45DBX_SECTOR_SIZE];
    at45dbx_init();

    if(at45dbx_mem_check() != true)   {
        return false;
    }

    // Prepare half a data flash sector to 0xAA
    for(uint16_t i=0;i<AT45DBX_SECTOR_SIZE;i++) {
        ram_buf[i]=0xAA;
    }

    at45dbx_write_sector_open(TARGET_SECTOR);
    at45dbx_write_sector_from_ram(ram_buf);
    at45dbx_write_close();

    // Read back this sector and compare to expected values
    at45dbx_read_sector_open(TARGET_SECTOR);
    at45dbx_read_sector_to_ram(ram_buf);
    at45dbx_read_close();
   
    for(uint8_t i=0;i< 9 ;i++) {
        if (ram_buf[i]!=0xAA) {
            return false;
        }
    }

    return true;

}

uint8_t serial_number_reade_byte(uint16_t address) {
    NVM_CMD = NVM_CMD_READ_CALIB_ROW_gc;
    uint8_t result;
    __asm__ ("lpm %0, Z\n" : "=r" (result) : "z" (address)); 
    NVM_CMD = NVM_CMD_NO_OPERATION_gc;
    return result;
}
void print_serial_number(void) {}
enum {
  LOTNUM0=8,  // Lot Number Byte 0, ASCII
  LOTNUM1,    // Lot Number Byte 1, ASCII
  LOTNUM2,    // Lot Number Byte 2, ASCII
  LOTNUM3,    // Lot Number Byte 3, ASCII
  LOTNUM4,    // Lot Number Byte 4, ASCII
  LOTNUM5,    // Lot Number Byte 5, ASCII
  WAFNUM =16, // Wafer Number
  COORDX0=18, // Wafer Coordinate X Byte 0
  COORDX1,    // Wafer Coordinate X Byte 1
  COORDY0,    // Wafer Coordinate Y Byte 0
  COORDY1,    // Wafer Coordinate Y Byte 1
};
  uint8_t uuid[11];
  uuid[ 0]=serial_number_reade_byte(LOTNUM0);
  uuid[ 1]=serial_number_reade_byte(LOTNUM1);
  uuid[ 2]=serial_number_reade_byte(LOTNUM2);
  uuid[ 3]=serial_number_reade_byte(LOTNUM3);
  uuid[ 4]=serial_number_reade_byte(LOTNUM4);
  uuid[ 5]=serial_number_reade_byte(LOTNUM5);
  uuid[ 6]=serial_number_reade_byte(WAFNUM );
  uuid[ 7]=serial_number_reade_byte(COORDX0);
  uuid[ 8]=serial_number_reade_byte(COORDX1);
  uuid[ 9]=serial_number_reade_byte(COORDY0);
  uuid[10]=serial_number_reade_byte(COORDY1);
  uint8_t b[2];
    for (uint16_t i = 0; i < 11; i++) {
        snprintf(b, sizeof(b), "%02x", uuid[i]);
        gfx_draw_string_aligned(b, 30+(9*i), 70, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    }
}

void test_flash_uuid(void) {
    gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(), GFX_COLOR_BOOT_GRAY);
    uint8_t secure_data[128];
    uint8_t b[4];
    at45dbx_get_uuid(&secure_data);
    uint8_t blocks = 0;
    uint8_t height =0;
    for (uint16_t i = 64; i < 128; i++) {
        snprintf(b, sizeof(b), "%02x", secure_data[i]);
        gfx_draw_string_aligned(b, 4+(18*blocks), 50+(height*20), &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
        blocks++;
        if (blocks >= 17) {
            height++;
            blocks = 0;
        }
    }
}

// this will run durring boot screen as it checks time
void esp_send_test(void) {  

    if (!esp8266_wifi_connected()) {
        esp8266_wifi_connect();
    }

    char buff[128];
    char tmp[64];

    esp8266_get_ip(&tmp);
    gfx_draw_string_aligned(tmp, gfx_get_width() / 2, 132,  &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);

    //LED_On(LED0);

    if (esp8266_wifi_connected()) {
        esp8266_get_data("atticus.klintholmes.com", "/index.php", "atticus.klintholmes.com", &buff);
        unsigned long timestamp = atol(buff);
       

        char str[15];
        snprintf(str, sizeof(str), "%lu", timestamp);
        gfx_draw_string_aligned(str, gfx_get_width() / 2, 132,  &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
        
        if (timestamp > 0 && rtc_get_time() + 3 < timestamp) {
            rtc_set_time(timestamp);
        } else {
            gfx_draw_string_aligned(buff, gfx_get_width() / 2, 132,  &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
        }
    }
}

bool ir_test(void) {
    decode_results  result;
    irparams.rcvstate = STATE_IDLE;

    for (int i = 0; i < 5; i++ ) {
        irda_send(0xC0FF, 16); // SC
        delay_ms(80);
    }

    if (irparams.rcvstate == STATE_STOP) {
        decode(&result);

        // char bat_lvl[15];
        // snprintf(bat_lvl, sizeof(bat_lvl), "%02x", result.value);
        // gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(), GFX_COLOR_BLUE);
        // gfx_draw_string_aligned(bat_lvl,    3 , 44, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);

        irparams.rcvstate = STATE_IDLE;
        irparams.rawlen = 0;
    }
    if (result.value == 0xC0FF) {
        gfx_draw_string_aligned("IRDA    : Working.", 3, 198, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
        return true;
    }
    gfx_draw_string_aligned("IRDA    : Not Working.", 3, 198, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    return false;
}