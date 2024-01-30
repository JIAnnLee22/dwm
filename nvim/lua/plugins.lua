vim.cmd [[packadd packer.nvim]]

return require('packer').startup(function(use)
	-- lsp
	use { "williamboman/mason.nvim" }
	use { "williamboman/mason-lspconfig.nvim" }
	use { "neovim/nvim-lspconfig" }

	-- lsp completion
	use { 'hrsh7th/nvim-cmp' }
	use { 'hrsh7th/cmp-nvim-lsp' }
	use { 'hrsh7th/cmp-path' }
	use { 'hrsh7th/cmp-cmdline' }
	-- For vsnip users.
	use { 'hrsh7th/cmp-vsnip' }
	use { 'hrsh7th/vim-vsnip' }

	-- colorscheme
	use { 'folke/tokyonight.nvim' }
	use { "catppuccin/nvim", as = "catppuccin" }

	-- smooth scroller
	use 'karb94/neoscroll.nvim'

	-- nvim-tree
	use {
		'nvim-tree/nvim-tree.lua',
		requires = {
			'nvim-tree/nvim-web-devicons', -- optional, for file icons
		},
		tag = 'nightly'               -- optional, updated every week. (see issue #1193)
	}
	use { 'akinsho/flutter-tools.nvim', requires = 'nvim-lua/plenary.nvim' }
	use {
		'akinsho/flutter-tools.nvim',
		requires = {
			'nvim-lua/plenary.nvim',
			'stevearc/dressing.nvim',   -- optional for vim.ui.select
		},
	}
	use {
		'nvim-telescope/telescope.nvim', tag = '0.1.5',
		-- or                            , branch = '0.1.x',
		requires = { {'nvim-lua/plenary.nvim'} }
	}
end)
