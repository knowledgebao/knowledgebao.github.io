---
layout: post
title: cmake-find_package
date: 2019-11-27 17:40:47
description: cmake-find_package
tag: cmake

---
## 第3章，检测外部库和程序，展示CMake如何简化对项目依赖项的检测

1. 使用CMake自带的find-module(调用find_package函数)，但并不是所有的包在CMake的find模块都找得到。
   - find_package是包装器命令，用于发现和设置包的CMake模块。这些模块包含CMake命令，用于标识系统标准位置中的包。CMake模块文件称为`Find<name>.cmake`，当调用find_package(`<name>`)时，模块中的命令将会运行。
   - `Find<name>.cmake`一般位于cmake的按照目录的Modules文件夹下,或者供应商按照在标准位置的cmake的文件夹下
   - execute_process ,命令将作为CMake命令的子进程执行一个或多个命令。最后，子进程返回值将保存到变量作为参数传递给RESULT_VARIABLE，而管道标准输出和标准错误的内容将被保存到变量作为参数传递给OUTPUT_VARIABLE和ERROR_VARIABLE。execute_process可以执行任何命令，并使用它们的结果来推断系统的配置。include(FindPackageHandleStandardArgs)
   - add_custom_command 引用此命令时，可以正确的处理与版本相关的选项(REQUIRED和EXACT)，而无需更多的CMake代码。需要include(FindPackageHandleStandardArgs)
   - find_package_handle_standard_args 命令提供了标准工具，用于处理与查找安装系统上的相关程序和库。include(FindPackageHandleStandardArgs)
2. 使用`<package>Config.cmake, <package>ConfigVersion.cmake`和`<package>Targets.cmake`，这些文件由软件包供应商提供，并与软件包一起安装在标准位置的cmake文件夹下。
3. 依赖pkg-config程序，来找到系统上的包。这依赖于包供应商在.pc配置文件中，其中有关于发行包的元数据。
   - pkg_check_modules，查找传递列表中的所有模块(库和/或程序)
   - pkg_search_module，要在传递的列表中找到第一个工作模块
4. 为依赖项编写自己的find-package模块