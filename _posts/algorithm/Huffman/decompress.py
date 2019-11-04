# coding=utf-8
"""
huffman解压
"""
import os
import sys
import huffman
import constant

def decoding(fin, fout, root, total, num):
    '''
    解码文件
    :fin: 输入文件
    :fout: 输出文件
    :root: huffman树的根节点
    :total: 要解码串的长度(byte)
    :num: 最后一个字节的有效位数 
    '''
    cur = root
    for byte in range(total):
        code = int.from_bytes(fin.read(1), 'little')    # 读一个字节的编码
        n = num if byte == total-1 else constant.BYTE_SIZE
        for bit in range(n):
            if code & constant.MASKS[bit]:
                # 此位为1, 向右子树移动
                cur = cur.right
            else:
                # 此位为0,向左子树移动
                cur = cur.left
            if not (cur.left or cur.right):
                # 左右子树为空,表示到达叶子节点
                char = cur.char
                print(char)
                fout.write(char.to_bytes(1,'little'))
                cur = root# 从根节点重新开始
        fout.flush()


def decompress(input_file, output_file):
    '''
    解压缩
    :input_file:压缩文件
    :output_fileh:输出文件
    '''
    with open(input_file, 'rb') as fin, open(output_file, 'wb') as fout:
        fin.seek(-(constant.FOUR*2), 2) # 文件最后的8字节是编码串的长度(字节为单位),和最后一个字节编码的有效位数
        total = int.from_bytes(fin.read(constant.FOUR), 'little')
        num = int.from_bytes(fin.read(constant.FOUR), 'little')

        print(f'total = {total}, num = {num}')

        # 读取字符频度表
        fin.seek(total, 0)
        weights = [int.from_bytes(fin.read(constant.FOUR),'little') for i in range(constant.CHAR_NUM)]

        # 构建huffman树
        huffman_tree = huffman.HuffTree()
        huffman_tree.build_huffman_tree(weights)

        print(f'huffman_tree.root.right.char = {huffman_tree.root.right.char}')
        print(f'huffman_tree.root.right({huffman_tree.root.right.left}, {huffman_tree.root.right.right})')

        # 解码后输出文件
        fin.seek(0,0)
        decoding(fin, fout, huffman_tree.root, total, num)
        
    print(f'{input_file} decompress as {output_file}')

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print(f'usage: python {sys.argv[0]}')
        sys.exit()

    input_file = sys.argv[1]
    output_file = input_file.rsplit('.', 1)[0] # 
    decompress(input_file, output_file)




