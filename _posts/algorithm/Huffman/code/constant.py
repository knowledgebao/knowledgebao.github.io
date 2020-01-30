# coding=utf-8

# 常量
CHAR_NUM = 256  # 字符种类(一个字节所能表示的数量)
BYTE_SIZE = 8   # 字节的位数
FOUR = 4        # 4字节
MASKS = [ # 一个字节的从高位到低位的每一个的掩码
    2**(BYTE_SIZE-i-1) for i in range(BYTE_SIZE)
]
SUFFIX = '.zzz'







