#ifndef __PIC_H__
#define __PIC_H__
#define __PIC_H_ver__ 2
#include<windows.h>
#include<cstdio>
/*
函数的使用格式：
在程序同一目录下使用画图创建图片文件*.bmp
x,y和gotoxy的使用格式是一样的，是图片左上角的坐标。
注意：必须是bmp文件！！！
图片的横竖长度也要注意，不要过大，不然屏幕有可能塞不下。
*/
//绘制图片函数
void display_pic(const char* filename,int x,int y){
    HWND hwnd = GetConsoleWindow();
    HDC hdc = GetDC(hwnd);
    HBITMAP hbitmap =(HBITMAP)LoadImageA(
        NULL,
        filename,
        IMAGE_BITMAP,
        0,0,
        LR_LOADFROMFILE
    );
    BITMAP bitmap;
    GetObject(hbitmap,sizeof(BITMAP),&bitmap);
    int width=bitmap.bmWidth;
    int height=bitmap.bmHeight;
    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, hbitmap);
    BOOL result = BitBlt(
        hdc,           
        x, y,          
        width, height, 
        memDC,         
        0, 0,          
        SRCCOPY        
    );
    SelectObject(memDC, oldBitmap);
    DeleteDC(memDC);
    DeleteObject(hbitmap);
    ReleaseDC(hwnd, hdc);
}
/*
#include<windows.h>
#include<cstdio>

// 绘制图片函数（添加错误检查）
int display_pic(const char* filename, int x, int y) {
    // 1. 获取控制台窗口
    HWND hwnd = GetConsoleWindow();
    if (hwnd == NULL) {
        printf("display_pic: 无法获取控制台窗口\n");
        return 0;
    }
    
    HDC hdc = GetDC(hwnd);
    if (hdc == NULL) {
        printf("display_pic: 无法获取DC\n");
        return 0;
    }
    
    // 2. 加载图片
    HBITMAP hbitmap = (HBITMAP)LoadImageA(
        NULL,
        filename,
        IMAGE_BITMAP,
        0, 0,
        LR_LOADFROMFILE
    );
    
    if (hbitmap == NULL) {
        printf("display_pic: 无法加载图片 %s (错误码: %d)\n", filename, GetLastError());
        ReleaseDC(hwnd, hdc);
        return 0;
    }
    
    // 3. 获取图片尺寸
    BITMAP bitmap;
    if (GetObject(hbitmap, sizeof(BITMAP), &bitmap) == 0) {
        printf("display_pic: 无法获取图片信息\n");
        DeleteObject(hbitmap);
        ReleaseDC(hwnd, hdc);
        return 0;
    }
    
    int width = bitmap.bmWidth;
    int height = bitmap.bmHeight;
    
    // 4. 创建兼容DC并绘制
    HDC memDC = CreateCompatibleDC(hdc);
    if (memDC == NULL) {
        printf("display_pic: 无法创建兼容DC\n");
        DeleteObject(hbitmap);
        ReleaseDC(hwnd, hdc);
        return 0;
    }
    
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, hbitmap);
    
    BOOL result = BitBlt(
        hdc, x, y,
        width, height,
        memDC, 0, 0,
        SRCCOPY
    );
    
    if (!result) {
        printf("display_pic: BitBlt失败 (错误码: %d)\n", GetLastError());
    }
    
    // 5. 清理资源
    SelectObject(memDC, oldBitmap);
    DeleteDC(memDC);
    DeleteObject(hbitmap);
    ReleaseDC(hwnd, hdc);
    
    return result ? 1 : 0;
}
*/

#endif// __PIC_H__