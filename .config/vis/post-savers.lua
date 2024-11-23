local function basename(path)
	return path:match("(.*/)")
end

vis.events.subscribe(vis.events.FILE_SAVE_POST, function(_file, path)
	-- Remove temporary files
	local dir = basename(path)
	os.execute("/bin/rm -f " .. dir .. ".*vis*")
end)
