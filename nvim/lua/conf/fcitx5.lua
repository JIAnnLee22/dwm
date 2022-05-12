local M = {}
M.Fcitx5en = function()
				os.execute("fcitx5-remote -c")
end

vim.api.nvim_create_autocmd (
{ 'BufEnter', 'InsertLeave' },
{ callback = M.Fcitx5en }
)
