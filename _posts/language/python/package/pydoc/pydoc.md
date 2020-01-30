# pydoc

## 常用命令

1. `python -m pydoc 模块名`
   上面命令中的 -m 是 python 命令的一个选项，表示运行指定模块，此处表示运行 pydoc 模块。后面的“模块名”参数代表程序要查看的模块。
   按下空格键，pydoc 将会使用第二屏来显示文档信息,与使用 help() 命令查看帮助信息的差别并不大。
   在使用 pydoc 查看帮助信息时，它会有自己的组织方式，它总是按如下顺序来显示模块中的全部内容：
   模块的文档说明：就是＊.py 文件顶部的注释信息，这部分信息会被提取成模块的文档说明。
   - CLASSES 部分：这部分会列出该模块所包含的全部类。
   - FUNCTIONS 部分：这部分会列出该模块所包含的全部函数。
   - DATA 部分：这部分会列出该模块所包含的全部成员变量。
   - FILE 部分：这部分会显示该模块对应的源文件。
2. `python -m pydoc -w 模块名`
   上面命令主要就是为 pydoc 模块额外指定了 -w 选项，该选项代表 write，表明输出 HTML 文档。
3. `python3 -m pydoc -p 端口号` 只适用于目录
   在指定端口启动 HTTP 服务器，接下来用户可以通过浏览器来查看 Python 的所有模块的文档信息
   第一部分显示 Python 内置的核心模块。
   第二部分显示当前目录下的所有模块，此处显示的就是 fkmodule 模块。
   第三部分显示 PYTHONPATH 环境变量所指定路径下的模块。
   其他部分，将会依次看到 Python 系统在 D:\Python\Python36\DLLs、D:\Python\Python36\lib、D:\Python\Python36\lib\site-packages 路径下的所有模块。
4. `python3 -m pydoc -b` 只适用于目录
   在任意一个未占用的端口启动HTTP服务器，并自动打开网页。
5. `python -m pydoc -k 被搜索模块的部分内容`
   pydoc 还提供了一个 -k 选项，该选项用于查找模块。只能通过doc展示，无法通过网页展示

## 参考资料

1. [Python pydoc模块详解：查看、生成帮助文档](http://c.biancheng.net/view/2674.html)
2. [Documentation generator and online help system](https://docs.python.org/3/library/pydoc.html)
