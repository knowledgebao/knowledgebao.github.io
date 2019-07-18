---
layout: post
title: build--tags
date: 2019-07-10 18:40:12
description: build--tags
tag: go

---
# 关于编译选项-tags的整理
**-tags** build的一个编译选项  
此标记用于指定在实际编译期间需要受理的编译标签（也可被称为编译约束）的列表。   这些编译标签一般会作为源码文件开始处的注释的一部分，例如，在$GOROOT/src/os/file_posix.go开始处的注释为：
```
// Copyright 2009 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// +build darwin dragonfly freebsd linux nacl netbsd openbsd solaris windows
```
最后一行注释即包含了与编译标签有关的内容。大家可以查看代码包go/build的文档已获得更多的关于编译标签的信息。

## 相关链接
1. 命名规则，及简单使用[go build -tags 试验](https://studygolang.com/articles/19280)
2. 对应源码的包目录[Package build](http://docscn.studygolang.com/pkg/go/build/)

## 摘抄说明
### 作用
编译满足规则的文件

### 使用方法
1. 构建约束以一行+build开始的注释。在+build之后列出了一些条件，在这些条件成立时，该文件应包含在编译的包中；
1. 约束可以出现在任何源文件中，不限于go文件；
1. +build必须出现在package语句之前，+build注释之后应要有一个空行。
```
// 
// +build debug

package main

import "fmt"

func main() {
 fmt.Println("Hello World!")
}
```
### 语法规则
1. 只允许是字母数字或_
1. 多个条件之间，空格表示OR；逗号表示AND；叹号(!)表示NOT
1. 一个文件可以有多个+build，它们之间的关系是AND。如：
```
// +build linux darwin
// +build 386
等价于
// +build (linux OR darwin) AND 386
```
1. 预定义了一些条件：runtime.GOOS、runtime.GOARCH、compiler（gc或gccgo）、cgo、context.BuildTags中的其他单词
1. 如果一个文件名（不含后缀），以 *_GOOS, *_GOARCH, 或 *_GOOS_GOARCH结尾，它们隐式包含了 构建约束
1. 当不想编译某个文件时，可以加上// +build ignore。这里的ignore可以是其他单词，只是ignore更能让人知道什么意思
更多详细信息，可以查看go/build/build.go文件中shouldBuild和match方法。
