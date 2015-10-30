-- Usage require("badge").showHackerScore()


local moduleName = ...
local M = {}

function M.showUUID()
    print("SC+UUID="..require("UUID")())
    M.unload()
end

function M.showMAC()
    print("SC+MAC="..wifi.sta.getmac())
    M.unload()
end

-- Usage require("badge").showHackerScore()
function M.showHackerScore()
    print("SC+HCSCORE="..badgevars.hackerscore)
    M.unload()
end

-- Usage require("badge").showBcastMessage()
function M.showBcastMessage()
    print("SC+BMSG="..badgevars.pmessage)
    M.unload()
end

-- Usage require("badge").clearBcastMessage()
function M.clearBcastMessage()
    badgevars.bcastmessage = "nil"
end

-- Usage require("badge").showPmessage()
function M.showPmessage()
    print("SC+PMSG="..badgevars.pmessage)
    M.unload()
end

-- Usage require("badge").clearPmessage()
function M.clearPmessage()
    badgevars.pmessage = "nil"
end

-- Usage require("badge").showFirstName()
function M.showFirstName()
    print("SC+FNAME="..badgevars.info.first_name)
    M.unload()
end

-- Usage require("badge").showLastName()
function M.showLastName()
    print("SC+LNAME="..badgevars.info.last_name)
    M.unload()
end

-- Usage require("badge").showOrg()
function M.showOrg()
    print("SC+ORG="..badgevars.info.org)
    M.unload()
end

-- Usage require("badge").showHandle()
function M.showHandle()
    print("SC+HANDLE="..badgevars.info.handle)
    M.unload()
end

function M.unload()
    package.loaded[moduleName]=nil
    moduleName = nil
    M = nil
end

return M
