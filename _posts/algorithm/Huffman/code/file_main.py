# coding=utf-8
"""
huffman压缩/解压缩demo
"""
import sys
import constant
from compress import compress
from decompress import decompress

def usage(name):
    print(f'usage: python {name} -c/-d file' )
    print('     -c compress')
    print('     -d decompress')
    sys.exit()

def main():
    if len(sys.argv) != 3:
        usage(sys.argv[0])
    
    opt, input_file = sys.argv[1:]

    if opt == '-c':
        # 压缩文件
        output_file = input_file + constant.SUFFIX
        compress(input_file)
    elif opt == '-d':
        # 解压缩文件
        output_file = input_file.rsplit('.', 1)[0] # 取'.zzz'之前的字符串作为输出文件的名字
        decompress(input_file, output_file)
    else:
        usage(sys.argv[0])

if __name__ == '__main__':
    main()