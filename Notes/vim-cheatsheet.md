# Vim Cheatsheet

## Basics

Save and Quit

```
:w      save the buffer
:q      quit the buffer
:wq     save and quit
```

Move around under normal mode

```
hjkl    left down up right
Ctrl-F  Page Down
Ctrl-B  Page Up
w       move to next word
e       move to the word end
0       move to the head of line
$       move to the end of line
gg      jump to the top of the file
G       jump to the bottom of the file
```

Edit

```
i       start insert mode
<ESC>   end insert mod
a       append 
yy      yank the line
yw      yank to the word end under cursor
yiw     yank the whole word under cursor
dd      delete and yank the line
dw      delete to word end under cursor
diw     delete the whole word
p       paste yanked text
s       substitute
cw      change word at cursor
ciw     change in word
ci(     change in ()
cip     change in paragraph
```

Search

```
/foo    search 'foo' forward in current buffer. The word will be hightlighted.
        Use n to goto the next and N to goto the previous one.
?foo    search 'foo' backward in current buffer. Nagivigation is the same as above
```

## fold and unfold

```
za      open a fold under cursor
zA      open a fold under cursor
zm      increase one fold level 
zM      fold all
zr      decrease one fold level
zR      unfold all
zo      open fold at cursor
zO      open all fold at cursor
zj      move to next fold
zk      move to previous fold
zi      invert 'foldenable'
```

## vimgrep in current file

```
vimgrep /pattern/ %
```

## vimgrep in current folder

```
vimgrep /pattern/ *
```

## quickfix

```
copen   open quickfix window
cnext   next item
cprev   previous item
```

## current date

```
:r !date
```

Actually you can always run the shell command in VIM and insert the outputs like this

```
:r !command
```

## change to current folder

```
:cd %:h

%       full path to current path
%:h     full path to current file without filename itself
```

## substitute

```
:%s/foo/bar/g       find and replace in all line
:s/foo/bar/g        find and replace in current line
:%s/foo/bar/gc      find and replace in current line and ask for confirmation
:%s/foo/bar/gci     find and replace in current line, ask for confirmation, case insensative
```
## autocomplete

```
^x^n    for just this file
^x^f    for filenames
^x^]    for tags
^x      for anything specified by the 'complete' option
```

## command line

```
@:         | run last command
<Ctrl-r>"  | paste from register " to vim command line
:<Ctrl-f>  | to edit the command line with vim normal mode
q:, q/, q? | edit,   search in command line

```

## scroll

```
zt or z<CR> put current line at top of window
zz or z.    put current line at center of window
zb or z-    put current line at bottom of window
```

## file name modifiers

http://vimdoc.sourceforge.net/htmldoc/cmdline.html#filename-modifiers

