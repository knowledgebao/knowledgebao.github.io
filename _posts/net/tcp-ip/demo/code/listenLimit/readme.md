# 1. 使用说明

- [1. 使用说明](#1-使用说明)
  - [1.1. 目的](#11-目的)
  - [1.2. 步骤](#12-步骤)
  - [1.3. 预期结果](#13-预期结果)
  - [1.4. 参考资料](#14-参考资料)

## 1.1. 目的

验证三次握手缓存队列 `int listen(int sockfd, int backlog)` 函数的第二个参数
实际缓存队列为 `min(/proc/sys/net/core/somaxconn,backlog)`

## 1.2. 步骤

- cd listenLimit
- make clean && make
- `./server 9999` 新窗口执行
- `./client 127.0.0.1 9999` 新窗口执行
- `sudo tcpdump -i "lo"` 新窗口执行

## 1.3. 预期结果

5个连接成功,5个连接失败

```log
0: ip:127.0.0.1 port:42678 , connect ok 
1: ip:127.0.0.1 port:42680 , connect ok 
2: ip:127.0.0.1 port:42682 , connect ok 
3: ip:127.0.0.1 port:42684 , connect ok 
4: ip:127.0.0.1 port:42686 , connect ok 
connect failed. Error: Socket operation on non-socket
5: ip:0.0.0.0 port:0 , connect fail 
connect failed. Error: Socket operation on non-socket
6: ip:0.0.0.0 port:0 , connect fail 
connect failed. Error: Socket operation on non-socket
7: ip:0.0.0.0 port:0 , connect fail 
connect failed. Error: Socket operation on non-socket
8: ip:0.0.0.0 port:0 , connect fail 
connect failed. Error: Socket operation on non-socket
9: ip:0.0.0.0 port:0 , connect fail 
```

```log
netstat -anp | grep 9999
tcp        5      0 0.0.0.0:9999            0.0.0.0:*               LISTEN      14070/./server      
tcp        0      0 127.0.0.1:42726         127.0.0.1:9999          ESTABLISHED 14071/./client      
tcp        0      0 127.0.0.1:42720         127.0.0.1:9999          ESTABLISHED 14071/./client      
tcp        0      0 127.0.0.1:42718         127.0.0.1:9999          ESTABLISHED 14071/./client      
tcp        0      0 127.0.0.1:9999          127.0.0.1:42724         ESTABLISHED -                   
tcp        0      0 127.0.0.1:9999          127.0.0.1:42722         ESTABLISHED -                   
tcp        0      0 127.0.0.1:42724         127.0.0.1:9999          ESTABLISHED 14071/./client      
tcp        0      0 127.0.0.1:9999          127.0.0.1:42720         ESTABLISHED -                   
tcp        0      0 127.0.0.1:42722         127.0.0.1:9999          ESTABLISHED 14071/./client      
tcp        0      0 127.0.0.1:9999          127.0.0.1:42718         ESTABLISHED -                   
tcp        0      0 127.0.0.1:9999          127.0.0.1:42726         ESTABLISHED -              
```

## 1.4. 参考资料

1. [linux里的backlog](https://blog.csdn.net/raintungli/article/details/37913765)
2. [理解 Linux backlog/somaxconn 内核参数](https://jaminzhang.github.io/linux/understand-Linux-backlog-and-somaxconn-kernel-arguments/)
