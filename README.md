# knowledgebao

本博客在[leopardpan](https://github.com/leopardpan/leopardpan.github.io.git)基础上修改的。  

博客对应代码位置：
https://github.com/knowledgebao/gotest

注意点：
1. _posts中的文件必须以是markdown格式的文件，并且文件名称以年月日(xx-xx-xx)开头。文件内容开头必须包含下边内容：
```
---
layout: post
title: test
date: 2019-06-28 13:39:10
description: test
tag: _posts

---
```
其中layout固定，title是标题，date是时间，description是描述信息，tag是标签也就是分类(博客分类就是按照这个来分类)。  
2. 由于_posts下文件格式的特殊性，我专门写了个函数专门来处理指定目录下的文件，使其复合博客发布要求。代码位置：https://github.com/knowledgebao/gotest/fileprocess/fileprocess.go
3. 本地启动命令 jekyll server