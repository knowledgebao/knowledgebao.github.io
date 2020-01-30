---
layout: post
title: python3与python2
date: 2019-11-08 17:45:20
description: python3与python2
tag: python

---



[TOC]

## python2.7的安全支持2020年就要结束了
## Python 2/3的思想基本是共通的，只有少量的语法有差别甚至不兼容。


# 一、主要区别:
## 编码方式:
- python3:
    - phython3默认编码是utf-8, 内存里(也就是字符串) 是编码是unicode，即使声明了某种编码，在内存里还是unicode。

- python2:
    - python2文件默认编码是ASCII,字符串默认也是ASCII，但是如果文件头声明了某种编码，那字符串编码就是那个编码.
    - 如果想写中文，文件头声明了utf-8,python2的解释器会用声明的编码去解码，加载到内存后也是用utf-8解码，而不是unicode!这就意味着用windows(中文版windwos默认编码是gbk)去执行的话就会出现乱码。因为在windows上只有2种情况windows上显示才不会乱：
        - 字符串以GBK格式显示
        - 字符串是unicode编码

## 数据类型:
### 1.字符串:
- Python3:
    - 只有一种字符串类型，unicode字符串，所以str()函数即可完成所有的功能。 Python3 中两者做了严格区分，分别用 str 表示字符串，bytes 表示字节序列，任何需要写入文本或者网络传输的数据都只接收字节序列
- python２:
    - 字符串有两个类型，一个是 unicode，一个是 str，前者表示文本字符串，后者表示字节序列，不过两者并没有明显的界限

|python2|python3|表现|转换|作用|
|-|-|-|-|-|
|str|	bytes|	字节|	encode|	存储、传输|
|unicode|	str	|字符|	decode|	展示|

**例子**:
```python
# coding=utf-8
import six
import sys

def py2():
    print(sys.getdefaultencoding())
    str1 = u"1234hello world 你好世界"
    print(type(str1))
    print(str1)
    print("-"*30)

    with open("./ttt.jpg", 'rb') as f:
        str2 = f.read()
    print(type(str2))
    print(str2[:30])

def py3():
    print(sys.getdefaultencoding())
    str1 = u"1234hello world 你好世界"
    print(type(str1))
    print(str1)
    print("-"*30)

    with open("./ttt.jpg", 'rb') as f:
        str2 = f.read(100)
    print(type(str2))
    print(str2[:30])

if __name__ == "__main__":
    if six.PY2:
        py2()
    if six.PY3:
        py3()

```


### 2.long长整型:
- python3:
    - 在python3里,只有一种整数类型int,大多数情况下，和python２中的长整型类似。
- python2:
    - python2有非浮点数准备的int和long类型。int类型最大值不能超过sys.maxint，而且这个最大值是平台相关的。可以通过在数字的末尾附上一个Ｌ来定义长整型，显然，它比int类型表示的数字范围更大。

**例子**:
```python
# coding=utf-8
import six
import sys

def py2():
    int_max = sys.maxint
    print("max int:{}".format(int_max))
    int1 = 9223372036854775807
    print(type(int1), int1)
    int2 = 9223372036854775808922337203685477580892233720368
    print(type(int2), int2)
    int3 = 928
    print(type(int3), int3)


def py3():
    # py3的sys没有maxint
    # int_max = sys.maxint
    # print("max int:{}".format(int_max))

    int1 = 9223372036854775807
    print(type(int1), int1)
    int2 = 92233720368547758089999999999999999999999999223
    print(type(int2), int2)
    int3 = 928
    print(type(int3), int3)


if __name__ == "__main__":
    if six.PY2:
        py2()
    if six.PY3:
        py3()
```

### 3.字典中的键keys()，值values()，键值对items():
- python3:
    - keys()，值values()，键值对items()其实也都是个迭代器想要的时候可以生成列表给你具体的值，不要的时候只会占很少的空间;

