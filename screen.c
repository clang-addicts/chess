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
    // program init
    setCursor(0);
    setBorder(220, 50);
    clear();

    // print background
    fBOX(0, 0, 220, 50, BF_GRAY_WHITE, ' ');

    // print options box
    fBOX(18, 27, 80, 5, BF_LYELLOW_BLACK, ' ');
    fBOX(20, 28, 80, 5, BF_LCYAN_BLACK, ' ');
    fBOX(118, 27, 80, 5, BF_LYELLOW_BLACK, ' ');
    fBOX(120, 28, 80, 5, BF_LWHITE_BLACK, ' ');
    fBOX(18, 34, 80, 5, BF_LYELLOW_BLACK, ' ');
    fBOX(20, 35, 80, 5, BF_LWHITE_BLACK, ' ');
    fBOX(118, 34, 80, 5, BF_LYELLOW_BLACK, ' ');
    fBOX(120, 35, 80, 5, BF_LWHITE_BLACK, ' ');
    fBOX(68, 41, 80, 5, BF_LYELLOW_BLACK, ' ');
    fBOX(70, 42, 80, 5, BF_LWHITE_BLACK, ' ');

    // print option description
    printc(57, 30, BF_LCYAN_BLACK, "1 vs 1");
    printc(156, 30, BF_LWHITE_BLACK, "1 vs CPU");
    printc(56, 37, BF_LWHITE_BLACK, "Settings");
    printc(155, 37, BF_LWHITE_BLACK, "Information");
    printc(108, 44, BF_LWHITE_BLACK, "Quit");
}

void screen_select_order() {
    printf("printing play order!\n");   
}

void screen_info() {
    printf("printing info/credit screen\n");   
}

void screen_server_or_client()
{
    // option box
    fBOX(70, 16, 80, 20, BF_LYELLOW_BLACK, ' ');
    fBOX(72, 17, 80, 20, BF_LWHITE_BLACK, ' ');
    printc(76, 19, BF_LWHITE_BLACK, "Select Endpoint Mode");

    // input boxes
    printc(76, 23, BF_LWHITE_BLACK, "IP");
    fBOX(76, 24, 50, 1, BF_BLACK_WHITE, ' ');
    printc(76, 26, BF_LWHITE_BLACK, "Port");
    fBOX(76, 27, 50, 1, BF_BLACK_WHITE, ' ');
}

void screen_find_opponet()
{
    // option box
    fBOX(70, 16, 80, 20, BF_LYELLOW_BLACK, ' ');
    fBOX(72, 17, 80, 20, BF_LWHITE_BLACK, ' ');
    printc(76, 19, BF_LWHITE_BLACK, "Input your opponet IP:PORT information");

    // input boxes
    printc(76, 23, BF_LWHITE_BLACK, "IP");
    fBOX(76, 24, 50, 1, BF_BLACK_WHITE, ' ');
    printc(76, 26, BF_LWHITE_BLACK, "Port");
    fBOX(76, 27, 50, 1, BF_BLACK_WHITE, ' ');
}

void screen_settings() {
    printf("printing settings screen!\n");   
}

// Chess Board
static void chessBoard(int x,int y,int color1, int color2){
    setColor(color1);
    int i,j;
    for(j=0;j<4;j++){
        for(i=0;i<4;i++){
            fBOX(x+i*24, y+j*12, 12, 6, color1,' ');   
        }
        for(i=0;i<4;i++){
            fBOX(x+12+i*24, y+6+j*12 , 12, 6, color1,' ');   
        }
    }
    setColor(color2);
    for(j=0;j<4;j++){
        for(i=0;i<4;i++){
            fBOX(x+12+i*24, y+j*12, 12, 6, color2,' ');   
        }
        for(i=0;i<4;i++){
            fBOX(x+i*24, y+6+j*12 , 12, 6, color2,' ');   
        }
    }
}



void screen_board(){
    clear();
    eBOX(0,0,100,50,BF_LGRAY_BLACK,' ');    //(220,50)
    eBOX(98,0,122,50,BF_LGRAY_BLACK,' ');    //(76,34)
    chessBoard(2,1,BF_LWHITE_BLACK,BF_BLACK_WHITE);
}

void screen_network_mode()
{
    // secondary menu
    fBOX(44, 8, 130, 30, BF_LYELLOW_BLACK, ' ');
    fBOX(46, 9, 130, 30, BF_LGRAY_BLACK, ' ');

    // options
    fBOX(50, 11, 59, 26, BF_LWHITE_BLACK, ' ');
    fBOX(113, 11, 59, 26, BF_LWHITE_BLACK, ' ');
    printc(76, 24, BF_LWHITE_BLACK, "Server");
    printc(140, 24, BF_LWHITE_BLACK, "Client");

    // current option selection
    eBOX(50, 11, 59, 26, BF_LCYAN_BLACK, ' ');
}

void screen_waiting_on_opponet()
{
    // secondary menu
    fBOX(44, 8, 130, 30, BF_LYELLOW_BLACK, ' ');
    fBOX(46, 9, 130, 30, BF_LGRAY_BLACK, ' ');
    printc(80, 24, BF_LGRAY_BLACK, "Waiting on opponet...");

    // tmp
    int a;
    scanf("%s", &a);
}