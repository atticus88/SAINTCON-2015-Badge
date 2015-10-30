
print("Waiting 5 sec....")
tmr.alarm(0,5000,0, function()
    print("Compile check...")
    if file.open('compilecheck','r') == nil then
        file.close()
        print("compiling")
        require("firstcompile")
    else
        print("No compile needed")
    end
    tmr.wdclr()
    sc_wifievents = require("scwifi")
    tmr.wdclr()
    scmqtt = require("scmqtt")
    tmr.wdclr()
    require("badge").showUUID()
    tmr.wdclr()
    require("badge").showMAC()
    tmr.wdclr()
    sc_wifievents.init()
    tmr.wdclr()
end)
