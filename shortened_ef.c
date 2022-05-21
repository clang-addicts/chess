//C
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <process.h>
//C++
#include <iostream>

// 출력 위치 변경 (x는 좌우, y는 상하) 
// 사용 예시: gotoxy(5,2);
void gotoxy(short X, short Y)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){X,Y});
}

// 커서 숨기기
// 사용 예시: cursor(false);
void cursor(BOOL input)
{
    CONSOLE_CURSOR_INFO pos;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pos);
    pos.bVisible = input;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pos);
}

// 색갈 지정 (0~255, window color)
// 사용 예시: SetColor(48);
void SetColor(int color) 
{
	SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), color);
}

// 특정 키가 입력될때까지 대기하는 함수
// 사용 예시: pause(ENTER);
enum KEY{
	ENTER,
	ESC,
	SPACE,
	BACK
};
void pause( _KEY){
	short WAIT_KEY;
	switch(_KEY){
		case ENTER: WAIT_KEY = 13; break;
		case ESC: WAIT_KEY = 27; break;
		case SPACE: WAIT_KEY = 32; break;
		case BACK: WAIT_KEY = 8; break;
	}
	while(1){
		if(kbhit()){
			int in = getch();
			if(in == WAIT_KEY){
				break;
			}
		}
	}
}