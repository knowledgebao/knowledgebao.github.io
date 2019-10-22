---
layout: post
title: dockerCommand
date: 2019-10-18 20:35:10
description: dockerCommand
tag: docker

---
- [docker常用命令](#docker常用命令)
  - [名称解释](#名称解释)
    - [玄虚镜像](#玄虚镜像)
  - [常用命令](#常用命令)
    - [pull](#pull)
    - [image ls](#image-ls)
    - [image prune](#image-prune)
    - [system df](#system-df)
    - [docker image rm](#docker-image-rm)
  - [参考资料](#参考资料)

# docker常用命令
## 名称解释
### 玄虚镜像
    仓库名、标签均为 <none> 的镜像

## 常用命令
### pull
    具体的选项可以通过 docker pull --help 命令看到
    docker pull [选项] [Docker Registry 地址[:端口号]/]仓库名[:标签]
### image ls
    显示所有顶层镜像
    -f 表示过滤的意思,有点类似grep
    -f dangling=true 过滤出玄虚镜像
    -f since=mongo:3.2 显示mongo:3.2之后的版本
    -f since=before:3.2 显示mongo:3.2之前的版本
    -a 同时显示中间层镜像(中间层镜像只会被保存一份)
    -q 只显示ID
    --format "{{.ID}}: {{.Repository}}" 只显示ID和仓库名,这是模板语法
    --format "table {{.ID}}\t{{.Repository}}\t{{.Tag}}" 按指定顺序显示列
    可以直接加仓库名或者仓库名:标签 来精确搜索镜像
    如果镜像构建时，定义了 LABEL，还可以通过 LABEL 来过滤。
### image prune 
    删除玄虚镜像
### system df

### docker image rm

## 参考资料