---
layout: post
title: pkg-config说明
date: 2019-11-08 17:45:20
description: pkg-config说明
tag: pkgconfig

---
# pkg-config

## 简介

&emsp;&emsp;大家应该都知道用第三方库，就少不了要使用到第三方的头文件和库文件。我们在编译、链接的时候，必须要指定这些头文件和库文件的位置。

&emsp;&emsp;对于一个比较大第三方库，其头文件和库文件的数量是比较多的。如果我们一个个手动地写，那将是相当麻烦的。所以，pkg-config就应运而生了。pkg-config能够把这些头文件和库文件的位置指出来，给编译器使用。

&emsp;&emsp;pkg-config的主要用途是为编译程序并将其链接到库提供必要的详细信息。此元数据存储在pkg-config文件中。这些文件的后缀为 .pc，位于pkg-config工具已知的特定位置 。

## 写 pkg-config

for example：

```ini
prefix=/usr/local
exec_prefix=${prefix}
includedir=${prefix}/include
libdir=${exec_prefix}/lib

Name: foo
Description: The foo library
Version: 1.0.0
Cflags: -I${includedir}/foo
Libs: -L${libdir} -lfoo
```

- Name: 名称，无实际作用，查找时使用文件名name.pc中的name，和这里的Name无关。
- Description: 描述，无实际作用
- URL: 现象URL， 无实际作用
- Version: 版本号，建议递增
- Requires: 依赖的第三方库，会导出给调用者，可携带版本号
- Requires.private: 依赖的第三方库，不会导出给调用者，可携带版本号
- Conflicts: 冲突包，可以携带版本号。
- Cflags: 编译标识及不支持pkg-config的依赖库的编译标识(compiler flag)，主要是头文件位置
- Libs: 本库的链接标识及不支持pkg-config的依赖库的链接标识(link flag)，主要是链接库的位置
- Libs.private: 同Libs，只是不导出给调用者

## 使用 pkt-config

PKG_CONFIG_PATH 宏定义存储的是 pkg-config(*.pc) 所在的目录

- `pkg-config --modversion foo`
- `pkg-config --libs foo` //注意foo是文件名称，不是里边的Name，一般文件名称和库名称一致，但是不强求
- `pkg-config --cflags bar`
- `pkg-config --exists foo` //判断是否存在
- `pkg-config --libs "bar >= 2.7"` //指定版本号
- `pkg-config --exists --print-errors xoxo` //提供更详细的输出
- ```cc `pkg-config --cflags --libs x` -o myapp myapp.c```  //通用调用方法

更多 pkg-config 命令可以通过 pkg-config --help 查看，也见参考资料2

## 问题集

1. 我的程序使用库x。我该怎么办？
    可以很容易地在编译器命令行上使用。假设x库具有x.pc pkg-config文件：

    cc`pkg-config --cflags --libs x` -o myapp myapp.c

    与autoconf和 automake一起使用时，集成可以更强大 。通过使用提供的PKG_CHECK_MODULES宏，可以在构建过程中轻松访问元数据。

    configure.ac：
    PKG_CHECK_MODULES（[X]，[x]）

    Makefile.am：
    myapp_CFLAGS = $（X_CFLAGS）
    myapp_LDADD = $（X_LIBS）

    如果找到x模块，则宏将填充并替换X_CFLAGS和X_LIBS变量。如果找不到模块，将产生错误。可以将可选的第3和第4个参数提供给PKG_CHECK_MODULES，以控制是否找到模块的操作。

2. 我的库z头文件包含libx 的头文件。我在z.pc文件中怎么写？

    如果x库支持pkg-config，则将其添加到Requires.private字段中。如果不支持，请在Cflags添加必需的编译器标志。无论哪种情况，无论是否使用--static，pkg-config都会导出编译器标志。

3. 我的库z在内部使用libx，但未在其公共API中公开libx数据类型。我在z.pc文件中怎么写 ？

    同样，如果模块支持pkg-config，则将其 添加到Requires.private中。在这种情况下，编译选项不会导出，但可确保在静态链接时有链接选项。如果libx不支持pkg-config，则将必要的链接选项添加到Libs.private中。

## 参考资料

1. [pkg-config的一些用法](https://blog.csdn.net/luotuo44/article/details/24836901)
2. [linux-man](https://linux.die.net/man/1/pkg-config)
3. [guide](https://people.freedesktop.org/~dbn/pkg-config-guide.html)
