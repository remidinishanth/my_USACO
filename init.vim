set nocompatible              " be iMproved, required
filetype off                  " required

call plug#begin()
" griw, replace inner word, useful when you copy & replace
Plug 'https://github.com/vim-scripts/ReplaceWithRegister'

Plug 'tpope/vim-commentary'
Plug 'tpope/vim-surround'
Plug 'tpope/vim-repeat'
Plug 'tpope/vim-fugitive'

Plug 'preservim/nerdtree'

" Intellisense
Plug 'neoclide/coc.nvim', {'branch': 'release'}

" Syntax checker
Plug 'dense-analysis/ale'

" Fuzzy finding and searching
Plug 'mileszs/ack.vim'
Plug 'junegunn/fzf', { 'do': { -> fzf#install() } }
Plug 'junegunn/fzf.vim'

" Have the file system follow you around
Plug 'airblade/vim-rooter'

" Colorizer
Plug 'morhetz/gruvbox'
Plug 'norcalli/nvim-colorizer.lua'

Plug 'yggdroot/indentline'  " Show indentation lines

" Themes
Plug 'ryanoasis/vim-devicons'
Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'

call plug#end()

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
set mouse=a          " enable mouse in all modes
set wildmenu         " visual autocomplete for command menu
set nowrap           " disable soft wrap for lines
set hlsearch         " highlight search results
set incsearch        " incremental search
set splitbelow       " split opens at bottom
set splitright       " new vertical split opens right
set signcolumn=yes   " always show signcolumns - used by ALE

syntax enable        " keep your current color settings

if (has('termguicolors'))
  set termguicolors
endif

colorscheme gruvbox

" FZF settings
let g:fzf_layout = {'up':'~90%', 'window': { 'width': 0.8, 'height': 0.8,'yoffset':0.5,'xoffset': 0.5, 'border': 'sharp', 'highlight': 'Identifier'} }
let g:fzf_tags_command = 'ctags -R'

" layout - reverse => push search area where we type our terms to the top
let $FZF_DEFAULT_OPTS = '--layout=reverse  --inline-info'
let $FZF_DEFAULT_COMMAND = "rg --files --hidden --glob '!.git/**' --glob '!build/**' --glob '!.dart_tool/**' --glob '!.idea'"

" Automatically displays all buffers when there's only one tab open.
let g:airline#extensions#tabline#enabled = 1
let g:airline#extensions#tabline#buffer_min_count = 2   " show tabline only if there is more than 1 buffer

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

nmap <Leader>gs :G<CR> "git status, use s and u to stage and unstage

" Competitive programming CPP
"autocmd filetype cpp nnoremap <F5> :w <bar> !g++ -std=c++17 -Wshadow -Wall % -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -g
nnoremap <F5> :w <bar> !g++ -DLOCAL -std=c++17 -Wshadow -Wall % -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -g <CR>

" set the runtime path to include Vundle and initialize
set rtp+=/usr/local/opt/fzf

" coc.nvim
" Use tab for trigger completion with characters ahead and navigate.
" NOTE: Use command ':verbose imap <tab>' to make sure tab is not mapped by
" other plugin before putting this into your config.
inoremap <silent><expr> <TAB>
      \ pumvisible() ? "\<C-n>" :
      \ <SID>check_back_space() ? "\<TAB>" :
      \ coc#refresh()
inoremap <expr><S-TAB> pumvisible() ? "\<C-p>" : "\<C-h>"

function! s:check_back_space() abort
  let col = col('.') - 1
  return !col || getline('.')[col - 1]  =~# '\s'
endfunction

" Make <CR> auto-select the first completion item and notify coc.nvim to
" format on enter, <cr> could be remapped by other vim plugin
inoremap <silent><expr> <cr> pumvisible() ? coc#_select_confirm()
                              \: "\<C-g>u\<CR>\<c-r>=coc#on_enter()\<CR>"

" Also uses https://github.com/clangd/coc-clangd
