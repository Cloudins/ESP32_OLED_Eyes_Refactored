# ESP32 Interactive OLED Eyes (Refactored)

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Platform](https://img.shields.io/badge/platform-ESP32-green.svg)
![Framework](https://img.shields.io/badge/framework-Arduino/PlatformIO-orange.svg)

这是一个基于 ESP32 和 SSD1306 OLED 屏幕的交互式电子眼睛项目。该项目已从原始的单文件代码重构为符合工业标准的 **面向对象 (OOP)** 架构，极大提高了代码的可维护性与扩展性。

## 🌟 项目亮点
- **模块化重构**：将动画引擎、定时器、绘图引擎与核心逻辑解耦。
- **Web 端交互**：支持通过 WiFi 连接手机/电脑，实时切换表情与动作。
- **自定义表情**：集成了多种预设表情，包括新增的 **Confused (大小眼)** 模式。
- **丝滑动画**：基于硬件加速的绘图逻辑，支持 30+ FPS 的平滑过度。

## 🛠️ 硬件配置
- **开发板**: ESP32 (DevKit v1)
- **屏幕**: 0.96" SSD1306 OLED (I2C)
- **引脚连接**:
  - SDA -> GPIO 21
  - SCL -> GPIO 22

## 📂 目录结构
使用以下代码块格式，可以让你的目录结构在 GitHub 上清晰呈现：

```text
.
├── include/                # 头文件目录
│   ├── Animations.h        # 动画基类与缓动算法
│   ├── AsyncTimer.h        # 异步定时器
│   ├── EyeConfig.h         # 眼睛参数结构体
│   ├── EyeDrawer.h         # 几何绘图引擎 (SSD1306 优化版)
│   ├── Face.h              # 脸部核心协调类
│   └── FaceEmotions.h      # 表情枚举定义 (含新增的 Confused)
├── src/                    # 源文件目录
│   ├── main.cpp            # 程序入口 (Web Server & 逻辑调度)
│   ├── Eye.cpp             # 眼睛对象实现
│   ├── FaceExpression.cpp  # 表情切换逻辑实现
│   └── EyePresets.cpp      # 表情静态参数字典
├── platformio.ini          # 项目配置文件 (依赖管理 & 波特率)
└── readme.md               # 项目文档