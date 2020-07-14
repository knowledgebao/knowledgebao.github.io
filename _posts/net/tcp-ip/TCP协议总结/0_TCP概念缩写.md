# 1. TCP概念

- [1. TCP概念](#1-tcp概念)
  - [1.1. 缩写](#11-缩写)
    - [1.1.1. cwnd(congestion window)](#111-cwndcongestion-window)
    - [1.1.2. MSS(Maximum Segment Size)](#112-mssmaximum-segment-size)
    - [rwnd(接收方窗口)](#rwnd接收方窗口)
    - [RTO(Retransmission TimeOut)](#rtoretransmission-timeout)
  - [1.2. 参考资料](#12-参考资料)

## 1.1. 缩写

### 1.1.1. cwnd(congestion window)

拥塞窗口，用慢启动算法，单位MSS。[参考章节《TCP的超时与重传》的慢启动](4_TCP的超时与重传)

### 1.1.2. MSS(Maximum Segment Size)

不拆包的情况下，所能接收的最大长度报文(单位字节)。[参考《TCP格式》MSS](1_TCP格式.md)

### rwnd(接收方窗口)

窗口大小，对方可以接收的窗口大小，(单位字节)。 [参考《TCP格式》窗口大小](1_TCP格式.md)

### RTO(Retransmission TimeOut)

重传超时时间

## 1.2. 参考资料
