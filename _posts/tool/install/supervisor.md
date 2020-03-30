# 1. supervisor

- [1. supervisor](#1-supervisor)
  - [1.1. 简介](#11-%e7%ae%80%e4%bb%8b)
  - [1.2. 安装](#12-%e5%ae%89%e8%a3%85)
  - [1.3. 进程配置](#13-%e8%bf%9b%e7%a8%8b%e9%85%8d%e7%bd%ae)
  - [1.4. 参考资料](#14-%e5%8f%82%e8%80%83%e8%b5%84%e6%96%99)

## 1.1. 简介

Supervisor是一个用 Python 写的进程管理工具，可以很方便的用来启动、重启、关闭进程（不仅仅是 Python 进程）。除了对单个进程的控制，还可以同时启动、关闭多个进程，比如很不幸的服务器出问题导致所有应用程序都被杀死，此时可以用 supervisor 同时启动所有应用程序而不是一个一个地敲命令启动。

## 1.2. 安装

Supervisor 可以运行在 Linux、Mac OS X 上。如前所述，supervisor 是 Python 编写的，所以安装起来也很方便，可以直接用 pip :

按照步骤：

- 按装: `sudo pip install supervisor`
- 生成配置: `echo_supervisord_conf > /etc/supervisor/supervisord.conf`
- 启动 `supervisord -c /etc/supervisor/supervisord.conf`

如果是 Ubuntu 系统，还可以使用 apt-get 安装。

配置文件可以在任何可访问目录保存，配置文件中最重要的是[include],包含管理的进程配置文件
一般和supervisord.conf同目录下创建conf.d目录，用户进程配置文件都放在这里。

```shell
cd /etc/supervisor/
supervisord.conf
conf.d
    a.conf
    b.conf
    c.conf
    ...
```

```supervisord.conf
[unix_http_server]
file=/tmp/supervisor.sock   ; UNIX socket 文件，supervisorctl 会使用
;chmod=0700                 ; socket 文件的 mode，默认是 0700
;chown=nobody:nogroup       ; socket 文件的 owner，格式： uid:gid

;[inet_http_server]         ; HTTP 服务器，提供 web 管理界面
;port=127.0.0.1:9001        ; Web 管理后台运行的 IP 和端口，如果开放到公网，需要注意安全性
;username=user              ; 登录管理后台的用户名
;password=123               ; 登录管理后台的密码

[supervisord]
logfile=/tmp/supervisord.log ; 日志文件，默认是 $CWD/supervisord.log
logfile_maxbytes=50MB        ; 日志文件大小，超出会 rotate，默认 50MB
logfile_backups=10           ; 日志文件保留备份数量默认 10
loglevel=info                ; 日志级别，默认 info，其它: debug,warn,trace
pidfile=/tmp/supervisord.pid ; pid 文件
nodaemon=false               ; 是否在前台启动，默认是 false，即以 daemon 的方式启动
minfds=1024                  ; 可以打开的文件描述符的最小值，默认 1024
minprocs=200                 ; 可以打开的进程数的最小值，默认 200

; the below section must remain in the config file for RPC
; (supervisorctl/web interface) to work, additional interfaces may be
; added by defining them in separate rpcinterface: sections
[rpcinterface:supervisor]
supervisor.rpcinterface_factory = supervisor.rpcinterface:make_main_rpcinterface

[supervisorctl]
serverurl=unix:///tmp/supervisor.sock ; 通过 UNIX socket 连接 supervisord，路径与 unix_http_server 部分的 file 一致
;serverurl=http://127.0.0.1:9001 ; 通过 HTTP 的方式连接 supervisord

; 包含其他的配置文件
[include]
files = relative/directory/*.ini    ; 可以是 *.conf 或 *.ini
```

## 1.3. 进程配置

supervisord.conf一般无需修改，最多修改一下include部分。

下边是usercenter的配置文件，启动时

```/etc/supervisor/conf.d/usercenter.conf
[program:usercenter]
directory = /home/leon/projects/usercenter ; 程序的启动目录
command = gunicorn -w 8 -b 0.0.0.0:17510 wsgi:app  ; 启动命令
autostart = true     ; 在 supervisord 启动的时候也自动启动
startsecs = 5        ; 启动 5 秒后没有异常退出，就当作已经正常启动了
autorestart = true   ; 程序异常退出后自动重启
stopasgroup=true     ; 同时stop子进程
killasgroup=true     ; 同时kill子进程
startretries = 3     ; 启动失败自动重试次数，默认是 3
stopsignal=TERM      ; stop时发送的信号
stopwaitsecs=10      ; stop时等待signal的时间，超时发送SIGKILL杀进程
user = leon          ; 用哪个用户启动
redirect_stderr = true  ; 把 stderr 重定向到 stdout，默认 false
stdout_logfile_maxbytes = 20MB  ; stdout 日志文件大小，默认 50MB
stdout_logfile_backups = 20     ; stdout 日志文件备份数
; stdout 日志文件，需要注意当指定目录不存在时无法正常启动，所以需要手动创建目录（supervisord 会自动创建日志文件）
stdout_logfile = /data/logs/usercenter_stdout.log
```

supervisord: 服务端，启动后无需管理
supervisorctl: 客户端

supervisorctl -c /etc/supervisor/supervisord.conf 可以直接进入交互界面,supervisord.conf必须与supervisord一致

> status    # 查看程序状态
> stop usercenter   # 关闭 usercenter 程序
> start usercenter  # 启动 usercenter 程序
> restart usercenter    # 重启 usercenter 程序
> reread    ＃ 读取有更新（增加）的配置文件，不会启动新添加的程序
> update    ＃ 重启配置文件修改过的程序

## 1.4. 参考资料

1. [doc](http://supervisord.org/introduction.html)
2. [git](https://github.com/Supervisor/supervisor)
3. [使用 supervisor 管理进程](http://liyangliang.me/posts/2015/06/using-supervisor/)