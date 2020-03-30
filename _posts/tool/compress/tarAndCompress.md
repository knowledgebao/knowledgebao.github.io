# 1. 常用压缩命令

- [1. 常用压缩命令](#1-%e5%b8%b8%e7%94%a8%e5%8e%8b%e7%bc%a9%e5%91%bd%e4%bb%a4)
  - [1.1. 简介](#11-%e7%ae%80%e4%bb%8b)
    - [1.1.1. tar](#111-tar)
    - [1.1.2. gunzip/gzip](#112-gunzipgzip)
    - [1.1.3. bunzip2/bzip2](#113-bunzip2bzip2)
    - [1.1.4. compress/uncompress](#114-compressuncompress)
    - [1.1.5. zip/unzip](#115-zipunzip)
    - [1.1.6. rar](#116-rar)
    - [1.1.7. lha](#117-lha)
  - [1.2. 后缀](#12-%e5%90%8e%e7%bc%80)
    - [1.2.1. .tar](#121-tar)
    - [1.2.2. .tar.gz或.tgz或.tar.tgz](#122-targz%e6%88%96tgz%e6%88%96tartgz)
    - [1.2.3. .tar.bz2](#123-tarbz2)
    - [1.2.4. .tar.bz](#124-tarbz)
    - [1.2.5. .tar.Z](#125-tarz)
    - [1.2.6. .gz](#126-gz)
    - [1.2.7. .bz2](#127-bz2)
    - [1.2.8. .bz](#128-bz)
    - [1.2.9. .Z](#129-z)
    - [1.2.10. .zip](#1210-zip)
    - [1.2.11. .rar](#1211-rar)
    - [1.2.12. .lha](#1212-lha)
  - [1.3. 参考资料](#13-%e5%8f%82%e8%80%83%e8%b5%84%e6%96%99)

## 1.1. 简介

### 1.1.1. tar

打包，可以配合其他压缩工具一块使用

### 1.1.2. gunzip/gzip

压缩解压 .gz 格式，可配合tar使用

### 1.1.3. bunzip2/bzip2

压缩解压 .bz .bz2 格式，可配合tar使用

### 1.1.4. compress/uncompress

压缩解压 .Z 格式，可配合tar使用

### 1.1.5. zip/unzip

压缩解压 .zip 格式

### 1.1.6. rar

压缩解压 .zip 格式

### 1.1.7. lha

压缩解压 .lha 格式

## 1.2. 后缀

### 1.2.1. .tar

    解包: tar xvf FileName.tar
    打包: tar cvf FileName.tar DirName
    （注: tar是打包，不是压缩！）

### 1.2.2. .tar.gz或.tgz或.tar.tgz

    解压: tar zxvf FileName.tar.gz
    压缩: tar zcvf FileName.tar.gz DirName

### 1.2.3. .tar.bz2

    解压: tar jxvf FileName.tar.bz2
    压缩: tar jcvf FileName.tar.bz2 DirName

### 1.2.4. .tar.bz

    解压: tar jxvf FileName.tar.bz
    压缩: tar jcvf FileName.tar.bz DirName

### 1.2.5. .tar.Z

    解压: tar Zxvf FileName.tar.Z
    压缩: tar Zcvf FileName.tar.Z DirName

### 1.2.6. .gz

    解压1: gunzip FileName.gz
    解压2: gzip -d FileName.gz

    压缩: gzip FileName

### 1.2.7. .bz2

    解压1: bzip2 -d FileName.bz2
    解压2: bunzip2 FileName.bz2

    压缩:  bzip2 -z FileName

### 1.2.8. .bz

    解压1: bzip2 -d FileName.bz
    解压2: bunzip2 FileName.bz

    压缩: 未知

### 1.2.9. .Z

    解压: uncompress FileName.Z
    压缩: compress FileName

### 1.2.10. .zip

    解压: unzip FileName.zip
    压缩: zip FileName.zip DirName

### 1.2.11. .rar

    解压: rar a FileName.rar
    压缩: rar e FileName.rar

### 1.2.12. .lha

    解压: lha -e FileName.lha
    压缩: lha -a FileName.lha FileName

## 1.3. 参考资料

1. [在linux下如何将文件夹压缩成.tgz文件](https://blog.csdn.net/haixin1109/article/details/18882459)
2. [tar命令](https://man.linuxde.net/tar)
