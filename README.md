Trochilus
========

**A fast&free windows remote administration Tool**

Coded in C++ (using VS2010)

Features
---
* Support TCP,UDP,HTTP,HTTPS
* Serilize Protocol
* Support Non-UAC
* Shellcode Extension
* Remote Uninstall
* Singled-Threaded
* File Manager
* Remote Shell
* Download & Execute
* Upload & Execute
* System Information

Compiling
---
	devenv.exe build.sln /rebuild RELEASE

Build
---
	Run build.bat

ToDo
---
* ~~Reverse SOCKS5 Proxy~~
* ~~Support UDP reliable transfer.~~
* Shellcode extension SDK.

Contributing
---
1. Fork it
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request


1:  需要关闭windows 本地的 安全-病毒和威胁防护-实时保护等，否则生成的dll库在编译生成的时候就被系统删掉，编译报错

2：开发编译环境： vs2019 ,
    木马调试：加输出，打印到文件,
    控制端调试：可以用vs2019联调

3：Generator项目下 生成 Generator.exe，在上面填写后服务器的ip,通信协议，端口等配置后，
文件路径：trochilus\client\generator\Generator

 就可以生成一个setup.exe木马，用于在目标机器上执行

Generator.exe 调用打包工具 makensis.exe，将body.dll,shell.dll打包成木马setup.exe
将项目body生成的trochilus\client\bin\body.dll 和 项目 shell生成的shell.dll 拷贝到 trochilus\bin\Generator\bingo目录下
 将shell.dll 拷贝为 shell.bak
双击 trochilus\bin\Generator\Generator.exe，就生成了setup.exe（木马）


4：木马是客户端，不是windows的普通应用程序，是windows服务程序，
在  我的电脑右键-管理-服务和应用程序-服务 选择下找到木马程序 Medialoader Service，这个服务名称，可以在代码中修改

木马程序入口函数：项目路径shell/main/svtshell.cpp  svtshell:main()
	svtshell.cpp的文件路径：torchilus/client/servant/shell/svtshell.cpp

运行机制：1：注册服务 包括写入注册表，
                2：运行服务
消息处理函数 Manager::QueryCommandHandler
文件路径：trochilus\client\servant\body\Manager.cpp


5：控制端 也就是服务端，界面使用mfc实现，项目路径：torchilus：torchilus.cpp
文件路径：torchilus/server/torchilus/torchilus/torchilus.cpp
与客户端交互的消息，采用注册制
   如：RegisterMsgHandler(MSGID_REQUEST_REPORT_INFO, MsgHandler_ClientInfo, this)
函数MsgHandler_ClientInfo 用来处理 客户端发过来的MSGID_REQUEST_REPORT_INFO消息

消息循环处理函数 
tcp协议消息循环处理函数 tcp.cpp:WorkerProc()
CommManager.cpp文件的 TcpMsgHandler 为tcp消息循环处理函数


