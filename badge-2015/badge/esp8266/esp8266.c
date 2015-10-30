/*
 * esp82661.c
 *
 * Created: 12/16/2014 11:01:29 AM
 *  Author: Klint
 */ 

#include "esp8266.h"
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/atomic.h>
#include "at45dbx.h"
#include "math.h"
//#include "tc.h"
#include "buzzer.h"
//#define     ESP_USB_DEBUG_MODE

#define     UART_FRAME_ERROR        0x0800
#define     UART_OVERRUN_ERROR      0x0400
#define     UART_BUFFER_OVERFLOW    0x0200
#define     UART_NO_DATA            0x0100


bool esp8266_connected = false;
USART_t* esp8266_usart;


void esp8266_init(USART_t* port) {
    // 127 is max size of fifo buffer 
    fifo_init(&test_fifo_desc, test_fifo_buffer, FIFO_BUFFER_SIZE);

    // test with timer 
    // tc_enable(&TCD1);
    // tc_set_overflow_interrupt_callback(&TCD1, esp8266_check_buffer);
    // tc_set_wgm(&TCD1, TC_WG_NORMAL);
    // tc_write_period(&TCD1, 3200);
    // tc_set_overflow_interrupt_level(&TCD1, TC_INT_LVL_LO);
    // tc_write_clock_source(&TCD1, TC_CLKSEL_DIV1_gc);

    wifi_ready = false;
    wifi_error = false;
    esp_data_ready = false;
    esp_received_fname = false;
    esp_received_lname = false;
    esp_received_handle = false;
    esp_received_org = false;
    esp_received_uuid = false;
    esp_received_location = false;
    esp_received_hcrank = false;
    esp_received_hcscore = false;
    esp_received_pmsg = false;
    esp_received_bmsg = false;
    //current_location = 0;


    static usart_rs232_options_t opt = {
        .baudrate = USART_SERIAL_EXAMPLE_BAUDRATE,
        .charlength = USART_SERIAL_CHAR_LENGTH,
        .paritytype = USART_SERIAL_PARITY,
        .stopbits = USART_SERIAL_STOP_BIT
    };

    esp8266_usart = port;
    usart_init_rs232(esp8266_usart, &opt);
    usart_set_rx_interrupt_level(esp8266_usart, USART_INT_LVL_HI);

}



void clear_buffer(char *buffer) {
    for (int i = 0; i < FIFO_BUFFER_SIZE; i++) {
        buffer[i] =  0;
    }
}

uint16_t event_counter = 0;
uint32_t esp_data_size = 0;
bool sched = false;
bool array_data = false;



bool esp8266_check_buffer(void) {
    ioport_set_pin_level(LED0, !fifo_is_full(&test_fifo_desc));
    if (!fifo_is_empty(&test_fifo_desc)) {
        union buffer_element item;
        fifo_pull_uint8(&test_fifo_desc, &item.byte);
        uint8_t c = item.byte;

        if (c == '\n') {
            esp_data[esp_data_size] = 0x0;
            esp8266_parse_data();
            clear_buffer(esp_data);
            esp_data_size = 0;

        } else {

            esp_data[esp_data_size] = c;
            esp_data_size++;
        } 
    }
    //esp_data_ready = false;
}


