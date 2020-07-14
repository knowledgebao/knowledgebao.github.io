---
layout: post
title: tool-markdown
date: 2019-11-08 17:45:20
description: tool-markdown
tag: vscode

---



# vscode中编辑markdown的工具

- [vscode中编辑markdown的工具](#vscode中编辑markdown的工具)
  - [markdown all in one](#markdown-all-in-one)
    - [支持功能](#支持功能)
  - [markdown pdf](#markdown-pdf)
  - [markdown TOC](#markdown-toc)
  - [Markdown Preview Enhanced](#markdown-preview-enhanced)
  - [markdownlint](#markdownlint)
  - [参考网址](#参考网址)

## markdown all in one

### 支持功能

1. 提供了常用操作便利的快捷键  

| Key              | Command                                                 |
| ---------------- | ------------------------------------------------------- |
| Ctrl + B         | Toggle bold      粗体                                   |
| Ctrl + I         | Toggle italic     斜体                                  |
| Ctrl + Shift + ] | Toggle heading (uplevel)标题升级                        |
| Ctrl + Shift + [ | Toggle heading (downlevel)标题降级                      |
| Ctrl + M         | Toggle math environment  触发数学公式环境               |
| Alt + C          | Check/Uncheck task list item                            |
| Ctrl + Shift + V | Toggle preview  新标签预览                              |
| Ctrl + K V       | Toggle preview to side 右侧预览                         |
| Ctrl + F2        | Change All Occurrences 选择用鼠标所在区域(右键默认提供) |
| Shift + Alt+F    | Format Document 格式化文档(右键默认提供)                |
| Tab              | 自动降级                                                |
| Enter            | 自动升级                                                |

1. 支持目录
   - 自动生成目录,方法如下(可更新)
     - ctrl + shift + p
     - Markdown: Create Table of Contents
     - Markdown: Update Table of Contents
2. 一边书写一边预览
   - Ctrl + Shift + V
   - Ctrl + K V
3. 可轻松转换为HTML文件
     - ctrl + shift + p
     - Markdown: Print current document to HTML
4. 优化了List editing的编辑
   - 通过tab和enter快速编辑list
5. 可格式化table (Alt + Shift + F) 以及Task list (use Alt + C to check/uncheck a list item)
   - [ ] A
   - [x] B
   - [ ] C
6. 支持特殊数学符号渲染(Ctrl+M)  Markdown: Toggle code span
   $A+B=C$
7. 插入代码
   Markdown: Toggle code span
8. 自动添加标题序号
   - 触发条件,有待挖掘

## markdown pdf

1. 转换为html,可以由markdown all in one代替.
2. 除了转换为html还可以转换为pdf,jpg,png等
3. 转换pdf的时候可以设置 css 风格。
   - 参考：[含css文件](https://blog.csdn.net/luckybaimao/article/details/81140597),已经下载下来，详见 《markdown.css》
   - [N多种CSS风格](http://jasonm23.github.io/markdown-css-themes/)
   - 设置CSS方法1：setting.json："markdown-pdf.styles": ["D:\\gwork\\knowledgebao\\knowledgebao.github.io\\_posts\\ide\\vscode\\markdown.css"],
   - 设置CSS方法2：File → Preferences → Settings → Extensions → markdown-pdf configurations → styles 中 add 一个 css 文件路径
4. 默认会自动下载chrome,如果已安装chrom浏览器，或下载失败，则可在配置中指定chrome.exe路径。
   - 方法1：更 markdown-pdf.executablePath 配置项的值为chrom程序路径。
   - 方法2：setting.json："markdown-pdf.executablePath": "C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe",

## markdown TOC

1. 生成目录,可以由markdown all in one代替.
2. 此工具如果标题带数字会失效
3. 目前(2019-9-30)有2个版本,一个是1.5.6版本,一个是3.0.1版本,请测3.0.1版本好使(1.5.6不好使),但是1.5.6版本下载人数远远多于3.0.1版本.

## Markdown Preview Enhanced

- 官网介绍：https://shd101wyy.github.io/markdown-preview-enhanced/#/zh-cn/code-chunk
- 支持一下数据画图方式
- Code Chunk
- Matplotlib
- LaTeX
- TikZ
- Plotly

## markdownlint

- 插件介绍：https://marketplace.visualstudio.com/items?itemName=DavidAnson.vscode-markdownlint
github：https://github.com/DavidAnson/markdownlint/blob/master/doc/CustomRules.md
- vscde 中下载最多的Markdown 插件
- 主要是一些格式规范,错误检测等

## 参考网址

1. [免费好用的全平台 Markdown 编辑器，你可以自己「做」一个](https://sspai.com/post/53327)
2. [Markdown All in One 书写Markdown利器](https://segmentfault.com/a/1190000017461306)
3. [Markdown Preview Enhanced](https://zhuanlan.zhihu.com/p/56699805)