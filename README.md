# 介绍

Yshell 是一个模拟 bash 写的一个终端命令行程序，其主要的功能都来自于 Bash 。

主要实现的功能主要是：

通过 Readline 库实现命令行的自动补全和历史记录功能。并且可以支持常见的命令行快捷键：Ctrl+l 、Ctrl+u、Ctrl+a、Ctrl+e等。
实现了一个终端需要的基本命令，如 cd、ls、pwd、mkdir、rm、mv、cp、touch、cat、echo、grep、find、sed、awk、head、tail、history、alias、unalias、source、exec、exit等。
实现了一些常用的 shell 扩展，如 source、alias、history、cd、pwd、echo、printf、read、test、if、for、while、until、case、function等。
实现了常见的环境变量，如 $HOME、$PATH、$PS1、$PS2等
实现了常见的命令符号：|、>、<、&&、||等
实现了对于常见的信号的支持：SIGINT、SIGHUB、SIGQUIT、SIGPIPE等
支持多线程的程序执行


这是一个可以运行在 Linux 系统上的命令行工具，实现了常用的命令以及支持信号处理。更多的信息可以查看[此处](https://ysc2.github.io/2024/07/09/Yshell%EF%BC%881%EF%BC%89/)
