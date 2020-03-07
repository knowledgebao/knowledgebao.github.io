# C/C++函数

## 导入/导出

### Win32

- 导出 __declspec(dllexport)
- 导入 __declspec(dllimport)

```C
#if defined(example_EXPORTS)
#    define MEG_API __declspec(dllexport)
#else
#    define MEG_API __declspec(dllimport)
#endif

extern "C" MEG_API int add_v5(int a, int b, int c);

class MEG_API AddOp {};
```

Windows DLL编译时没有.lib生成，绝大部分是忘记加 __declspec(dllexport) 了。

### Linux

通过控制符号可见性控制导出

```C
#if example_EXPORTS
#    define MEG_API __attribute__((visibility("default")))
#  else
#    define MEG_API
#endif
```

## 调用约定

下面几种调用方式在 x86 下有效, x64 下统一用cdecl。

### cdecl

- 参数传递顺序： 从右到左
- 调用方清理堆栈
- 内部函数名加 `_` 前缀，如 _func

### stdcall

- 参数传递顺序： 从右到左
- 调用方清理堆栈
- 内部函数名加 `_` 前缀，函数名加后缀 @参数size， 如： _func@12

### fastcall

- 前两个DWORD参数放入ECX和EDX寄存器，其他参数入栈
- 函数清理堆栈。
- 函数名加@前缀，函数名加后缀 @参数size；如：@add_v4@12，

### thiscall

- this 指针放入ECX

示例：

```C
extern "C" {

MEG_API int add_v1(int a, int b, int c);

MEG_API int CDECL add_v2(int a, int b, int c);

MEG_API int WINAPI add_v3(int a, int b, int c);

MEG_API int FASTCALL add_v4(int a, int b, int c);
}

extern "C" MEG_API int add_v5(int a, int b, int c);

class MEG_API AddOp {
public:
    int add_v6(int a, int b, int c);
    int CDECL add_v7(int a, int b, int c);
};
```

vc++ x86 编译

```assembly
N/A, N/A,            ??4AddOp@@QAEAAV0@$$QAV0@@Z, 0x000010b9, Microsoft
N/A, 1 (0x00000001), ??4AddOp@@QAEAAV0@ABV0@@Z, 0x00001140, Microsoft
N/A, 2 (0x00000002), ?add_v1@@YAHHHH@Z, 0x0000100a, Microsoft
N/A, 3 (0x00000003), ?add_v6@AddOp@@QAEHHHH@Z, 0x00001069, Microsoft
N/A, 4 (0x00000004), ?add_v7@AddOp@@QAAHHHH@Z, 0x00001032, Microsoft
N/A, 5 (0x00000005), @add_v4@12, 0x0000106e, None
N/A, 6 (0x00000006), add_v2, 0x000010c3, None
N/A, 7 (0x00000007), _add_v3@12, 0x0000107d, None
N/A, 8 (0x00000008), add_v5, 0x00001050, None
```

vc++ x64编译

```assembly
N/A, N/A,            ??4AddOp@@QEAAAEAV0@$$QEAV0@@Z, 0x000011db, Microsoft
N/A, 1 (0x00000001), ??4AddOp@@QEAAAEAV0@AEBV0@@Z, 0x00001195, Microsoft
N/A, 2 (0x00000002), ?add_v1@@YAHHHH@Z, 0x0000100a, Microsoft
N/A, 3 (0x00000003), ?add_v6@AddOp@@QEAAHHHH@Z, 0x000010a5, Microsoft
N/A, 4 (0x00000004), ?add_v7@AddOp@@QEAAHHHH@Z, 0x00001032, Microsoft
N/A, 5 (0x00000005), add_v2, 0x00001127, None
N/A, 6 (0x00000006), add_v3, 0x0000101e, None
N/A, 7 (0x00000007), add_v4, 0x00001082, None
N/A, 8 (0x00000008), add_v5, 0x00001172, None
```

## name mangling(c++)

- C++ 支持成员函数，支持函数重载，支持运算符重载。编译器使用 name mangling 解决重载问题。
- 不同编译器的 name mangling 规则不一样。

```C
int add_v8(int a, int b) { return a + b; }
int add_v8(int a, int b, int c) { return a + b + c; }
int add_v8(int a, int b, int c, int d){ return a + b + c + d; }

# vc++ x64
N/A, 5 (0x00000005), ?add_v8@@YAHHH@Z, 0x00001131, Microsoft
N/A, 6 (0x00000006), ?add_v8@@YAHHHH@Z, 0x0000101e, Microsoft
N/A, 7 (0x00000007), ?add_v8@@YAHHHHH@Z, 0x000011bd, Microsoft

# gcc x64
N/A, 1 (0x00000001), _Z6add_v8ii, 0x00001106, Demumble
N/A, 2 (0x00000002), _Z6add_v8iii, 0x0000111a, Demumble
N/A, 3 (0x00000003), _Z6add_v8iiii, 0x00001137, Demumble
```

## 动态库加载

- CDLL cdecl, return int
- WinDLL stdcall, return int
- OleDLL stdcall, return HRESULT, raised WindowsError
- PyDLL cdecl, Python GIL is not released.

