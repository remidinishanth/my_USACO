" set the runtime path to include Vundle and initialize
set rtp+=/usr/local/opt/fzf

call plug#begin('~/.vim/plugged')

" Fuzzy finding and searching
Plug 'junegunn/fzf', { 'do': { -> fzf#install() } }
Plug 'junegunn/fzf.vim'
Plug 'mileszs/ack.vim'

" Themes
Plug 'joshdick/onedark.vim'
Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'

Plug 'scrooloose/nerdtree', { 'on': 'NERDTreeToggle' }

" Use release branch (Recommend), autocomplete
Plug 'neoclide/coc.nvim', {'branch': 'release'}

" Lint checkers
Plug 'w0rp/ale'
Plug 'nvie/vim-flake8'

" griw, replace inner word, useful when you copy & replace
Plug 'https://github.com/vim-scripts/ReplaceWithRegister'

Plug 'tpope/vim-commentary'
Plug 'tpope/vim-surround'
Plug 'tpope/vim-repeat'
Plug 'tpope/vim-fugitive'

call plug#end()

filetype plugin indent on    " required

" Try not to put settings you don’t understand in your .vimrc
set clipboard=unnamed " copy vim clipboard to system clipboard
set backspace=indent,eol,start "to make backspace work as expected
set nocompatible     " removes incompatibility with the original vi
set expandtab        " convert tabs to spaces
set shiftwidth=4     " no of spaces inserted for indentation
set tabstop=4        " 1 tab = 4 spaces
set softtabstop=4    " with BS pretend like tab is removed, even if spaces
set smartindent      " does the right thing (mostly) in programs
set autoindent       " copy the indentation from the previous line
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
set display+=lastline " long last line will be displayed as much as possible instead of @

syntax enable        " keep your current color settings

set background=dark
" let g:solarized_termcolors=256
colorscheme onedark

if &listchars ==# 'eol:$'
  set listchars=tab:>\ ,trail:-,extends:>,precedes:<,nbsp:+
endif

" Smart way to move between windows in split
map <C-j> <C-W>j
map <C-k> <C-W>k
map <C-h> <C-W>h
map <C-l> <C-W>l

let mapleader = ","  " comma is leader
nnoremap <leader><space> :noh<CR> " turn off search highlight
nmap <Leader>f :Files<CR>
nmap <Leader>n :NERDTreeToggle<CR>


" Competitive programming CPP 
"autocmd filetype cpp nnoremap <F5> :w <bar> !g++ -std=c++17 -Wshadow -Wall % -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -g
nnoremap <F5> :w <bar> !g++ -DLOCAL -std=c++17 -Wshadow -Wall % -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -g <CR>
nnoremap <F6> :!./a.out <CR>

" coc.vim
" Use tab for trigger completion with characters ahead and navigate.
" NOTE: Use command ':verbose imap <tab>' to make sure tab is not mapped by
" other plugin before putting this into your config.
inoremap <silent><expr> <TAB>
      \ pumvisible() ? "\<C-n>" :
      \ <SID>check_back_space() ? "\<TAB>" :
      \ coc#refresh()
inoremap <expr><S-TAB> pumvisible() ? "\<C-p>" : "\<C-h>"
