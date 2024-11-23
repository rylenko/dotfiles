-- Globals
line_max_length = 79
overlong_lines_max_count = 10

vis.events.subscribe(vis.events.FILE_SAVE_PRE, function(file, _path)
	local overlong_lines = {}

	for i=1, #file.lines do
		-- Trim trailing whitespace
		if string.match(file.lines[i], '[ \t]$') then
			file.lines[i] = string.gsub(file.lines[i], '[ \t]*$', '')
		end

		-- Get overlong lines
		if #overlong_lines < overlong_lines_max_count then
			if string.len(file.lines[i]) > line_max_length then
				table.insert(overlong_lines, i)
			end
		end
	end

	-- Display overlong line numbers
	if #overlong_lines > 0 then
		local are_or_is = (function(x)
			if #overlong_lines > 1 then return "are" else return "is" end
		end)(#overlong_lines)
		vis:info(string.format(
			"%d lines %s longer than %d characters: %s.",
			#overlong_lines,
			are_or_is,
			line_max_length,
			table.concat(overlong_lines, ", ")
		))
	end
end)
