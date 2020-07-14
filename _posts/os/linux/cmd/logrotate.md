# 1. logrotate

- [1. logrotate](#1-logrotate)
  - [1.1. 简介](#11-简介)
  - [1.2. 配置文件](#12-配置文件)
  - [1.3. 参数说明](#13-参数说明)
  - [1.4. 原理](#14-原理)
    - [1.4.1. 默认方案](#141-默认方案)
    - [1.4.2. copytruncate](#142-copytruncate)
  - [1.5. 运行机制](#15-运行机制)
  - [1.6. 举例](#16-举例)
  - [1.7. 参考资料](#17-参考资料)

## 1.1. 简介

&emsp;&emsp;对于Linux系统安全来说，日志文件是极其重要的工具。日志文件包含了关于系统中发生的事件的有用信息，在排障过程中或者系统性能分析时经常被用到。当日志文件不断增长的时候，就需要定时切割，否则，写日志的速度和性能也会下降，更不便于我们归档，查询。

&emsp;&emsp;所以便有了使用logrotate的时候 ，logrotate是个十分有用的工具，它可以自动对日志进行截断（或轮循）、压缩以及删除旧的日志文件。例如，你可以设置logrotate，让/var/log/foo日志文件每30天轮循，并删除超过6个月的日志。配置完后，logrotate的运作完全自动化，不必进行任何进一步的人为干预。

## 1.2. 配置文件

Linux系统默认安装logrotate工具，它默认的配置文件在：
/etc/logrotate.conf
/etc/logrotate.d/

logrotate.conf 才主要的配置文件，logrotate.d 是一个目录，该目录里的所有文件都会被主动的读入/etc/logrotate.conf中执行。

另外，如果 /etc/logrotate.d/ 里面的文件中没有设定一些细节，则会以/etc/logrotate.conf这个文件的设定来作为默认值。

实际运行时，Logrotate会调用配置文件/etc/logrotate.conf。

可以在/etc/logrotate.d目录里放置自定义好的配置文件，用来覆盖Logrotate的缺省值。

## 1.3. 参数说明

- `compress` 通过gzip 压缩转储以后的日志
- `nocompress` 不做gzip压缩处理
- `create mode owner group` 轮转时指定创建新文件的属性，如create 0777 nobody nobody
- `nocreate` 不建立新的日志文件
- `delaycompress` 和 `compress` 一起使用时，转储的日志文件到下一次转储时才压缩
- `nodelaycompress` 覆盖 `delaycompress` 选项，转储同时压缩。
- `missingok` 如果日志丢失，不报错继续滚动下一个日志
- `ifempty` 即使日志文件为空文件也做轮转，这个是logrotate的缺省选项。
- `notifempty` 当日志文件为空时，不进行轮转
- `mail address` 把转储的日志文件发送到指定的E-mail 地址
- `olddir directory` 转储后的日志文件放入指定的目录，必须和当前日志文件在同一个文件系统
- `noolddir` 转储后的日志文件和当前日志文件放在同一个目录下
- `prerotate` 在logrotate转储之前需要执行的指令，例如修改文件的属性等动作；必须独立成行
- `postrotate` 在logrotate转储之后需要执行的指令，例如重新启动 (kill -HUP) 某个服务！必须独立成行
- `sharedscripts` 运行 postrotate 脚本，作用是在所有日志都轮转后统一执行一次脚本。如果没有配置这个，那么每个日志轮转后都会执行一次脚本
- `daily` 指定转储周期为每天
- `weekly` 指定转储周期为每周
- `monthly` 指定转储周期为每月
- `rotate count` 指定日志文件删除之前转储的次数，0 指没有备份，5 指保留5 个备份
- `dateext` 使用当期日期作为命名格式
- `dateformat` .%s 配合 dateext 使用，紧跟在下一行出现，定义文件切割后的文件名，必须配合dateext使用，只支持 %Y %m %d %s 这四个参数
- `size(或minsize)` log-size 当日志文件到达指定的大小时才转储，log-size能指定bytes(缺省)及KB (sizek)或MB(sizem).
  - 当日志文件 >= log-size 的时候就转储。 以下为合法格式：（其他格式的单位大小写没有试过）
  - size = 5 或 size 5 （>= 5 个字节就转储）
  - size = 100k 或 size 100k
  - size = 100M 或 size 100M
- `copytruncate` 使用 copytruncate 方案，具体详见滚动方案

## 1.4. 原理

logrotate是怎么做到滚动日志时不影响程序正常的日志输出呢？logrotate提供了两种解决方案。

### 1.4.1. 默认方案

&emsp;&emsp;这个方案会创建一个新的日志文件给程序输出日志，第二个方案名`copytruncate`是个配置项，与此方案是互斥的。

- 这个方案的思路是重命名原日志文件，创建新的日志文件。详细步骤如下
  - 重命名程序当前正在输出日志的程序。因为重命名只会修改目录文件的内容，而进程操作文件靠的是inode编号，所以并不影响程序继续输出日志。
  - 创建新的日志文件，文件名和原来日志文件一样。虽然新的日志文件和原来日志文件的名字一样，但是inode编号不一样，所以程序输出的日志还是往原日志文件输出。
  - 通过某些方式通知程序，重新打开日志文件。程序重新打开日志文件，靠的是文件路径而不是inode编号，所以打开的是新的日志文件。

&emsp;&emsp;什么方式通知程序我重新打开日志呢，简单粗暴的方法是杀死进程重新打开。很多场景这种作法会影响在线的服务，于是有些程序提供了重新打开日志的接口，比如可以通过信号通知nginx。各种IPC方式都可以，前提是程序自身要支持这个功能。

&emsp;&emsp;有个地方值得一提，一个程序可能输出了多个需要滚动的日志文件。每滚动一个就通知程序重新打开所有日志文件不太划得来。有个`sharedscripts`的参数，让程序把所有日志都重命名了以后，只通知一次。

### 1.4.2. copytruncate

&emsp;&emsp;如果程序不支持重新打开日志的功能，又不能粗暴地重启程序，怎么滚动日志呢？copytruncate的方案出场了。

- 这个方案的思路是把正在输出的日志拷(copy)一份出来，再清空(trucate)原来的日志。详细步骤如下
  - 拷贝程序当前正在输出的日志文件，保存文件名为滚动结果文件名。这期间程序照常输出日志到原来的文件中，原来的文件名也没有变。
  - 清空程序正在输出的日志文件。清空后程序输出的日志还是输出到这个日志文件中，因为清空文件只是把文件的内容删除了，文件的inode编号并没有发生变化，变化的是元信息中文件内容的信息。

结果上看，旧的日志内容存在滚动的文件里，新的日志输出到空的文件里。实现了日志的滚动。

- 这个方案有两个有趣的地方
- 文件清空并不影响到输出日志的程序的文件表里的文件位置信息，因为各进程的文件表是独立的。那么文件清空后，程序输出的日志应该接着之前日志的偏移位置输出，这个位置之前会被\0填充才对。但实际上logroate清空日志文件后，程序输出的日志都是从文件开始处开始写的。这是怎么做到的？这个问题让我纠结了很久，直到某天灵光一闪，这不是logrotate做的，而是成熟的写日志的方式，都是用O_APPEND的方式写的。如果程序没有用O_APPEND方式打开日志文件，变会出现copytruncate后日志文件前面会被一堆\0填充的情况。
- 日志在拷贝完到清空文件这段时间内，程序输出的日志没有备份就清空了，这些日志不是丢了吗？是的，copytruncate有丢失部分日志内容的风险。所以能用create的方案就别用copytruncate。所以很多程序提供了通知我更新打开日志文件的功能来支持create方案，或者自己做了日志滚动，不依赖logrotate。

## 1.5. 运行机制

&emsp;&emsp;logrotate在很多Linux发行版上都是默认安装的。系统会定时运行logrotate，一般是每天一次。系统是这么实现按天执行的。crontab会每天定时执行`/etc/cron.daily`目录下的脚本，而这个目录下有个文件叫`logrotate`。在centos上脚本内容是这样的：

```bash
/usr/sbin/logrotate /etc/logrotate.conf >/dev/null 2>&1
EXITVALUE=$?
if [ $EXITVALUE != 0 ]; then
    /usr/bin/logger -t logrotate "ALERT exited abnormally with [$EXITVALUE]"
fi
exit 0
```

可以看到这个脚本主要做的事就是以`/etc/logrotate.conf`为配置文件执行了`logrotate`。就是这样实现了每天执行一次`logrotate`。

因为我的系统执行`/etc/cron.daily`目录下的脚本不是我想滚动日志的时间，所以我把`/etc/cron.daily/logrotate`拷了出来，改了一下`logrotate`配置文件的路径，然后在`crontab`里加上一条指定时间执行这个脚本的记录，自定义周期滚动日志就大功告成了。这种自定义的方式有两点要注意：

1. 配置文件里一定要配置`rotate` 文件数目这个参数。如果不配置默认是0个，也就是只允许存在一份日志，刚切分出来的日志会马上被删除。多么痛的领悟，说多了都是泪。

2. 执行`logrotate`命令最好加`-f`参数，不然有时候配置文件修改的内容不生效。

很多程序的会用到`logrotate`滚动日志，比如nginx。它们安装后，会在`/etc/logrotate.d`这个目录下增加自己的`logrotate`的配置文件。logrotate什么时候执行`/etc/logrotate.d`下的配置呢？看到`/etc/logrotate.conf`里这行，一切就不言而喻了。

`include /etc/logrotate.d`

## 1.6. 举例

```bash
#logrotate.conf
compress
rotate 3
copytruncate
/ssd/log/b2.log {
    size 100M
}
```

```bash
#nginx 常用日志切割配置
/data/log/nginx/*.log /data/log/nginx/*/*.log { # 对匹配上的日志文件进行切割
    weekly # 每周切割
    missingok     # 在日志轮循期间，任何错误将被忽略，例如“文件无法找到”之类的错误。
    rotate 6      # 保留 6 个备份
    compress     # 压缩
    delaycompress    # delaycompress 和 compress 一起使用时，转储的日志文件到下一次转储时才压缩

    notifempty     # 如果是空文件的话，不转储
    create 0644 www-data ymserver     # mode owner group 转储文件，使用指定的文件模式创建新的日志文件
    sharedscripts # 所有文件执行完滚存后统一执行 prerotate 和 postrotate 脚本

    prerotate # 在logrotate转储之前需要执行的指令，例如修改文件的属性等动作；必须独立成行
        if [ -d /etc/logrotate.d/httpd-prerotate ]; then \
            run-parts /etc/logrotate.d/httpd-prerotate; \
        fi \
    endscript

    postrotate  # 在logrotate转储之后需要执行的指令，例如重新启动 (kill -HUP) 某个服务！必须独立成行
        [ -s /run/nginx.pid ] && kill -USR1 `cat /run/nginx.pid`
    endscript

    su root ymserver # 轮训日志时切换设置的用户/用户组来执行（默认是root），如果设置的user/group 没有权限去让文件容用 create 选项指定的拥有者 ，会触发错误。
}
```

## 1.7. 参考资料

1. [linux 日志定时轮询流程详解](https://mp.weixin.qq.com/s?__biz=MzA3NzcwNjM0OA==&mid=2247494872&idx=2&sn=2b2015fc57baa7cc7fe8b78d2831dc2a&source=41#wechat_redirect)
2. [logrotate机制和原理](https://www.lightxue.com/how-logrotate-works)
