---
layout: post
title: opencv-API
date: 2019-11-12 15:12:58
description: opencv-API
tag: OpenCV3.1.0学习

---
# opencv-API

## resize

[官网说明](https://docs.opencv.org/master/da/d54/group__imgproc__transform.html#ga47a974309e9102f5f08231edc7e7529d)
resize( InputArray src, OutputArray dst,
Size dsize, double fx = 0, double fy = 0,
int interpolation = INTER_LINEAR );
结论：resize内存分配结论
1,如果dst内存是用户指定的,则dst的cols，rows, type必须与预期的一致，否则resize重新分配内存。
2,如果dst内存是Mat内部分配的，则只要dst的data大小比预期的大，就不重新分配内存。