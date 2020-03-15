set nocompatible              " be iMproved, required
filetype off                  " required

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
set rtp+=/usr/local/opt/fzf

call vundle#begin()
" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')

" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'

Plugin 'vim-airline/vim-airline'
Plugin 'vim-airline/vim-airline-themes'

Plugin 'scrooloose/nerdtree'
Plugin 'dense-analysis/ale'

Plugin 'nvie/vim-flake8'

Plugin 'valloric/youcompleteme'

Plugin 'junegunn/fzf.vim'
Plugin 'mileszs/ack.vim'

Plugin 'ReplaceWithRegister'

Plugin 'tpope/vim-commentary'
Plugin 'tpope/vim-surround'
Plugin 'tpope/vim-repeat'
Plugin 'tpope/vim-fugitive'

" All of your Plugins must be added before the following line
call vundle#end()            " required
filetype plugin indent on    " required
" To ignore plugin indent changes, instead use:
"filetype plugin on
"
" Brief help
" :PluginList       - lists configured plugins
" :PluginInstall    - installs plugins; append `!` to update or just :PluginUpdate
" :PluginSearch foo - searches for foo; append `!` to refresh local cache
" :PluginClean      - confirms removal of unused plugins; append `!` to auto-approve removal
"
" see :h vundle for more details or wiki for FAQ
" Put your non-Plugin stuff after this line





" Try not to put settings you don’t understand in your .vimrc

set clipboard=unnamed " copy vim clipboard to system clipboard
set backspace=indent,eol,start "to make backspace work as expected
set nocompatible     " removes incompatibility with the original vi
set expandtab        " convert tabs to spaces
set shiftwidth=4     " no of spaces inserted for indentation
set tabstop=4        " 1 tab = 4 spaces
set softtabstop=4    " with <BS> pretend like tab is removed, even if spaces
set smartindent      " does the right thing (mostly) in programs
set autoindent       " copy the indentation from the previous line
set cindent          " stricter rules for C programs
set history=1000     " command history options
set number           " turn absolute line numbers on
set relativenumber   " turn relative line numbers on
set ruler            " displays line, col number at bottom of window
set noerrorbells     " no beep occurs when an error message is displayed
set vb t_vb=         " no flash will ever occur vb is visualbell
set showcmd          " display incomplete commands
set showmode         " show current mode at the bottom of window
set mouse=a          " enable mouse in all modes
set cursorline       " highlight current line
set wildmenu         " visual autocomplete for command menu
set nowrap           " disable soft wrap for lines 
set hlsearch         " highlight search results
set incsearch        " incremental search
set splitbelow       " split opens at bottom
set splitright       " new vertical split opens right

syntax enable        " keep your current color settings
set background=dark
let g:solarized_termcolors=256
colorscheme solarized

" Smart way to move between windows in split
map <C-j> <C-W>j
map <C-k> <C-W>k
map <C-h> <C-W>h
map <C-l> <C-W>l

let mapleader = ","  " comma is leader

nnoremap <leader><space> :noh<CR> " turn off search highlight
nmap <Leader>f :Files<CR>

"autocmd filetype cpp nnoremap <F5> :w <bar> !g++ -std=c++17 -Wshadow -Wall % -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -g

nnoremap <F5> :w <bar> !g++ -DLOCAL -std=c++17 -Wshadow -Wall % -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -g <CR>

nnoremap <F6> :!./a.out <CR>

command! -bang -nargs=? -complete=dir Files
        \ call fzf#vim#files(<q-args>, {'options': ['--layout=reverse', '--info=inline', '--preview', '~/.vim/bundle/fzf.vim/bin/preview.sh {}']}, <bang>0)
