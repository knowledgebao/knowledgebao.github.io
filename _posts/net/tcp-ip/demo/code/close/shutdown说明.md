# 1. 使用说明

- [1. 使用说明](#1-使用说明)
  - [1.1. 目的](#11-目的)
  - [1.2. 步骤](#12-步骤)
  - [1.3. 预期结果](#13-预期结果)
  - [1.4. 参考资料](#14-参考资料)

## 1.1. 目的

验证半关闭状态 `int shutdown(int sockfd, int how)` 以及 CLOSE_WAIT,FIN_WAIT,TIME_WAIT 状态

- server 监听 9999 端口,启动 recv 接收数据
- client 连接 server,调用 send 发送数据
- client 调用shutdown 关闭写操作(只读不写)，当前 server 处于 CLOSE_WAIT 状态，client 处于 FIN_WAIT 状态
- server 通过 `ctrl C` 关掉 server ，此时 server 处于 TIME_WAIT 状态

## 1.2. 步骤

- cd close
- make clean && make
- ./server 9999
- ./client 127.0.0.1 9999 helloworld

## 1.3. 预期结果

1. 服务的收到 helloworld
2. 客户端收到服务的发送的系统时间

```log
#server

2020-11-10 19:6:19 : 9999 is listem
accept client[ ip:127.0.0.1,43022 handle:4 ]
recv: hello

#client

ip:127.0.0.1 port:43022 , connect ok 
S -> C: 2020-11-10 19:6:23
S -> C: 2020-11-10 19:6:24
...
```

```log
netstat -anp | grep 9999
tcp        0      0 0.0.0.0:9999            0.0.0.0:*               LISTEN      18643/./server      
tcp        1      0 127.0.0.1:9999          127.0.0.1:43022         CLOSE_WAIT  18643/./server      
tcp        0      0 127.0.0.1:43022         127.0.0.1:9999          FIN_WAIT2   18652/./client 

netstat -anp | grep 9999
tcp        0      0 127.0.0.1:43022         127.0.0.1:9999          TIME_WAIT   -   
```

## 1.4. 参考资料

1. [shutdown](https://man7.org/linux/man-pages/man2/shutdown.2.html)
