## SaintCon Badge 2015

### Getting Started
#### XMega-A3BU Xplained 
* For PDI programming cut jumper to disconnect JTAG from TDO from PDI DATA

#### Mac OSX
* Download CrossPack AVR Tools [CrossPack](http://www.obdev.com/downloads/crosspack/CrossPack-AVR-20131216.dmg)

#### Linux 
* Get latest version of AVRDUDE
```
$ sudo add-apt-repository ppa:pmjdebruijn/avrdude-release
$ sudo apt-get update
$ sudo apt-get install avrdude
```
* Download the latest [Atmel AVR Toolchain](http://www.atmel.com/tools/atmelavrtoolchainforlinux.aspx)
* Extract tools and add to path
```
$ tar xzf avr8-gnu-toolchain-3.4.5.1522-linux.any.x86.tar
$ export PATH=$PATH:/pathtotoolchain/avr8-gnu/bin/
```

### Contributing 
When contributing to the repository please create a new branch for the code you are working on and create a pull request when you want the code to be merged into the master branch.

```
# git checkout -b kh-esp-branch
```

### Boot-loader

The default boot-loader is now included in the project `badge-2015/xmega/bootloader/atxmega256a3bu_104.hex`

Use the following command to flash boot-loader:

```
$ avrdude -p atxmega256a3bu -P usb -c avrispmkII -U flash:w:atxmega256a3bu_104.hex
```

The xboot boot-loader is also inclueded in the project to allow for OTA updates `badge-2015/xmega/bootloader/xboot-boot.hex`
Example code doing OTA updates over Bluetooth [here](https://github.com/neonquill/nRF24L01P_xmega_lib).

Use the following command to flash the xboot boot-loader:

```
$ avrdude -p atxmega256a3bu -P usb -c avrispmkII -U flash:w:xboot-boot.hex
```

### Compile Application
```
# cd badge-2015/app/gcc
# make
# ./flash
```

### Write Application to ATXMega256A3BU
```
# avrdude -p atxmega256a3bu -P usb -c avrispmkII -U flash:w:app.hex
```

### Badge Test Application
To test the badge hardware checkout the badge-test branch. 

```
# git checkout badge-test
# cd badge-2015/app/gcc
# make
# ./flash
```

### Flashing ESP Firmware
To flash the ESP first you need to enable to USB USART Bridge. Make sure this line is un commented in `conf_usb.h`
```

#define ESP_USB_DEBUG_MODE

...
```
Make and flash the badge with the changes.

To get the badge into ESP flash mode, rotate badge into Name mode and press A. A blue light should flash on the ESP. Connect the badge to your USB and  you are ready to run esptool.py to update the firmware.

```
# python esptool.py --baud 115200 --port /dev/tty.usbmodem1451 write_flash --flash_mode dio --flash_size 32m 0x00000 nodemcu-mqtt-115200-integer-min.bin
```

Once esptool.py has finished. Restart the badge. You can verify that the ESP is running the correct version using the screen command.

```
# screen /dev/tty.usbmodem1451 115200
```  
Once connected with screen you should be able to type commands to the ESP and see the results.

### Creating BMP images
The maximum size of an images that can be compiled into the code.
(height * width) < 32768 
```
sips -s format bmp <file>.<ext> --out image.bmp
python create_image.py ili9341 image.bmp image_name > image_name.h
```