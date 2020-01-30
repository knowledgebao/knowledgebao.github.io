# coding=utf-8
import os
import sys
import huffman

leaf_num = 7 # 叶子节点数
node_num = 2*leaf_num -1 # 树内总结点

def main():
    key = input(f"请输入{leaf_num}个叶子结点所代表的字符(用逗号分割)：").split(",")
    value = input(f"请输入{leaf_num}个叶子结点的权值来建立哈夫曼树(用逗号分割)：").split(",")
    if len(key) != len(value):
        print("输入有误!")
        return
    node_dict = map(key,value)

if __name__ == "__main__":
    main()


