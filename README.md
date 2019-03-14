# SE_wordlist

## 项目介绍

[北航2019软件工程结对作业](https://edu.cnblogs.com/campus/buaa/BUAA_SE_2019_RJ/homework/2637)：查找最长单词链。

单词链：各个单词之间首尾相连的长度大于1的链，如ab-bc-cd。默认情况下单词链不允许成环，如ab-bc-cd-da成环。

对于输入错误、文件不存在、成环、长度不足等初五，将抛出异常并处理。

## 开发环境

开发工具：VS2019，QT，OpenCppCoverage。

语言：C++。

## 运行环境：

WIN10。

## 运行方法：

1. 命令行运行：进入BIN路径下，执行命令：Wordlist.exe [args] filepath。输出结果在solution.txt中。

2. GUI运行：进入GUIBIN路径下，运行QtGui_Wordlist.exe。输出结果路径由用户输入。

## 命令说明：

-w：查找单词个数最长的单词链。如：

    Wordlist.exe -w file.txt

-c：查找单词中字母总和最长的单词链。如：

    Wordlist.exe -c file.txt

参数-w和-c只能出现一个。

-h：要求以-h后的一个字母作为单词链开头字母，如：

    Wordlist.exe -w -h a file.txt

-t：要求以-t后的一个字母作为单词链结尾字母，如：

    Wordlist.exe -w -t c file.txt

-r：单词链可以成环，如：

    Wordlist.exe -w -r file.txt

参数-h -t -r可以各出现0或1次，可以组合使用。
