#include "screen.h"

void screen_menu() {
    clear();
    eBOX(0,0,60,28,BGO_COLOR_GRAY," ");

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
    setColor(159);
    int i;
    for(i=0;i<=119;i++)
    {
        printf(" ");
        gotoXY(i,29);
        printf(" ");
        gotoXY(i,0);
    }
    gotoXY(0,0);
    for(i=0;i<=29;i++)
    {
        printf("  \n");
        gotoXY(118,i);
        printf("  \n");
        gotoXY(0,i);
    }
    scanf("%d",i);
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