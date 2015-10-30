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
        description='Testing application for MQTT and the badge')

    parser.add_argument(
        '--infile', '-i',
        help='Filename data is read from to send to badge.',
        default=os.path.join(getScriptPath(), 'sample.json')
    )

    args = parser.parse_args()

    with open(args.infile) as data_file:
        jsondata = json.load(data_file)

    mqttc = mqtt.Client("python_pub", False)
    mqttc.on_connect = on_connect
    mqttc.on_disconnect = on_disconnect
    mqttc.on_log = on_log
    mqttc.username_pw_set("null", "password")
    mqttc.tls_set("/etc/ssl/certs/Go_Daddy_Class_2_CA.pem")
    mqttc.connect("badger.saintcon.org", 8883, 60)

    mqttc.loop_start()
    sleep(1)
    for badge in jsondata:
        mqttc.publish("to/badge/" + badge['UUID'] +
                      "/hackerscore", badge['hackerscore'], 1, False)
        sleep(1)
        mqttc.publish("to/badge/" + badge['UUID'] +
                      "/hackerrank", badge['hackerrank'], 1, False)
        sleep(1)
        mqttc.publish("to/badge/" + badge['UUID'] +
                      "/location", badge['location'], 1, False)
        sleep(1)
#        mqttc.publish("global/badges/bcastmessage",
#                      badge['bcastmessage'], 1, False)
        sleep(1)
        mqttc.publish(
            "to/badge/" + badge['UUID'] + "/pmessage", badge['pmessage'], 1, False)
        sleep(1)
        mqttc.publish("to/badge/" + badge['UUID'] +
                      "/info", json.dumps(badge['info']), 1, False)

    mqttc.disconnect()
    mqttc.loop_stop()
