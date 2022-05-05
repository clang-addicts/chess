#include "screen.h"

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

// ashz: set screen max buffer size (to remove scroll bar)
static void setBorder(int INX, int INY)
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

void screen_menu()
{
    log(LOG_WARNING, "disable cursor"); 
    setCursor(0);
    log(LOG_NOTICE, "disabled cursor"); 

    log(LOG_WARNING, "initiate border");
    setBorder(150, 40);
    log(LOG_NOTICE, "initiated border"); 

    clear();
    eBOX(0,0,75,40,BGO_COLOR_GRAY," ");
    setColor(15);
    gotoXY(3,4);
    printf("select? \n");
    printf("1.  1v1\n");
    printf("2.  1vCPU\n");
    printf("3.  setting\n");
    printf("4.  credit\n");
    printf("5.  exit\n");
    printf("> ");
}

void screen_select_order() {
    printf("printing play order!\n");   
}

void screen_info() {
    printf("printing info/credit screen\n");   
}

void screen_find_opponet() {
    printf("printing find opponet screen!\n");   
}

void screen_settings() {
    printf("printing settings screen!\n");   
}

// Chess Board
static void chessBoard(int posX, int posY, int length, int height, int color, char* side)	// length, height = multiple of 8 only
{
	setColor(color);
	gotoXY(posX,posY);
	int a,b,i,j;	// i = 체스판 x 좌표, j = 체스판 y 좌표 
	 
	for(a=0;a<4;a++)
	{
		for(i=0;i<posX+length*7/8;i++)
		{
			for(j=0;j<height/8;j++)
			{
				if(i%(length/4)==0)     //짝수 줄
				{
					gotoXY(posX+i,posY+j+a*height/4);
					for(b=0;b<length/8;b++)
					{
						printf("%s",side);
					}
                }
                else if(i%(length/4)==length/8)     //홀수 줄
				{		
					gotoXY(posX+i,posY+j+height/8+a*height/4);
					for(b=0;b<length/8;b++)	
					{				
						printf("%s",side);	
					}
				}
			}	
		}
	}
}
void screen_board() {
    clear();
    eBOX(0,0,75,40,119," ");    //(150,40)
    eBOX(3,3,38,34,128," ");    //(76,34)
    chessBoard(5,4,72,32,240," ");      //(5,4,72,32,240," ")
    scanf("%d",1);
    gotoXY(0,0);
}
