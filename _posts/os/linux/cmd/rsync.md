---
layout: post
title: rsync
date: 2019-12-11 10:13:09
description: rsync
tag: linux

---
# 1. rsync命令

- [1. rsync命令](#1-rsync命令)
  - [1.1. 简介](#11-简介)
  - [1.2. 常用功能](#12-常用功能)
    - [1.2.1. 上传文件或目录](#121-上传文件或目录)
    - [1.2.2. 下载文件或目录](#122-下载文件或目录)
    - [1.2.3. 删除文件](#123-删除文件)
  - [1.3. 参数OPTION](#13-参数option)
  - [1.4. 参考资料](#14-参考资料)

## 1.1. 简介

在Linux下一般用scp或者rsync个命令来通过ssh传输文件。

注意：用户要有目标的响应权限，下载需要有读权限，上传需要有写权限，否则会提示错误：Permission denied

src在前，dst在后
如果src是本地目录，dst是远程目录，就表示上传
如果src是远程目录，dst是本地目录，就表示下载

```shell
rsync [OPTION]... SRC DEST
rsync [OPTION]... SRC [USER@]host:DEST
rsync [OPTION]... [USER@]HOST:SRC DEST
rsync [OPTION]... [USER@]HOST::SRC DEST
rsync [OPTION]... SRC [USER@]HOST::DEST
rsync [OPTION]...
rsync://[USER@]HOST[:PORT]/SRC [DEST]
```

## 1.2. 常用功能

### 1.2.1. 上传文件或目录

将当前目录下的 testdir 或 test.exe 目录上传到服务器上
rsync -rvz --progress ./testdir portface@baidu::code/temp-g
rsync -rvz --progress ./test.exe portface@baidu::code/temp-g

-r 对子目录以递归模式处理
-v 详细输出模式
-z 对备份的文件在传输时进行压缩处理

### 1.2.2. 下载文件或目录

将 testdir 或 test.exe 目录下载到当前目录下
rsync -rvz --progress portface@baidu::code/temp-g/testdir .
rsync -rvz --progress portface@baidu::code/temp-g/test.exe .

通过 ssh 将远程文件 filename 下载到本地 local_dir 目录
`rsync -P -e 'ssh -p 12345' username@servername:/path/filename /var/www/local_dir`

当 SRC 和 DES 路径信息都不包含有单个冒号 ":" 分隔符时，操作的就是本地文件。

### 1.2.3. 删除文件

`rsync --delete-before -avH --progress --stats /tmp/empty/ /var/spool/postfix/maildrop`
`rsync --delete-before -avH --progress --stats /empty/ portface@baidu::code`

-delete-before 接收者在传输之前进行删除操作
–progress 在传输时显示传输过程
-a 归档模式，表示以递归方式传输文件，并保持所有文件属性
-H 保持硬连接的文件
-v 详细输出模式
–stats 给出某些文件的传输状态

## 1.3. 参数OPTION

| 缩写                  | 功能                                                                                         |
| --------------------- | -------------------------------------------------------------------------------------------- |
| -v，--verbose         | 详细模式输出。                                                                               |
| -q，--quiet           | 精简输出模式。                                                                               |
| -c，--checksum        | 打开校验开关，强制对文件传输进行校验。                                                       |
| -a，--archive         | 归档模式，表示以递归方式传输文件，并保持所有文件属性，等于 -rlptgoD。                        |
| -r，--recursive       | 对子目录以递归模式处理。                                                                     |
| -R，--relative        | 使用相对路径信息。                                                                           |
| -b，--backup          | 创建备份，目的文件已存在，将老的文件重新命名为 ~filename。                                   |
| --backup-dir          | 备份文件存放目录，配合 -b 使用。                                                             |
| -suffix=SUFFIX        | 定义备份文件前缀，配合 -b 使用。                                                             |
| -u，--update          | 仅仅进行更新，也就是跳过所有已经存在于 DST，并且文件时间晚于要备份的文件，不覆盖更新的文件。 |
| -l，--links           | 保留软链结。                                                                                 |
| -L，--copy-links      | 像对待常规文件一样处理软链结。                                                               |
| --copy-unsafe-links   | 仅仅拷贝指向 SRC 路径目录树以外的链结。                                                      |
| --safe-links          | 忽略指向 SRC 路径目录树以外的链结。                                                          |
| -H，--hard-links      | 保留硬链结。                                                                                 |
| -p，--perms           | 保持文件权限。                                                                               |
| -o，--owner           | 保持文件属主信息。                                                                           |
| -g，--group           | 保持文件属组信息。                                                                           |
| -D，--devices         | 保持设备文件信息。                                                                           |
| -t，--times           | 保持文件时间信息。                                                                           |
| -S，--sparse          | 对稀疏文件进行特殊处理以节省DST的空间。                                                      |
| -n，--dry-run         | 执行不做任何更改的试运行。                                                                   |
| -w，--whole-file      | 拷贝文件，不进行增量检测。                                                                   |
| -x，--one-file-system | 不要跨越文件系统边界。                                                                       |
| -B，--block-size=SIZE | 检验算法使用的块尺寸，默认是 700 字节。                                                      |
| -e，--rsh=command     | 指定使用 rsh、ssh 方式进行数据同步。                                                         |
| --rsync-path=PATH     | 指定远程服务器上的rsync命令所在路径信息。                                                    |
| -C，--cvs-exclude     | 使用和 CVS 一样的方法自动忽略文件，用来排除那些不希望传输的文件。                            |
| --existing            | 仅仅更新那些已经存在于 DST 的文件，而不备份那些新创建的文件。                                |
| --delete              | 删除 DST 中的指定文件，这些文件不在 SRC 里。                                                 |
| --delete-excluded     | 同样删除接收端那些被该选项指定排除的文件。                                                   |
| --delete-after        | 传输结束以后再删除。                                                                         |
| --ignore-errors       | 及时出现 IO 错误也进行删除。                                                                 |
| --max-delete=NUM      | 最多删除 NUM 个文件。                                                                        |
| --partial             | 保留那些因故没有完全传输的文件，以是加快随后的再次传输。                                     |
| --partial-dir=DIR     | 中间临时文件放置的目录。                                                                     |
| --force               | 强制删除目录，即使不为空。                                                                   |
| --numeric-ids         | 不将数字的用户和组id匹配为用户名和组名。                                                     |
| --timeout=time ip     | 超时时间，单位为秒。                                                                         |
| -I，--ignore-times    | 不跳过那些有同样的时间和长度的文件。                                                         |
| --size-only           | 当决定是否要备份文件时，仅仅察看文件大小而不考虑文件时间。                                   |
| --modify-window=NUM   | 决定文件是否时间相同时使用的时间戳窗口，默认为 0。                                           |
| -T --temp-dir=DIR     | 在 DIR 中创建临时文件。                                                                      |
| --compare-dest=DIR    | 同样比较 DIR 中的文件来决定是否需要备份。                                                    |
| -P 等同于             | --partial --progress                                                                         |
| --progress            | 显示备份进度过程。                                                                           |
| -z，--compress        | 对备份的文件在传输时进行压缩处理。                                                           |
| --exclude=PATTERN     | 指定排除不需要传输的文件模式。                                                               |
| --include=PATTERN     | 指定不排除而需要传输的文件模式。                                                             |
| --exclude-from=FILE   | 排除 FILE 中指定模式的文件。                                                                 |
| --include-from=FILE   | 不排除 FILE 指定模式匹配的文件。                                                             |
| --version             | 打印版本信息。                                                                               |
| --address             | 绑定到特定的地址。                                                                           |
| --config=FILE         | 指定其他的配置文件，不使用默认的 rsyncd.conf 文件。                                          |
| --port=PORT           | 指定其他的 rsync 服务端口。                                                                  |
| --blocking-io         | 对远程 shell 使用阻塞 IO。                                                                   |
| -stats                | 给出某些文件的传输状态。                                                                     |
| --log-format=formAT   | 指定日志文件格式。                                                                           |
| --password-file=FILE  | 从FILE中得到密码。                                                                           |
| --bwlimit=KBPS        | 限制I/O带宽，KBytes per second。                                                             |
| -h，--help            | 显示帮助信息。                                                                               |
| -–max-size            | 文件大小限制。                                                                               |
注意：参数值不能使用单双引号括起来，会报错或者不启作用。

## 1.4. 参考资料

1. [rsync 命令整理](https://www.jianshu.com/p/258ceb7b2223)
