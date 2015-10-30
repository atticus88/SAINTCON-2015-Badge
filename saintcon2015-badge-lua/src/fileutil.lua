local moduleName = ...
local M = {}

function M.savecjson(filedata, filename, mode)
    package.loaded[moduleName]=nil
    moduleName = nil
    if mode == nil then
        mode = "w+" --overwrite
    end
    if filedata and type(filedata) ~= "function" then
        file.open(filename, mode)
        file.write(cjson.encode(filedata))
        file.close()
    end
end

function M.readcjson(filename)
    package.loaded[moduleName]=nil
    moduleName = nil
    if file.open(filename,"r") then
        local filedata = file.read()
        file.close()
        if filedata and type(filedata) == "string" then
            local badgeinfo = cjson.decode(filedata)
            return badgeinfo
        end
    end
    return nil
end

return M
