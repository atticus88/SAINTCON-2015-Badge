-- ESP8266-HTTP Library
-- Written 2014 by Tobias Madel (t.maedel@alfeld.de)
-- Licensed unter MIT
-- https://github.com/Manawyrm/ESP8266-HTTP
--                       download(host, port, url, path, tls, callback)
-- callback parameter is the local file name just downloaded.

-- use require("httpDL"):download("myexample.com", 80, "/", "localfile.txt", 0, callback)
-- or for multi usages do the following:
-- instancevar = require("httpDL")
-- instancevar:download("myexample.com", 80, "/", "localfile.txt", 0, callback)
-- instancevar = nil --call this when done with module to free memory


local moduleName = ...
local M = {}

--local inUse = 1

function M:unload()
	if package.loaded[moduleName] ~= nil then
		package.loaded[moduleName]=nil
		moduleName = nil
	end
end

function M:download(host, port, url, path, tls, callback)
	file.remove(path);
	file.open(path, "w+")

	local payloadFound = false
	local httpcon=net.createConnection(net.TCP, tls)
	httpcon:on("receive", function(httpcon, payload)
		if (payloadFound == true) then
			file.write(payload)
			tmr.wdclr()
			file.flush()
		else
			if (string.find(payload,"\r\n\r\n") ~= nil) then
				tmr.wdclr()
				file.write(string.sub(payload,string.find(payload,"\r\n\r\n") + 4))
				tmr.wdclr()
				file.flush()
				payloadFound = true
			end
		end
		tmr.wdclr()
		payload = nil
	end)
	httpcon:on("disconnection", function(httpcon)
		file.close()
		if callback and type(callback) == "function" then
			callback(path)
		else
			print ("disconnection")
		end
		--inUse = nil
		--if package.loaded[moduleName] ~= nil then
		--	package.loaded[moduleName]=nil
		--	moduleName = nil
		--end
		M = nil
		httpcon = nil
	end)
	httpcon:on("connection", function(httpcon)
		httpcon:send("GET "..url.." HTTP/1.0\r\n"..
					"Host: "..host.."\r\n"..
					"Connection: close\r\n"..
					"Accept-Charset: utf-8\r\n"..
					"Accept-Encoding: \r\n"..
--					"User-Agent: Mozilla/4.0 (compatible; esp8266 Lua; Windows NT 5.1)\r\n"..
					"User-Agent: curl/7.9.8 (i686-pc-linux-gnu) libcurl"..
					"Accept: */*\r\n\r\n")
	end)

	httpcon:connect(port, host)

end
return M
