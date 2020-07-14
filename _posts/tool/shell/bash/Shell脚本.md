
# 1. shell脚本

- [1. shell脚本](#1-shell脚本)
  - [1.1. 简介](#11-简介)
  - [1.2. 常用函数](#12-常用函数)
    - [1.2.1. dirname](#121-dirname)
    - [1.2.2. getopt](#122-getopt)
    - [1.2.3. basename](#123-basename)
    - [1.2.4. tee](#124-tee)
    - [1.2.5. die](#125-die)
  - [1.3. 语法](#13-语法)
    - [1.3.1. here document](#131-here-document)
  - [1.4. tag](#14-tag)
  - [1.5. 参考资料](#15-参考资料)

## 1.1. 简介

## 1.2. 常用函数

### 1.2.1. dirname

`dirname $0` 返回这个脚本文件放置的目录，可以根据这个目录来定位所要运行程序的相对位置。

### 1.2.2. getopt

参考：[Linux下getopt()函数的简单使用](https://www.cnblogs.com/qingergege/p/5914218.html)

1. 遍历字符串 'bcdw:e:p:s:h'，-b ,-c ,-d ,-w, -e -p -s -h 。
2. 冒号表示参数，一个冒号就表示这个选项后面必须带有参数,但是这个参数可以和选项连在一起写，也可以用空格隔开
3. 两个冒号的就表示这个选项的参数是可选的，即可以有参数，也可以没有参数，但要注意有参数时，参数与选项之间不能有空格
4. 有些选项是不用带参数的，而这样不带参数的选项可以写在一起

```shell
while getopts 'bcdw:e:p:s:h' OPT; do
    case $OPT in
        b) REBUILD=ON           ;;
        c) CMD=COPY             ;;
        d) CMD=DEBUG            ;;
        w) DBG_DIR="$OPTARG"    ;;
        e) DBG_EXE="$OPTARG"    ;;
        p) DBG_PORT="$OPTARG"   ;;
        s) DBG_SERVER="$OPTARG" ;;
        h|?) usage ; exit 0 ;;
        *)   usage ; exit 1 ;;
    esac
done
```

`OPTARG` 选项的参数
`OPTIND` 下一个检索位置
`OPTERR` 是否将错误信息输出到stderr
`OPTOPT` 不在选项字符串optstring中的选项

### 1.2.3. basename

[[SHELL]：basename 命令详解](https://blog.csdn.net/happygongzhuo/article/details/6808721)

basename - strip directory and suffix from filenames，即去除文件名的目录部分和后缀部分。
返回一个字符串参数的基本文件名称。

basename NAME [SUFFIX]
basename OPTION

1. 如果 String 参数是 //(双斜杠) 或如果 String 参数包含的都是斜杠字符，则将字符串更改为单个 /(斜杠)。跳过步骤 2 到 4。
2. 从指定字符串除去任何拖尾的 / 字符。
3. 如果在 String 参数中剩余任何 / 字符，则除去字符串的前缀直到（包含）最后一个 / 字符。
4. 如果指定 Suffix 参数，且它和字符串中的剩余的字符相同，则不修改此字符串。

### 1.2.4. tee

[Linux tee命令](https://www.runoob.com/linux/linux-comm-tee.html)

Linux tee命令用于读取标准输入的数据，并将其内容输出成文件。
tee指令会从标准输入设备读取数据，将其内容输出到标准输出设备，同时保存成文件。

参数：
-a或--append 　附加到既有文件的后面，而非覆盖它．
-i或--ignore-interrupts 　忽略中断信号。
--help 　在线帮助。
--version 　显示版本信息。

### 1.2.5. die

在linux shell中执行命令后加上die命令，执行过程中如果出错会报出相应的原因与行号。如cat /usr/home/test.log || die $?，如果文件不存在，则会报出相应的错误。

## 1.3. 语法

### 1.3.1. here document

注意事项

1. delimiter 一般使用 EOF ，当然可以替换成任意的合法字符
2. 作为结尾的 delimiter 一定要顶格写，前面不能有任何字符
3. 作为结尾的 delimiter 后面也不能有任何的字符（包括空格）
4. 作为起始的 delimiter 前后的空格会被省略掉

```shell
cmd << delimiter
  Here Document Content
delimiter
```

1. 它的作用就是将两个 delimiter 之间的内容(Here Document Content 部分) 传递给cmd 作为输入参数。
2. Here Document 不仅可以在终端上使用，在shell 文件中也可以使用，例如下面的here.sh 文件
3. 还有一个用法就是将 '<<' 变为 '<<-'。 使用 <<- 的唯一变化就是Here Document 的内容部分每行前面的 tab (制表符)将会被删除掉，这种用法是为了编写Here Document的时候可以将内容部分进行缩进，方便阅读代码。
4. 在Here Document 的内容中，不仅可以包括普通的字符，还可以在里面使用变量，比如 $1,有时候不想展开这个变量怎么办呢，可以通过在起始的 delimiter的前后添加 " 来实现.
5. 运行这个脚本文件，会得到output.sh 这个新文件，里面的内容如下`echo "hello" echo "world"`

```shell
cat << EOF > output.sh
echo "hello"
echo "world"
EOF
```

## 1.4. tag

`tag::shell` `tag::base`

## 1.5. 参考资料

1. [linux 下 `dirname $0`](https://www.cnblogs.com/xupeizhi/archive/2013/02/19/2917644.html)
2. [shell脚本](http://docs.linuxtone.org/ebooks/C&CPP/c/ch31.html)
3. [linux shell 的here document 用法 (cat << EOF)](https://my.oschina.net/u/1032146/blog/146941)
4. [Linux下getopt()函数的简单使用](https://www.cnblogs.com/qingergege/p/5914218.html)
