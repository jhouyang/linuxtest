set history=499
set autoread
set ruler
set cmdheight=2
" Configure backspace so it acts as it should act
set backspace=eol,start,indent
set whichwrap+=<,>,h,l

set ignorecase
set smartcase

set hlsearch
set showmatch

set tabstop=4
set shiftwidth=4
set expandtab

set mouse=a
syntax enable
colorscheme desert
set nocompatible
set cindent
set autoindent
set incsearch
set nu

set list
set listchars=tab:\|\ 

set encoding=utf-8
set guioptions+=b
 
let fortran_fold=1
set foldmethod=syntax
set foldlevelstart=99

set tags=tags
set tags+=./tags
set tags=/home/jouyang/tags
"set tags+=./../tags,./*/tags
set autochdir
""""""""""""""""""""""""""""""
" set path for a.vim
""""""""""""""""""""""""""""""
set path+=./src,../
set path+=~/jouyang/jouyang/**
let g:alternateSearchPath = 'sfr:./src,sfr:../,sfr:../include,sfr:../src'

"set mapleader
let mapleader = ","
""""""""""""""""""""""""""""""
"Fasst reloading of the .vimrc
""""""""""""""""""""""""""""""
map <silent> <leader>ss :source ~/.vimrc<cr>
"Fast editing of .vimrc
map <silent> <leader>ee :e ~/.vimrc<cr>
"When .vimrc is edited, reload it
autocmd! bufwritepost .vimrc source ~/.vimrc et number

map <silent> <Leader>ma : set mouse=a<cr>
map <silent> <Leader>m : set mouse=<cr>

""""""""""""""""""""""""
" status bar 
""""""""""""""""""""""""
set laststatus=2
highlight StatusLine cterm=bold ctermfg=yellow ctermbg=blue

""function! CurDir()
    ""let curdir = substitute(getcwd(), $HOME, "~", "g")
    ""return getcwd()
""endfunction
""set statusline=[%n]\ %f%m%r%h\ \|\ \ pwd:\ %{CurDir()}\ \ \|%=\|\ %l,%c\ %p%%\ \|\ ascii=%b,hex=%b%{((&fenc==\"\")?\"\":\"\ \|\ \".&fenc)}\ \|\ %{$USER}\ @\ %{hostname()}\
set statusline=[%n]\ \|\ \ %{getcwd()}\/%f\ \ \|%=\|\ %l,%c\ %p%%\ \|\ 

""""""""""""""""""""""""""""""
"map p4 "
""""""""""""""""""""""""""""""
let mapleader = "."
map <silent> <Leader>e :!p4 edit %<cr>
map e :!p4 edit %<cr>
map pa :!p4 add %<cr>
map r :!p4 revert %<cr>
map pd :!p4 delete %<cr>

""""""""""""""""""""""""""""""
"taglist.vim setting
""""""""""""""""""""""""""""""
let Tlist_Show_One_File=1
let Tlist_Exit_OnlyWindow=1
""let Tlist_File_Fold_Auto_Close=1
let Tlist_GainFocus_On_ToggleOpen=0
let Tlist_Auto_Open=0

""""""""""""""""""""""""""""""
" netrw setting
""""""""""""""""""""""""""""""
let g:netrw_winsize = 30
nmap <silent> <leader>fe :Sexplore<cr>


""""""""""""""""""""""""""""""
" bufExplorer vim7.0 /minibufer explorer
""""""""""""""""""""""""""""""
"let g:bufExplorerDefaultHelp=0       " Do not show default help.
"let g:bufExplorerShowRelativePath=1  " Show relative paths.
"let g:bufExplorerSortBy='mru'        " Sort by most recently used.
"let g:bufExplorerSplitRight=0        " Split left.
"let g:bufExplorerSplitVertical=1     " Split vertically.
"let g:bufExplorerSplitVertSize = 30  " Split width
"let g:bufExplorerUseCurrentWindow=1  " Open in new window.
"autocmd! BufWinEnter \[Buf\ List\] set1 nonumber
let g:miniBufExplMapWindowNavVim = 1 
let g:miniBufExplMapWindowNavArrows = 1 
let g:miniBufExplMapCTabSwitchBufs = 1 
let g:miniBufExplModSelTarget = 1
let g:miniBufExplMoreThanOne=0

""""""""""""""""""""""""""""""
" winManager setting
"""""""""""""""""""""""""""""""
let g:winManagerWidth = 20
let g:defaultExplorer = 0
let g:NERDTree_title="[NERD Tree]" 
let g:winManagerWindowLayout="NERDTree|TagList"

function! NERDTree_Start()
    exec 'NERDTree'
endfunction

function! NERDTree_IsValid()
    return 1
endfunction

nmap <F3> :WMToggle<CR>

""""""""""""""""""""""""""""""
" lookup file with ignore case
""""""""""""""""""""""""""""""
function! LookupFile_IgnoreCaseFunc(pattern)
   let _tags = &tags
   try
      let &tags = eval(g:LookupFile_TagExpr)
      let newpattern = '\c' . a:pattern
      let tags = taglist(newpattern)
   catch
      echohl ErrorMsg | echo "Exception: " . v:exception | echohl NONE
      return ""
   finally
      let &tags = _tags
      endtry

" Show the matches for what is typed so far.
   let files = map(tags, 'v:val["filename"]')
   return files
endfunction
let g:LookupFile_LookupFunc = 'LookupFile_IgnoreCaseFunc' 

""""""""""""""""""""""""""""""
"lookupFile 1)file, F5/:lookupFile, 2) bufs :LUBufs, 3)dir :LUWalk
"""""""""""""""""""""""""""""""
let g:LookupFile_MinPatLength = 2               " 2 chars to star find
let g:LookupFile_PreserveLastPattern = 0        " don't save last find string
let g:LookupFile_PreservePatternHistory = 1     " save find history
let g:LookupFile_AlwaysAcceptFirst = 1          " Enter to open first match
let g:LookupFile_AllowNewFiles = 0              " don't allow create file don't exits
if filereadable("/home/jouyang/lookupFile.tags")               " tags name
	let g:LookupFile_TagExpr = '"/home/jouyang/lookupFile.tags"'
endif
nmap <silent> <leader>lk :LUTags<cr>
nmap <silent> <leader>ll :LUBufs<cr>
nmap <silent> <leader>lw :LUWalk<cr>

""""""""""""""""""""""""""""""
" mark setting : highlight
"""""""""""""""""""""""""""""""
nmap <silent> <leader>hl <Plug>MarkSet
vmap <silent> <leader>hl <Plug>MarkSet
nmap <silent> <leader>hh <Plug>MarkClear
vmap <silent> <leader>hh <Plug>MarkClear
nmap <silent> <leader>hr <Plug>MarkRegex
vmap <silent> <leader>hr <Plug>MarkRegex
 
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" cscope setting
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
if has("cscope")
  set csprg=/usr/bin/cscope
  set cscopequickfix=s-,c-,d-,i-,t-,e-
  set csto=1
  set cst
  set nocsverb
  " add any database in current directory
  if filereadable("/home/jouyang/cscope.out")
     cs add /home/jouyang/cscope.out /home/jouyang/vim
  endif
  set csverb
endif

nmap <C-@>s :cs find s <C-R>=expand("<cword>")<CR><CR>
nmap <C-@>g :cs find g <C-R>=expand("<cword>")<CR><CR>
nmap <C-@>c :cs find c <C-R>=expand("<cword>")<CR><CR>
nmap <C-@>t :cs find t <C-R>=expand("<cword>")<CR><CR>
nmap <C-@>e :cs find e <C-R>=expand("<cword>")<CR><CR>
nmap <C-@>f :cs find f <C-R>=expand("<cfile>")<CR><CR>
nmap <C-@>i :cs find i ^<C-R>=expand("<cfile>")<CR>$<CR>
nmap <C-@>d :cs find d <C-R>=expand("<cword>")<CR><CR>

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"omnicppcomplete.vim setting ---> too slow!!!
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
""set tags+=/home/jouyang/tags
""let OmniCpp_NamespaceSearch=2 "search namespace in this and included files
""let OmniCpp_GlobalScopeSearch=1
""let OmniCpp_ShowAccess = 1
""let OmniCpp_ShowPrototypeInAbbr =1 "show fuction prototype in popup window.
""let OmniCpp_MayCompletDot = 1
""let OmniCpp_MayCompleteArrow=1
""let OmniCpp_MayCompleteScope=1
""let OmniCpp_SelectFirstItem=2
""let OmniCpp_DisplayMode=1
""let OmniCpp_DefaultNamespaces=["std", "_GLIBCXX_STD"]
""au CursorMovedI,InsertLeave * if pumvisible() == 0|silent! pclose | endif
""set completeopt=menu,longest
" mapping
""inoremap <expr> <CR>       pumvisible()?"\<C-Y>":"\<CR>"
""inoremap <expr> <C-J>	   pumvisible()?"\<PageDown>\<C-N>\<C-P>":"\<C-X><C-O>"
""inoremap <expr> <C-K>      pumvisible()?"\<PageUp>\<C-P>\<C-N>":"\<C-K>"
""inoremap <expr> <C-U>      pumvisible()?"\<C-E>":"\<C-U>" 
" command to create tags for omnicpp
" ctags -R --c++-kinds=+p --fields=+iaS --extra=+q dir

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"disable tab, set as 4 space
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
set nocp
filetype plugin indent on
autocmd! FileType c,cpp 

""""""""""""""""""""""""
" color for omnicomplte
""""""""""""""""""""""""
highlight Pmenu    guibg=darkgrey  guifg=black
highlight PmenuSel guibg=lightgrey guifg=black


""""""""""""""""""""""""
" supertab, neoComplCache
""""""""""""""""""""""""
let g:SuperTabRetainCompletionType=2
let g:SuperTabDefaultCompletionType="<C-X><C-O>"

let g:NeoComplCache_EnableAtStartup = 1
""let g:NeoComplCache_DisableAutoComplete = 1
let g:SuperTabDefaultCompletionType="context"
let g:neocomplcache_enable_auto_select = 1
let g:neocomplcache_enable_at_startup = 1
let g:neocomplcache_enable_smart_case = 1

""""""""""""""""""""""""
""trinity.vim: Build the trinity of srcexpl,taglist,
""""""""""""""""""""""""
""let g:SrcExpl_isUpdateTags = 0
""let Tlist_WinWidth=16
""nmap <F12> :TrinityToggleAll<CR>
""nmap <F9> :TrinityToggleSourceExplorer<CR>
""nmap <F10> :TrinityToggleTagList<CR>
""nmap <F11> :TrinityToggleNERDTree<CR>


""""""""""""""""""""""""
" backet complete
""""""""""""""""""""""""
inoremap ( ()<Esc>i
inoremap [ []<Esc>i
inoremap { {<CR>}<Esc>O

function! ClosePair(char)
    if getline('.')[col('.') - 1] == a:char
        return "\<Right>"
    else
        return a:char
    endif
endf

function! CloseBracket()
    if match(getline(line('.') + 1), '\s*}') < 0
        return "\<CR>}"
    else
        return "\<Esc>j0f}a"
    endif
endf

function! QuoteDelim(char)
    let line = getline('.')
    let col = col('.')
    if line[col - 2] == "\\"
    "Inserting a quoted quotation mark into the string
        return a:char
    elseif line[col - 1] == a:char
    "Escaping out of the string
        return "\<Right>"
    else
    "Starting a string
       return a:char.a:char."\<Esc>i"
    endif
endf

autocmd Syntax html,vim inoremap < <lt>><Esc>i| inoremap > <c-r>=ClosePair('>')<CR>
inoremap ) <c-r>=ClosePair(')')<CR>
inoremap ] <c-r>=ClosePair(']')<CR>
inoremap } <c-r>=CloseBracket()<CR>
inoremap " <c-r>=QuoteDelim('"')<CR>
inoremap ' <c-r>=QuoteDelim("'")<CR>


