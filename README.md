# Qt C++ Action Example

一个小而完整的 Qt Widgets 示例：用同一组 `QAction` 驱动菜单、工具栏和页面按钮，并通过 CMake 在 Linux、macOS、Windows 上构建、测试和打包。

## 示例内容

- 增加、减少、重置三个共享动作，以及常用键盘快捷键
- 菜单栏、工具栏、按钮和状态栏的联动
- 与界面解耦的 `Counter` 模型及 CTest 单元测试
- Qt 6 优先、Qt 5 兼容的 CMake 配置
- GitHub Actions 三系统构建矩阵
- Qt 6.3+ 下由 `cmake --install` 自动收集运行库和平台插件

## 环境要求

- CMake 3.21 或更高版本
- 支持 C++17 的编译器
- Qt 6（推荐 6.5 或更高版本）或 Qt 5，包含 Widgets 模块

## 本地构建

如果 Qt 没有安装在系统默认位置，把 `CMAKE_PREFIX_PATH` 指向 Qt 的 CMake 目录或 Qt 安装前缀。

```bash
cmake -S . -B build \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_INSTALL_PREFIX="$PWD/package" \
  -DCMAKE_PREFIX_PATH=/path/to/Qt/6.x.x/<toolchain> \
  -DBUILD_TESTING=ON
cmake --build build --config Release --parallel
ctest --test-dir build --build-config Release --output-on-failure
```

运行程序：

```bash
# Linux / 常见单配置生成器
./build/ActionExample

# Windows 多配置生成器
./build/Release/ActionExample.exe

# macOS
open ./build/ActionExample.app
```

生成可分发目录：

```bash
cmake --install build --config Release
```

安装前缀必须是绝对路径。使用 Qt 6.3 或更高版本时，`package` 会包含应用、Qt 动态库和所需平台插件。使用 Qt 5 时仍可正常编译，但发布前需自行运行 `windeployqt`、`macdeployqt` 或对应的 Linux 部署工具。

## CI 流水线

`.github/workflows/build.yml` 在向 `main` 或 `master` 分支 push 时执行：

1. 在 Ubuntu、macOS、Windows runner 上安装 Qt 6.9.3，Windows 使用 MinGW-w64 13.1；
2. 配置并并行编译 Release 版本；
3. 运行 CTest；
4. 安装到独立目录并收集运行时依赖；
5. 上传每个平台各自的 `ActionExample-*` 构建产物。

如需切换 Qt 版本，只需修改工作流顶层的 `QT_VERSION`。生产发布通常还应增加代码签名、公证、安装包格式和发布到 Release 等步骤。

## 项目结构

```text
.
├── .github/workflows/build.yml  # 三系统 CI
├── CMakeLists.txt               # 构建、测试和部署规则
├── src/
│   ├── counter.*                # 可测试的业务模型
│   ├── main.cpp                 # 程序入口
│   └── mainwindow.*             # Qt Widgets 界面与 QAction
└── tests/counter_test.cpp       # 无图形环境依赖的测试
```
