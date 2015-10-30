-- https://github.com/DiUS/nodemcu-firmware/wiki/sntp-module-documentation

-- Example: require("scsntp")()
local moduleName = ...

return function ()
	sntp.sync("137.190.2.4",function(ntpstamp)
		print ("SC+NTP="..ntpstamp)
	end)
	package.loaded[moduleName]=nil
	moduleName = nil
end
