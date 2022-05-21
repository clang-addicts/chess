#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <conio.h>
#include <unistd.h>

#include "log.h"

// background color only
#define BGO_GRAY 119

// background and front
#define BF_GRAY_WHITE 143
#define BF_GREEN_BLACK 160
#define BF_LGRAY_BLACK 112
#define BF_LYELLOW_BLACK 224
#define BF_LCYAN_BLACK 176
#define BF_LWHITE_BLACK 240
#define BF_BLACK_WHITE 15

// 색갈 지정 (0~255, window color)
// 사용 예시: setColor(48);
#define setColor(color)	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), color)

// 출력 위치 변경 (x는 좌우, y는 상하) 
// 사용 예시: gotoXY(5,2);
#define gotoXY(X, Y) SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){(short)X,(short)Y})

#define printc(x,y,c,str,...) do{\
    gotoXY(x,y);\
    setColor(c);\
    printf(str,##__VA_ARGS__);\
}while(0)

void eBOX(int posX, int posY, int length, int height, int color, char outline);
void fBOX(int posX, int posY, int length, int height, int color, char outline);
void screen_menu();
void screen_board();
void screen_select_order();
void screen_info();
void screen_find_opponet();
void screen_settings();

#endif // __SCREEN_H__