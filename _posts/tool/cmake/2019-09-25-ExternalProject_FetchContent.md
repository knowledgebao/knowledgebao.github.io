---
layout: post
title: ExternalProject_FetchContent
date: 2019-09-24 21:08:35
description: ExternalProject_FetchContent
tag: cmake

---
# 使用及编译第三方库
[ExternalProject](https://cmake.org/cmake/help/latest/module/ExternalProject.html)
[FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html)
+ ExternalProject是老的第三方管理API
+ FetchContent是3.11（大约发行于2018年4月份左右）开始引入的一个模块。这个模块可以看成是原来 ExternalProject 模块的一个升级。也就是说FetchContent可以替换ExternalProject

## FetchContent涉及的方法 
+ 此方法是ExternalProject的扩展和优化,将声明与实现分离.而ExternalProject都集成到ExternalProject_Add接口中.
+ FetchContent_Declare :声明一个依赖项,对标ExternalProject_Add的Directory/Download,ExternalProject_Add的Directory/Download大部分参数都可用于FetchContent_Declare(FetchContent_Declare只是声明,不支持configure, build, install and test steps)
+ FetchContent_Populate :执行声明,甚至于没有FetchContent_Declare的话,FetchContent_Populate也可以直接执行,只是需要包含FetchContent_Declare对应的内容.
+ FetchContent_GetProperties :获取属性
+ FetchContent_MakeAvailable :等效于FetchContent_Populate() and add_subdirectory()

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


## ExternalProject 涉及方法
+ ExternalProject_Add 创建一个外部target,Download/Update/patch,configure,build,install and test.比FetchContent_Declare功能强大,相当于FetchContent_Declare/FetchContent_Populate的组合,比较复杂.可以定制外部项目
  + 参数分为几大类,每一类下边又有很多参数
    + Directory Options :目录结构相关
    + Download Step Options: 下载方法
      + URL Download
        + ...
      + Git
        + ...
      + Subversion
        + ...
      + Mercurial
        + ...
      + CVS
        + ...
    + Update/Patch Step Options: 更新
      + ...
    + Configure Step Options: 重写configure过程
      + ...
    + Build Step Options: 自定义编译步骤,比如非CMake/Makefile工程
      + ...
    + Install Step Options: 自定义安装步骤,比如非CMake/Makefile工程
      + ...
    + Test Step Options: 自定义测试步骤
      + ...
    + Output Logging Options: 日志选项
      + ...
    + Terminal Access Options: 访问终端输入
      + ...
    + Target Options: target选项
      + ...
    + Miscellaneous Options: 其他选项
      + ...
+ ExternalProject_Get_Property 
  + 类似于FetchContent_GetProperties
+ ExternalProject_Add_Step 
  + 除去ExternalProject_Add中几大步骤之外,再定义自己的步骤,非Download/Update/patch,configure,build,install and test,一般很少用
+ ExternalProject_Add_StepTargets 
  + 为每个子步骤定义target, <name>-<step>形式,一般很少用
+ ExternalProject_Add_StepDependencies 
  + 为每个子步骤添加依赖项,一般很少用