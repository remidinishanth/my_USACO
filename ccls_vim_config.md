### Setting up ccls
I use ccls as my C/C++ language server.

In macOS, run the following command to install ccls from Homebrew.

```bash
brew update
brew install ccls
```

In Vim, run :CocConfig to open the configuration file of coc.nvim and add the following lines to it.

```json
{
    "languageserver": {
        "ccls": {
            "command": "ccls",
            "filetypes": [
                "c",
                "cpp",
                "objc",
                "objcpp"
            ],
            "rootPatterns": [
                ".ccls",
                "compile_commands.json",
                ".vim/",
                ".git/",
                ".hg/"
            ],
            "initializationOptions": {
                "cache": {
                    "directory": "/tmp/ccls"
                }
            }
        }
    }
}
```

Ref: https://ianding.io/2019/07/29/configure-coc-nvim-for-c-c++-development/
