---
layout: post
title: dockerCommand
date: 2019-12-09 19:17:06
description: dockerCommand
tag: docker

---


# 1. docker常用命令

- [1. docker常用命令](#1-docker%e5%b8%b8%e7%94%a8%e5%91%bd%e4%bb%a4)
  - [1.1. 名称解释](#11-%e5%90%8d%e7%a7%b0%e8%a7%a3%e9%87%8a)
    - [1.1.1. 玄虚镜像](#111-%e7%8e%84%e8%99%9a%e9%95%9c%e5%83%8f)
  - [1.2. Docker 命令查询](#12-docker-%e5%91%bd%e4%bb%a4%e6%9f%a5%e8%af%a2)
    - [1.2.1. 基本语法](#121-%e5%9f%ba%e6%9c%ac%e8%af%ad%e6%b3%95)
    - [1.2.2. client-OPTION](#122-client-option)
    - [1.2.3. client-COMMAND](#123-client-command)
      - [1.2.3.1. 常用命令](#1231-%e5%b8%b8%e7%94%a8%e5%91%bd%e4%bb%a4)
      - [1.2.3.2. client-A-C](#1232-client-a-c)
      - [1.2.3.3. client-D-H](#1233-client-d-h)
      - [1.2.3.4. client-I-K](#1234-client-i-k)
      - [1.2.3.5. client-L-P](#1235-client-l-p)
      - [1.2.3.6. client-R-S](#1236-client-r-s)
      - [1.2.3.7. client-T-Z](#1237-client-t-z)
    - [1.2.4. server-OPTION](#124-server-option)
      - [1.2.4.1. server-A-C](#1241-server-a-c)
      - [1.2.4.2. server-D-F](#1242-server-d-f)
      - [1.2.4.3. server-G-I](#1243-server-g-i)
      - [1.2.4.4. server-L-S](#1244-server-l-s)
      - [1.2.4.5. server-T-Z](#1245-server-t-z)
  - [1.3. 参考资料](#13-%e5%8f%82%e8%80%83%e8%b5%84%e6%96%99)

## 1.1. 名称解释

### 1.1.1. 玄虚镜像

    仓库名、标签均为 <none> 的镜像

## 1.2. Docker 命令查询

![命令图](img/cmd_logic.png "")

### 1.2.1. 基本语法

Docker 命令有两大类，客户端命令和服务端命令。前者是主要的操作接口，后者用来启动 Docker Daemon。可以通过 man docker 或 docker help 来查看这些命令。

客户端命令：基本命令格式为 docker [OPTIONS] COMMAND [arg...]；
更多参数说明请使用 docker "commit" --help 查看。其中commit就是对于的命令

服务端命令：基本命令格式为 dockerd [OPTIONS]。
更多参数说明请使用 docker "commit" --help 查看。其中commit就是对于的命令

具体OPTION和COMMAND，详见 [client-OPTION](#122-client-option),[server-OPTION](#124-server-option),[client-COMMAND](#123-client-command)

### 1.2.2. client-OPTION

- --config=""
    指定客户端配置文件，默认为 ~/.docker；
- -D=true|false
    是否使用 debug 模式。默认不开启；
- -H, --host=[]
    指定命令对应 Docker 守护进程的监听接口，可以为 unix 套接字 unix:///path/to/socket，文件句柄 fd://socketfd 或 tcp 套接字 tcp://[host[:port]]，默认为 unix:///var/run/docker.sock；
- -l, --log-level="debug|info|warn|error|fatal"
    指定日志输出级别
- --tls=true|false
    是否对 Docker 守护进程启用 TLS 安全机制，默认为否；
- --tlscacert=/.docker/ca.pem
    TLS CA 签名的可信证书文件路径；
- --tlscert=/.docker/cert.pem
    TLS 可信证书文件路径；
- --tlscert=/.docker/key.pem：TLS
    密钥文件路径；
- --tlsverify=true|false
    启用 TLS 校验，默认为否。

### 1.2.3. client-COMMAND

可以通过 docker COMMAND --help 来查看这些命令的具体用法。

#### 1.2.3.1. 常用命令

- docker image ls : 查看现有docker
- 的

#### 1.2.3.2. client-A-C

- attach
  1. 依附到一个正在运行的容器中；
  1. 某些时候需要进入容器进行操作，包括使用 docker attach 命令,后边直接跟镜像ID
  1. 通过attach进入容器,如果从进入后的stdin 中 exit，会导致容器的停止。所以不推荐使用此命令,推介使用docker exec -it
- build
  1. docker build [选项] <上下文路径/URL/->
  1. 从一个 Dockerfile 创建一个镜像；
  1. -f ../Dockerfile.php 指定某个文件作为 Dockerfile。
  1. docker build 还支持从 URL 构建，比如可以直接从 Git repo 中构建:`docker build https://github.com/twang2218/gitlab-ce-zh.git#:11.1`
  1. 用给定的 tar 压缩包构建: `docker build http://server/context.tar.gz`
  1. 从标准输入中读取 Dockerfile 进行构建`docker build - < Dockerfile`或`cat Dockerfile | docker build -`
  1. 从标准输入中读取上下文压缩包进行构建`$ docker build - < context.tar.gz`,如果发现标准输入的文件格式是 gzip、bzip2 以及 xz 的话，将会使其为上下文压缩包，直接将其展开，将里面视为上下文，并开始构建。
  1. 镜像构建上下文（Context）
       - Docker 在运行时分为 Docker 引擎（也就是服务端守护进程）和客户端工具。Docker 的引擎提供了一组 REST API，被称为 Docker Remote API，而如 docker 命令这样的客户端工具，则是通过这组 API 与 Docker 引擎交互，从而完成各种功能。因此，虽然表面上我们好像是在本机执行各种 docker 功能，但实际上，一切都是使用的远程调用形式在服务端（Docker 引擎）完成。也因为这种 C/S 设计，让我们操作远程服务器的 Docker 引擎变得轻而易举。
       - 当我们进行镜像构建的时候，并非所有定制都会通过 RUN 指令完成，经常会需要将一些本地文件复制进镜像，比如通过 COPY 指令、ADD 指令等。而 docker build 命令构建镜像，其实并非在本地构建，而是在服务端，也就是 Docker 引擎中构建的。那么在这种客户端/服务端的架构中，如何才能让服务端获得本地文件呢？
       - 这就引入了上下文的概念。当构建的时候，用户会指定构建镜像上下文的路径，docker build 命令得知这个路径后，会将路径下的所有内容打包，然后上传给 Docker 引擎。这样 Docker 引擎收到这个上下文包后，展开就会获得构建镜像所需的一切文件。
        如果在 Dockerfile 中这么写：`COPY ./package.json /app/`
        这并不是要复制执行 docker build 命令所在的目录下的 package.json，也不是复制 Dockerfile 所在目录下的 package.json，而是复制 上下文（context） 目录下的 package.json。
       - 因此，COPY 这类指令中的源文件的路径都是相对路径。这也是初学者经常会问的为什么 COPY ../package.json /app 或者 COPY /opt/xxxx /app 无法工作的原因，因为这些路径已经超出了上下文的范围，Docker 引擎无法获得这些位置的文件。如果真的需要那些文件，应该将它们复制到上下文目录中去。
- commit
  1. 从一个容器的修改中创建一个新的镜像；
  1. docker commit [选项] <容器ID或容器名> [<仓库名>[:<标签>]],使用 docker commit 命令虽然可以比较直观的帮助理解镜像分层存储的概念，但是实际环境中并不会这样使用,实际使用Dockerfile定制镜像。
  1. **--author** 是指定修改的作者
  1. **--message** 则是记录本次修改的内容
- docker container
  1. **start**: 直接将一个已经终止的容器启动运行。
  1. **stop**:  来终止一个运行中的容器
  1. **rm**:    删除一个处于终止状态的容器,如果要删除一个运行中的容器，可以添加 -f 参数。Docker 会发送 SIGKILL 信号给容器。
  1. **prune**: 清理掉所有处于终止状态的容器。
  1. **ls -a**: 可以查看所有已经创建的包括终止状态的容器: 可以查看所有已经创建的包括终止状态的容器 
- cp
  1. 在容器和本地宿主系统之间复制文件中；
- create
  1. 创建一个新容器，但并不运行它；

#### 1.2.3.3. client-D-H

- diff
  1. 检查一个容器内文件系统的修改，包括修改和增加；
- events
  1. 从服务端获取实时的事件；
- exec
  1. 在运行的容器内执行命令；此命令也可以进入容器
  1. **-i** CONTAINER ID: 进入容器,但是没有命令提示符
  1. **-it** CONTAINER ID: 进入容器,有命令提示符
- export
  1. 导出容器内容为一个 tar 包；
  1. 导出本地某个容器快照,比如:docker export 7691a814370e > ubuntu.tar
- history
  1. 显示一个镜像的历史信息；

#### 1.2.3.4. client-I-K

- image ls
  1. 显示所有顶层镜像,也可以直接加"仓库名"或者"仓库名:标签"来精确搜索镜像,如果镜像构建时，定义了 LABEL，还可以通过 LABEL 来过滤。
  1. **-f dangling=true** 过滤出玄虚镜像
  1. **-f** 表示过滤的意思,有点类似grep,也可以写为--format
  1. **-f since=mongo:3.2** 显示mongo:3.2之后的版本
  1. **-f since=before:3.2** 显示mongo:3.2之前的版本
  1. **-f "{{.ID}}: {{.Repository}}"** 只显示ID和仓库名,这是模板语法
  1. **-f "table {{.ID}}\t{{.Repository}}\t{{.Tag}}"** 按指定顺序显示列
  1. **-a** 同时显示中间层镜像(中间层镜像只会被保存一份)
  1. **-q** 只显示ID
  1. **prune** 删除玄虚镜像(仓库名、标签均为 none 的镜像)
- image rm
  1. docker image rm [选项] <镜像1> [<镜像2> ...],其中，<镜像> 可以是 镜像短 ID、镜像长 ID、镜像名(<仓库名>:<标签>) 或者 镜像摘要。
  1. 所以并非所有的 docker image rm 都会产生删除镜像的行为，有可能仅仅是取消了某个标签而已,有可能由于其他依赖无法删除.比如某一层被其他进行依赖,或者进行有容器对其依赖都无法删除
  1. 可以结合ls命令来删除指定镜像,比如删除所有仓库名为 redis 的镜像:  
    docker image rm $(docker image ls -q redis)
- images
    列出存在的镜像；
- import
  1. 导入一个文件（典型为 tar 包）路径或目录来创建一个本地镜像；
  2. 从容器快照文件中再导入为镜像,比如:cat ubuntu.tar | docker import - test/ubuntu:v1.0
  3. 此外，也可以通过指定 URL 或者某个目录来导入docker import http://example.com/exampleimage.tgz example/imagerepo
  4. 容器快照文件将丢弃所有的历史记录和元数据信息（即仅保存容器当时的快照状态）,从容器快照文件导入时可以重新指定标签等元数据信息,而docker load不可以修改.
- info
  1. 显示一些相关的系统信息；
- inspect
  1. 显示一个容器的具体配置信息；
- kill
  1. 关闭一个运行中的容器 (包括进程和所有相关资源)；

#### 1.2.3.5. client-L-P

- load
  1. 从一个 tar 包中加载一个镜像；
  1. 导入镜像存储文件到本地镜像库
  1. 镜像存储文件将保存完整记录，体积也要大。
- login
  1. 注册或登录到一个 Docker 的仓库服务器；
- logout
  1. 从 Docker 的仓库服务器登出；
- logs
  1. 获取容器的 log 信息；
- network
  1. 管理 Docker 的网络，包括查看、创建、删除、挂载、卸载等；
- node
  1. 管理 swarm 集群中的节点，包括查看、更新、删除、提升/取消管理节点等；
- pause
  1. 暂停一个容器中的所有进程；
- port
  1. 查找一个 nat 到一个私有网口的公共口；
- ps
  1. 列出主机上的容器；
- pull
  1. 从一个Docker的仓库服务器下拉一个镜像或仓库；
  1. 具体的选项可以通过 docker pull --help 命令看到
    docker pull [选项] [Docker Registry 地址[:端口号]/]仓库名[:标签]
- push
  1. 将一个镜像或者仓库推送到一个 Docker 的注册服务器；

#### 1.2.3.6. client-R-S

- rename
  1. 重命名一个容器；
- restart
  1. 重启一个运行中的容器；
- rm
  1. 删除给定的若干个容器；
- rmi
  1. 删除给定的若干个镜像；
- run
  1. 创建一个新容器，并在其中运行给定命令；
  1. 当利用 docker run 来创建容器时，Docker 在后台运行的标准操作包括：
      - 检查本地是否存在指定的镜像，不存在就从公有仓库下载
      - 利用镜像创建并启动一个容器
      - 分配一个文件系统，并在只读的镜像层外面挂载一层可读写层
      - 从宿主主机配置的网桥接口中桥接一个虚拟接口到容器中去
      - 从地址池配置一个 ip 地址给容器
      - 执行用户指定的应用程序
      - 执行完毕后容器被终止
  1. 具体参数
      - **-d**:让 Docker 在后台运行而不是直接把执行命令的结果输出在当前宿主机下
      - **--rm**:退出时就能够自动清理容器内部的文件系统。
      - -t, --tty: Allocate a pseudo-TTY
      - -i, --interactive: Keep STDIN open even if not attached
      - -v, --volume list: Bind mount a volum
- save
  1. 保存一个镜像为 tar 包文件；
- search
  1. 在 Docker index 中搜索一个镜像；
- service
  1. 管理 Docker 所启动的应用服务，包括创建、更新、删除等；
- start
  1. 启动一个容器；
- stats
  1. 输出（一个或多个）容器的资源使用统计信息；
- stop
  1. 终止一个运行中的容器；
- swarm
  1. 管理 Docker swarm 集群，包括创建、加入、退出、更新等；
- system df
  1. 查看镜像、容器、数据卷所占用的空间。

#### 1.2.3.7. client-T-Z

- tag
  1. 为一个镜像打标签；
- top
  1. 查看一个容器中的正在运行的进程信息；
- unpause
  1. 将一个容器内所有的进程从暂停状态中恢复；
- update
  1. 更新指定的若干容器的配置信息；
- version
  1. 输出 Docker 的版本信息；
- volume
  1. 管理 Docker volume，包括查看、创建、删除等；
- wait
  1. 阻塞直到一个容器终止，然后输出它的退出符。
- Dockerfile指令
[详见Dockerfile.md](Dockerfile.md)

### 1.2.4. server-OPTION

#### 1.2.4.1. server-A-C

- api-cors-header=""  
    CORS 头部域，默认不允许 CORS，要允许任意的跨域访问，可以指定为 "*"；
- authorization-plugin=""  
    载入认证的插件；
- -b=""  
    将容器挂载到一个已存在的网桥上。指定为 none 时则禁用容器的网络，与 - bip 选项互斥；
- bip=""  
    让动态创建的 docker0 网桥采用给定的 CIDR 地址; 与 -b 选项互斥；
- cgroup-parent=""  
    指定 cgroup 的父组，默认 fs cgroup 驱动为 /docker，systemd cgroup 驱动为 system.slice；
- cluster-store=""  
    构成集群（如 Swarm）时，集群键值数据库服务地址；
- cluster-advertise=""  
    构成集群时，自身的被访问地址，可以为 host:port 或 interface:port；
- cluster-store-opt=""  
    构成集群时，键值数据库的配置选项；
- config-file="/etc/docker/daemon.json"  
    daemon 配置文件路径；
- containerd=""  
    containerd 文件的路径；

#### 1.2.4.2. server-D-F

- -D, --debug=true|false  
    是否使用 Debug 模式。缺省为 false；
- default-gateway=""  
    容器的 IPv4 网关地址，必须在网桥的子网段内；
- default-gateway-v6=""  
    容器的 IPv6 网关地址；
- default-ulimit=[]  
    默认的 ulimit 值；
- disable-legacy-registry=true|false  
    是否允许访问旧版本的镜像仓库服务器；
- dns=""  
    指定容器使用的 DNS 服务器地址；
- dns-opt=""  
    DNS 选项；
- dns-search=[]  
    DNS 搜索域；
- exec-opt=[]  
    运行时的执行选项；
- exec-root=""  
    容器执行状态文件的根路径，默认为 /var/run/docker；
- fixed-cidr=""  
    限定分配 IPv4 地址范围；
- fixed-cidr-v6=""  
    限定分配 IPv6 地址范围；

#### 1.2.4.3. server-G-I

- -G, --group=""  
    分配给 unix 套接字的组，默认为 docker；
- -g, --graph=""  
    Docker 运行时的根路径，默认为 /var/lib/docker；
- -H, --host=[]  
    指定命令对应 Docker daemon 的监听接口，可以为 unix 套接字 unix:///path/to/socket，文件句柄 fd://socketfd 或 tcp 套接字 tcp://[host[:port]]，默认为 unix:///var/run/docker.sock；
- icc=true|false  
    是否启用容器间以及跟 daemon 所在主机的通信。默认为 true。
- insecure-registry=[]  
    允许访问给定的非安全仓库服务；
- ip=""  
    绑定容器端口时候的默认 IP 地址。缺省为 0.0.0.0；
- ip-forward=true|false  
    是否检查启动在 Docker 主机上的启用 IP 转发服务，默认开启。注意关闭该选项将不对系统转发能力进行任何检查修改；
- ip-masq=true|false  
    是否进行地址伪装，用于容器访问外部网络，默认开启；
- iptables=true|false  
    是否允许 Docker 添加 iptables 规则。缺省为 true；
- ipv6=true|false  
    是否启用 IPv6 支持，默认关闭；

#### 1.2.4.4. server-L-S

- -l, --log-level="debug|info|warn|error|fatal"  
    指定日志输出级别；
- label="[]"  
    添加指定的键值对标注；
- log-driver="json-file|syslog|journald|gelf|fluentd|awslogs|splunk|etwlogs|gcplogs|none"  
    指定日志后端驱动，默认为 json-file；
- log-opt=[]  
    日志后端的选项；
- mtu=VALUE  
    指定容器网络的 mtu；
- -p=""  
    指定 daemon 的 PID 文件路径。缺省为 /var/run/docker.pid；
- --raw-logs  
    输出原始，未加色彩的日志信息；
- `registry-mirror=<scheme>://<host>`  
    指定 docker pull 时使用的注册服务器镜像地址；
- -s, --storage-driver=""  
    指定使用给定的存储后端；
- selinux-enabled=true|false  
    是否启用 SELinux 支持。缺省值为 false。SELinux 目前尚不支持 overlay 存储驱动；
- storage-opt=[]  
    驱动后端选项；

#### 1.2.4.5. server-T-Z

- tls=true|false  
    是否对 Docker daemon 启用 TLS 安全机制，默认为否；
- tlscacert=/.docker/ca.pem  
    TLS CA 签名的可信证书文件路径；
- tlscert=/.docker/cert.pem  
    TLS 可信证书文件路径；
- tlscert=/.docker/key.pem  
    TLS 密钥文件路径；
- tlsverify=true|false  
    启用 TLS 校验，默认为否；
- userland-proxy=true|false  
    是否使用用户态代理来实现容器间和出容器的回环通信，默认为 true；
- userns-remap=default|uid:gid|user:group|user|uid  
    指定容器的用户命名空间，默认是创建新的 UID 和 GID 映射到容器内进程。

## 1.3. 参考资料

1.[Docker 命令查询](https://docker_practice.gitee.io/zh-cn/appendix/command/)
