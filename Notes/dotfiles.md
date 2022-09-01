# How to backup dotfiles

One trick is to use the `work-tree` option of `git`.

Add this two line in your `.zshrc`

```zsh
DOTFILES_PATH=$HOME/.df
alias dtf="git --git-dir $DOTFILES_PATH --work-tree=$HOME"
```

Then reload the config.

```zsh
source ~/.zshrc
```

Create `git-dir`

```zsh
mkdir ~/.df
```

Now you can start backup your dotfiles.


```zsh
dtf add .vimrc .tmux.conf .zshrc .spacemacs
dtf status
dtf commit -m "vimrc backuped"
dtf push
```
