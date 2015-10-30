# SaintCon 2015 Badge Wifi module - NodeMCU
Lua files contained in this directory are used on the SaintCon 2015 badge to control wifi access. Instructions are below on how to flash the latest NodeMCU firmware and upload your own Lua files.
 
[![Build Status](https://semaphoreci.com/api/v1/projects/71ad16a3-5ec5-4e16-957a-e54555ed95f2/576513/badge.svg)](https://semaphoreci.com/jkarras/saintcon2015-badge-lua)

Firmware downloads hosted at [https://badger.saintcon.org/esp/images/](https://badger.saintcon.org/esp/images/)



## Firmware Flashing instructions
1. Pull GPIO0 to GND.
2. Reset module by pulling RST to ground temporarily.
3. Run flash uploader program. See tools section for info.
4. Let GPIO0 float and reset ESP module.

If using a badge instructions are different. Contact Klint for details.

## Connecting
- Default NodeMCU baud is 9600.
- Default NodeMCU baud on SaintCon edition is 115200 - This may change. See downloads link on left for various ESP firmware builds.

## Lua Upload instructions
- Use custom upload script lua-upload.sh to upload in bulk.
- Use python script [nodemcu-uploader](https://github.com/kmpm/nodemcu-uploader)
- [ESPlorer](https://github.com/4refr0nt/ESPlorer)
- Upload manually via UART

## Tools
- [esptool](https://github.com/themadinventor/esptool) - Python tool similar to ESP8266flasher but cross platform.
- [nodemcu-uploader](https://github.com/kmpm/nodemcu-uploader) - Used to manipulate files on the nodemcu flash file system.
- [ESPlorer](https://github.com/4refr0nt/ESPlorer) - Java based IDE for manipulating Lua files on the file system.
- [ESP8266flasher](https://github.com/nodemcu/nodemcu-flasher) - Windows only firmware flashing tool.
- [spiffy](https://github.com/xlfe/spiffy) - Tool to create spiffs file systems for burning directly to esp8266.

## Useful Links
- [NodeMCU API EN](https://github.com/nodemcu/nodemcu-firmware/wiki/nodemcu_api_en)
- [Lua Cheat Sheet](http://thomaslauer.com/download/luarefv51.pdf)
- [NodeMCU unoffcial FAQ](http://www.esp8266.com/wiki/doku.php?id=nodemcu-unofficial-faq)
- [NodeMCU Build farm](http://frightanic.com/nodemcu-custom-build/)