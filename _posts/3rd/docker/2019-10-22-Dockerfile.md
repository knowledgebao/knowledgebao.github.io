---
layout: post
title: Dockerfile
date: 2019-10-22 18:27:23
description: Dockerfile
tag: docker

---

- [Dockerfile](#dockerfile)
  - [简介](#简介)
  - [命令详解](#命令详解)
    - [FROM](#from)
    - [RUN](#run)
- [建立 redis 用户，并使用 gosu 换另一个用户执行命令](#建立-redis-用户并使用-gosu-换另一个用户执行命令)
- [下载 gosu](#下载-gosu)
- [设置 CMD，并以另外的用户执行](#设置-cmd并以另外的用户执行)
      - [构建时从其他镜像复制文件](#构建时从其他镜像复制文件)
  - [参考资料](#参考资料)
    - [1.Dockerfile 最佳实践](#1dockerfile-最佳实践)

# Dockerfile
## 简介
    从刚才的 docker commit 的学习中，我们可以了解到，镜像的定制实际上就是定制每一层所添加的配置、文件。如果我们可以把每一层修改、安装、构建、操作的命令都写入一个脚本，用这个脚本来构建、定制镜像，那么之前提及的无法重复的问题、镜像构建透明性的问题、体积的问题就都会解决。这个脚本就是 Dockerfile。
    Dockerfile 是一个文本文件，其内包含了一条条的 指令(Instruction)，每一条指令构建一层，因此每一条指令的内容，就是描述该层应当如何构建。
## 命令详解
### FROM
    FROM 就是指定 基础镜像，因此一个 Dockerfile 中 FROM 是必备的指令，并且必须是第一条指令。比如:FROM nginx
### RUN
    RUN 指令是用来执行命令行命令的。由于命令行的强大能力，RUN 指令在定制镜像时是最常用的指令之一。其格式有两种：

+ shell 格式：RUN <命令>，就像直接在命令行中输入的命令一样。刚才写的 Dockerfile 中的 RUN 指令就是这种格式。
```RUN echo '<h1>Hello, Docker!</h1>' > /usr/share/nginx/html/index.html```
+ exec 格式：RUN ["可执行文件", "参数1", "参数2"]，这更像是函数调用中的格式。
+ Dockerfile 支持 Shell 类的行尾添加 \ 的命令换行方式，以及行首 # 进行注释的格式。所以多条RUN命令要合理使用换行符,保证在同一层上.
### COPY
    格式：
    COPY [--chown=<user>:<group>] <源路径>... <目标路径>
    COPY  [--chown=<user>:<group>] ["<源路径1>",... "<目标路径>"]
    和 RUN 指令一样，也有两种格式，一种类似于命令行，一种类似于函数调用。

+ COPY 指令将从构建上下文目录中 <源路径> 的文件/目录复制到新的一层的镜像内的 <目标路径> 位置。比如：`COPY package.json /usr/src/app/`
+ <源路径> 可以是多个，甚至可以是通配符，其通配符规则要满足 Go 的 filepath.Match 规则，如：`COPY hom* /mydir/`或`COPY hom?.txt /mydir/`
+ <目标路径> 可以是容器内的绝对路径，也可以是相对于工作目录的相对路径（工作目录可以用 WORKDIR 指令来指定）。目标路径不需要事先创建，如果目录不存在会在复制文件前先行创建缺失目录。
+ 此外，还需要注意一点，使用 COPY 指令，源文件的各种元数据都会保留。比如读、写、执行权限、文件变更时间等。这个特性对于镜像定制很有用。特别是构建相关文件都在使用 Git 进行管理的时候。
+ 在使用该指令的时候还可以加上 --chown=<user>:<group> 选项来改变文件的所属用户及所属组。
```Dockerfile
COPY --chown=55:mygroup files* /mydir/
COPY --chown=bin files* /mydir/
COPY --chown=1 files* /mydir/
COPY --chown=10:11 files* /mydir/
```
### ADD
+ ADD 指令和 COPY 的格式和性质基本一致。但是在 COPY 基础上增加了一些功能。
  + 比如 <源路径> 可以是一个 URL，这种情况下，Docker 引擎会试图去下载这个链接的文件放到 <目标路径> 去。下载后的文件权限自动设置为 600，如果这并不是想要的权限，那么还需要增加额外的一层 RUN 进行权限调整，
  + 另外，如果下载的是个压缩包，需要解压缩，也一样还需要额外的一层 RUN 指令进行解压缩。所以不如直接使用 RUN 指令，然后使用 wget 或者 curl 工具下载，处理权限、解压缩、然后清理无用文件更合理。因此，**这个功能其实并不实用，而且不推荐使用**。
  + 如果 <源路径> 为一个 tar 压缩文件的话，压缩格式为 gzip, bzip2 以及 xz 的情况下，ADD 指令将会自动解压缩这个压缩文件到 <目标路径> 去。在某些情况下，这个自动解压缩的功能非常有用，比如官方镜像 ubuntu 中(但在某些情况下，如果我们真的是希望复制个压缩文件进去，而不解压缩，这时就不可以使用 ADD 命令了。)：
```Dockerfile
FROM scratch
ADD ubuntu-xenial-core-cloudimg-amd64-root.tar.gz /
...
```

  + 在 Docker 官方的 Dockerfile 最佳实践文档 中要求，尽可能的使用 COPY，因为 COPY 的语义很明确，就是复制文件而已，而 ADD 则包含了更复杂的功能，其行为也不一定很清晰。最适合使用 ADD 的场合，就是所提及的需要自动解压缩的场合。
  + 另外需要注意的是，ADD 指令会令镜像构建缓存失效，从而可能会令镜像构建变得比较缓慢。
  + 因此在 COPY 和 ADD 指令中选择的时候，可以遵循这样的原则，所有的文件复制均使用 COPY 指令，仅在需要自动解压缩的场合使用 ADD。在使用该指令的时候还可以加上 --chown=<user>:<group> 选项来改变文件的所属用户及所属组。
```Dockerfile
ADD --chown=55:mygroup files* /mydir/
ADD --chown=bin files* /mydir/
ADD --chown=1 files* /mydir/
ADD --chown=10:11 files* /mydir/
```
### CMD
+ CMD 指令的格式和 RUN 相似，也是两种格式：
  + shell 格式：CMD <命令>
  + exec 格式：CMD ["可执行文件", "参数1", "参数2"...]
  + 参数列表格式：CMD ["参数1", "参数2"...]。在指定了 ENTRYPOINT 指令后，用 CMD 指定具体的参数。
+ 之前介绍容器的时候曾经说过，Docker 不是虚拟机，容器就是进程。既然是进程，那么在启动容器的时候，需要指定所运行的程序及参数。CMD 指令就是用于指定默认的容器主进程的启动命令的。
+ 在指令格式上，一般推荐使用 exec 格式，这类格式在解析时会被解析为 JSON 数组，因此一定要使用双引号 "，而不要使用单引号。如果使用 shell 格式的话，实际的命令会被包装为 sh -c 的参数的形式进行执行。比如：`CMD echo $HOME`在实际执行中，会将其变更为：`CMD [ "sh", "-c", "echo $HOME" ]`
+ 一些初学者将 CMD 写为：`CMD service nginx start`然后发现容器执行后就立即退出了。这就是因为没有搞明白前台、后台的概念，没有区分容器和虚拟机的差异，依旧在以传统虚拟机的角度去理解容器。对于容器而言，其启动程序就是容器应用进程，容器就是为了主进程而存在的，主进程退出，容器就失去了存在的意义，从而退出，其它辅助进程不是它需要关心的东西。而使用 `service nginx start` 命令，则是希望 upstart 来以后台守护进程形式启动 nginx 服务。而刚才说了 `CMD service nginx start`会被理解为 `CMD [ "sh", "-c", "service nginx start"]`，因此主进程实际上是 sh。那么当 `service nginx start` 命令结束后，sh 也就结束了，sh 作为主进程退出了，自然就会令容器退出。
正确的做法是直接执行 nginx 可执行文件，并且要求以前台形式运行。比如：
`CMD ["nginx", "-g", "daemon off;"]`
### ENTORPOINT
+ ENTRYPOINT 的格式和 RUN 指令格式一样，分为 exec 格式和 shell 格式。
+ 当指定了 ENTRYPOINT 后，CMD 的含义就发生了改变，不再是直接的运行其命令，而是将 CMD 的内容作为参数传给 ENTRYPOINT 指令，换句话说实际执行时，将变为：`<ENTRYPOINT> "<CMD>"`
+ 那么有了 CMD 后，为什么还要有 ENTRYPOINT 呢？这种 <ENTRYPOINT> "<CMD>" 有什么好处么？让我们来看几个场景。
  + 场景一：让镜像变成像命令一样使用
    + 如果想给镜像传递参数,必须使用ENTRYPOINT,如果不使用ENTRYPOINT,CMD无法动态传递参数
  + 场景二：应用运行前的准备工作
    + ENTRYPOINT做前期准备工作,CMD执行正则命令
### ENV
+ 格式有两种：
  + ENV <key> <value>
  + ENV <key1>=<value1> <key2>=<value2>...
+ 这个指令很简单，就是设置环境变量而已，无论是后面的其它指令，如 RUN，还是运行时的应用，都可以直接使用这里定义的环境变量。下边这个例子中演示了如何换行，以及对含有空格的值用双引号括起来的办法，这和 Shell 下的行为是一致的。
```Dockerfile
ENV VERSION=1.0 DEBUG=on \
    NAME="Happy Feet"
```
+ 下列指令可以支持环境变量展开： ADD、COPY、ENV、EXPOSE、LABEL、USER、WORKDIR、VOLUME、STOPSIGNAL、ONBUILD。可以从这个指令列表里感觉到，环境变量可以使用的地方很多，很强大。通过环境变量，我们可以让一份 Dockerfile 制作更多的镜像，只需使用不同的环境变量即可。
### ARG
+ 格式：ARG <参数名>[=<默认值>]
+ 构建参数和 ENV 的效果一样，都是设置环境变量。所不同的是，ARG 所设置的构建环境的环境变量，在将来容器运行时是不会存在这些环境变量的。但是不要因此就使用 ARG 保存密码之类的信息，因为 docker history 还是可以看到所有值的。
+ Dockerfile 中的 ARG 指令是定义参数名称，以及定义其默认值。该默认值可以在构建命令 docker build 中用 --build-arg <参数名>=<值> 来覆盖。
+ 在 1.13 之前的版本，要求 --build-arg 中的参数名，必须在 Dockerfile 中用 ARG 定义过了，如果对应参数没有被定义，则会报错退出构建。从 1.13 开始，这种严格的限制被放开，不再报错退出，而是显示警告信息，并继续构建。这对于使用 CI 系统，用同样的构建流程构建不同的 Dockerfile 的时候比较有帮助，避免构建命令必须根据每个 Dockerfile 的内容修改。
### VOLUME
+ 格式为：
  + VOLUME ["<路径1>", "<路径2>"...]
  + VOLUME <路径>
+ 之前我们说过，容器运行时应该尽量保持容器存储层不发生写操作，对于数据库类需要保存动态数据的应用，其数据库文件应该保存于卷(volume)中。为了防止运行时用户忘记将动态文件所保存目录挂载为卷，在 Dockerfile 中，我们可以事先指定某些目录挂载为匿名卷，这样在运行时如果用户不指定挂载，其应用也可以正常运行，不会向容器存储层写入大量数据。
+ 比如`VOLUME /data`这里的 /data 目录就会在运行时自动挂载为匿名卷，任何向 /data 中写入的信息都不会记录进容器存储层，从而保证了容器存储层的无状态化。当然，运行时可以覆盖这个挂载设置。比如：`docker run -d -v mydata:/data xxxx`在这行命令中，就使用了 mydata 这个命名卷挂载到了 /data 这个位置，替代了 Dockerfile 中定义的匿名卷的挂载配置。
### EXPOSE
+ 格式为 EXPOSE <端口1> [<端口2>...]。
+ EXPOSE 指令是声明运行时容器提供服务端口，这只是一个声明，在运行时并不会因为这个声明应用就会开启这个端口的服务。在 Dockerfile 中写入这样的声明有两个好处，一个是帮助镜像使用者理解这个镜像服务的守护端口，以方便配置映射；另一个用处则是在运行时使用随机端口映射时，也就是 `docker run -P` 时，会自动随机映射 EXPOSE 的端口。
+ 要将 EXPOSE 和在运行时使用 `-p <宿主端口>:<容器端口>` 区分开来。-p，是映射宿主端口和容器端口，换句话说，就是将容器的对应端口服务公开给外界访问，而 EXPOSE 仅仅是声明容器打算使用什么端口而已，并不会自动在宿主进行端口映射。
### WORKDIR
+ 格式为 WORKDIR <工作目录路径>。
+ 使用 WORKDIR 指令可以来指定工作目录（或者称为当前目录），以后各层的当前目录就被改为指定的目录，如该目录不存在，WORKDIR 会帮你建立目录。
+ 之前提到一些初学者常犯的错误是把 Dockerfile 等同于 Shell 脚本来书写，这种错误的理解还可能会导致出现下面这样的错误：
```Dockerfile
RUN cd /app
RUN echo "hello" > world.txt
```
如果将这个 Dockerfile 进行构建镜像运行后，会发现找不到 /app/world.txt 文件，或者其内容不是 hello。原因其实很简单，在 Shell 中，连续两行是同一个进程执行环境，因此前一个命令修改的内存状态，会直接影响后一个命令；而在 Dockerfile 中，这两行 RUN 命令的执行环境根本不同，是两个完全不同的容器。这就是对 Dockerfile 构建分层存储的概念不了解所导致的错误。之前说过每一个 RUN 都是启动一个容器、执行命令、然后提交存储层文件变更。第一层 RUN cd /app 的执行仅仅是当前进程的工作目录变更，一个内存上的变化而已，其结果不会造成任何文件变更。而到第二层的时候，启动的是一个全新的容器，跟第一层的容器更完全没关系，自然不可能继承前一层构建过程中的内存变化。
+ 因此如果需要改变以后各层的工作目录的位置，那么应该使用 WORKDIR 指令。
### USER
+ 格式：USER <用户名>[:<用户组>]
+ USER 指令和 WORKDIR 相似，都是改变环境状态并影响以后的层。WORKDIR 是改变工作目录，USER 则是改变之后层的执行 RUN, CMD 以及 ENTRYPOINT 这类命令的身份。当然，和 WORKDIR 一样，USER 只是帮助你切换到指定用户而已，这个用户必须是事先建立好的，否则无法切换。
```Dockerfile
RUN groupadd -r redis && useradd -r -g redis redis
USER redis
RUN [ "redis-server" ]
```
+ 如果以 root 执行的脚本，在执行期间希望改变身份，比如希望以某个已经建立好的用户来运行某个服务进程，不要使用 su 或者 sudo，这些都需要比较麻烦的配置，而且在 TTY 缺失的环境下经常出错。建议使用 gosu。
```Dockerfile
# 建立 redis 用户，并使用 gosu 换另一个用户执行命令
RUN groupadd -r redis && useradd -r -g redis redis
# 下载 gosu
RUN wget -O /usr/local/bin/gosu "https://github.com/tianon/gosu/releases/download/1.7/gosu-amd64" \
    && chmod +x /usr/local/bin/gosu \
    && gosu nobody true
# 设置 CMD，并以另外的用户执行
CMD [ "exec", "gosu", "redis", "redis-server" ]
```
### HEALTHCHECK
+ 格式：
  + HEALTHCHECK [选项] CMD <命令>：设置检查容器健康状况的命令
  + HEALTHCHECK NONE：如果基础镜像有健康检查指令，使用这行可以屏蔽掉其健康检查指令
  + HEALTHCHECK 指令是告诉 Docker 应该如何进行判断容器的状态是否正常，这是 Docker 1.12 引入的新指令。如果没有健康检查,如果程序进入死锁状态，或者死循环状态，应用进程并不退出，但是该容器已经无法提供服务了。
+ 状态
  + starting 初始状态
  + healthy HEALTHCHECK 指令检查成功后
  + unhealthy 如果连续一定次数失败
+ 支持参数
  + --interval=<间隔>：两次健康检查的间隔，默认为 30 秒；
  + --timeout=<时长>：健康检查命令运行超时时间，如果超过这个时间，本次健康检查就被视为失败，默认 30 秒；
  + --retries=<次数>：当连续失败指定次数后，则将容器状态视为 unhealthy，默认 3 次。
+ 和 CMD, ENTRYPOINT 一样，HEALTHCHECK 只可以出现一次，如果写了多个，只有最后一个生效。
+ 为了帮助排障，健康检查命令的输出（包括 stdout 以及 stderr）都会被存储于健康状态里，可以用 docker inspect 来查看。
```Dockerfile
$ docker inspect --format '{{json .State.Health}}' web | python -m json.tool
{
    "FailingStreak": 0,
    "Log": [
        {
            "End": "2016-11-25T14:35:37.940957051Z",
            "ExitCode": 0,
            "Output": "<!DOCTYPE html>...</html>\n",
            "Start": "2016-11-25T14:35:37.780192565Z"
        }
    ],
    "Status": "healthy"
}
```
### ONBUILD
+ 格式：ONBUILD <其它指令>。
ONBUILD 是一个特殊的指令，它后面跟的是其它指令，比如 RUN, COPY 等，而这些指令，在当前镜像构建时并不会被执行。只有当以当前镜像为基础镜像，去构建下一级镜像的时候才会被执行。
+ Dockerfile 中的其它指令都是为了定制当前镜像而准备的，唯有 ONBUILD 是为了帮助别人定制自己而准备的。
## Dockerfile多阶段构建
### 之前的做法
    在 Docker 17.05 版本之前，我们构建 Docker 镜像时，通常会采用两种方式：
#### 全部放入一个 Dockerfile
    一种方式是将所有的构建过程编包含在一个 Dockerfile 中，包括项目及其依赖库的编译、测试、打包等流程，这里可能会带来的一些问题：
    1. 镜像层次多，镜像体积较大，部署时间变长
    2. 源代码存在泄露的风险
#### 分散到多个 Dockerfile
    另一种方式，就是我们事先在一个 Dockerfile 将项目及其依赖库编译测试打包好后，再将其拷贝到运行环境中，这种方式需要我们编写两个 Dockerfile 和一些编译脚本才能将其两个阶段自动整合起来，这种方式虽然可以很好地规避第一种方式存在的风险，但明显部署过程较复杂。
### 使用多阶段构建
    为解决以上问题，Docker v17.05 开始支持多阶段构建 (multistage builds)。使用多阶段构建我们就可以很容易解决前面提到的问题，并且只需要编写一个 Dockerfile：
#### 只构建某一阶段的镜像
+ 例如，编写 Dockerfile 文件
```Dockerfile
FROM golang:1.9-alpine as builder
RUN apk --no-cache add git
WORKDIR /go/src/github.com/go/helloworld/
RUN go get -d -v github.com/go-sql-driver/mysql
COPY app.go .
RUN CGO_ENABLED=0 GOOS=linux go build -a -installsuffix cgo -o app .

FROM alpine:latest as prod
RUN apk --no-cache add ca-certificates
WORKDIR /root/
COPY --from=0 /go/src/github.com/go/helloworld/app .
CMD ["./app"]
```
+ 我们可以使用 as 来为某一阶段命名，例如
`FROM golang:1.9-alpine as builder`
+ 例如当我们只想构建 builder 阶段的镜像时，增加 --target=builder 参数即可
`$ docker build --target builder -t username/imagename:tag .`
#### 构建时从其他镜像复制文件
上面例子中我们使用
` COPY --from=0 /go/src/github.com/go/helloworld/app . `
从上一阶段的镜像中复制文件，我们也可以复制任意镜像中的文件。
`$ COPY --from=nginx:latest /etc/nginx/nginx.conf /nginx.conf`
## 参考资料
### 1.[Dockerfile 最佳实践](https://docker_practice.gitee.io/zh-cn/appendix/best_practices.html)