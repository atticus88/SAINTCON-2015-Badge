local moduleName = ...
local MQ = {}

local mc
local UUID = require("UUID")()
local fromTopic = "from/badge/" .. UUID
local toTopic = "to/badge/" .. UUID
local discheck = 0
local mqttstate = 0

function MQ.init()
    if mqttstate == 0 or mc == nil then
        print("starting: SaintCon mqtt process")
        -- TODO change login info
        -- TODO turn on TLS after Mosquitto is up and running
        local mqttcreds = require("fileutil").readcjson("creds.json")
        if mqttcreds == nil then
            mqttcreds = {}
            mqttcreds.username = "null"
            mqttcreds.password = "password"
            mqttcreds.server = "badger.saintcon.org"
        end
        -- Lua: mqtt.Client(clientid, keepalive, user, pass, clean_session)
        mc=mqtt.Client(UUID, 120, mqttcreds.username, mqttcreds.password, 0)

        mc:on("connect",function(m)
            tmr.stop(2)
            --TODO cleanup print line not necessarily needed in production.
    	    -- print("SC+WIFI=READY\n") --needs new line
            -- Subscribe to multiple topics at one time via table.
            -- Subscribing via multiple calls can lead to a reboot.
            m:subscribe(toTopic.."/#",1,function()
                m:subscribe("global/badges/bcastmessage",1,function()
                    MQ:frombadge("macaddr",wifi.sta.getmac(),function()
                        print("SC+WIFI=READY\n")
                        end)
                    end)
            end)
            --m:subscribe({[toTopic .. "/#"]=0,["global/badges/commands"]=0,["global/badges/bcastmessage"]=0},function() print("subscribe") end)
        end)

        mc:on("offline", function(m)
            --TODO clean this message up. Probably not needed for production.
            print("disconnect to broker..." .. node.heap())
            discheck = 1 + discheck
            if discheck > 5 then
                discheck = 0
                m:close()
                local retryin = math.random(5000,30000)
                print("retrying in:" .. retryin/1000 .. " seconds")
                tmr.alarm(2,retryin,0, function() m:connect(mqttcreds.server,1883,0,1) end)
            end
            --TODO track disconnects and backoff if needed
        end)

        mc:on("message", dispatch )
        -- Lua: mqtt:connect( host, port, secure, auto_reconnect, function(client) )
        mc:connect(mqttcreds.server,1883,0,1)
        --allow cleanup of creds
        mqttcreds = nil
        mqttstate = 1
    else
        print("previously connected")
    end
end

function MQ.unload()
    --tmr.stop(1)
    MQ.disconnect()
    package.loaded[moduleName]=nil
    moduleName = nil
end

-- Call this function before setting module to nil.
function MQ.disconnect()
    mqttstate = 0
    if mc ~= nil then
        mc:close()
        mc = nil
    end
end

local m_dis={}
function dispatch(m,t,pl)
    if pl~=nil and m_dis[t] then
        m_dis[t](m,pl)
    end
end

-- payload(json): {"cmd":xxx,"content":xxx}
function badgeglobalcommandfunc(m,pl)
    --TODO remove print line below
    print("get1: "..pl)
    local pack = cjson.decode(pl)
    if pack.content then
        if pack.cmd == "open" then file.open(pack.content,"w+")
            elseif pack.cmd == "UUID" then m:publish(fromTopic.."/UUID", UUID, 1,1, puback)
            elseif pack.cmd == "write" then file.write(pack.content)
            elseif pack.cmd == "close" then file.close()
            elseif pack.cmd == "remove" then file.remove(pack.content)
            elseif pack.cmd == "run" then dofile(pack.content)
            elseif pack.cmd == "compile" then node.compile(pack.content)
            elseif pack.cmd == "heap" then m:publish(fromTopic.."/heap", node.heap() ,1,0, puback)
            elseif pack.cmd == "espinfo" then m:publish(fromTopic.."/espinfo", espinfo() ,1,1, puback)
            elseif pack.cmd == "update" then require('update').run(0)
        end
    end
end
m_dis["global/badges/commands"]=badgeglobalcommandfunc
m_dis[toTopic .. "/commands"]=badgeglobalcommandfunc

function badgehackerscore(m,pl)
    if pl ~= nil then
        if type(pl) ~= "userdata" then
            print("SC+HCSCORE="..pl)
        end
    end
end
m_dis[toTopic .. "/hackerscore"]=badgehackerscore

function badgehackerrank(m,pl)
    if pl ~= nil then
        if type(pl) ~= "userdata" then
            print("SC+HCRANK="..pl)
        end
    end
end
m_dis[toTopic .. "/hackerrank"]=badgehackerrank

function badgetopten(m,pl)
    if pl ~= nil then
        if type(pl) ~= "userdata" then
            print("SC+TOPTEN="..pl)
        end
    end
end
m_dis[toTopic .. "/topten"]=badgetopten

function mselocation(m,pl)
    --TODO Find how Klint wants this formatted.
    if pl ~= nil then
        if type(pl) ~= "userdata" then
            print("SC+MSELOC="..pl)
        end
    end
end
m_dis["to/badge/".. wifi.sta.getmac() .. "/location"]=mselocation
m_dis[toTopic .. "/location"]=mselocation

function bcastmessage(m,pl)
    if pl ~= nil then
        if type(pl) ~= "userdata" then
            print("SC+BMSG="..pl)
        end
    end
end
m_dis["global/badges/bcastmessage"]=bcastmessage

function pmessage(m,pl)
    if pl ~= nil then
        if type(pl) ~= "userdata" then
            print("SC+PMSG="..pl)
        end
    end
end
m_dis[toTopic .. "/pmessage"]=pmessage

function badgeinfo(m,pl)
    local info = cjson.decode(pl)
    if info ~= nil then
        if info.first_name ~= nil then
            if type(info.first_name) == "string" then
                print("SC+FNAME="..info.first_name)
            end
        end
        if info.last_name ~= nil then
            if type(info.last_name) == "string" then
                print("SC+LNAME="..info.last_name)
            end
        end
        if info.org ~= nil then
            if type(info.org) == "string" then
                print("SC+ORG="..info.org)
            end
        end
        if info.handle ~= nil then
            if type(info.handle) == "string" then
                print("SC+HANDLE="..info.handle)
            end
        end
    end
    info = nil
end
m_dis[toTopic .. "/info"]=badgeinfo

function espinfo()
    local info = {}
    info.majorVer, info.minorVer, info.devVer, info.chipid, info.flashid, info.flashsize, info.flashmode, info.flashspeed = node.info()
    return cjson.encode(info)
end

function MQ:frombadge(subtopic,data,callback)
    if callback and type(callback) == "function" then
        mc:publish(fromTopic.."/"..subtopic, data,1,0,callback)
    else
        mc:publish(fromTopic.."/"..subtopic, data,1,0,puback)
    end
end

function puback(conn)
    print("SC+PUBACK")
end

return MQ

-- usage:
-- another client(pc) subscribe to /topic2, will receive the test.lua content.
-- and publish below message to /topic1
-- {"cmd":"open","content":"test.lua"}
-- {"cmd":"write","content":"print([[hello world]])\n"}
-- {"cmd":"write","content":"print(\"hello2 world2\")\n"}
-- {"cmd":"run","content":"test.lua"}
-- {"cmd":"read","content":"test.lua"}
