/**
 * \file
 *
 * \brief USB configuration file for CDC application
 *
 * Copyright (c) 2011-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef _CONF_USB_H_
#define _CONF_USB_H_

#include "compiler.h"
//#define ESP_USB_DEBUG_MODE

/**
 * USB Device Configuration
 */
//@{
//! Device definition (mandatory)
#define  USB_DEVICE_VENDOR_ID               USB_VID_ATMEL
#define  USB_DEVICE_PRODUCT_ID              USB_PID_ATMEL_XPLAINED
#define  USB_DEVICE_MAJOR_VERSION           1
#define  USB_DEVICE_MINOR_VERSION           0
#define  USB_DEVICE_POWER                   100 // Consumption on Vbus (mA)
#define  USB_DEVICE_ATTR                    \
	(USB_CONFIG_ATTR_SELF_POWERED)
// (USB_CONFIG_ATTR_BUS_POWERED)
// (USB_CONFIG_ATTR_REMOTE_WAKEUP|USB_CONFIG_ATTR_SELF_POWERED)
// (USB_CONFIG_ATTR_REMOTE_WAKEUP|USB_CONFIG_ATTR_BUS_POWERED)

//! USB Device string definitions (Optional)
#define  USB_DEVICE_MANUFACTURE_NAME        "ATMEL ASF"
#define  USB_DEVICE_PRODUCT_NAME            "CDC Virtual Com"
//#define  USB_DEVICE_SERIAL_NAME
// #define  USB_DEVICE_GET_SERIAL_NAME_POINTER cdc_serial_number
// #define  USB_DEVICE_GET_SERIAL_NAME_LENGTH  12


/**
 * Device speeds support
 * Low speed not supported by CDC
 */
//@{
//! To authorize the High speed
#if (UC3A3||UC3A4)
#define  USB_DEVICE_HS_SUPPORT
#endif
//@}

 /**
 * USB Device Callbacks definitions (Optional)
 * @{
 */
// #define  UDC_VBUS_EVENT(b_vbus_high)
// #define  UDC_SOF_EVENT()                  main_sof_action()
// #define  UDC_SUSPEND_EVENT()              main_suspend_action()
// #define  UDC_RESUME_EVENT()               main_resume_action()
// #define  UDC_VBUS_EVENT(b_vbus_high)
// #define  UDC_SOF_EVENT()
// #define  UDC_SUSPEND_EVENT()
// #define  UDC_RESUME_EVENT()
//! Mandatory when USB_DEVICE_ATTR authorizes remote wakeup feature
// #define  UDC_REMOTEWAKEUP_ENABLE()
// #define  UDC_REMOTEWAKEUP_DISABLE()
//! When a extra string descriptor must be supported
//! other than manufacturer, product and serial string
// #define  UDC_GET_EXTRA_STRING()
//@}

//@}


/**
 * USB Interface Configuration
 */
//@{
/**
 * Configuration of CDC interface
 */
//@{
 //! Define two USB communication ports

#ifdef ESP_USB_DEBUG_MODE

#define  UDI_CDC_PORT_NB 1

//! Interface callback definition
#define  UDI_CDC_ENABLE_EXT(port)            	main_cdc_enable(port)
#define  UDI_CDC_DISABLE_EXT(port)			  	main_cdc_disable(port)
#define  UDI_CDC_RX_NOTIFY(port)			   	uart_rx_notify(port)
#define  UDI_CDC_SET_CODING_EXT(port,cfg)	   	uart_config(port,cfg)
#define  UDI_CDC_SET_DTR_EXT(port,set)         	cdc_set_dtr(set)
#define  UDI_CDC_SET_RTS_EXT(port,set)

#else

//! Interface callback definition
#define  UDI_CDC_ENABLE_EXT(port)             true
#define  UDI_CDC_DISABLE_EXT(port)
#define  UDI_CDC_RX_NOTIFY(port)
#define  UDI_CDC_SET_CODING_EXT(port,cfg)
#define  UDI_CDC_SET_DTR_EXT(port,set)         cdc_set_dtr(set)
#define  UDI_CDC_SET_RTS_EXT(port,set)

#define  UDI_CDC_DEFAULT_RATE             115200
#define  UDI_CDC_DEFAULT_STOPBITS         CDC_STOP_BITS_1
#define  UDI_CDC_DEFAULT_PARITY           CDC_PAR_NONE
#define  UDI_CDC_DEFAULT_DATABITS         8


#endif

/**
 * Define it when the transfer CDC Device to Host is a low rate (<512000 bauds)
 * to reduce CDC buffers size.
 */
//#define  UDI_CDC_LOW_RATE

//! Default configuration of communication port

//@}
//@}


/**
 * USB Device Driver Configuration
 */
//@{
//@}

#define GAMEPAD_MODE
#ifdef GAMEPAD_MODE

#define UDI_HID_KBD_ENABLE_EXT() my_callback_keyboard_enable()
extern bool my_callback_keyboard_enable(void);
#define UDI_HID_KBD_DISABLE_EXT() my_callback_keyboard_disable()
extern void my_callback_keyboard_disable(void);
#define  UDI_HID_KBD_CHANGE_LED(value)  //ui_kbd_led(value)
#include "udi_hid_kbd_conf.h"
#endif

/*
 * The includes of classes and other headers must be done at the end of this
 * file to avoid compile error.
 */
//#include "udi_cdc_conf.h"
//#include "cdc.h"
//#include "esp8266_usb_bridge.h"

#endif // _CONF_USB_H_