- python2:
    - keys()，值values()，键值对items()都是作为列表的形式存放值，虽然能存储所有的值，但是占内存空间大。

**例子**:
```python
# coding=utf-8
import six

def py2():
    dd={"a":1,"b":2, "hello":"world"}
    print(dd.keys())
    print(type(dd.keys()))
    print("-"*10)

    print(dd.values())
    print(type(dd.values()))
    print("-"*10)

    print(dd.items())
    print(type(dd.items()))


def py3():
    dd={"a":1,"b":2, "hello":"world"}
    print(dd.keys())
    print(type(dd.keys()))
    print("-"*10)

    print(dd.values())
    print(type(dd.values()))
    print("-"*10)

    print(dd.items())
    print(type(dd.items()))


if __name__ == "__main__":
    if six.PY2:
        py2()
    if six.PY3:
        py3()
```

### 4.True和False:
- python3:
    - True 和 False 变为两个关键字，永远指向两个固定的对象，不允许再被重新赋值。

    ```python
    >>> True = 1
      File "<stdin>", line 1
    SyntaxError: can't assign to keyword
    ```

- python2:
    - True 和 False 在 Python2 中是两个全局变量（名字），在数值上分别对应 1 和 0，所以他们可以指向其他变量
    ```python
    >>> True = False
    >>> True
    False
    >>> True is False
    True
    >>> False = "x"
    >>> False
    'x'
    >>> if False:
    ...     print("yes")
    ... 
    yes
    ```

### 5.迭代器:
- python3:
    - 在 Python2 中很多返回列表对象的内置函数和方法在 Python 3 都改成了返回类似于迭代器的对象
    - 字典对象的 dict.keys()、dict.values() 方法都不再返回列表，而是以一个类似迭代器的 "view" 对象返回。高阶函数 map、filter、zip 返回的也都不是列表对象了
    -  Python3 获取下一个值改成了 `__next__`

- python2:
    - Python2的迭代器必须实现 next 方法。

**例子**:
```python
# coding=utf-8
import six
from collections import Iterable, Iterator

def func(x):
    return x+1

class  Iterpy2:
    def __init__(self, data):
        self.data = data         # 上边界
        self.now = 0             # 当前迭代值，初始为0

    def __iter__(self):
        return self              # 返回该对象的迭代器类的实例；因为自己就是迭代器，所以返回self

    def next(self):              # 迭代器类必须实现的方法, 可迭代不用实现next
        while self.now < self.data:
            self.now += 1
            return self.now - 1  # 返回当前迭代值
        raise StopIteration      # 超出上边界，抛出异常



def py2():
    dd = {"a":1, "B":2, "hello":"world"}
    print(type(dd.keys()))
    print("-"*10)
    print(type(dd.values()))
    print("-"*10)
    print(type(dd.items()))
    print("#"*30)

    # map
    mm = map(func, [1,2,3,4,5])
    print(mm, type(mm)) 
    print("-"*10)

    # filter
    ff = filter(func, [1,2,3,4,5])
    print(ff, type(ff))
    print("-"*10)

    # zip
    a = [1,2,3]
    b = [4,5,6]
    c = [4,5,6,7,8]
    zz = zip(a,b)
    zz2 = zip(a,b,c)
    print(zz, type(zz))
    print(zz2, type(zz2))
    print("#"*30)

    # 迭代器
    print(dir([]))
    print(isinstance([], Iterable)) # __iter__
    print(isinstance([], Iterator)) 
    # list、dict、str虽然是Iterable(可迭代)，却不是Iterator(迭代器)
    print
    it = iter(a)
    try:
        print(next(it))
    except Exception as e:
        print(e) 

    for i in a:
        pass

    #  for循环等价如下
    while True:
        try:
            x = next(it)
            print(x)
        except StopIteration:
            # 遇到StopIteration就退出循环
            break


def py3():
    dd = {"a":1, "B":2, "hello":"world"}
    print(type(dd.keys()))
    print("-"*10)
    print(type(dd.values()))
    print("-"*10)
    print(type(dd.items()))
    print("#"*30)

    # map
    mm = map(func, [1,2,3,4,5])
    print(mm, type(mm)) 
    print("-"*10)

    # filter
    ff = filter(func, [1,2,3,4,5])
    print(ff, type(ff))
    print("-"*10)

    # zip
    a = [1,2,3]
    b = [4,5,6]
    c = [4,5,6,7,8]
    zz = zip(a,b)
    zz2 = zip(a,b,c)
    print(zz, type(zz))
    print(zz2, type(zz2))
    print("#"*30)

    # 迭代器
    print(dir([]))
    print(isinstance([], Iterable)) # __iter__
    print(isinstance([], Iterator)) 
    # list、dict、str虽然是Iterable(可迭代)，却不是Iterator(迭代器)
    print

    it = iter(a)
    try:
        print(it.__next__())
    except Exception as e:
        print(e) 


if __name__ == "__main__":
    if six.PY2:
        py2()
    if six.PY3:
        py3()

```


