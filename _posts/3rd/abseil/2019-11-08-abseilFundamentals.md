---
layout: post
title: abseilFundamentals
date: 2019-11-08 17:45:20
description: abseilFundamentals
tag: abseil

---

# Abseil Fundamentals

- [Abseil Fundamentals](#abseil-fundamentals)
  - [简介](#简介)
  - [Abseil风格指导](#abseil风格指导)
    - [Abseil 异常指导](#abseil-异常指导)
    - [内存泄漏检测](#内存泄漏检测)
  - [Abseil的基础库](#abseil的基础库)
  - [参考资料](#参考资料)

## 简介

本指南涵盖了Abseil中所有工作的公共概念。本指南涵盖的主题有：

- Abseil代码用到的主要指导思想及设计模式
- 有用的基本代码，所有使用者不要指导的代码
- 内部机制需要的基本代码，但是从开发的角度来看可能并不重要

## Abseil风格指导

&emsp;&emsp;Abseil代码遵循谷歌官方的c++编程风格指南。在Abseil代码中的其他约束/关注点，都继承与谷歌官方的C++编程指南

### Abseil 异常指导

&emsp;&emsp;谷歌(相当有名)在其生产代码中不使用异常。我们当然不要求你方遵守这样的政策。但是，您应该注意对代码库的一些影响。

&emsp;&emsp;我们不相信移动构造函数中抛出异常是一个好的idea。我们最多允许在移动构造中，因为内存不足抛出异常。在Abseil代码中，如果你使用-DABSL_ALLOCATOR_NOTHROW编译选项，move构造函数不会因为内存不足而抛出异常。保持move构造函数不抛出异常可以做到更好的优化，特别是结合标准库行为(std::vector使用非抛出的move构造函数更有效地调整大小)。

&emsp;&emsp;一般来说，我们会在合理的api和设计中支持异常。然而，我们对异常灵活性在什么地方会被性能所取代有自己的看法。我们将试图弄清楚异常在哪些地方是糟糕的设计选择，并在可能的情况下标记为noexcept。不要将对异常的概念支持与对所有地方的异常的认可相混淆。比如如果您的散列函子抛出异常，那么您只能自己处理。

注意noexcept的含义:这并不是保证不会发生异常，而是该API发成异常时，进程将以std::terminate()结束。

### 内存泄漏检测

&emsp;&emsp;Abseil代码被设计用来处理由LeakSanitizer (LSan)构建的目标，该目标是一个集成在AddressSanitizer (ASan)内的内存泄漏探测器，作为一个附加组件，或者可以单独使用。缺省情况下，在所有ASan构建中都启用了泄漏检查。

&emsp;&emsp;有关 LeakSanitizer 的更多信息，请参阅地址 [Address Sanitizer docs](https://github.com/google/sanitizers/wiki/AddressSanitizerLeakSanitizer)

为了在你的代码中启用LSan，包括Abseil代码(使用 Bazel ):

```Bazel
# Enable just LSan.
# Note that LSan requires Clang instead of gcc.
# You probably want to define a crosstool or bazel configuration to
# do this properly - provided for demonstration purposes only.
$ CC=clang BAZEL_COMPILER=llvm bazel build --copt=-DLEAK_SANITIZER \
    --linkopt=-fsanitize=leak *target*

# Enable ASan, which also includes LSan.
$ CC=clang BAZEL_COMPILER=llvm bazel build --copt=-DADDRESS_SANITIZER \
    --copt=-fsanitize=address --linkopt=-fsanitize=address *target*
```

debugging/leak_check.h 头文件包含几个实用程序函数，用于自定义代码中的泄漏检查行为。有关更多信息，请参考该头文件。

## Abseil的基础库

&emsp;&emsp;Abseil代码在absl/base目录中。从技术上讲，这些文件不是通常意义上的紧凑“库”。它们与基本文件的区别在于它们没有外部依赖关系; absl/base 头文件只依赖于其他的 absl/base 头文件。 base 库包含所有其他 Abseil 代码所依赖的基本代码。因此， base 的内容被保持在绝对必要的最小值。

&emsp;&emsp;这个基本库由配置文件、核心代码所需的一些 Abseil 实用程序和初始化原语组成。

基本库的配置头文件包括以下内容:

- policy_checks.h
可在构建时强制执行的Abseil策略，例如最小编译器和库版本。如需更多信息，请参考[咨询平台](https://abseil.io/docs/cpp/platforms/)
- macros.h
提供在Abseil代码中用于语言特性的宏。
- optimization.h
提供几个平台相关的宏来实现优化技术。
- config.h
提供用于确定平台和编译器支持的宏。有关更多信息，请参阅[特性检查宏指南](https://abseil.io/docs/cpp/platforms/feature_checks)

此外，基本库包括一个实用工具头文件:

- casts.h
提供一些有用的扩展来执行更安全的类型转换。

有关更多信息，请参考该头文件。
Base库的相关文件包含在“Base”中，因为它们是初始化和线程管理的基础，包括以下内容:

- call_once.h
提供原语，以确保在对象初始化期间仅调用一次函数。
- thread_annotations.h
提供一组用于在代码中标识并发环境中的预期行为的注释。

这些api是在同步指南中单独记录的，而不是在本指南中，因为它们与同步指南中的其他抽象密切相关。

## 参考资料

1. [Abseil Fundamentals](https://abseil.io/docs/cpp/guides/base)