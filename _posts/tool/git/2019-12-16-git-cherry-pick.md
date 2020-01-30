---
layout: post
title: git-cherry-pick
date: 2019-12-13 11:36:50
description: git-cherry-pick
tag: git

---
# git cherry-pick

## 简介

git cherry-pick可以理解为”挑拣”提交，它会获取某一个分支的单笔提交，并作为一个新的提交引入到你当前分支上。 当我们需要在本地合入其他分支的提交时，如果我们不想对整个分支进行合并，而是只想将某一次提交合入到本地当前分支上，那么就要使用git cherry-pick了。

## 命令

git cherry-pick -h

```powershell
用法：git cherry-pick [<选项>] <提交号>...
  或：git cherry-pick <子命令>

    --quit                终止反转或拣选操作
    --continue            继续反转或拣选操作
    --abort               取消反转或拣选操作
    --skip                跳过当前提交并继续
    --cleanup <模式>      设置如何删除提交说明里的空格和#注释
    -n, --no-commit       不要自动提交
    -e, --edit            编辑提交说明
    -s, --signoff         添加 Signed-off-by: 签名
    -m, --mainline <父编号>
                          选择主干父提交编号
    --rerere-autoupdate   如果可能，重用冲突解决更新索引
    --strategy <策略>     合并策略
    -X, --strategy-option <选项>
                          合并策略的选项
    -S, --gpg-sign[=<key-id>]
                          GPG 提交签名
    -x                    追加提交名称
    --ff                  允许快进式
    --allow-empty         保留初始化的空提交
    --allow-empty-message
                          允许提交说明为空
    --keep-redundant-commits
                          保持多余的、空的提交
```

## 常用方法

- `git cherry-pick 2555c6e`
    将2555c6e合并到当前分支，如果有冲突，解决冲突，解决冲突后需要git commit手动进行提交，或者git add .后直接使用git cherry-pick --continue继续。
- `git cherry-pick -n 2555c6e`
    不会自动提交，只合并2555c6e分支
- `git cherry-pick -e 2555c6e`
    合并的同时，修改注释
- `git cherry-pick master`
    合并master顶端提交
- `git cherry-pick ..< branchname >`或`git cherry-pick ^HEAD < branchname >`
    应用所有提交引入的更改，这些提交是branchname的祖先但不是HEAD的祖先。也就是分叉后的所有提交

## 参考资料

1. [[Git] Git整理(五) git cherry-pick的使用](https://blog.csdn.net/FightFightFight/article/details/81039050)
