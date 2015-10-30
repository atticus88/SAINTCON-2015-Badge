#!/bin/bash

PORT=ttyUSB0
BAUD=9600

function usage()
{
    echo "Script used to upload lua files."
    echo ""
    echo "lua-upload.sh"
    echo "\t-h --help"
    echo "\t--port=$PORT"
    echo "\t--baud=$BAUD"
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
        *)
            echo "ERROR: unknown parameter \"$PARAM\""
            usage
            exit 1
            ;;
    esac
    shift
done


DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

#Must change pwd to location of source. Script doesn't properly strip file names
#from the directory path when supplied as an absolute path.
cd $DIR/src/
$DIR/nodemcu-uploader/nodemcu-uploader.py \
  --port /dev/$PORT \
  --baud $BAUD \
  upload --compile --restart *.lua
