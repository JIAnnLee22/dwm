vim.opt.termguicolors = true
vim.opt.clipboard = 'unnamedplus'

vim.o.number = true
vim.o.relativenumber = true
vim.o.tabstop = 2
vim.o.shiftwidth = 2
vim.o.smartcase = true

vim.o.scrolloff = 10

vim.cmd [[colorscheme catppuccin-mocha]]

-- keymapping
local keymap = vim.api.nvim_set_keymap
local opts = { noremap = true, silent = true }
--Remap space as leader key
keymap("", "<Space>", "<Nop>", opts)
vim.g.mapleader = " "
vim.g.maplocalleader = " "
vim.keymap.set('n', '<space>ntt', ':NvimTreeToggle<CR>', opts)
vim.keymap.set('n', '<space>ntf', ':NvimTreeFocus<CR>', opts)

vim.keymap.set('n', '<space>ntl', ':NvimTreeResize +3<CR>', opts)
vim.keymap.set('n', '<space>nth', ':NvimTreeResize -3<CR>', opts)


local autocmd = vim.api.nvim_create_autocmd
-- auto close nvimtree when last window close
autocmd("BufEnter", {
	nested = true,
	callback = function()
		if #vim.api.nvim_list_wins() == 1 and require('nvim-tree.utils').is_nvim_tree_buf() then
			vim.cmd 'quit'
		end
	end
})
