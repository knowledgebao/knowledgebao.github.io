# coding=utf-8
"""
压缩文件功能
"""
import sys
import huffman
import constant

def count_weight(fin):
    '''
    扫描文件,统计字符
    :fin: 文件对象
    '''
    weights = [0 for _ in range(constant.CHAR_NUM)]
    c = fin.read(1)
    while c:
        weights[int.from_bytes(c,'little')] += 1 # 'little'最高位字节放在字节数组的末尾
        c = fin.read(1)
    return weights

def encoding_file(fin, fout, char_to_code):
    '''
    编码文件:
    :fin: 输入文件
    :fout: 输出文件
    :char_to_code: 字符到编码的映射
    :return: 
        编码后的长度(字节为单位)和编码串最后一个字节的有效长度

    '''
    total = 0   # 编码总长度
    cur = 0     # 待输出的一个字节编码串
    size = 0    # 当前待输出的比特书
    c = fin.read(1)
    while c:
        code = char_to_code[int.from_bytes(c,'little')] # 编码串
        for i in range(len(code)):
            if code[i] == '0':
                # 往左子树移为0
                cur = cur << 1
            else:
                # 往右子树移为1
                cur = (cur << 1)| 1
            size += 1

            if size == constant.BYTE_SIZE:
                fout.write(cur.to_bytes(1, 'little'))
                total += 1
                size = 0
                cur = 0
        c = fin.read(1)
    if size :
        # 不足一个字节
        cur = cur << (constant.BYTE_SIZE-size)
        fout.write(cur.to_bytes(1, 'little'))
        total += 1
    else:
        # 足够一个字节
        size = 8

    return total, size


def compress(input_file):
    '''
    压缩文件
    :input_file: 目标文件
    :return:
        output_file: 输出文件
    '''
    output_file = input_file+constant.SUFFIX
    with open(input_file, 'rb') as fin, open(output_file, 'wb') as fout:
        # 统计字符出现的频数
        weights = count_weight(fin)

        print(f"weights: {str(weights)}")

        # 建立huffman树
        huffman_tree = huffman.HuffTree()
        huffman_tree.build_huffman_tree(weights)

        # 构建字符到编码串的映射
        char_to_code = huffman_tree.build_dictionary()

        print(f"char_to_code:{char_to_code}")

        # 重新读取文件
        fin.seek(0)
        total, num = encoding_file(fin,fout,char_to_code)

        print(f'total={total}, num={num}')

        # 保存字符频数表到文件后面
        for i in range(constant.CHAR_NUM):
            fout.write(weights[i].to_bytes(constant.FOUR, 'little'))
            fout.flush()
        
        # 保存total, num
        fout.write(total.to_bytes(constant.FOUR, 'little'))
        fout.write(num.to_bytes(constant.FOUR, 'little'))

    src_file_size = huffman_tree.root.weight    # 源文件大小
    dst_file_size = total+constant.CHAR_NUM * constant.FOUR + constant.FOUR * 2   # 压缩后文件大小

    print(f'{input_file} compress as {output_file}')
    print(f'dst/src = {dst_file_size}/{src_file_size} ~= {dst_file_size/src_file_size}%')

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print(f'usage: python {sys.argv[1]} input_file')
        sys.exit()
    
    input_file = sys.argv[1]
    compress(input_file)









