#include "screen.h"

// 커서 숨기기
// 사용 예시: setCursor(0);
static void setCursor(int input)
{
    CONSOLE_CURSOR_INFO cinfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cinfo);
    cinfo.bVisible = (BOOL)input;

    log(LOG_INFO, "disabling cursor"); 
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cinfo);
}

// ashz: clear screen 
static void clear()
{
    log(LOG_INFO, "clearing screen");
    system("cls");
}

// ashz: set screen max buffer size (to remove scroll bar)
static void setBorder(int INX, int INY)
{
    SMALL_RECT ConsoleRectangle;

	if(INX==0 || INY==0){
		return;
	}
	ConsoleRectangle = (SMALL_RECT) {0,0,INX-1,INY-1};

    log(LOG_WARNING, "initiating border");
	
	// Pre-designate buffers and/or cordinates into the system for output
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){(short)INX, (short)INY});
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &ConsoleRectangle);
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){(short)INX, (short)INY});
}

// ashz: edge box
void eBOX(int posX, int posY, int length, int height, int color, char outline)
{
    int i = 0;

    setColor(color);

    gotoXY(posX, posY);
    for(i=0; i<length; i++) {
        printf("%c", outline);
    }

    for(i=1; i<(height-1); i++) {
        gotoXY(posX, posY+i);
        printf("%c%c", outline, outline);
        gotoXY((posX+length)-2, posY+i);
        printf("%c%c", outline, outline);
    }

    gotoXY(posX, posY+(height-1));
    for(i=0; i<length; i++) {
        printf("%c", outline);
    }
}

// ashz: fill box
void fBOX(int posX, int posY, int length, int height, int color, char outline)
{
    char *buf = NULL;
    int i = 0;

    // create printable string
    buf = (char*)malloc((size_t)(length+1));
    for(i=0; i<length; i++) {
        buf[i]=outline; 
    }
    buf[i]='\0';

    // set color
    setColor(color);

    // print using gotoXY
    for(i=0; i<height; i++) {
        gotoXY(posX, posY+i);
        printf("%s", buf);
    }

    // free allocated memory
    free(buf);
}

void screen_menu()
{
    // init
    setCursor(0);
    setBorder(220, 50);
    clear();

    // show
    fBOX(0, 0, 220, 50, BF_GRAY_WHITE, ' ');
    fBOX(20, 28, 80, 5, BF_GREEN_BLACK, ' ');
    fBOX(120, 28, 80, 5, BF_LGRAY_BLACK, ' ');
    fBOX(20, 35, 80, 5, BF_LGRAY_BLACK, ' ');
    fBOX(120, 35, 80, 5, BF_LGRAY_BLACK, ' ');
    fBOX(70, 42, 80, 5, BF_LGRAY_BLACK, ' ');
    printc(57, 30, BF_GREEN_BLACK, "1 vs 1");
    printc(156, 30, BF_LGRAY_BLACK, "1 vs CPU");
    printc(56, 37, BF_LGRAY_BLACK, "Settings");
    printc(155, 37, BF_LGRAY_BLACK, "Information");
    printc(108, 44, BF_LGRAY_BLACK, "Quit");
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
    eBOX(0,0,150,40,119,' ');    //(150,40)
    eBOX(3,3,76,34,128,' ');    //(76,34)
    chessBoard(5,4,72,32,240," ");      //(5,4,72,32,240," ")
    scanf("%d",1);
    gotoXY(0,0);
}