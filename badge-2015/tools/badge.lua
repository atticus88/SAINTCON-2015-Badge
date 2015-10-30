-- Usage require("badge").showHackerScore()


local moduleName = ...
local M = {}

-- Usage require("badge").showHackerScore()
function M.showHackerScore()
    print(badgevars.hackerscore)
    unload()
end

-- Usage require("badge").showPmessage()
function M.showPmessage()
    print(badgevars.pmessage)
    unload()
end

-- Usage require("badge").showFirstName()
function M.showFirstName()
    print(badgevars.info.firstname)
    unload()
end

-- Usage require("badge").showLastName()
function M.showLastName()
    print(badgevars.info.lastname)
    unload()
end

-- Usage require("badge").showHandle()
function M.showHandle()
    print(badgevars.info.handle)
    unload()
end

local function unload()
    package.loaded[moduleName]=nil
    moduleName = nil
end

return M
