# 1. Settings Sync

- [1. Settings Sync](#1-settings-sync)
  - [1.1. 简介](#11-简介)
  - [1.2. 概念](#12-概念)
  - [1.3. 方法](#13-方法)
    - [1.3.1. 上传配置方法](#131-上传配置方法)
    - [1.3.2. 下载配置方法](#132-下载配置方法)
  - [1.4. 参考资料](#14-参考资料)

## 1.1. 简介

Setting Sync 是一个在多台设备之间同步 VSCode 配置，扩展，快捷键等设置的工具。有点类似于 git

## 1.2. 概念

- `github token`(指定存放位置)

访问 github 的钥匙。

github token 就是访问 github 指定账户的密钥。 github token 支持不同的账户权限，具体可搜索 github token 相关内容。
settings sync 需要 github token 的 gists 权限，用于存放 vscode 的配置等信息。
所以上传配置依赖 github token，生成 github token 的方法，详见参考资料2

- `Gist ID`(指定配置ID)

当上传一次 vscode 配置后就会生成一个 Gist ID, 有点类似于 git commit 之后生成的git ID。
下载 VSCode 配置的使用，需要指定一个 github token(从哪里取配置)，以及一个 Gist ID(指定哪一次上传的配置)

## 1.3. 方法

### 1.3.1. 上传配置方法

1. 安装 `Setting Sync`
2. 如果没有开启的话，把 Setting Sync 开启,命令如下： `settings sync: Turn On` 。如果已经开启了，则只有 >`settings sync: Turn Off`
3. 配置 `github token`,命令如下：`Sync: Advanced Options` 和 `Sync: 打开设置`,填写对应内容即可
4. 上传配置，命令如下：`sync: Update/Upload Settings` 。依赖配置 `github token`,上传后会生成一个 `Gist ID`(标识这次上传的内容标号，后续用于下载)

### 1.3.2. 下载配置方法

1. 安装 `Setting Sync`
2. 如果没有开启的话，把 Setting Sync 开启,命令如下： `settings sync: Turn On` 。如果已经开启了，则只有 >`settings sync: Turn Off`
3. 配置 `github token` 和 `Gist ID`(上传配置时生成的),命令如下：`Sync: Advanced Options` 和 `Sync: 打开设置`,填写对应内容即可
4. 下载配置，命令如下： >`sync: Download Settings`。 依赖配置 `github token` 和 `Gist ID`

## 1.4. 参考资料

1. [官网](https://code.visualstudio.com/docs/editor/settings-sync)
2. [常规方法](https://blog.csdn.net/mrsyf/article/details/106184967)
