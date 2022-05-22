vim.cmd [[packadd packer.nvim]]

return require('packer').startup(function()
	-- packer itself
	use 'wbthomason/packer.nvim'

	-- nvim tree
	use {
		'kyazdani42/nvim-tree.lua',
		requires = {
			'kyazdani42/nvim-web-devicons', -- optional, for file icon
		}
	}

	-- colorizer
	use {
		'norcalli/nvim-colorizer.lua',
		config = function()
			require('conf.nvim-colorizer')
		end
	}
	-- lspconfig
	use {
		'neovim/nvim-lspconfig'
	}
	use {
		"williamboman/nvim-lsp-installer",
		{
			"neovim/nvim-lspconfig",
			config = function()
				require("nvim-lsp-installer").setup {}
				local lspconfig = require("lspconfig")
				lspconfig.sumneko_lua.setup {}
			end
		}
	}
	use {
		'karb94/neoscroll.nvim',
		config = function()
			require('neoscroll').setup {}
		end
	}
  -- nvim-cmp
  use 'hrsh7th/cmp-nvim-lsp' -- { name = nvim_lsp }
  use 'hrsh7th/cmp-buffer'   -- { name = 'buffer' },
  use 'hrsh7th/cmp-path'     -- { name = 'path' }
  use 'hrsh7th/cmp-cmdline'  -- { name = 'cmdline' }
  use 'hrsh7th/nvim-cmp'
  -- vsnip
  use 'hrsh7th/cmp-vsnip'    -- { name = 'vsnip' }
  use 'hrsh7th/vim-vsnip'
  use 'rafamadriz/friendly-snippets'
  -- lspkind
  use 'onsails/lspkind-nvim'
end)
