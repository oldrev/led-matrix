# 配置构建环境

TODO

## 需求

* STM32CubeMX：可到 ST.com 免费下载
* ST-Link2：可到 ST.com 免费下载
* OpenOCD: 
* VSCode: 
* ARM GCC:
* CMake/Make
* mkdocs

# 执行构建

以下基于 Windows 说明，若 Linux/MacOS 等系统可参考 build.bat 文件中的命令执行。

进入 `firmware` 目录执行：

```cmd
build.bat build
```

# 烧写程序

将编程器连接到板子，执行：

```cmd
build.bat burn
```

!!! warning "警告"

    连接电脑进行烧写编程，必须确保板子的 12V 主电源已经断开，或必须确保编程器到板子的 3.3V 电源未连接，否则可能烧毁编程器、板子或者电脑。