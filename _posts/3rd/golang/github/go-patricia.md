# go-patricia

## 简介

在Go (Golang)中实现的一种通用的 trie (也称为基数树)。trie (also called radix tree)

在计算机科学中，trie，又称前缀树或字典树，是一种有序树，用于保存关联数组，其中的键通常是字符串。与二叉查找树不同，键不是直接保存在节点中，而是由节点在树中的位置决定。一个节点的所有子孙都有相同的前缀，也就是这个节点对应的字符串，而根节点对应空字符串。一般情况下，不是所有的节点都有对应的值，只有叶子节点和部分内部节点所对应的键才有相关的值。

1. 访问保存在树中的所有项目，
2. 访问所有匹配特定前缀的项(访问子树)
3. 给定一个字符串，访问与该字符串的某个前缀匹配的所有项

[]byte作为key，interface{}作为value

Trie 不是线程安全的。

常用函数

创建

```golang
trie := NewTrie()
trie := NewTrie(MaxPrefixPerNode(16), MaxChildrenPerSparseNode(10))
```

插入和删除

```golang
// Insert some items.
trie.Insert(Prefix("Pepa Novak"), 1)
trie.Insert(Prefix("Pepa Sindelar"), 2)

// Delete some items.
trie.Delete(Prefix("Pepa Novak"))
trie.Delete(Prefix("Karel Macha"))
```

修改和获取

```golang
trie.Set(Prefix("Karel Hynek Macha"), 10)
trie.Get(Prefix("Karel Hynek Macha"))
```

检测

```golang
trie.Match(Prefix("Pepa Novak"))//完全匹配
trie.MatchSubtree(Prefix("Karel"))//前缀匹配
```

遍历

```golang
printItem := func(prefix patricia.Prefix, item patricia.Item) error {
    fmt.Printf("%q: %v\n", prefix, item)
    return nil
}
trie.Visit(printItem)//遍历所有
trie.VisitSubtree(Prefix("Pepa"), printItem)//遍历匹配前缀
prefix := Prefix("Karel Hynek Macha je kouzelnik")
trie.VisitPrefixes(prefix, printItem)//遍历多前缀

```

## 参考资料

1. [go-patricia](https://github.com/tchap/go-patricia)