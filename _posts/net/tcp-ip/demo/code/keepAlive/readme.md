# 1. 使用说明

- [1. 使用说明](#1-使用说明)
  - [1.1. 目的](#11-目的)
  - [1.2. 步骤](#12-步骤)
  - [1.3. 预期结果](#13-预期结果)
  - [1.4. 参考资料](#14-参考资料)
  - [wsl2使用window主机，建立代理](#wsl2使用window主机建立代理)

## 1.1. 目的

启动 tcp 保活机制

## 1.2. 步骤

- cd keepAlive
- make clean && make

正常保活测试流程：
- `sudo tcpdump -i "lo port 9999"` 新窗口执行
- `./server 9999` 新窗口执行
- `./client 127.0.0.1 9999 1` 新窗口执行,正常保活
- 30秒后，查看抓包结果

客户端奔溃测试流程(注意，使用一台不断网的机器连接223执行命令，避免断网前端服务停止，当然可以后端运行)
- `sudo tcpdump -i "eno1" port 9999` 新窗口执行(223服务器)
- `./server 9999` 新窗口执行(223服务器)
- `./client 127.0.0.1 9999 1` 新窗口执行,正常保活(wsl2)
- 30秒后，禁用wsl2的网口，90秒后停止抓包，查看抓包结果

客户端奔溃后重启
- `./client 127.0.0.1 9999 2` 新窗口执行,客户端奔溃(通过拔网线模拟，需二台机器)
- `./client 127.0.0.1 9999 3` 新窗口执行,租期奔溃，并且重启(通过拔网线，端口client，然后再插上网线，需二台机器)

## 1.3. 预期结果


## 1.4. 参考资料

1. [linux里的backlog](https://blog.csdn.net/raintungli/article/details/37913765)
2. [理解 Linux backlog/somaxconn 内核参数](https://jaminzhang.github.io/linux/understand-Linux-backlog-and-somaxconn-kernel-arguments/)

## wsl2使用window主机，建立代理

1. 假设 window 主机 IP 为 10.156.10.150
2. 假设 wsl2 的eth0 IP 为 172.19.137.93
3. 在 window 下的 cmd(以管理员身份运行) 窗口，执行如下命令： `netsh interface portproxy add v4tov4 listenport=9999 listenaddress=10.156.10.150 connectport=9999 connectaddress=127.19.137.93`
4. 外网想要访问 wsl2 的 `172.19.137.93:9999` 直接访问 `10.156.10.150:9999` 即可
5. 如果需要删除代理，执行下边命令： `netsh interface portproxy delete v4tov4 listenport=9999 listenaddress=10.156.10.150`
6. 查看 netsh 的代理端口，通过命令： `netsh interface portproxy show all` 查看