## 继承:
### 1.新/旧式类:
- 新式类:
    - 任何直接或者间接的继承于object的类就称之为新式类.(python3中的类的顶部都是object,所以python3中全是新式类)
    - 新式类的继承顺序,先深度遍历,当遇到共同的父类时就广度遍历,新式类的继承顺序还可以通过调用mro方法来查看

- 旧式类(经典类):
    - 不是object的子类,只有python2中有经典类的继承顺序,全部都是深度遍历

### 2.子类访问父类内容super()的区别:
- python3:
    -  解释器做了优化,可以省略不写
```python
# 子类访问父类的内容
class Person:
    def __init__(self,name,age):
        self.name = name
        self.age = age

    def eat(self):
        print('%s会吃东西'%self.name)

class Student(Person):
    def __init__(self,name,age,id):
        # 第一种,父类名直接调用,这种方法什么地方都可以调用,与继承无关,并且需要写上对象本身
        Person.__init__(self,name,age)
        # 第二种,super(类名,对象本身),是python2内置的
        super(Student,self).__init__(name,age)
        # 第三种,python3做了优化可以内部不传参,推荐使用
        super().__init__(name,age)
        self.id = id

    def eat(self):
        super().eat()  # 第三种方法在访问父类的方法
        super(Student,self).eat()  # 第二种方法在访问父类的方法
        print('%s吃更好的东西'%self.name)

s1 = Student('sxc',18,188)
s1.eat()
```
- python2: 
    - 需要写出super(当前类名,对象本身)


## 包:
### 1.生成包时的区别__init__文件
- python3:
    - 包下面没有__init__文件也不会报错;
- python2:
    - 包下面必须要有__init__文件

## 常用的函数方法:
### 1.print:
- python3:
    - Python3 中作为函数存在。
    ```python
    >>> print("hello", "world")
        ('hello', 'world')
    ```


- python2:
    - 在 Python 2 中，print 是一条语句。
    ```python
    >>> print("hello", "world")
        hello world
    ```

### 2.input:
- python2:
    - raw_input就相当于Python3中的input,把用户输出的数据全部转化为str字符串类型.
    - input让用户输出的是用户输出数据的原始类型,例如:用户输入int类型,他显示的也是int类型.
- python:
    - 只有input.
        - 把用户输出的数据全部转化为str字符串类型.

### 3.range:
- python2:
    - range:返回一个列表;
    - xrange:返回一个迭代器,其实就是python3中的range;

- python3:
    - range:就是一个迭代器,需要值的才会给值;

### 4.file与open:
- python3:
    - open():对文件的读写操作;

- python2:
    - file()与open():两者都能够打开文件，对文件进行操作，也具有相似的用法和参数，但是，这两种文件打开方式有本质的区别，file为文件类，用file()来打开文件，相当于这是在构造文件类，而用open()打开文件，是用python的内建函数来操作，一般使用open()打开文件进行操作，而用file当做一个类型，比如type(f) is file

