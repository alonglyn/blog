# macos 终端使用

## iterm2 + oh-my-zsh + git + alias
1. 安装
> [iterm2等安装](https://juejin.cn/post/6844904178075058189)

2. 配置.zshrc

```shell
alias python=python3
alias pip=pip3

# change folder
alias cdws='cd ~/work/Stability'
alias cdwsa='cd ~/work/Stability/Automation'
alias cdwsas='cd ~/work/Stability/Automation/saflib'
alias cdwss='cd ~/work/Stability/scripts'
alias cdwid='cd ~/work/iOS/Dev'
alias cdwie='cd ~/work/iOS/Example'
alias cdwir='cd ~/work/iOS/rc'
alias cdp='cd ~/playground'
alias cdwris='/Users/bytedance/work/Read/iOS/SourceReading'

# xcode alias
alias xcbv='xcodebuild -version'
alias xcs='xcode-select'
```
> 另外还有很多git 的alias 是默认加载的， 可以`code ~/.oh-my-zsh/plugins/git/git.plugin.zsh` 查看

