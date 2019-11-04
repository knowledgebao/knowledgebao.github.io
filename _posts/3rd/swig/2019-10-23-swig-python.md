---
layout: post
title: swig-python
date: 2019-10-23 20:40:39
description: swig-python
tag: swig

---
- [swig-python](#swig-python)
  - [简介](#简介)
  - [SWIG文档说明](#swig文档说明)
  - [参考文档](#参考文档)
    - [1.swig自引用](#1swig自引用)
    - [2.利用 SWIG 对 C++ 库进行 Python 包装](#2利用-swig-对-c-库进行-python-包装)

# swig-python
## 简介
利用SWIG，可以现实以下功能：
+ 用Python调用C/C++库
+ 用Python继承C++类，并在Python中使用该继承类
+ C++使用Python扩展（通过文档描述应该可以支持，未验证）

## SWIG文档说明
&emsp;&emsp;SWIG的文档非常详尽，我甚至觉得太过详尽，不可能全看。我刚开始因为对SWIG文档组织不熟悉，看完一部分SWIG Basices就开始尝试，一路摸索到可以使用，后来才发现SWIG还有针对Python的专门文档。相比之下我之前摸索到的方案相当丑陋。

SWIG文档大体分两部分：  
&emsp;&emsp;一部分为SWIG本身：SWIG基本使用，对C及C++的支持，SWIG库及扩展等
另一部分为SWIG对每一个目标语言的文档，如SWIG和Python的文档。我建议只看和具体语言相关的文档，遇到问题时再去看SWIG本身的相关部分。  
&emsp;&emsp;喜欢原汁原味且有充足时间又comfortable with English的同学可直接看SWIG的文档。

## 参考文档
### 1.[swig自引用](swig.md)
### 2.[利用 SWIG 对 C++ 库进行 Python 包装](https://segmentfault.com/a/1190000013219667)
