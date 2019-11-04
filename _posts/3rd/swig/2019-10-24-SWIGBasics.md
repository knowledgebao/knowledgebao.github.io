---
layout: post
title: SWIGBasics
date: 2019-10-24 10:45:28
description: SWIGBasics
tag: swig

---
- [基础](#基础)
  - [运行swig](#运行swig)
    - [输入格式](#输入格式)
    - [SWIG输出](#swig输出)
    - [注释](#注释)
    - [预处理器](#预处理器)
    - [SWIG指令](#swig指令)
    - [解析显示](#解析显示)
  - [封装简单的C声明](#封装简单的c声明)
    - [Basic Type Handling](#basic-type-handling)
    - [Global Variables](#global-variables)
    - [Constants](#constants)
    - [A brief word about const](#a-brief-word-about-const)
    - [A cautionary tale of char *](#a-cautionary-tale-of-char-)
  - [Pointers and complex objects](#pointers-and-complex-objects)
    - [Simple pointers](#simple-pointers)
    - [Run time pointer type checking](#run-time-pointer-type-checking)
    - [Derived types, structs, and classes](#derived-types-structs-and-classes)
    - [Undefined datatypes](#undefined-datatypes)
    - [Typedef](#typedef)
  - [Other Practicalities](#other-practicalities)
    - [Passing structures by value](#passing-structures-by-value)
    - [Return by value](#return-by-value)
    - [Linking to structure variables](#linking-to-structure-variables)
    - [Linking to char *](#linking-to-char-)
    - [Arrays](#arrays)
    - [Creating read-only variables](#creating-read-only-variables)
    - [Renaming and ignoring declarations](#renaming-and-ignoring-declarations)
      - [Simple renaming of specific identifiers](#simple-renaming-of-specific-identifiers)
      - [Advanced renaming support](#advanced-renaming-support)
      - [Limiting global renaming rules](#limiting-global-renaming-rules)
      - [Ignoring everything then wrapping a few selected symbols](#ignoring-everything-then-wrapping-a-few-selected-symbols)
    - [Default/optional arguments](#defaultoptional-arguments)
    - [Pointers to functions and callbacks](#pointers-to-functions-and-callbacks)
  - [Structures and unions](#structures-and-unions)
    - [Typedef and structures](#typedef-and-structures)
    - [Character strings and structures](#character-strings-and-structures)
    - [Array members](#array-members)
    - [Structure data members](#structure-data-members)
    - [C constructors and destructors](#c-constructors-and-destructors)
    - [Adding member functions to C structures](#adding-member-functions-to-c-structures)
    - [Nested structures](#nested-structures)
    - [Other things to note about structure wrapping](#other-things-to-note-about-structure-wrapping)
  - [Code Insertion](#code-insertion)
    - [The output of SWIG](#the-output-of-swig)
    - [Code insertion blocks](#code-insertion-blocks)
    - [Inlined code blocks](#inlined-code-blocks)
    - [Initialization blocks](#initialization-blocks)
  - [An Interface Building Strategy](#an-interface-building-strategy)
    - [Preparing a C program for SWIG](#preparing-a-c-program-for-swig)
    - [The SWIG interface file](#the-swig-interface-file)
    - [Why use separate interface files?](#why-use-separate-interface-files)
    - [Getting the right header files](#getting-the-right-header-files)
    - [What to do with main()](#what-to-do-with-main)

# 基础
说明：此内容主要来源是：http://www.swig.org/Doc4.0/SWIG.html#SWIG  
[翻译文档](SWIG基础.pdf)  
&emsp;&emsp;这章主要描述SWIG的基础，输入文件的结构，如何处理标准ISO的C声明。下一章是关于C++的支持描述。然后这一章是下一章的基础。其它不同语言的描述在后续章节中。
## 运行swig
    为了运行swig，需要这样调用swig [ options ] filename，其中filename就是swig接口文件或者一个C/C++头文件，可以通过 `swig -help` 命令获取swig接口文件完整信息，也可以通过 `swit -c++ -help` 查看C++的命令完整信息，其他语言类似。

    也可以把options写的文件中，通过 swig @file 方式调用，file中的option通过空格分隔，如果参数中有空格，需要用引号引起来。当然file中也可以继续通过@file的方式嵌套调用，如果file不存在或不可读，则swig也不会报错，只会把它单个字符串进行处理。

### 输入格式
&emsp;&emsp;输入文件是以 .i 或 .swig 结尾的文件，包含C/C++声明和SWIG指令。大部分情况长这个样子。
```
%module mymodule 
%{
#include "myheader.h"
%}
// Now list ISO C/C++ declarations
int foo;
int bar(int x);
...
```
module具体可以参考[Modles模块](http://www.swig.org/Doc4.0/Modules.html#Modules_introduction)

### SWIG输出
&emsp;&emsp;输出文件是一个后缀是 .c 或 .cpp 的文件，当然也可以通过 -o 或 -outdir 来指定输出名称及路径。C/C++使用输出的文件编译成一个库即可被目标语言使用。在生成 .c 或 .cpp 的文件的同时，会同时生成目标语言对应的文件，供目标语言使用。
### 注释
C/C++注释可以出现在接口文件的任何位置，之前的版本主要用注释来生成文档。这个特征被修改了，在稍后的SWIG release中详细说明。
### 预处理器
&emsp;&emsp;与C语言一样，SWIG通过增强版的C预处理器对所有输入文件进行预处理。支持所有标准的预处理器特性，包括文件包含、条件编译和宏。但是，除非提供了-includeall命令行选项，否则将忽略#include语句。禁用include的原因是，SWIG有时用于处理原始的C头文件。在这种情况下，通常只希望扩展模块在提供的头文件中包含函数，而不是对内容进行预处理。  
&emsp;&emsp;还应该注意的是，SWIG预处理程序会跳过%{…%}。此外，预处理器还包括大量的宏处理增强功能，使其比普通的C预处理器更强大。这些扩展在“[预处理器](http://www.swig.org/Doc4.0/Preprocessor.html#Preprocessor)”一章中进行了描述。
### SWIG指令
&emsp;&emsp;SWIG的大部分操作是由特殊指令控制的，这些指令前面总是有一个“%”，以将它们与普通的C声明区分开来。这些指令用于提供SWIG提示或以某种方式改变SWIG的解析行为。  
&emsp;&emsp;由于SWIG指令不是合法的C语法，它通常不可能包括在头文件。然而，SWIG指令可以包括在C头文件使用条件编译像这样:
```
/* header.h  --- Some header file */

/* SWIG directives -- only seen if SWIG is running */ 
#ifdef SWIG
%module foo
#endif
```

### 解析显示
&emsp;&emsp;虽然SWIG可以解析大多数C/ c++声明，但它没有提供完整的C/ c++解析器实现。这些限制大多涉及非常复杂的类型声明和某些高级c++特性。具体来说，目前不支持以下功能:
+ 非常规类型声明,比如：
```
/* Non-conventional placement of storage specifier (extern) */
const int extern Number;

/* Extra declarator grouping */
Matrix (foo);    // A global variable

/* Extra declarator grouping in parameters */
void bar(Spam (Grok)(Doh));
```
+ c++源文件(.C、.cpp或.cxx文件中的代码)作为SWIG的接口文件
+ 一些新特性，可能版本跟不上
## 封装简单的C声明

### Basic Type Handling
### Global Variables
### Constants
### A brief word about const
### A cautionary tale of char *
## Pointers and complex objects
### Simple pointers
### Run time pointer type checking
### Derived types, structs, and classes
### Undefined datatypes
### Typedef
## Other Practicalities
### Passing structures by value
### Return by value
### Linking to structure variables
### Linking to char *
### Arrays
### Creating read-only variables
### Renaming and ignoring declarations
#### Simple renaming of specific identifiers
#### Advanced renaming support
#### Limiting global renaming rules
#### Ignoring everything then wrapping a few selected symbols
### Default/optional arguments
### Pointers to functions and callbacks
## Structures and unions
### Typedef and structures
### Character strings and structures
### Array members
### Structure data members
### C constructors and destructors
### Adding member functions to C structures
### Nested structures
### Other things to note about structure wrapping
## Code Insertion
### The output of SWIG
### Code insertion blocks
### Inlined code blocks
### Initialization blocks
## An Interface Building Strategy
### Preparing a C program for SWIG
### The SWIG interface file
### Why use separate interface files?
### Getting the right header files
### What to do with main()