# coding=utf-8
"""
实现huffman算法的细节
"""
import heapq

class HuffNode():
    '''huffman节点'''
    def __init__(self,weight,char=None):
        self.weight = weight    # 权重
        self.char = char    # 节点元素数据(int)
        self.left = None    # 左节点
        self.right = None   # 右节点

    def __lt__(self, other):
        return self.weight < other.weight

class HuffTree():
    '''huffman树'''
    def __init__(self):
        self.root = None    # 根节点

    def _build_dictionary(self,cur,d,code=''):
            if not (cur.left or cur.right):
                # 左右为空,该节点为叶子节点
                d[cur.char] = code
                print(f'({cur.char}=>{code})')
            else:
                # 存在子树
                if cur.left:
                    self._build_dictionary(cur.left, d, code+'0') # 向左移动为0
                if cur.right:
                    self._build_dictionary(cur.right, d, code+'1') # 向右移动为1
    
    def build_dictionary(self):
        '''遍历huffman树,构造huffman字典'''
        d = {}
        self._build_dictionary(self.root, d)   
        return d

    def build_huffman_tree(self,weight):
        '''
        根据权重列表,构建huffman树
        :weight: 权重列表
        '''
        w_size = len(weight)
        heap = [HuffNode(weight[i],i) for i in range(w_size)]   # 构建一组单节点的树
        heapq.heapify(heap) # 堆化

        for i in range(w_size-1):
            # 去两棵最小的树
            x = heapq.heappop(heap)
            y = heapq.heappop(heap)
            
            # 合并两棵树
            z = HuffNode(x.weight+y.weight)
            z.left = x
            z.right = y

            print(f'z.weight = {z.weight}')
            
            # 将合并后的树入堆
            heapq.heappush(heap, z)
        
        self.root = heap[0]
        print(f'tree root: {self.root.weight}, {self.root.char}')
