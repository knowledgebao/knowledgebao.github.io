# git-lfg

- Git LFS 是 Github 开发的一个 Git 的扩展，用于实现 Git 对大文件的支持
- git的diff/patch等是基于文件行的.对于二进制文件来说. git需要存储每次commit的改动.
- 每次当二进制文件修改,发生变化的时候. 都会产生额外的提交量.导致clone和pull的数据量大增.在线仓库的体积也会迅速增长.
- LFS(Large File Storage) 就是为了解决这一问题而产生的工具.
- 它将你所标记的大文件保存至另外的仓库,而在主仓库仅保留其轻量级指针.
- 那么在你检出版本时,根据指针的变化情况下更新对应的大文件.而不是在本地保存所有版本的大文件

## 安装

### Linux

- `curl -s https://packagecloud.io/install/repositories/github/git-lfs/script.deb.sh | sudo bash`
- `sudo apt-get install git-lfs`
- `git lfs install`

### Mac

- `安装HomeBrew /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"`
- `brew install git-lfs`
- `git lfs install`

### Windows

- 下载安装 `windows installer`
- 运行 `windows installer`
- 在命令行执行 `git lfs install`

### 使用

- 执行 `git lfs install` 开启lfs功能
- 使用 `git lfs track` 命令进行大文件追踪 例如 `git lfs track "*.png"` 追踪所有后缀为png的文件
- 使用 `git lfs track` 查看现有的文件追踪模式
- 提交代码需要将 `.gitattributes` 文件提交至仓库. 它保存了文件的追踪记录
- 提交后运行 `git lfs ls-files` 可以显示当前跟踪的文件列表
- 将代码 `push` 到远程仓库后，LFS 跟踪的文件会以『Git LFS』的形式显示:
- clone 时 使用`git clone` 或 `git lfs clone` 均可

`git lfs track "design-resources/design.psd"` 跟踪具体文件
`git lfs track "*.indd"` 追踪指定后缀文件
`git lfs track "design-assets/*"` 最终指定目录

追踪完成后，还是需要通过 `git add` `git commit` `git push` 推送给后端，别忘记推送 `.gitattributes` 哦

## 参考资料

1. [Git LFS的使用](https://www.jianshu.com/p/493b81544f80)