# 简介

  * tinyToolkit是为减少编码工作而封装的简易工具套件, 不同工具代码之间无相互依赖关系, 可单独提取源码使用

# 要求

  * 标准特性
    - c++11

  * 构建工具
    - cmake 3.0 

# 系统

  * MacOS
  * Kylin
  * CentOS
  * Debian
  * Fedora
  * Ubuntu
  * Windows
  * OracleLinux

# 选项

  * BUILD_TEST
    - 描述: 编译单元测试用例
    - 使用: -DBUILD_TEST={ON|OFF}
    - 默认: 启用

# 安装

  ```shell
  # 生成
  cmake . -B build [-DBUILD_TEST={ON|OFF}]
  # 编译
  cmake --build build
  # 安装
  cmake --install build
  ```
