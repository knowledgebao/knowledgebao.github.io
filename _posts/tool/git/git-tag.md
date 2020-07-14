# 1. git-tag

- [1. git-tag](#1-git-tag)
  - [1.1. 简介](#11-简介)
  - [1.2. 常用命令](#12-常用命令)
    - [1.2.1. 查看tag](#121-查看tag)
    - [1.2.2. 打tag](#122-打tag)
    - [1.2.3. 删除tag](#123-删除tag)
    - [1.2.4. 推送tag](#124-推送tag)
    - [1.2.5. 查看tag提交信息](#125-查看tag提交信息)
  - [1.3. 参考资料](#13-参考资料)

## 1.1. 简介

Git 可以给仓库历史中的某一个提交打上标签，以示重要。 比较有代表性的是人们会使用这个功能来标记发布结点（ v1.0 、 v2.0 等等）。 在本节中，你将会学习如何列出已有的标签、如何创建和删除新的标签、以及不同类型的标签分别是什么。

## 1.2. 常用命令

### 1.2.1. 查看tag

1. 查看本地分支标签 `git tag`
2. 查看远程所有标签 `git ls-remote --tags`

### 1.2.2. 打tag

1. 给当前分支打标签 `git tag 《标签名》`
2. 给特定的某个commit版本打标签 `git tag v1.0.0 039bf8b`

### 1.2.3. 删除tag

1. 删除本地某个标签 `git tag --delete v1.0.0`
2. 删除远程的某个标签 `git push --delete origin v1.0.0` 或 `git push origin --delete v1.0.0`

 有些git版本可以使用 -d 代替 --delete

### 1.2.4. 推送tag

1. 将本地标签一次性推送到远程 `git push --tags` 或 `git push --tag` 或 `git push origin --tags` 或 `git push origin --tag`
2. 将本地某个特定标签推送到远程 `git push origin v1.0.0`

### 1.2.5. 查看tag提交信息

1. git show v1.0.0

## 1.3. 参考资料

1. [git tag的基本用法](https://www.jianshu.com/p/154d58451ef7)