---
layout: post
title: git-fetch_pull_merge
date: 2019-11-20 15:30:22
description: git-fetch_pull_merge
tag: git

---

# 1. git merge/pull/fetch

- [1. git merge/pull/fetch](#1-git-mergepullfetch)
  - [1.1. merge](#11-merge)
  - [1.2. pull](#12-pull)
  - [1.3. fetch](#13-fetch)
  - [1.4. 实用功能](#14-%e5%ae%9e%e7%94%a8%e5%8a%9f%e8%83%bd)
    - [1.4.1. 合并本地某分支到当前分支](#141-%e5%90%88%e5%b9%b6%e6%9c%ac%e5%9c%b0%e6%9f%90%e5%88%86%e6%94%af%e5%88%b0%e5%bd%93%e5%89%8d%e5%88%86%e6%94%af)
    - [1.4.2. 合并远端对应分支到当前分支](#142-%e5%90%88%e5%b9%b6%e8%bf%9c%e7%ab%af%e5%af%b9%e5%ba%94%e5%88%86%e6%94%af%e5%88%b0%e5%bd%93%e5%89%8d%e5%88%86%e6%94%af)
    - [1.4.3. rebase远端对应分支到本地分支](#143-rebase%e8%bf%9c%e7%ab%af%e5%af%b9%e5%ba%94%e5%88%86%e6%94%af%e5%88%b0%e6%9c%ac%e5%9c%b0%e5%88%86%e6%94%af)
    - [1.4.4. 合并远端指定分支到当前分支](#144-%e5%90%88%e5%b9%b6%e8%bf%9c%e7%ab%af%e6%8c%87%e5%ae%9a%e5%88%86%e6%94%af%e5%88%b0%e5%bd%93%e5%89%8d%e5%88%86%e6%94%af)
    - [1.4.5. rebase远端指定分支到当前分支](#145-rebase%e8%bf%9c%e7%ab%af%e6%8c%87%e5%ae%9a%e5%88%86%e6%94%af%e5%88%b0%e5%bd%93%e5%89%8d%e5%88%86%e6%94%af)
  - [1.5. 参考资料](#15-%e5%8f%82%e8%80%83%e8%b5%84%e6%96%99)

## 1.1. merge

git merge -h 查看 merge 的帮助信息。

合并分支

```powershell
用法：git merge [<选项>] [<提交>...]
  或：git merge --abort
  或：git merge --continue

    -n                    在合并的最后不显示差异统计
    --stat                在合并的最后显示差异统计
    --summary             （和 --stat 同义）
    --log[=<n>]           在合并提交信息中添加（最多 <n> 条）精简提交记录
    --squash              创建一个单独的提交而不是做一次合并
    --commit              如果合并成功，执行一次提交（默认）
    -e, --edit            在提交前编辑提交说明
    --cleanup <模式>      设置如何删除提交说明里的空格和#注释
    --ff                  允许快进（默认）
    --ff-only             如果不能快进就放弃合并
    --no-ff               不管是否能快进都创建新分支
    --rerere-autoupdate   如果可能，重用冲突解决更新索引
    --verify-signatures   验证指定的提交是否包含一个有效的 GPG 签名
    -s, --strategy <策略>
                          要使用的合并策略
    -X, --strategy-option <option=value>
                          所选的合并策略的选项
    -m, --message <说明>  合并的提交说明（针对非快进式合并）
    -F, --file <路径>     从文件中读取提交说明
    -v, --verbose         更加详细
    -q, --quiet           更加安静
    --abort               放弃当前正在进行的合并
    --quit                --abort，但是保留索引和工作区
    --continue            继续当前正在进行的合并
    --allow-unrelated-histories
                          允许合并不相关的历史
    --progress            强制显示进度报告
    -S, --gpg-sign[=<key-id>]
                          GPG 提交签名
    --overwrite-ignore    更新忽略的文件（默认）
    --signoff             添加 Signed-off-by: 签名
    --no-verify           绕过 pre-merge-commit 和 commit-msg 钩子

```

## 1.2. pull

git pull -h 查看 pull 的帮助信息。

```powershell
用法：git pull [<选项>] [<仓库> [<引用规格>...]]

    -v, --verbose         更加详细
    -q, --quiet           更加安静
    --progress            强制显示进度报告
    --recurse-submodules[=<on-demand>]
                          控制子模组的递归获取

和合并相关的选项
    -r, --rebase[=(false|true|merges|preserve|interactive)]
                          使用变基操作取代合并操作以合入修改
    -n                    在合并的最后不显示差异统计
    --stat                在合并的最后显示差异统计
    --log[=<n>]           在合并提交信息中添加（最多 <n> 条）精简提交记录
    --signoff[=...]       添加 Signed-off-by: 签名
    --squash              创建一个单独的提交而不是做一次合并
    --commit              如果合并成功，执行一次提交（默认）
    --edit                在提交前编辑提交说明
    --cleanup <模式>      设置如何删除提交说明里的空格和#注释
    --ff                  允许快进式
    --ff-only             如果不能快进就放弃合并
    --verify-signatures   验证指定的提交是否包含一个有效的 GPG 签名
    --autostash           变基操作前后执行自动贮藏和弹出贮藏
    -s, --strategy <策略>
                          要使用的合并策略
    -X, --strategy-option <option=value>
                          所选的合并策略的选项
    -S, --gpg-sign[=<key-id>]
                          GPG 提交签名
    --allow-unrelated-histories
                          允许合并不相关的历史

和获取相关的参数
    --all                 从所有的远程抓取
    -a, --append          追加到 .git/FETCH_HEAD 而不是覆盖它
    --upload-pack <路径>  上传包到远程的路径
    -f, --force           强制覆盖本地分支
    -t, --tags            抓取所有的标签和关联对象
    -p, --prune           清除远程已经不存在的分支的跟踪分支
    -j, --jobs[=<n>]      并发拉取的子模组的数量
    --dry-run             演习
    -k, --keep            保持下载包
    --depth <深度>        深化浅克隆的历史
    --unshallow           转换为一个完整的仓库
    --update-shallow      接受更新 .git/shallow 的引用
    --refmap <引用映射>   指定获取操作的引用映射
    -4, --ipv4            只使用 IPv4 地址
    -6, --ipv6            只使用 IPv6 地址
    --show-forced-updates
                          在所有更新分支上检查强制更新
    --set-upstream        为 git pull/fetch 设置上游
```

`git pull` 的默认行为是 `git fetch + git merge` 更确切的说是 `git fetch` + `git merge FETCH_HEAD` 的缩写。
更准确地说，git pull使用给定的参数运行 git fetch,比如：

`git pull --rebase`  是  `git fetch` + `git rebase FETCH_HEAD` 的缩写。

- 首先，git 会把当前分支里面的每个 commit 取消掉；
- 其次，把上面的操作临时保存成 patch 文件，存在 .git/rebase 目录下；
- 然后，把当前分支更新到最新的 origin 分支；//git fetch origin curbranch
- 最后，把上面保存的 patch 文件应用到 feature1 分支上；

`git rebase --abort` 会放弃合并，回到rebase操作之前的状态，之前的提交的不会丢弃；
`git rebase --skip` 则会将引起冲突的commits丢弃掉（慎用！！）；当然还是可以通过git reflog命令找回丢失的 commit 信息
`git rebase --continue` 合并冲突，结合"git add 文件"命令一起用与修复冲突，提示开发者，一步一步地有没有解决冲突。（fix conflicts and then run "git rebase --continue"）

## 1.3. fetch

`git fetch -h` 查看 fetch 的帮助信息。

```powershell
用法：git fetch [<选项>] [<仓库> [<引用规格>...]]
  或：git fetch [<选项>] <组>
  或：git fetch --multiple [<选项>] [(<仓库> | <组>)...]
  或：git fetch --all [<选项>]

    -v, --verbose         更加详细
    -q, --quiet           更加安静
    --all                 从所有的远程抓取
    --set-upstream        为 git pull/fetch 设置上游
    -a, --append          追加到 .git/FETCH_HEAD 而不是覆盖它
    --upload-pack <路径>  上传包到远程的路径
    -f, --force           强制覆盖本地引用
    -m, --multiple        从多个远程抓取
    -t, --tags            抓取所有的标签和关联对象
    -n                    不抓取任何标签(--no-tags)
    -j, --jobs <n>        子模组获取的并发数
    -p, --prune           清除远程已经不存在的分支的跟踪分支
    -P, --prune-tags      清除远程不存在的本地标签，并且替换变更标签
    --recurse-submodules[=<on-demand>]
                          控制子模组的递归抓取
    --dry-run             演习
    -k, --keep            保持下载包
    -u, --update-head-ok  允许更新 HEAD 引用
    --progress            强制显示进度报告
    --depth <深度>        深化浅克隆的历史
    --shallow-since <时间>
                          基于时间来深化浅克隆的历史
    --shallow-exclude <版本>
                          深化浅克隆的历史，除了特定版本
    --deepen <n>          深化浅克隆的历史
    --unshallow           转换为一个完整的仓库
    --update-shallow      接受更新 .git/shallow 的引用
    --refmap <引用映射>   指定获取操作的引用映射
    -o, --server-option <server-specific>
                          传输选项
    -4, --ipv4            只使用 IPv4 地址
    -6, --ipv6            只使用 IPv6 地址
    --negotiation-tip <版本>
                          报告我们只拥有从该对象开始可达的对象
    --filter <参数>       对象过滤
    --auto-gc             获取后执行 'gc --auto'
    --show-forced-updates
                          在所有更新分支上检查强制更新
```

FETCH_HEAD 指的是: 某个branch在服务器上的最新状态'.

每一个执行过 fetch 操作的项目'都会存在一个 FETCH_HEAD 列表, 这个列表保存在 .git/FETCH_HEAD 文件中, 其中每一行对应于远程服务器的一个分支.
当前分支指向的 FETCH_HEAD, 就是这个文件第一行对应的那个分支.

通过 `git log -p FETCH_HEAD` 可以查看,返回的信息包括更新的文件名，更新的作者和时间，以及更新的代码（19行红色[删除]和绿色[新增]部分）。
我们可以通过这些信息来判断是否产生冲突，以确定是否将更新 merge 到当前分支。

一般来说, 存在两种情况:
    如果没有显式的指定远程分支, 则远程分支的master将作为默认的 FETCH_HEAD.
    如果指定了远程分支, 就将这个远程分支作为 FETCH_HEAD.

用法：

1. `git fetch`
  
    具体细节分2步走：
    a. 创建并更新本地远程分支。即创建并更新 origin/xxx 分支，拉取代码到 origin/xxx 分支上。
    b. 在 FETCH_HEAD 中设定当前分支-origin/当前分支对应，如直接到时候git merge就可以将origin/abc合并到abc分支上。
    缺点：会拉取当前项目的所有分支的commit。这样没必要，如当前项目有很多人在参与，那么就会有很多分支，那么其他分支的提交也会拉取下来，你得等半天下下来，网速不好就蛋疼了。

2. `git fetch origin`

    只是手动指定remote分支，和上边没区别

3. `git fetch origin branch1`

    设定当前分支的 FETCH_HEAD' 为远程服务器的branch1分支`.
    注意: 在这种情况下, 不会在本地创建本地远程分支, 这是因为:
    这个操作是git pull origin branch1的第一步, 而对应的pull操作,并不会在本地创建新的branch.

    一个附加效果是:这个命令可以用来测试远程主机的远程分支branch1是否存在, 如果存在, 返回0, 如果不存在, 返回128, 抛出一个异常.

4. `git fetch origin branch1:branch2`

    使用远程branch1分支在本地创建branch2(但不会切换到该分支),
    如果本地不存在branch2分支, 则会自动创建一个新的branch2分支,
    如果本地存在branch2分支, 并且是`fast forward', 则自动合并两个分支, 否则, 会阻止以上操作.

5. `git fetch origin :branch2`

    等价于: git fetch origin master:branch2

## 1.4. 实用功能

### 1.4.1. 合并本地某分支到当前分支

`git merge <name> --no-ff`:  
合并分支name到本分支

默认执行fast forward合并，看不出来曾经做过合并。
--no-ff参数就可以用普通模式合并，合并后的历史有分支，能看出来曾经做过合并。
--ff-only： 如果不能快进就放弃合并

### 1.4.2. 合并远端对应分支到当前分支

`git pull`

默认行为是 `git fetch + git merge` 更确切的说是 `git fetch` + `git merge FETCH_HEAD` 的缩写。

### 1.4.3. rebase远端对应分支到本地分支

`git pull --rebase`

实际是  `git fetch` + `git rebase FETCH_HEAD` 的缩写。

### 1.4.4. 合并远端指定分支到当前分支

`git fetch origin otherbranch` + `git merge FETCH_HEAD`

设定当前分支的 FETCH_HEAD 为远程服务器的 otherbranch 分支，对 FETCH_HEAD 执行 merge 操作

### 1.4.5. rebase远端指定分支到当前分支

`git fetch origin otherbranch` + `git rebase FETCH_HEAD`

设定当前分支的 FETCH_HEAD 为远程服务器的 otherbranch 分支，对 FETCH_HEAD 执行 rebase 操作

## 1.5. 参考资料

1. [git的突出解决--git rebase之abort、continue、skip](https://www.cnblogs.com/chenjunjie12321/p/6876220.html)
2. [git fetch 详解](https://www.jianshu.com/p/a5c4d2f99807)
