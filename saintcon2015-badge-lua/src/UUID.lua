--Self contained fuction returns a sha256 of the flashID + the MAC address.
--Converts result to uppercase then trims to the last 12 of the hash.
--First lines help with garbage collection. By using require instead of load file
--we are able to make the call without specifying the file extension. Thus allowing
--use of compiled lua as well as standard lua.

-- Example usage:
-- myvar = require("UUID")()
-- print(require("UUID")()


local moduleName = ...
return function()
    package.loaded[moduleName]=nil
    module = nil
    return crypto.toHex(crypto.hash("sha256",node.flashid()..wifi.sta.getmac())):sub(-12):upper()
  end
