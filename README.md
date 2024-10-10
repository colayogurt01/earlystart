# EarlyStart

**EarlyStart** 是一个用于提前启动在 `.earlystart` 文件中配置的应用程序的工具。

## 功能概述

- **安装程序 (Installer)**：在 `C:\EarlyStart\.earlystart` 目录中生成一个配置文件，以便管理要启动的应用程序。
- **卸载程序 (Uninstaller)**：用于安全地卸载 **EarlyStart** 工具及其相关文件。
- **主程序 (EarlyStart)**：负责读取配置文件并自动启动其中指定的应用程序。

## 操作方法

### 安装程序

1. 运行 **installer**。
2. 该程序将在指定路径 `C:\EarlyStart\.earlystart` 下创建一个配置文件。

### 卸载程序

1. 运行 **uninstaller**。
2. 该程序将安全地删除 **EarlyStart** 工具及其生成的配置文件。

### 主程序

1. 运行 **earlystart**。
2. 主程序会自动读取 `.earlystart` 文件中的应用程序配置，并按需启动它们。


## 许可证

该项目使用 [MIT 许可证](LICENSE)。

