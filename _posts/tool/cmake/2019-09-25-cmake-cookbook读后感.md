---
layout: post
title: cmake-cookbook读后感
date: 2019-09-24 18:02:48
description: cmake-cookbook读后感
tag: cmake

---
# CMake Cookbook读后感
[CMake Cookbook](https://chenxiaowei.gitbook.io/cmake-cookbook/)
## 前言+配置环境
+ 介绍背景,介绍资料,介绍代码,介绍目录等
+ CMake及其姊妹CTest、CPack和CDash已经成为源码构建的主要工具集
+ 介绍CMake流程图
+ 环境搭建
+ 演示需要涉及到的库以及依赖
+ 源码位置以及测试环境,改进建议途经

## 第1章，从简单的可执行文件到库，展示了如何开始配置和使用CMake构建简单的可执行文件和库。
1. 编译可执行文件
    + cmake -H. -Bbuild等价于mkdir -p build ; cd build  ; cmake ..
    + GNU/Linux上，CMake默认生成Unix Makefile来构建项目：
      + Makefile: make将运行指令来构建项目。
      + CMakefile：包含临时文件的目录，CMake用于检测操作系统、编译器等。此外，根据所选的生成    器，它还包含特定的文件。
      + cmake_install.cmake：处理安装规则的CMake脚本，在项目安装时使用。
      + CMakeCache.txt：如文件名所示，CMake缓存。CMake在重新运行配置时使用这个文件。
    + 编译代码命令:cmake --build .
    + 执行指定target,比如clean等:cmake --build . --target clean
2. 切换生成器
   + cmake --help下边的generators就是生成器,比如:MSYS Makefiles,MinGW Makefiles,Visual Studio 15 2017 [arch],Ninja...
   + cmake -G Ninja .. 通过-G来指定切换生成器
   + cmake -G "Visual Studio 15 2017" ..
   + cmake -G "MSYS Makefiles" ..
3. 构建静态库和动态库
   + 同时生成同名的动态库和静态库
     + add_library(message-objs  OBJECT Message.hpp Message.cpp)
     + add_library(message-shared SHARED $&lt;TARGET_OBJECTS:message-objs&gt;)
     + add_library(message-static STATIC $&lt;TARGET_OBJECTS:message-objs&gt;)
     + set_target_properties(message-shared PROPERTIES OUTPUT_NAME "message")
     + set_target_properties(message-static PROPERTIES OUTPUT_NAME "message")
   + add_library(message STATIC Message.hpp Message.cpp)：生成必要的构建指令，将指定的源码编译到库中。add_library的第一个参数是目标名。整个CMakeLists.txt中，可使用相同的名称来引用库。生成的库的实际名称将由CMake通过在前面添加前缀lib和适当的扩展名作为后缀来形成。生成库是根据第二个参数(STATIC或SHARED)和操作系统确定的。
     + STATIC：用于创建静态库，即编译文件的打包存档，以便在链接其他目标时使用，例如：可执行文件。
     + SHARED：用于创建动态库，即可以动态链接，并在运行时加载的库。可以在CMakeLists.txt中使用`add_library(message SHARED Message.hpp Message.cpp) `从静态库切换到动态共享对象(DSO)。
     + OBJECT：可用于将给定给add_library的列表中的源码编译到目标文件，不将它们归档到静态库中，也不能将它们链接到共享对象中。如果需要一次性创建静态库和动态库，那么使用对象库尤其有用。我们将在本示例中演示。
     + MODULE：又为DSO组。与SHARED库不同，它们不链接到项目中的任何其他目标，但是可以在稍后进行动态加载。该参数可以用于构建运行时插件。
     + IMPORTED：此类库目标表示位于项目外部的库。此类库的主要用途是，对上游包提供的项目的现有依赖项进行建模。因此，IMPORTED库将被视为不可变的。我们将在本书的其他章节演示使用IMPORTED库的示例。参见: https://cmake.org/cmake/help/latest/manual/cmakebuildsystem.7.html#imported-targets 
     + INTERFACE：这种库与IMPORTED库类似，不过，该类型库可变，没有位置信息。它主要用于项目之外的目标建模使用。我们将在本章第5节中演示INTERFACE库的示例，在第11章中以Conda包的形式，发布依赖项。参见: https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#interface-libraries 
     + ALIAS：顾名思义，这种库为项目中已存在的库目标定义别名。不过，不能为IMPORTED库选择别名。参见: https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#alias-libraries
   + target_link_libraries(hello-world message): 将库链接到可执行文件。此命令还确保hello-world可执行文件可以正确地依赖于消息库。因此，我们确保在消息库链接到hello-world可执行文件之前，完成消息库的构建。
4. 条件句
   + set(USE_LIBRARY OFF) //预先定义好参数
   + if(USE_LIBRARY)…else(USE_LIBRARY)…endif(USE_LIBIRAY) 
5. 用户选项
   + option(USE_LIBRARY "Compile sources into a library" OFF) 
   + cmake -D USE_LIBRARY=ON .. //用户传递参数
6. 编译器选择
   + CMAKE_&lt;LANG&gt;_COMPILER ,其中&lt;LANG&gt;是受支持的任何一种语言,比如C/CXX/Fortran等
   + cmake --system-information information.txt 所有可以通过-D设置的参数
   + CMAKE_&lt;LANG&gt;_COMPILER_LOADED:如果为项目启用了语言&lt;LANG&gt;，则将设置为TRUE。
   + CMAKE_&lt;LANG&gt;_COMPILER_ID:编译器标识字符串，编译器供应商所特有。例如，GCC用于GNU编译器集合，AppleClang用于macOS上的Clang, MSVC用于Microsoft Visual Studio编译器。注意，不能保证为所有编译器或语言定义此变量。
   + CMAKE_COMPILER_IS_GNU&lt;LANG&gt;:如果语言&lt;LANG&gt;是GNU编译器集合的一部分，则将此逻辑变量设置为TRUE。注意变量名的&lt;LANG&gt;部分遵循GNU约定：C语言为CC, C++语言为CXX, Fortran语言为G77。
   + CMAKE_&lt;LANG&gt;_COMPILER_VERSION:此变量包含一个字符串，该字符串给定语言的编译器版本。版本信息在major[.minor[.patch[.tweak]]]中给出。但是，对于CMAKE_&lt;LANG&gt;_COMPILER_ID，不能保证所有编译器或语言都定义了此变量。
7. 构建类型
   + 控制生成构建系统使用的配置变量是CMAKE_BUILD_TYPE。该变量默认为空，CMake识别的值为:
      + Debug：用于在没有优化的情况下，使用带有调试符号构建库或可执行文件。
      + Release：用于构建的优化的库或可执行文件，不包含调试符号。
      + RelWithDebInfo：用于构建较少的优化库或可执行文件，包含调试符号。
      + MinSizeRel：用于不增加目标代码大小的优化方式，来构建库或可执行文件。
    + 比如:cmake .. -G"Visual Studio 12 2017 Win64" -D CMAKE_CONFIGURATION_TYPES="Release;Debug" //将为Release和Debug配置生成一个构建树。
      + cmake --build . --config Release //通过config指定具体编译类型
8. 编译器选项
   + 给指定的target设置编译选项,设置的编译选项有三种范围,如下:
     + PRIVATE:只给自己用，不给依赖者用
     + INTERFACE:自己不用，给依赖者用
     + PUBLIC:自己和依赖者都可以用
   + list(APPEND flags "-fPIC" "-Wall")
        if(NOT WIN32)
            list(APPEND flags "-Wextra" "-Wpedantic")
        endif()
   + target_compile_options(geometry PRIVATE ${flags})
   + cmake --build . -- VERBOSE=1可以查看编译器选项
9.  语言和版本
   + 代码如下
```
    set_target_properties(animal-farm
    PROPERTIES
        CXX_STANDARD 14
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
    )
```
   + 设置标准
      + CXX_STANDARD会设置我们想要的标准。
      + CXX_EXTENSIONS告诉CMake，只启用ISO C++标准的编译器标志，而不使用特定编译器的扩展。
      + CXX_STANDARD_REQUIRED必需指定所选标准的版本。如果这个版本不可用，CMake将停止配置并出现错误。当这个属性被设置为OFF时，CMake将寻找下一个标准的最新版本，直到一个合适的标志。这意味着，首先查找C++14，然后是C++11，然后是C++98。（译者注：目前会从C++20或C++17开始查找）
1.  控制流
    + foreach endforeach 可以与break结合使用，以便尽早从循环中跳出。
      + 有四种用法:多变量,列表,Items,范围
      + foreach(loop_var arg1 arg2 ...): 其中提供循环变量和显式项列表。当为sources_with_lower_optimization中的项打印编译器标志集时，使用此表单。注意，如果项目列表位于变量中，则必须显式展开它；也就是说，${sources_with_lower_optimization}必须作为参数传递。
      + 通过指定一个范围，可以对整数进行循环，例如：foreach(loop_var range total)或foreach(loop_var range start stop [step])。
      + 对列表值变量的循环，例如：foreach(loop_var IN LISTS [list1[...]]) 。参数被解释为列表，它们的内容会自动展开。
      + 对变量的循环，例如：foreach(loop_var IN ITEMS [item1 [...]])。参数的内容没有展开。
    + while-endwhile 可以与break结合使用，以便尽早从循环中跳出。
      + 类似C语言里的while(true){}do;
## 第2章，检测环境，解释如何使用简单的CMake命令与操作系统和处理器体系结构交互。
1. 操作系统及系统相关预定义
   + CMAKE_SYSTEM_NAME:Linux/Darwin/Windows,在具有uname命令的系统上，将此变量设置为uname -s的输出。该变量在macOS上设置为“Darwin”。在Linux和Windows上，它分别计算为“Linux”和“Windows”。
   + CMAKE_CXX_COMPILER_ID:Intel/GNU/PGI/XL等,编译器ID,并非所有编译器CMAKE都有预定义
   + CMAKE_HOST_SYSTEM_PROCESSOR:“i386”、“i686”、“x86_64”、“AMD64”
   + CMAKE_SIZEOF_VOID_P:为void指针的大小8或4,使用CMAKE_SIZEOF_VOID_P是检查当前CPU是否具有32位或64位架构的唯一“真正”可移植的方法。
   + NUMBER_OF_LOGICAL_CORES/NUMBER_OF_PHYSICAL_CORES/TOTAL_VIRTUAL_MEMORY/AVAILABLE_VIRTUAL_MEMORY/TOTAL_PHYSICAL_MEMORY/AVAILABLE_PHYSICAL_MEMORY/IS_64BIT/HAS_FPU/HAS_MMX/HAS_MMX_PLUS/HAS_SSE/HAS_SSE2/HAS_SSE_FP/HAS_SSE_MMX/HAS_AMD_3DNOW/HAS_AMD_3DNOW_PLUS/HAS_IA64/OS_NAME/OS_RELEASE/OS_VERSION/OS_PLATFORM...
2. 预定义
   + target_compile_definitions(hello-world PUBLIC "IS_LINUX")设置IS_LINUX宏,C/C++代码中可以直接使用
   + add_definitions(-DIS_LINUX)会修改编译整个项目的定义
## 第3章，检测外部库和程序，展示CMake如何简化对项目依赖项的检测。
1. 使用CMake自带的find-module(调用find_package函数)，但并不是所有的包在CMake的find模块都找得到。
   + find_package是包装器命令，用于发现和设置包的CMake模块。这些模块包含CMake命令，用于标识系统标准位置中的包。CMake模块文件称为Find<name>.cmake，当调用find_package(<name>)时，模块中的命令将会运行。
   + Find<name>.cmake一般位于cmake的按照目录的Modules文件夹下,或者供应商按照在标准位置的cmake的文件夹下
   + execute_process ,命令将作为CMake命令的子进程执行一个或多个命令。最后，子进程返回值将保存到变量作为参数传递给RESULT_VARIABLE，而管道标准输出和标准错误的内容将被保存到变量作为参数传递给OUTPUT_VARIABLE和ERROR_VARIABLE。execute_process可以执行任何命令，并使用它们的结果来推断系统的配置。include(FindPackageHandleStandardArgs)
   + add_custom_command 引用此命令时，可以正确的处理与版本相关的选项(REQUIRED和EXACT)，而无需更多的CMake代码。需要include(FindPackageHandleStandardArgs)
   + find_package_handle_standard_args 命令提供了标准工具，用于处理与查找安装系统上的相关程序和库。include(FindPackageHandleStandardArgs)
2. 使用<package>Config.cmake, <package>ConfigVersion.cmake和<package>Targets.cmake，这些文件由软件包供应商提供，并与软件包一起安装在标准位置的cmake文件夹下。
3. 依赖pkg-config程序，来找到系统上的包。这依赖于包供应商在.pc配置文件中，其中有关于发行包的元数据。
   + pkg_check_modules，查找传递列表中的所有模块(库和/或程序)
   + pkg_search_module，要在传递的列表中找到第一个工作模块
4. 为依赖项编写自己的find-package模块。
## 第4章，创建和运行测试，解释如何利用CMake和CTest的功能来定义和运行测试。
1. 简单单元测试
## 第5章，配置时操作和构建时操作，展示了如何使用跨平台CMake命令在构建过程的不同阶段执行定制操作。
1. CMake工作流程相关的时序:
   + CMake时或构建时：CMake正在运行，并处理项目中的CMakeLists.txt文件。
   + 生成时：生成构建工具(如Makefile或Visual Studio项目文件)。比如:cmake ..
   + 构建时：由CMake生成相应平台的原生构建脚本，在脚本中调用原生工具构建。此时，将调用编译器在特定的构建目录中构建目标(可执行文件和库)。比如:cmake --build .
   + CTest时或测试时：运行测试套件以检查目标是否按预期执行。
   + CDash时或报告时：当测试结果上传到仪表板上，与其他开发人员共享测试报告。
   + 安装时：当目标、源文件、可执行程序和库，从构建目录安装到相应位置。
   + CPack时或打包时：将项目打包用以分发时，可以是源码，也可以是二进制。
   + 包安装时：新生成的包在系统范围内安装。
2. 文件操作
   + add_custom_target，创建执行自定义命令的目标
     + 构建用户自己的target,比如解压缩或者执行一些其他操作,别的target可以依赖此target
3. 配置时运行自定义命令
   + execute_process，从CMake中执行任意进程，并检索它们的输出。
4. 运行时运行自定义命令
   + add_custom_command 向目标添加规则，并通过执行命令生成输出。add_custom_command中声明的任何目标，即在相同的CMakeLists.txt中声明的任何目标，使用输出的任何文件作为源文件的目标，在构建时会有规则生成这些文件。因此，源文件生成在构建时，目标和自定义命令在构建系统生成时，将自动处理依赖关系。
   + add_custom_command 有两个限制(第二个限制，可以使用add_dependencies来避免。不过，规避这两个限制的正确方法是使用add_custom_target命令，我们将在下一节的示例中详细介绍。):
     + 只有在相同的CMakeLists.txt中，指定了所有依赖于其输出的目标时才有效。
     + 对于不同的独立目标，使用add_custom_command的输出可以重新执行定制命令。这可能会导致冲突，应该避免这种情况的发生。
   + add_custom_command 可以通过指定参数,指定执行时间
     + PRE_BUILD：在执行与目标相关的任何其他规则之前执行的命令。但能在Visual Studio 7或更高版本进行。
     + PRE_LINK：使用此选项，命令在编译目标之后，调用链接器或归档器之前执行。Visual Studio 7或更高版本之外的生成器中使用PRE_BUILD将被解释为PRE_LINK。
     + POST_BUILD：如前所述，这些命令将在执行给定目标的所有规则之后运行。

5. 研究编译和链接命令
6. 研究编译器标志命令
7. 研究可执行命令
8.  使用生成器表达式微调配置和编译
## 第6章，生成源代码，展示CMake命令自动生成源代码。
## 第7章，结构化项目，显示了强大的CMake语法，用于组织您的项目，使它们更易于维护。
## 第8章，超级构建模式，解释了功能强大的CMake超级构建模式，用于管理具有副作用控制的关键项目依赖关系。
## 第9章，混合语言项目，展示如何在CMake的帮助下，构建不同编程语言混合的项目。
## 第10章，编写一个安装程序，负责使用CMake的跨平台功能安装项目。
## 第11章，打包项目，展示如何使用CPack生成源文件和平台本机源文件打包，以及如何构建用于发布的Python和Conda包。
## 第12章，生成文档，展示如何使用CMake也生成代码的文档。
## 第13章，替代生成器和交叉编译，展示了如何使用CMake交叉编译项目。
## 第14章，测试仪表面板，显示如何将测试结果报告到在线仪表面板上。
## 第15章，将项目移植到CMake中，将展示最佳实践示例、注意事项和一些技巧，这些将帮助您将项目移植到基于CMake的构建系统中。