set nocompatible	"required for Vundle
filetype off		"required for Vundle

set rtp+=~/.vim/bundle/Vundle.vim

call vundle#begin()
	Plugin 'VundleVim/Vundle.vim'
	Plugin 'christophermca/meta5'
	Plugin 'fcevado/molokai_dark'
	Plugin 'tomsik68/vim-crystallite'
call vundle#end()

syntax enable		" enable syntax processing
set number		" shows line numbers
set hlsearch		" highlights matches to search

filetype plugin indent on	" automatically indents
set backspace=indent,eol,start
set tabstop=4			"sets tabs to 4 spaces
set shiftwidth=4		"sets autoindent to 4 spaces

set textwidth=79
set breakindent
set breakindentopt=shift:4
set fo=coqt

colorscheme Crystallite
