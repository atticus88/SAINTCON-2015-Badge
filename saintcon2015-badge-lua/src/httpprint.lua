-- Based on the HTTP library
-- ESP8266-HTTP Library
-- Written 2014 by Tobias Madel (t.maedel@alfeld.de)
-- Licensed unter MIT
-- https://github.com/Manawyrm/ESP8266-HTTP

--                       download(host, port, url, tls)
-- use require("httpprint"):download("myexample.com", 80, "/", 0)

local moduleName = ...
local M = {}

local httpcon

function M:download(host, port, url, tls)
	local payloadFound = false
	httpcon=net.createConnection(net.TCP, tls)
	httpcon:on("receive", function(httpcon1, payload)
		if (payloadFound == true) then
			print(payload)
		else
			if (string.find(payload,"\r\n\r\n") ~= nil) then
				print(string.sub(payload,string.find(payload,"\r\n\r\n") + 4))
				payloadFound = true
			end
		end
		payload = nil
	end)

	httpcon:on("disconnection", function(httpcon1)
		payloadFound = nil
		httpcon:close()
		if package.loaded[moduleName] ~= nil then
			package.loaded[moduleName]=nil
			moduleName = nil
		end
		httpcon = nil
		M = nil
	end)

	httpcon:on("connection", function(httpcon1)
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