**例子:**
```python
# coding=utf-8
import six

def py2():
    # file(name[, mode[, buffering]])
    f = file('test.txt')
    print(f.read())
    print(dir(f))
    print(type(f))
    print("#"*50)

    f = file('ttt.jpg')
    print(f.read(100))
    print(dir(f))
    print(type(f))


def py3():
    # f = file('test.txt') # 报错

    with open("./test.txt","r+") as f:
        print(f.read())
        print(dir(f))
        print(type(f))
    print("#"*50)

    with open("./ttt.jpg","rb") as f:
        print(f.read(100))
        print(dir(f))
        print(type(f))


if __name__ == "__main__":
    if six.PY3:
        py3()
    if six.PY2:
        py2()
```



### 5.f-string(py3.6):
官方文档: https://docs.python.org/zh-cn/3/reference/lexical_analysis.html#f-strings
- python2:
    - format:

- python3:
    - 既可以使用format,也可以使用f-string;


# 二、python3新增：
## 1.nonlocal：
- 在Python2中可以在函数里面可以用关键字 global 声明某个变量为全局变量，但是在嵌套函数中，想要给一个变量声明为非局部变量是没法实现的，在Pyhon3，新增了关键字 nonlcoal
```python
In [x]: def func():
   ...:     c = 1
   ...:     def foo():
   ...:         c=12
   ...:     foo()
   ...:     print(c)
   ...:

In [x]: func()
1
```
```python
In [x]: def func():
   ...:     c = 1
   ...:     def foo():
   ...:         nonlocal c
   ...:         c=12
   ...:     foo()
   ...:     print(c)
   ...:

In [x]: func()
12

```
## 2.类型注解:
函数注解语法 可以在定义函数的时候对参数和返回值添加注解：
例如:
```ptyhon
def foobar(a: int, b: "it's b", c: str = 5) -> tuple:
    return a, b, c
```
> a: int 这种是注解参数
>
> c: str = 5 是注解有默认值的参数
>
> -> tuple 是注解返回值。
注解的内容既可以是个类型也可以是个字符串，甚至表达式：
```python
def funr(a: 1+1) -> 2 * 2:
    return a

fun(3)
3
```
同时提供了获取定义的函数注解的两种办法：
- __annotations__
```python
>>> foobar.__annotations__
{'a': int, 'b': "it's b", 'c': str, 'return': tuple}
```
- inspect.signature:
```python
>>> import inspect
>>> sig = inspect.signature(foobar)
>>> # 获取函数参数
>>> sig.paraments
mappingproxy(OrderedDict([('a', <Parameter "a:int">), ('b', <Parameter "b:"it's b"">), ('c', <Parameter "c:str=5">)]))
>>> # 获取函数参数注解
>>> for k, v in sig.parameters.items():
        print('{k}: {a!r}'.format(k=k, a=v.annotation))     
a: <class 'int'>
b: "it's b"
c: <class 'str'>
>>> # 返回值注解
>> sig.return_annotation
tuple
```

