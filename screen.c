#include "screen.h"

void screen_menu() {
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

void screen_board() {
    clear();
    eBOX(0,0,75,40,119," ");    //(150,40)
    eBOX(3,3,38,34,128," ");    //(76,34)
    chessBoard(5,4,72,32,240," ");      //(5,4,72,32,240," ")
    scanf("%d",1);
    gotoXY(0,0);
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