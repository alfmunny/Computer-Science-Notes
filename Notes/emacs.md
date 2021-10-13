  - [Emacs](#sec-1)
    - [Install Emacs](#sec-1-1)
      - [install](#sec-1-1-1)
      - [develop branch](#sec-1-1-2)
      - [org-indent-mode](#sec-1-1-3)
    - [Timestamp](#sec-1-2)
    - [Tags](#sec-1-3)
    - [Tree](#sec-1-4)
    - [Search](#sec-1-5)
    - [Todo keywords <code>[2/2]</code>](#sec-1-6)
    - [Org-mode](#sec-1-7)
    - [Org-Babel](#sec-1-8)
      - [python](#sec-1-8-1)
      - [java](#sec-1-8-2)
      - [how to tangle a block](#sec-1-8-3)
    - [Org-agenda](#sec-1-9)
    - [Org-capture](#sec-1-10)
    - [Org-habit](#sec-1-11)
    - [Org-refile](#sec-1-12)
    - [Export](#sec-1-13)
    - [Archive tasks](#sec-1-14)
    - [Binding keys](#sec-1-15)
    - [Multi-line editing](#sec-1-16)
    - [Clock](#sec-1-17)
    - [Python mode](#sec-1-18)
    - [Diary-date](#sec-1-19)
    - [visual-line-mode](#sec-1-20)
    - [Line number](#sec-1-21)
    - [Spell Checking](#sec-1-22)
    - [Current Time Stamp](#sec-1-23)
    - [Enable Writeroom Mode](#sec-1-24)
    - [asm mode](#sec-1-25)

# Emacs     :emacs:<a id="sec-1"></a>


## Install Emacs<a id="sec-1-1"></a>

### install<a id="sec-1-1-1"></a>

emacs.app

```shell
brew cask install emacs
git clone https://github.com/syl20bnr/spacemacs ~/.emacs.d
```

but it does create the path for command line. [Tips for emacs setup on OS X](https://emacsformacosx.com/tips).

### develop branch<a id="sec-1-1-2"></a>

```shell
git checkout develop #use the master version
```

### org-indent-mode<a id="sec-1-1-3"></a>

```emacs-lisp
(setq org-startup-indented t)
```

## Timestamp     :cheatsheet:<a id="sec-1-2"></a>

`, d t`:

    active timestamp: <2020-02-09 23:00 Sun>

`, d T`:

    inactive timestamp [2020-02-09 Sun]

[info:org#Timestamps](org#Timestamps)

## Tags     :cheatsheet:<a id="sec-1-3"></a>

`, i t`: add tags to headline

`SPC a o m`: open a org-tags-view

## Tree     :cheatsheet:<a id="sec-1-4"></a>

`, s a`: add archive tag

`, s n`: narrow to the subtree

`, s N`: widen

## Search     :cheatsheet:<a id="sec-1-5"></a>

`SPC s s`: search in current buffer

`SPC s f`: fuzzy search for files

`SPC s d`: ag search in current dir

`SPC s r f`: rg search in files

`SPC a o m`: search with tags in agenda files

`SPC a o r`: full text search in agenda files

`SPC a o s`: search with keywords in agenda files

Custom Commands:

`SPC o s`: helm-org-agenda-files-heading search headings in agenda files. Bind this to a shortcut.

[How to bind keys](#orgd9e5f66)

## Todo keywords <code>[2/2]</code><a id="sec-1-6"></a>

-   [X] Add more keywords
    
    ```emacs-lisp
    (setq org-todo-keywords '((sequence "iTODO(t)i" "PROGRESS(p)" "|" "DONE(d)" "CANCELLED(c)")))
    ```
    
    [org-todo-keywords](file:///Users/alfmunny/.spacemacs)

-   [X] Add the highlights of the keywords
    
    ```emacs-lisp
    (custom-set-variables 
     '(org-todo-keyword-faces
       (quote
        (("TODO" . "#dc752f")
         ("PROGRESS" . "#4f97d7")
         ("DONE" . "#86dc2f"))))
     )
    ```
    
    [org-todo-keyword-faces](file:///Users/alfmunny/.spacemacs)
    
    If the effects are not taken, use org-mode-restart to clear the caches in Emacs.

## Org-mode<a id="sec-1-7"></a>

[The Org Manual](https://github.com/mudan/mudan.github.io/blob/master/Emacs/The_Org_Manual/The_Org_Manual.org) [Org Mode - Organize Your Life In Plain Text](http://doc.norang.ca/org-mode.html)

## Org-Babel     :cheatsheet:<a id="sec-1-8"></a>

`C-c, C-,` or `, i b`: open code block templates

`C-c, C-,`: open code block templates

`C-c, C-'`: edit code block in separate window

`C-c, C-C`: edit code block in separate window

`C-c, C-v, t`: tangle code block in buffer

`SPC u, C-c, C-v, t`: tangle current code block

### python<a id="sec-1-8-1"></a>

```python
print "This Is A python code"
print "hahaha"
```

    >>>

### java<a id="sec-1-8-2"></a>

```java
import edu.princeton.cs.algs4.StdIn;
class Test {
    private String pat;

    public Test(String pat) {
        this.pat = pat;
    }

    public static void main(String[] args) {
        System.out.println("Hello World!");
    }
}
```

### how to tangle a block<a id="sec-1-8-3"></a>

```python
print("this")
```

## Org-agenda     :cheatsheet:<a id="sec-1-9"></a>

`C-c a`: trigger org-agenda menu

```emacs-lisp
(setq org-agenda-files (quote
                        ("~/OneDrive/org/notes.org"
                         "~/OneDrive/org/gtd.org")))
```

[org-agenda-files](file:///Users/alfmunny/.spacemacs)

-   In agenda view
    
    `C-c C-s`: to schedule item

## Org-capture     :cheatsheet:<a id="sec-1-10"></a>

`C-c c`: trigger org-capture

[org-capture-templates](file:///Users/alfmunny/.spacemacs)

-   Add template for org-capture.

```emacs-lisp
(setq org-capture-templates
      '(("n" "Notes" entry (file+headline "~/OneDrive/org/notes.org" "Notes"))
        ("t" "ToDo" entry (file+headline "~/OneDrive/org/gtd.org" "Tasks")
         "* TODO %?\n  %i\n  %a")
        ))
```

-   How to use [Template Expansion](https://orgmode.org/manual/Template-expansion.html#Template-expansion)

## Org-habit     :cheatsheet:<a id="sec-1-11"></a>

1.  configuration in `org-modules`
    
    ```emacs-lisp
    (defun dotspacemacs/user-config ()
      "Configuration for user code:
    This function is called at the very end of Spacemacs startup, after layer
    configuration.
    Put your configuration code here, except for variables that should be set
    before packages are loaded."
      (setq org-modules (quote (org-habit)))
      (setq org-agenda-files '("~/OneDrive/org/gtd.org"))
      )
    ```

2.  add a **schedule** to a TODO task.
3.  add `:STYLE: habit` to the task.

`C-k` toggle habit in agenda view

## Org-refile     :cheatsheet:<a id="sec-1-12"></a>

Problem after installation of the develop branch.

```shell
# org-refile does not work. org-copy-subtree: Invalid function: org-preserve-local-variables
cd ~/.emacs.d && git pull --rebase; find ~/.emacs.d/elpa/2*/develop/org-plus-contrib* -name '*.elc' -delete
```

[Reference](https://github.com/syl20bnr/spacemacs/issues/11801)

`, s r`: open refile window

```emacs-lisp
(setq org-refile-targets '((org-agenda-files :maxlevel . 3)))
(setq org-refile-use-outline-path 'file)
(setq org-outline-path-complete-in-steps nil)
```

<file:///Users/alfmunny/.spacemacs>

## Export     :cheatsheet:<a id="sec-1-13"></a>

`SPC m e e` open export menu

## Archive tasks     :cheatsheet:<a id="sec-1-14"></a>

Options:

-   :Archive: tag, `, s a`
    
    Maybe suitable for some project

-   Archive to `C-c C-x A` (org-archive-to-archive-sibling)
    
    For major categories, like this one Tasks

-   Use org-refile, refile it to a structured notes, `, s r`
    
    Important notes, which has to be taken into notes

-   Archive to \*<sub>archive</sub>, `, s A`
    
    Not needed anymore
    
    Reference: [info:org#Archiving](org#Archiving)

## Binding keys<a id="sec-1-15"></a>

```emacs-lisp
(spacemacs/declare-prefix "o" "custom")
(spacemacs/set-leader-keys "os" 'helm-org-agenda-files-headings)
```

[binding-keys](https://develop.spacemacs.org/doc/DOCUMENTATION.html#binding-keys)

```emacs-lisp
(global-set-key (kbd "C-c n l") 'org-roam)
(global-set-key (kbd "C-c n f") 'org-roam-find-file)
(global-set-key (kbd "C-c n g") 'org-roam-graph)
(global-set-key (kbd "C-c n i") 'org-roam-insert)
(global-set-key (kbd "C-c n I") 'org-roam-insert-immediate)
```

<https://develop.spacemacs.org/doc/DOCUMENTATION.html#binding-keys>

## Multi-line editing     :cheatsheet:<a id="sec-1-16"></a>

`g-r-A` multi editing using visual selection

`g-r-q` quit register

## Clock     :cheatsheet:<a id="sec-1-17"></a>

`, C i`: clock in

`, C o`: clock out

`, C R`: clock report

    :LOGBOOK:
    CLOCK: [2020-02-13 Thu 17:04]--[2020-02-13 Thu 17:06] =>  0:02
    :END:

## Python mode     :cheatsheet:<a id="sec-1-18"></a>

`SPC m s b`: send buffer `SPC m s B`: send buffer and switch to REPL `SPC m s f`: send function and switch to REPL `SPC m s i`: start the inferior REPL process `SPC m c c`: execute current file in a comint shell

## Diary-date     :cheatsheet:<a id="sec-1-19"></a>

## visual-line-mode<a id="sec-1-20"></a>

```lisp
setq visual-line-mode t
```

To navigate under visual line mode:

`M-x spacemacs/toggle-visual-line-navigation-on`

## Line number<a id="sec-1-21"></a>

`SPC t n a` absolute line number

`SPC t n r` relative line number

`SPC t n v` visual line number

## Spell Checking<a id="sec-1-22"></a>

`SPC t S` toggle spell checking

```emacs-lisp
(setq spell-checking-enable-by-default nil)
```

## Current Time Stamp<a id="sec-1-23"></a>

`C-u C-c .` insert current active time with prompt

`C-u C-u C-c .` insert current active time without prompt

`C-u C-c !` insert current inactive time with prompt `C-u C-u C-c !` insert current inactive time without prompt

## Enable Writeroom Mode<a id="sec-1-24"></a>

`M-x writeroom-mode` [Writeroom Mode](file:///Users/alfmunny/OneDrive/org/roam/journal_2021.md)

## asm mode     :emacs:<a id="sec-1-25"></a>

```asm
mov ax, 1000H
```
