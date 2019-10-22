---
layout: post
title: git-branch
date: 2019-09-07 21:07:06
description: git-branch
tag: git

---
## git branch
**功能**:分支功能
说明: branch-name表示分支名称, origin表示远程主机名
+ git branch [-r/-a]
    查看所有本地分支,默认查看本地分支,-r表示远端分支,-a表示本地+远端分支
+ git remote show origin
    查看关于远端origin的一些信息，包括分支是否tracking
+ git branch <name> <commid>
    创建本地分支,可以基于某一次提交，默认基于当前HEAD创建分支。
+ git checkout branch-name/git checkout -b branch-name2 origin/branch-name
    切换分支，如果本地没有，则从远端下载分支后再切换，如果远端也没有，则执行失败。第二条命令可以指定本地分支名称与远端分支名称不一样
+  git checkout -b <name>
    等价于git branch <name>+git checkout <name>创建+切换分支: 
+ git branch -d <name>
    删除本地分支,如果本地分支没有被合并过，把-d换成-D强制删除
+ git remote prune origin 
    删除远端不存在的本地分支
+ git branch --set-upstream branch-name origin/branch-name
    建立本地分支和远程分支的关联，建议使用--set-upstream-to代替，原因一：git push有同名参数--set-upstream-to容易混淆，原因二：详见git branch --set-upstream-to
+ git branch --set-upstream-to origin/master master
    建立本地分支和远程分支的关联，默认本地分支可以省略，省略就表示当前分支；2012年引入此方法代替git branch --set-upstream
    因为git branch --set-upstream 后边跟的第一个参数是本地branch，有时候第一个参数被误写为远端branch导致行为混乱(git branch --set-upstream origin/master会在本地创建一个分支与当前分支关联)所以引入了--set-upstream-to，表示关联到远端分支，远端分支作为第一个参数，第二个参数表示本地分支可以忽略不写
    关联以后，后续push的时候就不需要指定远端分支。否则push的时候需要使用-u指定远端branch，git push -u origin remote-branch
+ git branch -vv
    显示与本地所有branch建立track的远端分支名称
+ git branch -m old_branch new_branch
    修改本地分支名称

+ git push origin --delete <name>
    删除远端分支，如果无法删除，则可以尝试先删除本地远端，然后再长传。git branch -r -d origin/branch-name，git push origin :branch-name
+ git push origin :old_branch
    修改远端分支名称，推送一个空的分支名到远程
+ git push --set-upstream origin/new_branch branch
    当前branch与远端origin/new_branch建立tracking
+ git branch --edit-description
    这将打开您的编辑器,并允许您将元数据附加到分支.您可以提取它：
+ git config branch.<branch>.description
    提取branch的描述信息