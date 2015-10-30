-- https://github.com/annejan/nodemcu-lua-watch/blob/master/ntp.lua
-- Example: require("ntp"):show_ustamp()
-- Unused by the badge

local moduleName = ...
local M = {}


local hour=0
local minute=0
local second=0
local lastsync=0
local ustamp=0
local tz=-6
local udptimer=2
local udptimeout=1000
local ntpserver="137.190.2.4"
local sk=nil

function M.sync(self, callback)
	local request=string.char( 227, 0, 6, 236, 0,0,0,0,0,0,0,0, 49, 78, 49, 52,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	)
	sk=net.createConnection(net.UDP, 0)
	sk:on("receive",function(sck,payload)
		sck:close()
		lastsync=M:calc_stamp(payload:sub(41,44))
		M:set_time()
		if callback and type(callback) == "function" then
			callback(M)
		end
		sck = nil
	end)
	sk:connect(123,ntpserver)
	tmr.alarm(udptimer,udptimeout,0,function()
		sk:close()
	 	sk = nil
	end)
	sk:send(request)
end

function M.calc_stamp(self, bytes)
	local highw,loww,ntpstamp
	highw = bytes:byte(1) * 256 + bytes:byte(2)
	loww = bytes:byte(3) * 256 + bytes:byte(4)
	ntpstamp=( highw * 65536 + loww ) + ( tz * 3600)	-- NTP-stamp, seconds since 1.1.1900
	M.ustamp=ntpstamp - 1104494400 - 1104494400 		-- UNIX-timestamp, seconds since 1.1.1970
	return(M.ustamp)
end

function M.set_time(self)
	hour = M.ustamp % 86400 / 3600
	minute = M.ustamp % 3600 / 60
	second = M.ustamp % 60
end

function M.show_time()
	return(string.format("%02u:%02u:%02u",hour,minute,second))
end

function M.run(self,t,uinterval,sinterval,server)
	if server then ntpserver = server end
	lastsync = sinterval * 2 * -1	-- force sync on first run
	tmr.alarm(t,uinterval * 1000,1,function()
		M.ustamp = M.ustamp + uinterval
		M:set_time()
		if lastsync + sinterval < M.ustamp then
			M:sync()
		end
	end)
end

function M.show_ustamp(self)
	package.loaded[moduleName]=nil
	module = nil
	M:sync(function(M) print(M.ustamp ) end)
end

return M
