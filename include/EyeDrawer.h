#ifndef _EYEDRAWER_h
#define _EYEDRAWER_h

#include <Arduino.h>
#include <U8g2lib.h>
#include "EyeConfig.h"

// 必须声明一个全局的 u8g2 对象供绘图引擎使用（具体实现在 main.cpp 里）
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;

enum CornerType {T_R, T_L, B_L, B_R};

class EyeDrawer {
  public:
    static void Draw(int16_t centerX, int16_t centerY, EyeConfig *config);
    static void FillEllipseCorner(CornerType corner, int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color);
    static void FillRectangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t color);
    static void FillRectangularTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t color);
    static void FillTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t color);
};
#endif