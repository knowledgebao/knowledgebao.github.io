---
layout: post
title: git-checkout
date: 2019-09-11 15:19:16
description: git-checkout
tag: git

---
## git checkout
**功能**：
[参考网址](https://git-scm.com/docs/git-checkout)
+ git checkout [-q] [-f] [-m] [<branch>]
+ git checkout [-q] [-f] [-m] --detach [<branch>]
+ git checkout [-q] [-f] [-m] [--detach] <commit>
+ git checkout [-q] [-f] [-m] [[-b|-B|--orphan] <new_branch>] [<start_point>]
+ git checkout [-f|--ours|--theirs|-m|--conflict=<style>] [<tree-ish>] [--] <paths>…​
+ git checkout [-p|--patch] [<tree-ish>] [--] [<paths>…]
  
**参数说明：**
--soft：修改HEAD指向指定的commid
--mixed: 修改HEAD/INDEX指向指定的commid,此参数是默认参数
--hard:修改HEAD/INDEX/Working Copy指向指定的commid

1. 切换分支(默认切换到HEAD)：
+ git checkout branch_name
  
2. 创建并且切换分支：
+ git checkout -b branch_name

3. 本地代码库回滚(如果文件名与branch_name不重复,--可以省略):
+ git checkout -- file_name  从INDEX中签出file_name文件，覆盖工作区文件。
+ git checkout -- .          从INDEX中签出所有文件，覆盖工作区文件。
+ git checkout commit_id -- file_name  #//从commit_id中取文件file_name到本地,commit_id可以是分支名，可以是tag名，可以是某一次提交的commit_id,本质上都是一个commit hash值

4. 切换到某一次commit提交
+ git checkout -f commit_id   如果INDEX已经修改，必须加-f，HEAD/INDEX/Working Copy都会改变，此时进入了“分离头指针”状态，git checkout branch_name即可回到之前,commit_id可以是tag_name

5. 对工作区自检
+ git checkout

6. 切换到分支的游离状态，默认以该分支下的最后一次提交ID
+ git checkout --datch <branch>

7. 删除所有提交信息。是的，假如你的某个分支上，积累了无数次的提交，你也懒得去打理，打印出的log也让你无力吐槽，那么这个命令将是你的神器，它会基于当前所在分支新建一个赤裸裸的分支，没有任何的提交历史，但是当前分支的内容一一俱全。新建的分支，严格意义上说，还不是一个分支，因为HEAD指向的引用中没有commit值，只有在进行一次提交后，它才算得上真正的分支。
+ git checkout --orphan <branch>

8. 切换分支的时候，将当前分支修改的内容一起打包带走，同步到切换的分支下。第一，如果当前分支和切换分支间的内容不同的话，容易造成冲突。第二，切换到新分支后，当前分支修改过的内容就丢失了。
+ git checkout --merge <branch>



参考资料：  
+ [git checkout详解](https://www.cnblogs.com/hutaoer/archive/2013/05/07/git_checkout.html)
+ [【Git】checkout 用法总结](https://www.jianshu.com/p/cad4d2ec4da5)