Python 解释器并不会基于函数注解来自动进行类型检查, 所以就可以使用类型注解的方式对函数/方法进行类型检查
```python
# coding: utf8
import collections
import functools
import inspect


def check(func):
    msg = ('Expected type {expected!r} for argument {argument}, '
           'but got type {got!r} with value {value!r}')
    # 获取函数定义的参数
    sig = inspect.signature(func)
    parameters = sig.parameters          # 参数有序字典
    arg_keys = tuple(parameters.keys())   # 参数名称

    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        CheckItem = collections.namedtuple('CheckItem', ('anno', 'arg_name', 'value'))
        check_list = []

        # collect args   *args 传入的参数以及对应的函数参数注解
        for i, value in enumerate(args):
            arg_name = arg_keys[i]
            anno = parameters[arg_name].annotation
            check_list.append(CheckItem(anno, arg_name, value))

        # collect kwargs  **kwargs 传入的参数以及对应的函数参数注解
        for arg_name, value in kwargs.items():
           anno = parameters[arg_name].annotation
           check_list.append(CheckItem(anno, arg_name, value))

        # check type
        for item in check_list:
            if not isinstance(item.value, item.anno):
                error = msg.format(expected=item.anno, argument=item.arg_name,
                                   got=type(item.value), value=item.value)
                raise TypeError(error)

        return func(*args, **kwargs)

    return wrapper
    
    
@check
def foobar(a: int, b: str, c: float = 3.2) -> tuple:
    return a, b, c
```
### 3.dataclass--数据类(py3.7):
#### 3.1. 包: Lib/dataclasses.py
#### 3.2. 说明:
dataclass 可以为简单的情况自动生成方法，例如，一个__init__接受这些参数并将其分配给自己，之前的小例子可以重写为:
```python
@dataclass
class MyClass:
    var_a: str
    var_b: str
```
#### 3.3. 装饰器用法:
> @dataclasses.dataclass(*, init=True, repr=True, eq=True, order=False, unsafe_hash=False, frozen=False)

#### 3.4 其他用法:
https://docs.python.org/zh-cn/3/library/dataclasses.html

### 4 .最后,官方文档的说明: https://docs.python.org/zh-cn/3/whatsnew/index.html
# 二、支持的库:
## 1.主要支持python3的库:
- NumPy 与 SciPy(科学计算)
- Django、Flask、CherryPy、Pyramid(web开发)
- Pyramid(图片处理，代替PIL)
- cx_Freeze(将python文件打包成可执行文件)
- py2exe(打包成window可执行文件)
- OpenCV 3(开源的机器学习与计算机图形库)
- requests(http请求库)
- lxml(python xml解析库)
- BeautifulSoup4(html dom解析库)
- ipython与jupyter(交互计算)

## 2.只能用在python3,不能移植到python2的原因:
- 字符串默认编码为Unicode
- 清除unicode与bytes分离
- 异常链
- 函数注解
- 关键词参数语法
- 扩展的tuple解包
- 没有局部变量定义

## 3.six库:
https://six.readthedocs.io/

# 三、python之禅(python的世界观):
python2和python3都有
```python
In [1]: import this                                                                                                                                                           
The Zen of Python, by Tim Peters

Beautiful is better than ugly.
Explicit is better than implicit.
Simple is better than complex.
Complex is better than complicated.
Flat is better than nested.
Sparse is better than dense.
Readability counts.
Special cases aren't special enough to break the rules.
Although practicality beats purity.
Errors should never pass silently.
Unless explicitly silenced.
In the face of ambiguity, refuse the temptation to guess.
There should be one-- and preferably only one --obvious way to do it.
Although that way may not be obvious at first unless you're Dutch.
Now is better than never.
Although never is often better than *right* now.
If the implementation is hard to explain, it's a bad idea.
If the implementation is easy to explain, it may be a good idea.
Namespaces are one honking great idea -- let's do more of those!
```
```
美胜于丑。
显式优于隐式。
简单胜于复杂。
复杂总比复杂好。
平滑的比嵌套的好。
稀疏胜于稠密。
可读性很重要。
特殊情况不足以打破规则。
尽管实用性胜过纯洁性。
错误永远不会悄悄地过去。
除非明确沉默。
面对歧义，拒绝猜测的诱惑。
应该有一种——最好只有一种——显而易见的方法来做到这一点。
不过，如果不是荷兰语的话，这种方式一开始可能并不明显。
现在总比没有好。
虽然从来没有比现在更好。
如果实现很难解释，那是个坏主意。
如果实现很容易解释，这可能是一个好主意。
名称空间是一个非常好的主意——让我们做更多的事情吧！
```

# (欢迎指正补充...)