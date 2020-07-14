# 1. cmake 举例

- [1. cmake 举例](#1-cmake-举例)
  - [1.1. 单文件编译](#11-单文件编译)
  - [1.2. 多文件编译](#12-多文件编译)
  - [1.3. 库编译](#13-库编译)
  - [1.4. 库调用](#14-库调用)

## 1.1. 单文件编译

详见 ./code/single_file

```bash
cd code/single_file
cmake -B build -G Ninja #可以不用 -G 指定 Generators
cmake --build build     #编译生成可执行程序
```

## 1.2. 多文件编译

详见 ./code/mult_file

```bash
cd code/mult_file
cmake -B build -G Ninja #可以不用 -G 指定 Generators
cmake --build build     #编译生成可执行程序
```

## 1.3. 库编译

详见 ./code/used_lib/lib

```bash
cd code/used_lib/lib
cmake -B build -G Ninja #可以不用 -G 指定 Generators
cmake --build build     #编译生成动态库和静态库，这里使用Nigja,在windows下生成的是.a和.dll
```

```bash
cd code/used_lib/lib
cmake -B build
cmake --build build     #编译生成动态库和静态库，这里使用Visual Studio,在build\lib\Debug下生成.dll和.lib
```

## 1.4. 库调用
