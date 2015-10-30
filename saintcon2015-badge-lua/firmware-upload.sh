#!/bin/bash

PORT=ttyUSB0


BAUD=115200
#FLASH_SIZE=8m #ESP-12
FLASH_SIZE=32m #ESP-12e

function usage()
{
    echo "Script used to upload firmware files."
    echo ""
    echo "firmware-upload.sh"
    echo "\t-h --help"
    echo "\t--port=$PORT"
    echo "\t--baud=$BAUD"
    echo "\t--image=$IMAGENAME"
    echo "\t--flash_size=$FLASH_SIZE"
    echo ""
}

while [ "$1" != "" ]; do
    PARAM=`echo $1 | awk -F= '{print $1}'`
    VALUE=`echo $1 | awk -F= '{print $2}'`
    case $PARAM in
        -h | --help)
            usage
            exit
            ;;
        --port)
            PORT=$VALUE
            ;;
        --baud)
            BAUD=$VALUE
            ;;
        --image)
            IMAGENAME=$VALUE
            ;;
        --flash_size)
            FLASH_SIZE=$VALUE
            ;;
        *)
            echo "ERROR: unknown parameter \"$PARAM\""
            usage
            exit 1
            ;;
    esac
    shift
done


DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

$DIR/esptool/esptool.py \
  --port /dev/$PORT \
  --baud $BAUD \
  write_flash --flash_mode dio --flash_size $FLASH_SIZE --flash_freq 40m \
  0x00000 $IMAGENAME
