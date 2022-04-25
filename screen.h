#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <windows.h>
#include <stdio.h>

// background color only
#define BGO_COLOR_GRAY 119

// 색갈 지정 (0~255, window color)
// 사용 예시: setColor(48);
static void setColor(int color) 
{
	SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), color);
}
// 출력 위치 변경 (x는 좌우, y는 상하) 
// 사용 예시: gotoXY(5,2);
static void gotoXY(int X, int Y)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){(short)X,(short)Y});
}

// 커서 숨기기
// 사용 예시: setCursor(0);
static void setCursor(int input)
{
    CONSOLE_CURSOR_INFO cinfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cinfo);
    cinfo.bVisible = (BOOL)input;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cinfo);
}

// ashz: clear screen 
static void clear()
{
    system("cls");
}

// ashz: set screen max buffer size (to remove scroll bar)
static void init_border(int INX, int INY)
{
    SMALL_RECT ConsoleRectangle;

	if(INX==0 || INY==0){
		return;
	}
	ConsoleRectangle = (SMALL_RECT) {0,0,INX-1,INY-1};
	
	//Pre-Designate Buffers or Cordinates into the system
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){(short)INX, (short)INY});
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &ConsoleRectangle);
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){(short)INX, (short)INY});
}

// ashz: edge box
static void eBOX(int posX, int posY, int length, int height, int color, const char* outline)
{
    int i = 0;

    setColor(color);

    gotoXY(posX, posY);
    for(i=0; i<length*2; i++) {
        printf(outline);
    }

    for(i=1; i<(height-1); i++) {
        gotoXY(posX, posY+i);
        printf("%s%s", outline, outline);
        gotoXY((posX+(length*2))-2, posY+i);
        printf("%s%s", outline, outline);
    }

    gotoXY(posX, posY+(height-1));
    for(i=0; i<length*2; i++) {
        printf(outline);
    }
}

void screen_menu();
void screen_board();
void screen_select_order();
void screen_info();
void screen_find_opponet();
void screen_settings();

#endif // __SCREEN_H__