uint8_t item = 0;
bool esp8266_parse_data() {
    //gfx_draw_string_aligned(esp_data, 5, 150, &tiny_sysfont, GFX_COLOR_BLACK, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    if (strstr(esp_data, "SC+WIFI=READY")) {
        wifi_ready = true;
        wifi_error = false;
        return true;
    }

    if ( strstr(esp_data, "PANIC: ")) {
        wifi_ready = false;
        wifi_error = true;
        return false;
    }

    char *array[4];
    uint8_t i = 0;
    array[i] = strtok(esp_data,"+=");
    while(array[i] != NULL) {
        array[++i] = strtok(NULL, "+=");
    }

    if (strstr(array[1], "MSELOC")) {
        strcpy(current_location, array[2]);
        esp_received_location = true;
        return true;
    }
    
    if (strstr(array[1], "FNAME")) {
        //if (strcmp("nil", array[2])) {
            uint8_t ram_buf[AT45DBX_SECTOR_SIZE];
            for(uint16_t i=0;i<AT45DBX_SECTOR_SIZE;i++) {
                ram_buf[i]=0x00;
            }
            for (uint16_t i = 0; i < strlen(array[2]); i++) {
                ram_buf[i] = array[2][i];
            }
            at45dbx_write_sector_open(0x0002);
            at45dbx_write_sector_from_ram(ram_buf);
            at45dbx_write_close();

            esp_received_fname = true;
            return true;
        //}
        // esp_received_fname = false;
        //return false;
    }

    if (strstr(array[1], "LNAME")) {
        //if (strcmp("nil", array[2])) {
            uint8_t ram_buf[AT45DBX_SECTOR_SIZE];
            for(uint16_t i=0;i<AT45DBX_SECTOR_SIZE;i++) {
                ram_buf[i]=0x00;
            }
            for (uint16_t i = 0; i < strlen(array[2]); i++) {
                ram_buf[i] = array[2][i];
            }
            at45dbx_write_sector_open(0x0003);
            at45dbx_write_sector_from_ram(ram_buf);
            at45dbx_write_close();

            esp_received_lname = true;
            return true;
       // }
       //  esp_received_lname = false;
        //return false;
    }

    if (strstr(array[1], "HANDLE")) {
       // if (strcmp("nil", array[2])) {
            uint8_t ram_buf[AT45DBX_SECTOR_SIZE];
            for(uint16_t i=0;i<AT45DBX_SECTOR_SIZE;i++) {
                ram_buf[i]=0x00;
            }
            for (uint16_t i = 0; i < strlen(array[2]); i++) {
                ram_buf[i] = array[2][i];
            }
            at45dbx_write_sector_open(0x0004);
            at45dbx_write_sector_from_ram(ram_buf);
            at45dbx_write_close();

            esp_received_handle = true;
            return true;
        //}
        //esp_received_handle = false;
        //return false;
    }

    if (strstr(array[1], "ORG")) {
        //if (strcmp("nil", array[2])) {
            uint8_t ram_buf[AT45DBX_SECTOR_SIZE];
            for(uint16_t i=0;i<AT45DBX_SECTOR_SIZE;i++) {
                ram_buf[i]=0x00;
            }
            for (uint16_t i = 0; i < strlen(array[2]); i++) {
                ram_buf[i] = array[2][i];
            }
            at45dbx_write_sector_open(0x0005);
            at45dbx_write_sector_from_ram(ram_buf);
            at45dbx_write_close();

            esp_received_org = true;
            return true;
        //}
        // esp_received_org = false;
        //return false;
    }

    if (strstr(array[1], "UUID")) {
        // did change this if something is wrong look here
        strncpy(esp_uuid, array[2], strlen(array[2]+1));
        esp_received_uuid = true;
        return true;
    }

    if (strstr(array[1], "MAC")) {
        uint8_t ram_buf[AT45DBX_SECTOR_SIZE];
        for(uint16_t i=0;i<AT45DBX_SECTOR_SIZE;i++) {
            ram_buf[i]=0x00;
        }
        for (uint16_t i = 0; i < strlen(array[2]); i++) {
            ram_buf[i] = array[2][i];
        }

        at45dbx_write_sector_open(0x0007);
        at45dbx_write_sector_from_ram(ram_buf);
        at45dbx_write_close();
        return true;
    }

    if (strstr(array[1], "HCRANK")) {
        strcpy(esp_hcrank, array[2]);

        uint8_t ram_buf[AT45DBX_SECTOR_SIZE];
        for(uint16_t i=0;i<AT45DBX_SECTOR_SIZE;i++) {
           ram_buf[i]=0x00;
        }
        for (uint16_t i = 0; i < strlen(array[2]); i++) {
            ram_buf[i] = array[2][i];
        }
        at45dbx_write_sector_open(0x000A);
        at45dbx_write_sector_from_ram(ram_buf);
        at45dbx_write_close();

        return true;
    }

    if (strstr(array[1], "TOPTEN")) {
        uint8_t ram_buf[AT45DBX_SECTOR_SIZE];
        for(uint16_t i=0;i<AT45DBX_SECTOR_SIZE;i++) {
           ram_buf[i]=0x00;
        }
        for (uint16_t i = 0; i < strlen(array[2]); i++) {
            ram_buf[i] = array[2][i];
        }
        at45dbx_write_sector_open(0x000F);
        at45dbx_write_sector_from_ram(ram_buf);
        at45dbx_write_close();

        return true;
    }

    if (strstr(array[1], "PMSG")) {
        strcpy(esp_pmsg, array[2]);

        start_buzz(600);
        delay_ms(50);
        stop_buzz();
        delay_ms(50);
        start_buzz(600);
        delay_ms(50);
        stop_buzz();
        delay_ms(50);
        start_buzz(600);
        delay_ms(50);
        stop_buzz();
        esp_received_pmsg = true;
        return true;
    }

    if (strstr(array[1], "BMSG")) {
        strcpy(esp_bmsg, array[2]);

        start_buzz(600);
        delay_ms(50);
        stop_buzz();
        delay_ms(50);
        start_buzz(600);
        delay_ms(50);
        stop_buzz();
        delay_ms(50);
        start_buzz(600);
        delay_ms(50);
        stop_buzz();
        esp_received_bmsg = true;
        return true;
    }

    if (strstr(array[1], "HCSCORE")) {
        strcpy(esp_hcscore, array[2]);

        uint8_t ram_buf[AT45DBX_SECTOR_SIZE];
        for(uint16_t i=0;i<AT45DBX_SECTOR_SIZE;i++) {
           ram_buf[i]=0x00;
        }
        for (uint16_t i = 0; i < strlen(array[2]); i++) {
            ram_buf[i] = array[2][i];
        }
        at45dbx_write_sector_open(0x000B);
        at45dbx_write_sector_from_ram(ram_buf);
        at45dbx_write_close();

        return true;
    }

    if (strstr(array[1], "NTP")) {
        //gfx_draw_string_aligned(esp_data, 5, 150, &tiny_sysfont, GFX_COLOR_BLACK, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
        unsigned long timestamp = atol(array[2]);
        rtc_set_time(timestamp);
        return true;
    }

    if (strstr(array[1], "ERROR")) {
        strcpy(esp_error, array[2]);
        wifi_error = true;
        return true;
    }

}

unsigned long over = 0;
ISR(USARTE0_RXC_vect) {
    fifo_push_uint8(&test_fifo_desc, usart_getchar(esp8266_usart));
}

//=require("httpprint"):download("atticus.klintholmes.com", 80, "/demo.php", 0)
//require("httpprint"):download("137.190.2.245", 80, "/api/v1/wifi", 0)

void esp8266_wifi_command(char *data) {
    uint8_t len = strlen(data);
    for (uint8_t i = 0; i < len; i++) {
        usart_putchar(esp8266_usart, data[i]);
    }
}

void esp8266_enter_standby() {
    wifi_ready = false;
    wifi_error = false;
    ioport_set_pin_level(ESP_CH_PD, false);
}
void esp8266_exit_standby() {
    //wifi_ready = false;
    ioport_set_pin_level(ESP_CH_PD, true);
}
