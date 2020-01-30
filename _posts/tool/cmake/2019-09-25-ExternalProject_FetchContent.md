---
layout: post
title: ExternalProject_FetchContent
date: 2019-12-03 21:10:24
description: ExternalProject_FetchContent
tag: cmake

---


# 1. 使用及编译第三方库

- [1. 使用及编译第三方库](#1-%e4%bd%bf%e7%94%a8%e5%8f%8a%e7%bc%96%e8%af%91%e7%ac%ac%e4%b8%89%e6%96%b9%e5%ba%93)
  - [1.1. 简介](#11-%e7%ae%80%e4%bb%8b)
  - [1.2. ExternalProject](#12-externalproject)
    - [1.2.1. 说明](#121-%e8%af%b4%e6%98%8e)
    - [1.2.2. 函数](#122-%e5%87%bd%e6%95%b0)
      - [1.2.2.1. ExternalProject_Add](#1221-externalprojectadd)
        - [1.2.2.1.1. 目录参数](#12211-%e7%9b%ae%e5%bd%95%e5%8f%82%e6%95%b0)
        - [1.2.2.1.2. 下载步骤参数](#12212-%e4%b8%8b%e8%bd%bd%e6%ad%a5%e9%aa%a4%e5%8f%82%e6%95%b0)
        - [1.2.2.1.3. Update/Patch Step Options](#12213-updatepatch-step-options)
        - [1.2.2.1.4. Configure Step Options](#12214-configure-step-options)
        - [1.2.2.1.5. Build Step Options](#12215-build-step-options)
        - [1.2.2.1.6. Install Step Options](#12216-install-step-options)
        - [1.2.2.1.7. Test Step Options](#12217-test-step-options)
        - [1.2.2.1.8. Output Logging Options](#12218-output-logging-options)
        - [1.2.2.1.9. Terminal Access Options](#12219-terminal-access-options)
        - [1.2.2.1.10. Target Options](#122110-target-options)
        - [1.2.2.1.11. Miscellaneous Options](#122111-miscellaneous-options)
      - [1.2.2.2. ExternalProject_Get_Property](#1222-externalprojectgetproperty)
      - [1.2.2.3. ExternalProject_Add_Step](#1223-externalprojectaddstep)
      - [1.2.2.4. ExternalProject_Add_StepTargets](#1224-externalprojectaddsteptargets)
      - [1.2.2.5. ExternalProject_Add_StepDependencies](#1225-externalprojectaddstepdependencies)
  - [1.3. FetchContent](#13-fetchcontent)
    - [1.3.1. FetchContent说明](#131-fetchcontent%e8%af%b4%e6%98%8e)
      - [1.3.1.1. FetchContent_Declare](#1311-fetchcontentdeclare)
      - [1.3.1.2. FetchContent_Populate](#1312-fetchcontentpopulate)
      - [1.3.1.3. FetchContent_GetProperties](#1313-fetchcontentgetproperties)
      - [1.3.1.4. FetchContent_MakeAvailable](#1314-fetchcontentmakeavailable)
  - [1.4. 参考资料](#14-%e5%8f%82%e8%80%83%e8%b5%84%e6%96%99)

## 1.1. 简介

ExternalProject是老的第三方管理API
FetchContent是3.11（大约发行于2018年4月份左右）开始引入的一个模块。这个模块可以看成是原来 ExternalProject 模块的一个升级。也就是说FetchContent可以替换ExternalProject

## 1.2. ExternalProject

### 1.2.1. 说明

外部项目管理方法之一：ExternalProject

### 1.2.2. 函数

#### 1.2.2.1. ExternalProject_Add

ExternalProject_Add 创建一个外部target,Download/Update/patch,configure,build,install and test.比FetchContent_Declare功能强大,相当于FetchContent_Declare/FetchContent_Populate的组合,比较复杂.可以定制外部项目

##### 1.2.2.1.1. 目录参数

目录结构相关

`PREFIX  <dir>` : 根目录
`TMP_DIR  <dir>`: 临时目录
`STAMP_DIR <dir>` : 时间戳目录
`DOWNLOAD_DIR <dir>` : 解压缩文件之前要在其中存储下载文件的目录。该目录仅由URL下载方法使用，所有其他下载方法都SOURCE_DIR直接使用。
`SOURCE_DIR <dir>` : 将下载的内容解压缩到的源目录，或对于非URL下载方法，应检出，克隆存储库的目录等。如果未指定下载方法，则此目录必须指向外部已存在的现有目录项目已被解压或克隆/检出。
注意 如果指定了下载方法，则可以删除源目录中所有现有的内容。在启动下载之前，只有URL下载方法会检查此目录是否丢失或为空，如果不为空，则以错误停止。所有其他下载方法均以静默方式丢弃源目录中的所有先前内容。
`BINARY_DIR <dir>` : 指定构建目录位置。如果BUILD_IN_SOURCE启用，则忽略此选项 。
`INSTALL_DIR <dir>` : 安装目录
`LOG_DIR <dir>` : 日志目录

```cmake
如果PREFIX给定了选项或EP_PREFIX设置了 目录属性，那么将在指定的前缀下构建并安装一个外部项目

TMP_DIR      = <prefix>/tmp
STAMP_DIR    = <prefix>/src/<name>-stamp
DOWNLOAD_DIR = <prefix>/src
SOURCE_DIR   = <prefix>/src/<name>
BINARY_DIR   = <prefix>/src/<name>-build
INSTALL_DIR  = <prefix>
LOG_DIR      = <STAMP_DIR>

否则，如果EP_BASE设置了目录属性，则将外部项目的组件存储在指定的基础下

TMP_DIR      = <base>/tmp/<name>
STAMP_DIR    = <base>/Stamp/<name>
DOWNLOAD_DIR = <base>/Download/<name>
SOURCE_DIR   = <base>/Source/<name>
BINARY_DIR   = <base>/Build/<name>
INSTALL_DIR  = <base>/Install/<name>
LOG_DIR      = <STAMP_DIR>
```

##### 1.2.2.1.2. 下载步骤参数

如果使用该SOURCE_DIR选项指向现有的非空目录，则可以省略下载方法。否则，必须指定以下一种下载方法

`DOWNLOAD_COMMAND <cmd>...`

1. URL Download
2. Git
3. Subversion
4. Mercurial
5. CVS

##### 1.2.2.1.3. Update/Patch Step Options

: 更新

##### 1.2.2.1.4. Configure Step Options

: 重写configure过程

##### 1.2.2.1.5. Build Step Options

: 自定义编译步骤,比如非CMake/Makefile工程

##### 1.2.2.1.6. Install Step Options

: 自定义安装步骤,比如非CMake/Makefile工程

##### 1.2.2.1.7. Test Step Options

: 自定义测试步骤

##### 1.2.2.1.8. Output Logging Options

: 日志选项

##### 1.2.2.1.9. Terminal Access Options

: 访问终端输入

##### 1.2.2.1.10. Target Options

: target选项

##### 1.2.2.1.11. Miscellaneous Options

: 其他选项

#### 1.2.2.2. ExternalProject_Get_Property

  类似于FetchContent_GetProperties

#### 1.2.2.3. ExternalProject_Add_Step

  除去ExternalProject_Add中几大步骤之外,再定义自己的步骤,非Download/Update/patch,configure,build,install and test,一般很少用

#### 1.2.2.4. ExternalProject_Add_StepTargets
  
  为每个子步骤定义target, `<name>-<step>`形式,一般很少用

#### 1.2.2.5. ExternalProject_Add_StepDependencies
  
  为每个子步骤添加依赖项,一般很少用

## 1.3. FetchContent

### 1.3.1. FetchContent说明

+ 此方法是ExternalProject的扩展和优化,将声明与实现分离.而ExternalProject都集成到ExternalProject_Add接口中.

#### 1.3.1.1. FetchContent_Declare

  声明一个依赖项,对标ExternalProject_Add的Directory/Download,ExternalProject_Add的Directory/Download大部分参数都可用于FetchContent_Declare(FetchContent_Declare只是声明,不支持configure, build, install and test steps)

#### 1.3.1.2. FetchContent_Populate
  
  执行声明,甚至于没有FetchContent_Declare的话,FetchContent_Populate也可以直接执行,只是需要包含FetchContent_Declare对应的内容.

#### 1.3.1.3. FetchContent_GetProperties
  
  获取属性

#### 1.3.1.4. FetchContent_MakeAvailable
  
  等效于FetchContent_Populate() and add_subdirectory()

模板如下

```cmake
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.8.0
)

FetchContent_Declare(
  myCompanyIcons
  URL      https://intranet.mycompany.com/assets/iconset_1.12.tar.gz
  URL_HASH 5588a7b18261c20068beabfb4f530b87
)

FetchContent_Declare(
  myCompanyCertificates
  SVN_REPOSITORY svn+ssh://svn.mycompany.com/srv/svn/trunk/certs
  SVN_REVISION   -r12345
)
```

```cmake
# Check if population has already been performed
FetchContent_GetProperties(<name>)
string(TOLOWER "<name>" lcName)
if(NOT ${lcName}_POPULATED)
  # Fetch the content using previously declared details
  FetchContent_Populate(<name>)

  # Set custom variables, policies, etc.
  # ...

  # Bring the populated content into the build
  add_subdirectory(${${lcName}_SOURCE_DIR} ${${lcName}_BINARY_DIR})
endif()
```

## 1.4. 参考资料

1. [ExternalProject](https://cmake.org/cmake/help/latest/module/ExternalProject.html)
2. [FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html)