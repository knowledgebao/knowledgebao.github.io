---
layout: post
title: git rebase
date: 2019-11-25 14:02:15
description: git rebase
tag: git

---


# 1. git rebase

- [1. git rebase](#1-git-rebase)
  - [1.1. 基本功能](#11-%e5%9f%ba%e6%9c%ac%e5%8a%9f%e8%83%bd)
    - [1.1.1. 参数](#111-%e5%8f%82%e6%95%b0)
    - [1.1.2. 合并commit](#112-%e5%90%88%e5%b9%b6commit)
    - [1.1.3. 合并远程commit](#113-%e5%90%88%e5%b9%b6%e8%bf%9c%e7%a8%8bcommit)
    - [1.1.4. 当前branch的某一段commit粘贴到另一个分支上](#114-%e5%bd%93%e5%89%8dbranch%e7%9a%84%e6%9f%90%e4%b8%80%e6%ae%b5commit%e7%b2%98%e8%b4%b4%e5%88%b0%e5%8f%a6%e4%b8%80%e4%b8%aa%e5%88%86%e6%94%af%e4%b8%8a)
    - [1.1.5. 将其它分支的某一段commit粘贴到本分支上](#115-%e5%b0%86%e5%85%b6%e5%ae%83%e5%88%86%e6%94%af%e7%9a%84%e6%9f%90%e4%b8%80%e6%ae%b5commit%e7%b2%98%e8%b4%b4%e5%88%b0%e6%9c%ac%e5%88%86%e6%94%af%e4%b8%8a)
  - [1.2. 参考资料](#12-%e5%8f%82%e8%80%83%e8%b5%84%e6%96%99)

## 1.1. 基本功能

### 1.1.1. 参数

- 可以对某一段线性提交历史进行编辑、删除、复制、粘贴；
- git-rebase 存在的价值是：对一个分支做「变基」操作。
- 当我们在一个过时的分支上面开发的时候，执行 rebase 以此同步 master 分支最新变动；
- 假如我们要启动一个放置了很久的并行工作，现在有时间来继续这件事情，很显然这个分支已经落后了。这时候需要在最新的基准上面开始工作，所以 rebase 是最合适的选择。
- 只要你的分支上需要 rebase 的所有 commits 历史还没有被 push 过，就可以安全地使用 git-rebase来操作。
- git rebase -i  [startpoint]  [endpoint]
- git rebase  [startpoint]  [endpoint]  --onto  [branchName]  
- git rebase branchName  [startpoint]   [endpoint]  

### 1.1.2. 合并commit

`git rebase -i  [startpoint]`
不包含startpoint，将要合并的commit对应的pick修改为squash即可。

`git rebase -i  [startpoint]  [endpoint]`

1. 其中-i的意思是--interactive，即弹出交互式的界面让用户编辑完成合并操作
2. [startpoint]  [endpoint]则指定了一个编辑区间的commitID，如果不指定[endpoint]，则该区间的终点默认是当前分支HEAD(或FETCH_HEAD,如果有的话)所指向的commit(注：该区间指定的是一个前开后闭的区间)。当然commit可以是HEAD~3 或者 HEAD^^^等可以代替commitID的内容
3. 根据提示(可能需要输入大写E)进入修改,除去startpoint不需要修改，其它行将pick修改为squash，同时修改注释，然后保存OK,pick就是使用这个commit，squash意思是合并到pick的这个commit。 
4. 如果你异常退出了 vi 窗口，不要紧张 `git rebase --edit-todo` 这时候会一直处在这个编辑的模式里，我们可以回去继续编辑，修改完保存一下：

说明：

1. 此命令会修改所有的commitID以及修改时间，所以如果已经提交到了远端，需要慎用，涉及到修改远端的情况。
2. 如果本地有很多次提交，需要将某几个合并，直接执行`git rebase -i  [startpoint]`即可，将需要合并的commit的pick改为squash即可。因为如果你endpoint不是HEAD的话，会出现头指针分离的情况，合并的后的内容，将作为分离的HEAD存在，此HEAD指向你合并后的代码，没啥作用。

### 1.1.3. 合并远程commit

既然要合并远程commit，那么原来的commitID就会无效。这样先将对应本地的commit合并，然后使用 `git push -f` 强制推送，覆盖远程commit即可。

### 1.1.4. 当前branch的某一段commit粘贴到另一个分支上

`git rebase  [startpoint]   [endpoint]  --onto  [branchName]`
//其中，[startpoint]  [endpoint]仍然和上一个命令一样指定了一个编辑区间(前开后闭)，--onto的意思是要将该指定的提交复制到哪个分支上。

`git reset --hard  0c72e64`
 修改branchName的HEAD指针指向最新commit

### 1.1.5. 将其它分支的某一段commit粘贴到本分支上

`git rebase branchName  [startpoint]   [endpoint]`

//参考上一条，只是无需使用--onto指定本分支，rebase后边跟需要获取的分支。
比如：`git rebase master` ：就会将与master分离后的所有commit合并过来

## 1.2. 参考资料

1. [当前branch的某一段commit粘贴到另一个分支上](https://www.jianshu.com/p/4a8f4af4e803)
2. [彻底搞懂 Git-Rebase](http://jartto.wang/2018/12/11/git-rebase/)
3. [【Git】rebase 用法小结](https://www.jianshu.com/p/4a8f4af4e803)
