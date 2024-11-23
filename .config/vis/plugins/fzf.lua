cmd = "find / 2>/dev/null | fzf --height=50%"

vis:command_register("fzf", function(_argv, _force, _win, _selection, _range)
	-- Execute command
	local file = io.popen(cmd)
	local output = file:read()
	local _success, _msg, status = file:close()

	-- Load file and redraw window
	if status == 0 then
		vis:feedkeys(string.format(":e %s", output))
	else
		vis:info(string.format(
			"fzf-open: Exited with %d status code.",
			status
		))
	end
	vis:feedkeys("<vis-redraw>")
	return true;
end)
