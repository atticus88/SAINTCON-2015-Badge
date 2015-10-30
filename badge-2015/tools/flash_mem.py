#!/usr/bin/python
import serial
import argparse
import time

parser = argparse.ArgumentParser(description='Write data to the AT45DBX through the Xmeaga')
parser.add_argument('-f', dest='IMAGE', help='binary of firmware')
parser.add_argument('-d', dest='DEVICE', help='device')
parser.add_argument('-s', dest='BAUD', help='searial baud rate')
parser.add_argument('-t', dest='TYPE', help='image type')

args = parser.parse_args()

# TYPE = 'ESP'
# IMAGE = 'esp_firmware'
# DEVICE = '/dev/tty.usb'
# BAUD = 115200

s = serial.Serial(args.DEVICE, args.BAUD)

with open(args.IMAGE, 'rb') as f:
    byte = f.read(1)
    while byte:
        # Do stuff with byte.
        s.write(byte)
        tmp = s.read()
        #if (byte == tmp):
        	#break
        #time.sleep(.50)
        byte = f.read(1)
	#read_data = f.read()

# size = len(read_data)

# s = serial.Serial(args.DEVICE, args.BAUD)
# # HEADER SCIMG:<IMAGE TYPE>:<SIZE>
# print "SCIMG:%s:%d" % (args.TYPE, size)
# for b in read_data:
# 	s.write(b)

s.close()
