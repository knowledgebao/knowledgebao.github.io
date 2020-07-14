# tcpdump

## 简介

## 举例

- 存文件： `-w` tcpdump 的抓包保存到文件的命令参数是 `-w xxx.cap`
- 文件大小： `-c` 以100M大小分割保存文件， 超过100m另开一个文件 `-C 100m`
- 条件结束： `-C` 抓10000个包后退出 `-c 10000`
- 指定网卡： `-i` 抓eth1的包 `tcpdump -i eth1 -w /tmp/xxx.cap`
- 指定ip: `host` 抓 192.168.1.123的包 `tcpdump -i eth1 host 192.168.1.123 -w /tmp/xxx.cap`
- 指定port： `port` 抓192.168.1.123的80端口的包 `tcpdump -i eth1 host 192.168.1.123 and port 80 -w /tmp/xxx.cap`
- 排除port： `! port` 抓192.168.1.123的80端口和110和25以外的其他端口的包 `tcpdump -i eth1 host 192.168.1.123 and ! port 80 and ! port 25 and ! port 110 -w /tmp/xxx.cap`

抓192.168.1.123的icmp的包
tcpdump -i eth1 host 192.168.1.123 and icmp -w /tmp/xxx.cap

抓vlan 1的包
tcpdump -i eth1 port 80 and vlan 1 -w /tmp/xxx.cap

抓pppoe的密码
tcpdump -i eth1 pppoes -w /tmp/xxx.cap

抓下来的文件可以直接用ethereal 或者wireshark打开。

## 参考资料

1. [tcpdump举例](https://blog.csdn.net/zhuguorong11/article/details/52288760)
