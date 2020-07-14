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

- cd persist_timer
- make clean && make
- `./server 9999` 新窗口执行
- `./client 127.0.0.1 9999` 新窗口执行
- `sudo tcpdump -i "lo"` 新窗口执行

## 1.3. 预期结果

## 1.4. 参考资料
