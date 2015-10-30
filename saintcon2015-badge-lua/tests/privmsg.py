#!/usr/bin/python
# -*- coding: utf-8 -*-
import paho.mqtt.client as mqtt
import json
import argparse
import os
import sys
from pprint import pprint
from time import sleep


def on_connect(client, userdata, flags, rc):
    print("Connected..." + str(rc) + "\n")


def on_disconnect(client, userdata, rc):
    print("Disconnected...\n")


def on_log(client, userdata, level, buf):
    print(buf)


def getScriptPath():
    return os.path.dirname(os.path.realpath(sys.argv[0]))

if __name__ == '__main__':

    parser = argparse.ArgumentParser(
        description='Program up send private message.')

    parser.add_argument(
        'UUID',
        help='Badge ID to upgrade',
        nargs='?')
    parser.add_argument(
        'pmsg',
        help='Message text.',
        nargs='?')
        

    args = parser.parse_args()

    mqttc = mqtt.Client("python_pub", False)
    mqttc.on_connect = on_connect
    mqttc.on_disconnect = on_disconnect
    mqttc.on_log = on_log
    mqttc.username_pw_set("null", "password")
    mqttc.tls_set("/etc/ssl/certs/Go_Daddy_Class_2_CA.pem")
    mqttc.connect("badger.saintcon.org", 8883, 60)

    mqttc.loop_start()

    sleep(1)
    mqttc.publish("to/badge/" + args.UUID +
                "/pmessage", args.pmsg, 1, False)


    mqttc.disconnect()
    mqttc.loop_stop()
