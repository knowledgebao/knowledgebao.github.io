---
layout: post
title: new_method
date: 2019-11-08 17:45:20
description: new_method
tag: C_CPP

---

# new_method

## 简介

记录工作中碰到的新出现的C++函数，记录多了以后再后续整理

## 函数

### std::iota

[itoa](https://en.cppreference.com/w/cpp/algorithm/iota)
void iota( ForwardIt first, ForwardIt last, T value );
使用value填充迭代器区间，value每填充一个，执行一次value++

### print

来源:http://c.biancheng.net/view/693.html

```C++
valarray<int> data {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
valarray<int> more {2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6};
data[slice{0, 5, 1}] = 99; // Set elements in 1st row to 99
data [slice{10, 5, 1} ] = more; // Set elements in last row to values from more
std::cout << "data:\n";
print(data, 5, 4);//
```

### restrict

https://en.cppreference.com/w/c/language/restrict

### distance

https://en.cppreference.com/w/cpp/iterator/distance

### Traits::length(s)
