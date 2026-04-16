
目录结构

ESP32_OLED_Eyes/
├── .pio/                    # 自动生成：存放编译后的临时文件和库（不要动）
├── .vscode/                 # 自动生成：VS Code 的项目配置文件（不要动）
├── include/                 # 头文件目录：存放所有的 .h 文件
│   ├── Animations.h         # 动画基类与各种缓动算法定义
│   ├── AsyncTimer.h         # 异步定时器类定义
│   ├── EyeConfig.h          # 眼睛参数结构体
│   ├── EyeDrawer.h          # 几何绘图逻辑
│   ├── EyeComponents.h      # 包含 Transition, Transformation, Variation 等类
│   ├── FaceEmotions.h       # 表情枚举定义
│   ├── EyePresets.h         # 各个表情的静态参数配置
│   └── Face.h               # 脸部核心类声明（聚合所有组件）
├── lib/                     # 私有库目录：如果你自己写了通用的库，可以放这里
├── src/                     # 源文件目录：存放所有的 .cpp 文件
│   ├── Animations.cpp       
│   ├── AsyncTimer.cpp
│   ├── EyeDrawer.cpp
│   ├── EyeComponents.cpp
│   ├── Face.cpp             # 脸部逻辑实现
│   └── main.cpp             # 程序入口：只保留 setup() 和 loop()
├── test/                    # 测试目录：存放单元测试代码
├── data/                    # (可选) 存放 SPIFFS/LittleFS 闪存文件（如网页素材）
└── platformio.ini           # 核心配置文件：定义开发板、频率、依赖库和串口设置