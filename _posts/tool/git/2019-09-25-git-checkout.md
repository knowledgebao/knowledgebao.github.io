---
layout: post
title: git-checkout
date: 2019-12-12 18:24:19
description: git-checkout
tag: git

---

# 1. git checkout

- [1. git checkout](#1-git-checkout)
  - [1.1. 基本命令](#11-基本命令)
    - [1.1.1. 参数说明](#111-参数说明)
  - [1.2. 实用功能](#12-实用功能)
    - [1.2.1. 切换分支(默认切换到HEAD)](#121-切换分支默认切换到head)
    - [1.2.2. 创建并且切换分支](#122-创建并且切换分支)
    - [1.2.3. 获取其他分支文件](#123-获取其他分支文件)
    - [1.2.4. 切换到某一次commit提交](#124-切换到某一次commit提交)
    - [1.2.5. 对工作区自检](#125-对工作区自检)
    - [1.2.6. 切换到分支的游离状态](#126-切换到分支的游离状态)
    - [1.2.7. 删除所有提交信息](#127-删除所有提交信息)
    - [1.2.8. 将修改剪切到另一分支](#128-将修改剪切到另一分支)
  - [1.3. 参考资料](#13-参考资料)

## 1.1. 基本命令

- `git checkout [-q] [-f] [-m] [<branch>]`
- `git checkout [-q] [-f] [-m] --detach [<branch>]`
- `git checkout [-q] [-f] [-m] [--detach] <commit>`
- `git checkout [-q] [-f] [-m] [[-b|-B|--orphan] <new_branch>] [<start_point>]`
- `git checkout [-f|--ours|--theirs|-m|--conflict=<style>] [<tree-ish>] [--] <paths>…​`
- `git checkout [-p|--patch] [<tree-ish>] [--] [<paths>…]`
  
### 1.1.1. 参数说明

--soft：修改HEAD指向指定的commid
--mixed: 修改HEAD/INDEX指向指定的commid,此参数是默认参数
--hard:修改HEAD/INDEX/Working Copy指向指定的commid

## 1.2. 实用功能

### 1.2.1. 切换分支(默认切换到HEAD)

`git checkout branch_name`

### 1.2.2. 创建并且切换分支

`git checkout -b branch_name`

### 1.2.3. 获取其他分支文件

`git checkout -- file_name`  从INDEX中签出file_name文件，覆盖工作区文件。
`git checkout -- .`          从INDEX中签出所有文件，覆盖工作区文件。
`git checkout commit_id -- file_name/path_name`  #//从commit_id中取文件file_name/目录path_name到本地,commit_id可以是分支名，可以是tag名，可以是某一次提交的commit_id,本质上都是一个commit hash值
说明：如果文件名与branch_name不重复,--可以省略

### 1.2.4. 切换到某一次commit提交

`git checkout -f commit_id`
如果INDEX已经修改，必须加-f，HEAD/INDEX/Working Copy都会改变，此时进入了“分离头指针”状态，git checkout branch_name即可回到之前,commit_id可以是tag_name

### 1.2.5. 对工作区自检

`git checkout`

### 1.2.6. 切换到分支的游离状态

`git checkout --datch <branch>`
默认以该分支下的最后一次提交ID

### 1.2.7. 删除所有提交信息

`git checkout --orphan <branch>`
假如你的某个分支上，积累了无数次的提交，你也懒得去打理，打印出的log也让你无力吐槽，那么这个命令将是你的神器，它会基于当前所在分支新建一个赤裸裸的分支，没有任何的提交历史，但是当前分支的内容一一俱全。新建的分支，严格意义上说，还不是一个分支，因为HEAD指向的引用中没有commit值，只有在进行一次提交后，它才算得上真正的分支。

### 1.2.8. 将修改剪切到另一分支

`git checkout --merge <branch>`
切换分支的时候，将当前分支修改的内容一起打包带走，同步到切换的分支下。第一，如果当前分支和切换分支间的内容不同的话，容易造成冲突。第二，切换到新分支后，当前分支修改过的内容就丢失了。

## 1.3. 参考资料

- [git checkout详解](https://www.cnblogs.com/hutaoer/archive/2013/05/07/git_checkout.html)
- [【Git】checkout 用法总结](https://www.jianshu.com/p/cad4d2ec4da5)
- [参考网址](https://git-scm.com/docs/git-checkout)
