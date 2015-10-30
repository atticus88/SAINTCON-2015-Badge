local moduleName = ...
local M = {}
local dlcount = 0
local ppcount = 0

-- TODO figure out a callback to show processing is done so a reboot can happen.

local updatefile = "update.json"
local httpDL1 = require("httpDL")
local filelist = {}


local function dlcb(d)
    file.open(updatefile, "r")
    filelist = cjson.decode(file.read())
    file.close()
    filename, cmd = next(filelist)
    print(filename,cmd)
    tmr.wdclr()
    httpDL1:download("badger.saintcon.org", 80, "/esp/"..filename, filename, 0, postprocess)
end

function M.run(connectwifi)
    print("SC+UPGRADEINIT")
    --Disconnect MQTT processing and destroy modules.
    if scmqtt ~= nil then
        --scmqtt.unload()
        scmqtt = nil
    end

    if sc_wifievents ~= nil then
        wifi.sta.eventMonStop()
    end
    --TODO verify wifi connection. If non-existant make connection.
    if connectwifi == 1 then
        wifi.sta.eventMonStop()
        wifi.sta.eventMonReg(wifi.STA_GOTIP, initdownload)
        net.dns.setdnsserver("8.8.8.8",0)
        net.dns.setdnsserver("8.8.4.4",1)
        wifi.setmode(wifi.STATION)
        wifi.setphymode(wifi.PHYMODE_N)
        wifi.sta.eventMonStart()
        wifi.sta.config("zzBadge","8Sevu66Ec6g78f7r",1)
    else
        initdownload()
    end

end

function initdownload()
    file.remove('compilecheck')
    httpDL1:download("badger.saintcon.org", 80, "/esp/"..updatefile, updatefile, 0, dlcb)
end

function postprocess(filename)
    filename, cmd = next(filelist,filename)
    if filename ~= nil then
        print(filename,cmd)
        tmr.wdclr()
        httpDL1:download("badger.saintcon.org", 80, "/esp/"..filename, filename, 0, postprocess)
    else
        print("download done")
        print("SC+UPGRADERESTART")
        node.restart()
    end
end

return M
