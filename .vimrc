" Try not to put settings you don’t understand in your .vimrc

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

"autocmd filetype cpp nnoremap <F5> :w <bar> !g++ -std=c++17 -Wshadow -Wall % -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -g

nnoremap <F5> :w <bar> !g++ -DLOCAL -std=c++17 -Wshadow -Wall % -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -g <CR>

nnoremap <F6> :!./a.out <CR>
