---
layout: post
title: git rebase
date: 2019-08-22 15:27:15
description: git rebase
tag: git

---
# git rebase
参考网址[彻底搞懂 Git-Rebase](http://jartto.wang/2018/12/11/git-rebase/)

**功能**：
+ 可以对某一段线性提交历史进行编辑、删除、复制、粘贴；
+ git-rebase 存在的价值是：对一个分支做「变基」操作。
+ 当我们在一个过时的分支上面开发的时候，执行 rebase 以此同步 master 分支最新变动；
+ 假如我们要启动一个放置了很久的并行工作，现在有时间来继续这件事情，很显然这个分支已经落后了。这时候需要在最新的基准上面开始工作，所以 rebase 是最合适的选择。
+ 只要你的分支上需要 rebase 的所有 commits 历史还没有被 push 过，就可以安全地使用 git-rebase来操作。
+ git rebase -i  [startpoint]  [endpoint]
+ git rebase  [startpoint]   [endpoint]  --onto  [branchName]  
+ git rebase branchName  [startpoint]   [endpoint]  

## 合并多个commit为一个完整commit
参考网址:[【Git】rebase 用法小结](https://www.jianshu.com/p/4a8f4af4e803)  

1. **命令**：git rebase -i  [startpoint]  [endpoint]

+ 其中-i的意思是--interactive，即弹出交互式的界面让用户编辑完成合并操作
+ [startpoint]  [endpoint]则指定了一个编辑区间的commitID，如果不指定[endpoint]，则该区间的终点默认是当前分支HEAD所指向的commit(注：该区间指定的是一个前开后闭的区间)。当然commit可以是HEAD~3 或者 HEAD^^^等可以代替commitID的内容
+ 根据提示(可能需要输入大写E)进入修改,除去startpoint不需要修改，其它将行将pick修改为squash，同时修改注释，然后保存OK,pick就是使用这个commit，squash意思是合并到pick的这个commit。  
  

## 将当前branch的某一段commit粘贴到另一个分支上

[参考网址](https://www.jianshu.com/p/4a8f4af4e803)
+ git rebase  [startpoint]   [endpoint]  --onto  [branchName]  
//其中，[startpoint]  [endpoint]仍然和上一个命令一样指定了一个编辑区间(前开后闭)，--onto的意思是要将该指定的提交复制到哪个分支上。
+ git reset --hard  0c72e64 修改branchName的HEAD指针指向最新commit

## 将其它分支的某一段commit粘贴到本分支上
+ git rebase branchName  [startpoint]   [endpoint]  
//参考上一条，只是无需使用--onto指定本分支，rebase后边跟需要获取的分支。
比如：git rebase master：就会将与master分离后的所有commit合并过来
 