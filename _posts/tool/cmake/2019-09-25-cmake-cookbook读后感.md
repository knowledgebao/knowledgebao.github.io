---
layout: post
title: cmake-cookbook读后感
date: 2019-12-11 10:11:20
description: cmake-cookbook读后感
tag: cmake

---
# CMake Cookbook读后感

## 第5章，配置时操作和构建时操作，展示了如何使用跨平台CMake命令在构建过程的不同阶段执行定制操作

1. CMake工作流程相关的时序:
   - CMake时或构建时：CMake正在运行，并处理项目中的CMakeLists.txt文件。
   - 生成时：生成构建工具(如Makefile或Visual Studio项目文件)。比如:cmake ..
   - 构建时：由CMake生成相应平台的原生构建脚本，在脚本中调用原生工具构建。此时，将调用编译器在特定的构建目录中构建目标(可执行文件和库)。比如:cmake --build .
   - CTest时或测试时：运行测试套件以检查目标是否按预期执行。
   - CDash时或报告时：当测试结果上传到仪表板上，与其他开发人员共享测试报告。
   - 安装时：当目标、源文件、可执行程序和库，从构建目录安装到相应位置。
   - CPack时或打包时：将项目打包用以分发时，可以是源码，也可以是二进制。
   - 包安装时：新生成的包在系统范围内安装。
2. 文件操作
   - add_custom_target，创建执行自定义命令的目标
     - 构建用户自己的target,比如解压缩或者执行一些其他操作,别的target可以依赖此target
3. 配置时运行自定义命令
   - execute_process，从CMake中执行任意进程，并检索它们的输出。
4. 运行时运行自定义命令
   - add_custom_command 向目标添加规则，并通过执行命令生成输出。add_custom_command中声明的任何目标，即在相同的CMakeLists.txt中声明的任何目标，使用输出的任何文件作为源文件的目标，在构建时会有规则生成这些文件。因此，源文件生成在构建时，目标和自定义命令在构建系统生成时，将自动处理依赖关系。
   - add_custom_command 有两个限制(第二个限制，可以使用add_dependencies来避免。不过，规避这两个限制的正确方法是使用add_custom_target命令，我们将在下一节的示例中详细介绍。):
     - 只有在相同的CMakeLists.txt中，指定了所有依赖于其输出的目标时才有效。
     - 对于不同的独立目标，使用add_custom_command的输出可以重新执行定制命令。这可能会导致冲突，应该避免这种情况的发生。
   - add_custom_command 可以通过指定参数,指定执行时间
     - PRE_BUILD：在执行与目标相关的任何其他规则之前执行的命令。但能在Visual Studio 7或更高版本进行。
     - PRE_LINK：使用此选项，命令在编译目标之后，调用链接器或归档器之前执行。Visual Studio 7或更高版本之外的生成器中使用PRE_BUILD将被解释为PRE_LINK。
     - POST_BUILD：如前所述，这些命令将在执行给定目标的所有规则之后运行。

## 参考资料

1. [CMake Cookbook](https://chenxiaowei.gitbook.io/cmake-cookbook/)
