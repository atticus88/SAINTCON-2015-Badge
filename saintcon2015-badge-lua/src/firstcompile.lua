--Example: require("initcompile")
local flist = file.list()
for n,v in pairs(flist) do
	tmr.wdclr()
	if string.find(n,"^init") == nil then
		if string.find(n,".lua$") ~= nil then
			tmr.wdclr()
			file.remove(string.gsub(n, ".lua$", ".lc"))
			tmr.wdclr()
			print("Compiling: " .. n)
			node.compile(n)
			tmr.wdclr()
			file.remove(n)
			tmr.wdclr()
		end
	else
		tmr.wdclr()
		print("Skipping: " .. n)
	end
end

flist = nil
