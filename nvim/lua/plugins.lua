vim.cmd [[packadd packer.nvim]]

return require('packer').startup(function()
				-- packer itself
				use  'wbthomason/packer.nvim'

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
			end)
