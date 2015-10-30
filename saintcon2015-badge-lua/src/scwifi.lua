local moduleName = ...
local WIFI = {}

function WIFI.init()
    package.loaded[moduleName]=nil
    moduleName = nil

    --Setup the backup DNS servers. NodeMCU obtains from DHCP normally.
    net.dns.setdnsserver("8.8.8.8",0)
    net.dns.setdnsserver("8.8.4.4",1)
    wifi.setmode(wifi.STATION)
    wifi.setphymode(wifi.PHYMODE_N)
    wifi.sta.eventMonStop()
    print("Registering events:")
    wifi.sta.eventMonReg(wifi.STA_GOTIP, function() WIFI:gotip() end)
    print("STA_GOTIP")
    wifi.sta.eventMonReg(wifi.STA_IDLE, function() WIFI:idle() end)
    print("STA_IDLE")
    wifi.sta.eventMonReg(wifi.STA_CONNECTING, function() WIFI:connecting() end)
    print("STA_CONNECTING")
    wifi.sta.eventMonReg(wifi.STA_WRONGPWD, function() WIFI:wrong_password() end)
    print("STA_WRONG_PASSWORD")
    wifi.sta.eventMonReg(wifi.STA_APNOTFOUND, function() WIFI:apnotfound() end)
    print("STA_NO_AP_FOUND")
    wifi.sta.eventMonReg(wifi.STA_FAIL, function() WIFI:connectfail() end)
    print("STA_CONNECT_FAIL")

    print("Starting wifi event monitoring")
    wifi.sta.eventMonStart()
    print("Configuring wifi...")
    wifi.sta.config("zzBadge","8Sevu66Ec6g78f7r",1)
    print("Wifi configured: " .. wifi.sta.getconfig())
end

function WIFI.gotip()
    print("STATION_GOTIP")
    print(wifi.sta.getip())
    tmr.stop(0)
    if scmqtt == nil then
        scmqtt = require('scmqtt')
    end
    scmqtt:init()
end

function WIFI.connecting()
    print("STATION_CONNECTING")
end

function WIFI.wrong_password()
    print("SC+ERROR=STATION_WRONG_PASSWORD")
end

function WIFI.idle()
    print("STATION_IDLE")
end

function WIFI.apnotfound()
    print("SC+ERROR=STATION_AP_NOT_FOUND")
    local retryin = math.random(5,30000)
    print("retrying in:" .. retryin/1000 .. " seconds")
    if scmqtt then
        scmqtt.disconnect()
    end
    tmr.alarm(0,retryin,0, function() wifi.sta.connect() end)
end

function WIFI.connectfail()
    print("SC+ERROR=STATION_CONNECT_FAIL")
end

function WIFI.bounce()
    WIFI.disconnect()
    wifi.sta.connect()
end

function WIFI.disconnect()
    scmqtt.disconnect()
    wifi.sta.disconnect()
end

return WIFI
