-- Tabs
vis:map(vis.modes.NORMAL, "<C-w><C-w>", "<C-w>l")
vis:map(vis.modes.NORMAL, "<C-w>q", ":q<Enter>")

-- FZF
vis:map(vis.modes.NORMAL, "<C-f>", ":fzf<Enter>")
