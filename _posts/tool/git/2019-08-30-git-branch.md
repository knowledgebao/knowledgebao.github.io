---
layout: post
title: git-branch
date: 2019-12-10 11:06:27
description: git-branch
tag: git

---

# 1. git branch

- [<ol>
<li>git branch</li>
</ol>](#ol-ligit-branchli-ol)
  - [1.1. 分支功能](#11-%e5%88%86%e6%94%af%e5%8a%9f%e8%83%bd)
    - [1.1.1. 查看本地/远端分支](#111-%e6%9f%a5%e7%9c%8b%e6%9c%ac%e5%9c%b0%e8%bf%9c%e7%ab%af%e5%88%86%e6%94%af)
    - [1.1.2. 查看远端信息](#112-%e6%9f%a5%e7%9c%8b%e8%bf%9c%e7%ab%af%e4%bf%a1%e6%81%af)
    - [1.1.3. 显示本地对应的远程](#113-%e6%98%be%e7%a4%ba%e6%9c%ac%e5%9c%b0%e5%af%b9%e5%ba%94%e7%9a%84%e8%bf%9c%e7%a8%8b)
    - [1.1.4. 创建本地分支](#114-%e5%88%9b%e5%bb%ba%e6%9c%ac%e5%9c%b0%e5%88%86%e6%94%af)
    - [1.1.5. 切换分支](#115-%e5%88%87%e6%8d%a2%e5%88%86%e6%94%af)
    - [1.1.6. 创建并切换分支](#116-%e5%88%9b%e5%bb%ba%e5%b9%b6%e5%88%87%e6%8d%a2%e5%88%86%e6%94%af)
    - [1.1.7. 删除本地分支](#117-%e5%88%a0%e9%99%a4%e6%9c%ac%e5%9c%b0%e5%88%86%e6%94%af)
    - [1.1.8. 删除远端不存在的本地分支](#118-%e5%88%a0%e9%99%a4%e8%bf%9c%e7%ab%af%e4%b8%8d%e5%ad%98%e5%9c%a8%e7%9a%84%e6%9c%ac%e5%9c%b0%e5%88%86%e6%94%af)
    - [1.1.9. 关联本地分支与远端分支set-upstream(dpprecated)](#119-%e5%85%b3%e8%81%94%e6%9c%ac%e5%9c%b0%e5%88%86%e6%94%af%e4%b8%8e%e8%bf%9c%e7%ab%af%e5%88%86%e6%94%afset-upstreamdpprecated)
    - [1.1.10. 关联本地分支与远端分支set-upstream-to](#1110-%e5%85%b3%e8%81%94%e6%9c%ac%e5%9c%b0%e5%88%86%e6%94%af%e4%b8%8e%e8%bf%9c%e7%ab%af%e5%88%86%e6%94%afset-upstream-to)
    - [1.1.11. 修改本地分支名称](#1111-%e4%bf%ae%e6%94%b9%e6%9c%ac%e5%9c%b0%e5%88%86%e6%94%af%e5%90%8d%e7%a7%b0)
    - [1.1.12. 删除远端分支](#1112-%e5%88%a0%e9%99%a4%e8%bf%9c%e7%ab%af%e5%88%86%e6%94%af)
    - [1.1.13. 修改远端分支名称](#1113-%e4%bf%ae%e6%94%b9%e8%bf%9c%e7%ab%af%e5%88%86%e6%94%af%e5%90%8d%e7%a7%b0)
    - [1.1.14. 建立tracking](#1114-%e5%bb%ba%e7%ab%8btracking)
    - [1.1.15. 添加描述信息](#1115-%e6%b7%bb%e5%8a%a0%e6%8f%8f%e8%bf%b0%e4%bf%a1%e6%81%af)
    - [1.1.16. 提取branch的描述信息](#1116-%e6%8f%90%e5%8f%96branch%e7%9a%84%e6%8f%8f%e8%bf%b0%e4%bf%a1%e6%81%af)
  - [1.2. 辅助功能](#12-%e8%be%85%e5%8a%a9%e5%8a%9f%e8%83%bd)
    - [1.2.1. 列出所有分支的信息](#121-%e5%88%97%e5%87%ba%e6%89%80%e6%9c%89%e5%88%86%e6%94%af%e7%9a%84%e4%bf%a1%e6%81%af)
  - [1.3. 参考资料](#13-%e5%8f%82%e8%80%83%e8%b5%84%e6%96%99)

## 1.1. 分支功能

涉及名称说明

- branch-name  表示分支名称
- origin  表示远程主机名
- commid 提交的ID

参数说明

### 1.1.1. 查看本地/远端分支

`git branch [-r/-a]`
查看所有本地分支,默认查看本地分支,-r表示远端分支,-a表示本地+远端分支

### 1.1.2. 查看远端信息

`git remote show origin`
查看关于远端origin的一些信息，包括分支是否tracking

### 1.1.3. 显示本地对应的远程

git branch -vv
显示与本地所有branch建立track的远端分支名称

### 1.1.4. 创建本地分支

git branch branch-name commid
创建本地分支,可以基于某一次提交，默认基于当前HEAD创建分支。

### 1.1.5. 切换分支

git checkout branch-name
git checkout branch-name2 origin/branch-name

1. 切换分支，如果本地没有，则从远端下载分支后再切换，如果远端也没有，则执行失败。当然前提是通过`get fetch`更新了远端分支信息到本地。
2. 第二条命令可以指定本地分支名称与远端分支名称不一样(一般这种情况不存在)。

### 1.1.6. 创建并切换分支

git checkout -b branch-name
等价于git branch branch-name + git checkout branch-name创建+切换分支

### 1.1.7. 删除本地分支

git branch -d branch-name
删除本地分支,如果本地分支没有被合并过，把-d换成-D强制删除

### 1.1.8. 删除远端不存在的本地分支

git remote prune origin

### 1.1.9. 关联本地分支与远端分支set-upstream(dpprecated)

git branch --set-upstream branch-name origin/branch-name

建立本地分支和远程分支的关联，建议使用--set-upstream-to代替  
原因一：git push有同名参数--set-upstream-to容易混淆  
原因二：详见git branch --set-upstream-to

### 1.1.10. 关联本地分支与远端分支set-upstream-to

git branch --set-upstream-to origin/master master

建立本地分支和远程分支的关联，默认本地分支可以省略，省略就表示当前分支；2012年引入此方法代替git branch --set-upstream
因为git branch --set-upstream 后边跟的第一个参数是本地branch，有时候第一个参数被误写为远端branch导致行为混乱(git branch --set-upstream origin/master会在本地创建一个分支与当前分支关联)所以引入了--set-upstream-to，表示关联到远端分支，远端分支作为第一个参数，第二个参数表示本地分支可以忽略不写
关联以后，后续push的时候就不需要指定远端分支。否则push的时候需要使用-u指定远端branch，git push -u origin remote-branch

### 1.1.11. 修改本地分支名称

前提是还没有删除远端分支，如果已经上传远端分支，参考“修改远端分支名称”
git branch -m old_branch new_branch
如果已经位于 old_branch 分支下边，可以省略 old_branch

### 1.1.12. 删除远端分支

git push origin --delete branch-name
git push origin :old_branch 巧用改名删除

删除远端分支，如果无法删除，则可以尝试先删除本地远端，然后再上传。
git branch -r -d origin/branch-name，git push origin :branch-name

### 1.1.13. 修改远端分支名称

1. 修改本地分支：git branch -m oldName newName
2. 删除远端分支:git push --delete origin oldName
3. 推送本地分支：git push origin newName
4. 关联本地与远端分支:git branch --set-upstream-to origin/newName

更简单的步骤：

1. 切换到需要改名称的分支: git checkout oldName
2. 修改本地分支: git branch -m newName
3. 删除远端分支: git push --delete origin oldName
4. 推送同名到远端: git push origin HEAD

修改远端分支名称，推送一个空的分支名到远程

### 1.1.14. 建立tracking

git push --set-upstream origin/new_branch branch
当前branch与远端origin/new_branch建立tracking

### 1.1.15. 添加描述信息

git branch --edit-description
这将打开您的编辑器,并允许您将元数据附加到分支.您可以提取它：

### 1.1.16. 提取branch的描述信息

git config branch.branch-name.description

## 1.2. 辅助功能

### 1.2.1. 列出所有分支的信息

可以写在如下文件里：`C:\msys64\home\Administrator\.bashrc`
前提是需要通过git branch --edit-description为分支命名

```bash
alias gitbrdesc='for line in $(git branch); do
     description=$(git config branch.$line.description)
     if [ -n "$description" ]; then
       echo "$line     $description"
     fi
     done'
```

## 1.3. 参考资料
