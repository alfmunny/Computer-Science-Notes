## Shell

### Add man pages
```
export MANPATH="/Applications/X/C/D/P/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/share/man:$MANPATH"
```

## Git

### How to rebase your branch

```
git checkout branchname
git rebase -i master
```

### Change local user name

```
git config user.name "Your name"
git config user.email "Your email"
```
### Synchronize git branch with master
[Git Forks And Upstreams](https://www.atlassian.com/git/articles/git-forks-and-upstreams)

```
git checkout branchname
# some work and some commits
# some time passes
git fetch upstream
git rebase upstream/master
```

### Synchronize git master

```
git checkout master
git fetch upstream
git merge upstream/master (or git rebase upstream/master)
```

### Delete the commit on remote github

[See here](https://stackoverflow.com/questions/448919/how-can-i-remove-a-commit-on-github)

#### First remove the last commit
```
git rebase -i HEAD~2 ( Or use the option in IDE )
```

#### Force push

```
git push origin +branchname --force
```

### Worktree

It is useful when you want to push a folder to a different branch.
For example, push public/ to gh-pages

```
git worktree add -B gh-pages public upstream/gh-pages

```

## Network

### check port being forwarded

```
netstat -tpln
```

### ssh without password
```
ssh-keygen -t rsa(with default config)
ssh-copy-id root@172.100.51.192
ssh root@ip.address
```

### overwatch tcp call
Tool: tcpdump

```
tcpdump -i vmgmt port http and dst www.heise.de
```

### download from remote host

```
scp your_username@remotehost.edu:foobar.txt /local/dir
```
## System

### unmount busy device

```
umount -l /path/to/busy-device
```

### unmount busy nfs

```
umount -f /path/to/busy-network-file-system
```

### write random data to file

```
dd if=/dev/urandom of=sample.txt bs=1G count=1
dd if=/dev/urandom of=sample.txt bs=64M count=16
```

### firewall
```
/etc/init.d/firewall start
/etc/init.d/firewall stop
```

## Database

```
show databases;
GRANT ALL ON `DATABASE`.* TO 'user'@'localhost' IDENTIFIED BY 'password';
```

