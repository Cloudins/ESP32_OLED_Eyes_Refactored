#include "EyeDrawer.h"

void EyeDrawer::Draw(int16_t centerX, int16_t centerY, EyeConfig *config) {
    int32_t dyt = config->Height * config->Slope_Top / 2.0;
    int32_t dyb = config->Height * config->Slope_Bottom / 2.0;

    int32_t TLc_y = centerY + config->OffsetY - config->Height / 2 + config->Radius_Top - dyt;
    int32_t TLc_x = centerX + config->OffsetX - config->Width / 2 + config->Radius_Top;
    int32_t TRc_y = centerY + config->OffsetY - config->Height / 2 + config->Radius_Top + dyt;
    int32_t TRc_x = centerX + config->OffsetX + config->Width / 2 - config->Radius_Top;

    int32_t BLc_y = centerY + config->OffsetY + config->Height / 2 - config->Radius_Bottom - dyb;
    int32_t BLc_x = centerX + config->OffsetX - config->Width / 2 + config->Radius_Bottom;
    int32_t BRc_y = centerY + config->OffsetY + config->Height / 2 - config->Radius_Bottom + dyb;
    int32_t BRc_x = centerX + config->OffsetX + config->Width / 2 - config->Radius_Bottom;

    // 绘制核心矩形主体
    FillRectangle(TLc_x - config->Radius_Top, TLc_y, TRc_x + config->Radius_Top, BLc_y, 1);
    
    // 绘制上下倾斜的梯形补齐区域
    FillTriangle(TLc_x, TLc_y - config->Radius_Top, TRc_x, TRc_y - config->Radius_Top, TLc_x, TLc_y, 1);
    FillTriangle(TRc_x, TRc_y - config->Radius_Top, TLc_x, TLc_y, TRc_x, TRc_y, 1);
    FillTriangle(BLc_x, BLc_y + config->Radius_Bottom, BRc_x, BRc_y + config->Radius_Bottom, BLc_x, BLc_y, 1);
    FillTriangle(BRc_x, BRc_y + config->Radius_Bottom, BLc_x, BLc_y, BRc_x, BRc_y, 1);

    // 绘制四个圆角（根据配置判断是否需要画圆角）
    if (config->Radius_Top > 0) {
        FillEllipseCorner(T_L, TLc_x, TLc_y, config->Radius_Top, config->Radius_Top, 1);
        FillEllipseCorner(T_R, TRc_x, TRc_y, config->Radius_Top, config->Radius_Top, 1);
    }
    if (config->Radius_Bottom > 0) {
        FillEllipseCorner(B_L, BLc_x, BLc_y, config->Radius_Bottom, config->Radius_Bottom, 1);
        FillEllipseCorner(B_R, BRc_x, BRc_y, config->Radius_Bottom, config->Radius_Bottom, 1);
    }
}

void EyeDrawer::FillRectangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t color) {
    u8g2.setDrawColor(color);
    int32_t w = abs(x1 - x0);
    int32_t h = abs(y1 - y0);
    int32_t x = min(x0, x1);
    int32_t y = min(y0, y1);
    if (w > 0 && h > 0) {
        u8g2.drawBox(x, y, w, h);
    }
}

void EyeDrawer::FillRectangularTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t color) {
    u8g2.setDrawColor(color);
    u8g2.drawTriangle(x0, y0, x1, y1, x0, y1); 
}

void EyeDrawer::FillTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t color) {
    u8g2.setDrawColor(color);
    u8g2.drawTriangle(x0, y0, x1, y1, x2, y2);
}

void EyeDrawer::FillEllipseCorner(CornerType corner, int16_t x0, int16_t y0, int32_t rx, int32_t ry, uint16_t color) {
    u8g2.setDrawColor(color);
    uint8_t opt = 0;
    // 使用 U8g2 的四分之一圆盘绘制功能，完美适配各个角
    if (corner == T_R) opt = U8G2_DRAW_UPPER_RIGHT;
    else if (corner == T_L) opt = U8G2_DRAW_UPPER_LEFT;
    else if (corner == B_L) opt = U8G2_DRAW_LOWER_LEFT;
    else if (corner == B_R) opt = U8G2_DRAW_LOWER_RIGHT;
    
    u8g2.drawDisc(x0, y0, rx, opt);
}