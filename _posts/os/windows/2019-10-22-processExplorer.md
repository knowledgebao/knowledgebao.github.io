---
layout: post
title: processExplorer
date: 2019-10-22 18:27:23
description: processExplorer
tag: windows

---

- [processExploer](#processexploer)
  - [简介](#简介)
  - [功能说明](#功能说明)
    - [System Information](#system-information)
  - [问题集](#问题集)
    - [1. Windows 任务管理器被Process Explorer 取代后如何恢复](#1-windows-任务管理器被process-explorer-取代后如何恢复)
  - [参考资料](#参考资料)
    - [1.Windows任务管理器被procexp(Process Explorer)取代后如何恢复](#1windows任务管理器被procexpprocess-explorer取代后如何恢复)
    - [2.[]()](#2)

# processExploer
## 简介
    这是一款由Sysinternals开发的Windows系统和应用程序监视工具，目前Sysinternals已经被微软收购，此款不仅结合了文件监视和注册表监视两个工具的功能，还增加了多项重要的增强功能，此工具支持64位Windows系统
## 功能说明
### System Information
    系统信息,可以统计CPU/内存/IO/GPU等使用情况,CPU标签可以切换所有和单个CPU的显示.

## 问题集
### 1. Windows 任务管理器被Process Explorer 取代后如何恢复
+ 打开注册表:HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options\taskmgr.exe
+ 里面的Debugger就是processExploer替换默认任务管理器添加进来的，指定了 Process Explorer 的路径。删掉Debugger这一项就能恢复任务管理器了。(注意：是删掉Debugger，而不是删除)taskmgr.exe

## 参考资料
### 1.[Windows任务管理器被procexp(Process Explorer)取代后如何恢复](https://blog.csdn.net/pijianzhirui/article/details/83592596)
### 2.[]()