```python
from platform import uname
from ctypes import *

OS=uname()[0]
if OS == "Windows":
    dllEconder = WinDLL("Debug/DLLEncoder.dll")
elif OS == "Linux":
    dllEconder = CDLL("lib/libDLLEncoder.so")
elif OS == "Darwin":
    dllEconder = CDLL("lib/libDLLEncoder.dylib")
else
    print "Not support"
    exit()
```

## 类型映射

### 1. 数值类型

```python
i = c_int(123)
print(i.value)

i.value = -99
print(i.value)
```

### 2. C 字符串

```python
s = "Hello, World"
c_s = c_wchar_p(s)
print(c_s.value)  ==> 'Hello, World'
type(c_s.value)   ==> <class 'str'>

c_s2 = c_char_p(b'hello')
```

Python中str和bytes是只读的， 赋值给时 c_char_p, c_wchar_p, and c_void_p 重新分配内存。

```python
c_s = c_wchar_p(s)
print(c_s)
c_s.value = "Hi, there"
print(c_s)
```

## 3. 数组

```python
a1 = (c_ushort*3)()

print(a1)   ==> <__main__.c_ushort_Array_3 object at 0x00000000029bc268>

a1[:] = [1,2,3]
a1[2] = 6
print(a1[:]) ==> [1,2,6]

sizeof(a1) => 6

a2 = (c_ushort*3)()
memmove(a2, a1, sizeof(a1))
```

## 4. 字符数组

```python
b1 = (c_char*5)()
b1.value = b'Hello'
b1[:]   =>b'Hello'
b1[:3] =>b'Hel'

# 等价 (c_char*5)()
b2 = create_string_buffer(5)
b3 = create_string_buffer(b"Hello")

wb1 = create_unicode_buffer()
```

## 5. 结构体

```python
class meg_feature_t(Structure):
    _fields_ = [
                   ("version", c_int),
                   ("size", c_int),
                   ("data", c_uint8 * 4)]

f = meg_feature_t(1,2)
print(f.version)  #==> 1
print(f.size)     #==> 2
f.data[0] = 0x12

b1 = bytes(f)     #==> b'\x01\x00\x00\x00\x02\x00\x00\x00\x12\x00\x00\x00'
b2 = bytearray(f) #==> bytearray(b'\x01\x00\x00\x00\x02\x00\x00\x00\x12\x00\x00\x00')

f1 = meg_feature_t.from_buffer_copy(b1) // bytes not writable

f2 =  meg_feature_t.from_buffer(b2)
print(f2.version) #==> 1

f2.version = 5
print(b2)
```

## 6. 内存对齐

Python x64 默认按照4个字节对齐。

```python
class data2_t(Structure):
    _fields_ = [
                   ("v1", c_uint8),
                   ("v2", c_uint16),
                   ("v3", c_uint8),
                   ("v4", c_uint32),
                   ("v5", c_uint32),
                   ("v6", c_uint64)]

v = data2_t(0x01, 0x0202, 0x03, 0x04040404, 0x05050505, 0x0606060606060606)
>>> bytes(v)
b'\x01\x00\x02\x02\x03\x00\x00\x00\x04\x04\x04\x04\x05\x05\x05\x05\x06\x06\x06\x06\x06\x06\x06\x06'

>>> from struct import unpack
>>> [hex(x) for x in unpack('bxHbxIIQ', bytes(v))]
['0x1', '0x202', '0x3', '0x4040404', '0x5050505', '0x606060606060606']
```

## 7. Union

```python
class union_t(Union):
    _fields_ = [
                   ("v1", c_uint8),
                   ("v2", c_uint16),
                   ("v3", c_uint32),
                   ("v4", c_uint64)]
>>> u = union_t()
>>> u.v2=0x1221
>>> [hex(x) for x in bytes(u)]
['0x21', '0x12', '0x0', '0x0', '0x0', '0x0', '0x0', '0x0']
>>> hex(u.v1)
'0x21'
>>> hex(u.v3)
'0x1221'
>>> hex(u.v4)
'0x1221'
```

## 8. Pointer

类型：`c_int_p = POINTER(c_int)`
变量：`p = c_int_p(0)`

```python
c_int_p = POINTER(c_int)
p = c_int_p(0)

v = c_int(33)
p = pointer(v)
>>> p.contents
c_long(33)

>>> p[0]
18

>>> v.value=0x22
>>> p[0]
34
```

## 9. 函数

```python
extern "C" {
MEG_API int add_v9(int a, int b, int* OUT);
MEG_API int sprint(char *buffer, char a, int b, const char* c);
}
```

add_v9

```python
lib = CDLL("build/example.dll")

add_v9 = lib.add_v9
add_v9.argtypes = [c_int, c_int, POINTER(c_int)]
add_v9.restype = c_int

out = c_int()
print(add_v9(1,2,byref(out)))
print(out.value)
```

sprint

```python
sprint = lib.sprint
sprint.argtypes = [POINTER(c_char), c_char, c_int, c_char_p]
sprint.restype = c_int

buf = (c_char*255)()
count = sprint(cast(buf, c_char_p), ord('A'), 33, b"hello")
print(count)
print(buf[:])
print(buf[:count])
```
