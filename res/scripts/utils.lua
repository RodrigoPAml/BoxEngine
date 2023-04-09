function to_string(table, tab)
	if tab == nil then 
		tab = ""
	end
	
	local ttype = type(table)

	if ttype ~= "table" then 
		if ttype == "string" then
			return table
		elseif ttype == "number" then 
			return tostring(table)
		elseif ttype == "function" then
			return "function"
		elseif ttype == "boolean" then
			if table == true then 
				return "true"
			else 
				return "false"
			end
		end
	end

	local content = "{\n"

	for k, v in pairs(table) do
		local value = "unknow"
		local t = type(v)

		if t == "string" then
			value = v
		elseif t == "number" then 
			value = tostring(v)
		elseif t == "function" then
			value = "function"
		elseif t == "boolean" then
			if v == true then 
				value =  "true"
			else 
				value = "false"
			end
		elseif t == "table" then 
			value = to_string(v, tab .. "  ")
		end

		content = content .. "  " .. tab .. k .. " : " .. value .. ",\n"
    end

    return content .. tab .. "}"
end

_utils_.to_string = to_string