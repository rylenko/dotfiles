require("vis")
require("plugins")
require("post-savers")
require("pre-savers")

vis.events.subscribe(vis.events.INIT, function()
	-- Global configuration
	require("mappings")
	require("themes")
end)

vis.events.subscribe(vis.events.WIN_OPEN, function(win)
	-- Per window configuration
	require("options")
end)
