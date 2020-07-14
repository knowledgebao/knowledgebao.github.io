# 1. sdplog

- [1. sdplog](#1-sdplog)
  - [1.1. 简介](#11-简介)
  - [1.2. 结构概念介绍](#12-结构概念介绍)
    - [1.2.1. 文件结构](#121-文件结构)
    - [1.2.2. 概念介绍](#122-概念介绍)
  - [1.3. 常用方法](#13-常用方法)
  - [1.4. 注意事项](#14-注意事项)
  - [1.5. 参考资料](#15-参考资料)

## 1.1. 简介

spdlog是基于C++ 11的日志组件，它非常轻量，使用时你仅仅需要引入头文件就可以了。

## 1.2. 结构概念介绍

### 1.2.1. 文件结构

- sdplog
  - details
    - os.h/os-inl.h 实现操作系统相关功能，包括系统时间获取。支持utc和本地时间
  - fmt
  - sinks
  - other.h
  - formatter.h 基类，抽象类
    - pattern_formatter.h/pattern_formatter-inl.h 字段格式化
      - format 字符串格式化

### 1.2.2. 概念介绍

- fmt: 第三方结构化库，使用 {} 替代 %s, %d 等
- details: 封装的一些功能类，包括文件操作，内存操作，线程池，mutex等
- sinks: 日志目标文件夹
  - base 基本日志
  - daily_file 按照大小的循环覆盖日志
  - rotating_file 按照日期的循环覆盖日志
  - stdout 输出到控制台

## 1.3. 常用方法

- 支持实现使用本地时间还是utc时间

## 1.4. 注意事项

1. 如果需要修改日志的时间，可以在 pattern_formatter::get_time_中修改 msg.time 参数,linux下使用::clock_gettime(CLOCK_REALTIME_COARSE, &ts);windows使用 std::chrono::system_clock::now()

## 1.5. 参考资料

1. [wiki](https://github.com/gabime/spdlog/wiki)
2. [github](https://github.com/gabime/spdlog)
3. [spdlog学习笔记](https://blog.csdn.net/haojie_superstar/article/details/89383433?utm_medium=distribute.wap_relevant.none-task-blog-title-2)
4. [fmt](https://github.com/fmtlib/fmt)
