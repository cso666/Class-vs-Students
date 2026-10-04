#ifndef __SHAPE_H__
#define __SHAPE_H__
#define __SHAPE_H_ver__ 1
#include<windows.h>
#include<cmath>
#include<vector>
struct point{
    int x,y;
};
//color的格式：0xRRGGBB

enum LineStyle {
    SOLID = PS_SOLID,      // 实线
    DASH = PS_DASH,        // 虚线
    DOT = PS_DOT,          // 点线
    DASHDOT = PS_DASHDOT,  // 点划线
    DASHDOTDOT = PS_DASHDOTDOT // 双点划线
};
//画线
//参数：
// p1:第一个点
// p2:第二个点
// color:颜色
// thickness:粗细
// style：线的种类
void draw_line(point p1, point p2, int color, int thickness = 2, int style = SOLID) {
    HWND hwnd = GetConsoleWindow();
    if (hwnd == NULL) return;
    
    HDC hdc = GetDC(hwnd);
    if (hdc == NULL) return;
    
    int r = (color >> 16) & 0xFF;
    int g = (color >> 8) & 0xFF;
    int b = color & 0xFF;
    
    HPEN pen = CreatePen(style, thickness, RGB(r, g, b));
    HPEN oldPen = (HPEN)SelectObject(hdc, pen);
    
    MoveToEx(hdc, p1.x, p1.y, NULL);
    LineTo(hdc, p2.x, p2.y);
    
    SelectObject(hdc, oldPen);
    DeleteObject(pen);
    ReleaseDC(hwnd, hdc);
}
// 绘制多边形
// 参数：
//   vertices  - 顶点列表
//   color     - 颜色（边框颜色 = 填充颜色）
//   thickness - 边框粗细（默认 2）
//   filled    - 是否填充（默认 false，仅边框）
void draw_polygon(const std::vector<point>& vertices, int color, int thickness = 2, bool filled = false) {
    if (vertices.size() < 3) return;
    
    HWND hwnd = GetConsoleWindow();
    HDC hdc = GetDC(hwnd);
    
    std::vector<POINT> pts;
    for (const auto& p : vertices) {
        pts.push_back({p.x, p.y});
    }
    
    int r = (color >> 16) & 0xFF;
    int g = (color >> 8) & 0xFF;
    int b = color & 0xFF;
    
    // 创建画刷（用于填充）
    HBRUSH brush;
    if (filled) {
        brush = CreateSolidBrush(RGB(r, g, b));
    } else {
        brush = (HBRUSH)GetStockObject(NULL_BRUSH);  // 透明画刷
    }
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
    
    // 创建画笔（用于边框）
    HPEN pen = CreatePen(PS_SOLID, thickness, RGB(r, g, b));
    HPEN oldPen = (HPEN)SelectObject(hdc, pen);
    
    // 绘制多边形
    Polygon(hdc, pts.data(), (int)pts.size());
    
    // 清理
    SelectObject(hdc, oldPen);
    DeleteObject(pen);
    SelectObject(hdc, oldBrush);
    if (filled) {
        DeleteObject(brush);
    }
    ReleaseDC(hwnd, hdc);
}
// 画圆
// 参数：
//   cx, cy    - 圆心坐标
//   radius    - 半径
//   color     - 颜色（边框颜色 = 填充颜色）
//   thickness - 边框粗细（默认 2）
//   filled    - 是否填充（默认 false，仅边框）
void draw_circle(int cx, int cy, int radius, int color, int thickness = 2, bool filled = false) {
    if (radius <= 0) return;
    
    HWND hwnd = GetConsoleWindow();
    HDC hdc = GetDC(hwnd);
    
    int r = (color >> 16) & 0xFF;
    int g = (color >> 8) & 0xFF;
    int b = color & 0xFF;
    
    // 创建画刷（用于填充）
    HBRUSH brush;
    if (filled) {
        brush = CreateSolidBrush(RGB(r, g, b));
    } else {
        brush = (HBRUSH)GetStockObject(NULL_BRUSH);  // 透明画刷
    }
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
    
    // 创建画笔（用于边框）
    HPEN pen = CreatePen(PS_SOLID, thickness, RGB(r, g, b));
    HPEN oldPen = (HPEN)SelectObject(hdc, pen);
    
    // 绘制椭圆（圆是椭圆的一种）
    Ellipse(hdc, cx - radius, cy - radius, cx + radius, cy + radius);
    
    // 清理
    SelectObject(hdc, oldPen);
    DeleteObject(pen);
    SelectObject(hdc, oldBrush);
    if (filled) {
        DeleteObject(brush);
    }
    ReleaseDC(hwnd, hdc);
}
#endif