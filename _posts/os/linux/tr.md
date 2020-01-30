# tr

## 简介

Linux tr 命令用于转换或删除文件中的字符。
tr 指令从标准输入设备读取数据，经过字符串转译后，将结果输出到标准输出设备。

## 参数

语法
tr [-cdst][--help][--version][第一字符集][第二字符集]  
tr [OPTION]…SET1[SET2]
参数说明：

-c, --complement：反选设定字符。也就是符合 SET1 的部份不做处理，不符合的剩余部份才进行转换
-d, --delete：删除指令字符
-s, --squeeze-repeats：缩减连续重复的字符成指定的单个字符
-t, --truncate-set1：削减 SET1 指定范围，使之与 SET2 设定长度相等
--help：显示程序用法信息
--version：显示程序本身的版本信息
字符集合的范围：

\NNN 八进制值的字符 NNN (1 to 3 为八进制值的字符)
\\ 反斜杠
\a Ctrl-G 铃声
\b Ctrl-H 退格符
\f Ctrl-L 走行换页
\n Ctrl-J 新行
\r Ctrl-M 回车
\t Ctrl-I tab键
\v Ctrl-X 水平制表符
CHAR1-CHAR2 ：字符范围从 CHAR1 到 CHAR2 的指定，范围的指定以 ASCII 码的次序为基础，只能由小到大，不能由大到小。
[CHAR*] ：这是 SET2 专用的设定，功能是重复指定的字符到与 SET1 相同长度为止
[CHAR*REPEAT] ：这也是 SET2 专用的设定，功能是重复指定的字符到设定的 REPEAT 次数为止(REPEAT 的数字采 8 进位制计算，以 0 为开始)
[:alnum:] ：所有字母字符与数字
[:alpha:] ：所有字母字符
[:blank:] ：所有水平空格
[:cntrl:] ：所有控制字符
[:digit:] ：所有数字
[:graph:] ：所有可打印的字符(不包含空格符)
[:lower:] ：所有小写字母
[:print:] ：所有可打印的字符(包含空格符)
[:punct:] ：所有标点字符
[:space:] ：所有水平与垂直空格符
[:upper:] ：所有大写字母
[:xdigit:] ：所有 16 进位制的数字
[=CHAR=] ：所有符合指定的字符(等号里的 CHAR，代表你可自订的字符)

## 实例

- 将文件testfile中的小写字母全部转换成大写字母
  `cat testfile |tr a-z A-Z`或`cat testfile |tr [:lower:] [:upper:]`
- 所有的1换成2
  `tr 1 2 < height.txt`
- 间隔符是空格，我们把它修改为制表符
  `tr ‘ ‘ ‘\11′ < height.txt` 其中\11是八进制的制表符，回车是15，换行是12
- 重复指定的字符到与 SET1 相同长度为止
  `tr ‘1-5′ ‘[A*]‘ < number.txt` 变化：1234567890->AAAAA67890
  `tr 1-5 AB < number.txt`  变化：1234567890->ABBBB67890
  `tr 1-3 ABCDE < number.txt` 变化：1234567890->ABC4567890
- 重复指定的字符N次与 SET1 相同长度为止
  `tr ‘1-9′ ‘[A*5]BCDE’ < number.txt` 变化：1234567890->AAAAABCDE
- 将所有的数字都转换为字符x
  `tr [:alnum:] ‘[x*]‘ < number.txt`
- 如果有多个连续空格，就减为一个
  `tr -s ‘ ‘ ‘ ‘ < spaces.txt`
- 删除空格
  `tr -d ‘ ‘ < spaces.txt`
- 删除空行
  `tr -s "\n" < plane.txt`

## 参考资料

1. [Linux tr命令](https://www.runoob.com/linux/linux-comm-tr.html)
2. [shell tr命令的使用](https://www.iteye.com/blog/fyan-1172279)
