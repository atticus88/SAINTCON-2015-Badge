/*
 * esp8266.h
 *
 * Created: 12/16/2014 11:02:19 AM
 *  Author: Klint
 */ 
#ifndef ESP8266_H_
#define ESP8266_H_

#include <asf.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "usart.h"
#include "delay.h"
#include "rtc32.h"
#include "fifo.h"

#define USART_SERIAL_EXAMPLE            &USARTE0
#define USART_SERIAL_EXAMPLE_BAUDRATE   115200 //9600 //57600
#define USART_SERIAL_CHAR_LENGTH        USART_CHSIZE_8BIT_gc
#define USART_SERIAL_PARITY             USART_PMODE_DISABLED_gc
#define USART_SERIAL_STOP_BIT           false

#define ESP8266_BUFFER_SIZE             512

#define ESP_NTP_COMMAND					"=require(\"scsntp\")()\r\n"
#define ESP_UUID_COMMAND				"=require(\"badge\").showUUID()\r\n"
#define ESP_MAC_COMMAND 				"=print(\"badge\").showMAC()\r\n"

#define ESP_SC_HACKERSCORE				"=require(\"badge\").showHackerScore()\r\n"
#define ESP_SC_FNAME					"=require(\"badge\").showFirstName()\r\n"
#define ESP_SC_LNAME					"=require(\"badge\").showLastName()\r\n"
#define ESP_SC_HANDLE					"=require(\"badge\").showHandle()\r\n"
#define ESP_SC_ORG						"=require(\"badge\").showOrg()\r\n"
#define ESP_SC_PRIVMSG					"=require(\"badge\").showPmessage()\r\n"

volatile bool wifi_ready;
volatile bool wifi_error;
volatile bool esp_received_fname;
volatile bool esp_received_hcrank;
volatile bool esp_received_hcscore;
volatile bool esp_received_lname;
volatile bool esp_received_handle;
volatile bool esp_received_uuid;
volatile bool esp_received_org;
volatile bool esp_received_pmsg;
volatile bool esp_received_bmsg;
volatile bool esp_received_location;
volatile bool esp_data_ready;
volatile bool esp_data_dirty;

volatile char esp_uuid[14];
volatile char esp_error[64];
volatile char esp_hcrank[64];
volatile char esp_hcscore[64];
volatile char esp_bmsg[141];
volatile char esp_pmsg[141];


#define FIFO_BUFFER_SIZE  1024

volatile char current_location[64]; 

union buffer_element {
	uint8_t  byte;
	uint16_t halfword;
	uint32_t word;
};

union buffer_element test_fifo_buffer[FIFO_BUFFER_SIZE];
fifo_desc_t test_fifo_desc;

uint8_t esp_data[FIFO_BUFFER_SIZE];


// volatile uint8_t uuid[13];
// volatile uint8_t macAddress[18];

void esp8266_init(USART_t* port);

// functions for updating the esp8266
void esp8266_enter_flash_mode(void);
bool esp8266_flash_firmware(void);
// void esp8266_update_firmware(void);

// uint16_t htole16(uint16_t n);
// uint32_t htole32(uint32_t n);
// uint32_t esp_checksum(void *data, unsigned int len);
// bool esp8266_flash_send(ESP_REQUEST_HEADER *header, void *body);
// bool esp8266_flash_mem(uint8_t *buf, uint32_t size, uint32_t address);
// bool esp8266_flash_sync(void);

// bool esp8266_get_version(char *version);
// bool esp8266_get_ip(char *ip);
// bool esp8266_get_mac(char *mac);

// unsigned long esp8266_ntp();

bool esp8266_check_buffer(void);
bool esp8266_parse_data(void);

// bool esp8266_get_result(char *success, char *error, char stop, char *data);
// bool esp8266_get_data(char *success, char *error, char *buffer);

void esp8266_wifi_command(char *data);
// bool esp8266_wifi_connected(void);
// bool esp8266_wifi_connect(void);
// bool esp8266_wifi_connected(void);


void esp8266_enter_standby(void);
void esp8266_exit_standby(void);

void clear_buffer(char *buffer);
// bool esp8266_wait_for(char *success, char *error);
// bool esp8266_wait_for_e(char *success, char *error, char *e);
// unsigned long esp82661_ntp(void);
// unsigned char esp8266_post_data(char* ip, char* uri, char* host, char* data);
//bool esp8266_wifi_dissconnect();

#endif
