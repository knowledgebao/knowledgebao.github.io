---
layout: post
title: VSCode下的cmake
date: 2019-11-08 17:45:20
description: VSCode下的cmake
tag: cmake

---

# VSCode下的cmake

## 常用命令

| cmake tool对应命令            | 对应的命令   | 说明                                                       |
| ----------------------------- | ------------ | ---------------------------------------------------------- |
| build                         | make         | 编译，如果文件变化会自动调用configure                      |
| configure                     | cmake ..     | 配置                                                       |
| Edit User_Local CMake Kits    |              | 编辑本地Kits文件，手动加入的Kits需要设置 "keep" :true 属性 |
| Scan for Kits                 |              | 重新扫描本地Kits。                                         |
| Clean                         | make clean   | 执行make clean                                             |
| Delete cached and reconfigure |              | 删除缓存并重新配置                                         |
| Install                       | make install | 按照                                                       |
| debug                         |              | 使用gdb调试                                                |
| 活动栏                        |              | 可以从右侧的活动栏选择相应的项目进行编译、构建了           |

## 参考资料

1. [VS Code与CMake真乃天作之合](https://zhuanlan.zhihu.com/p/52874931)
