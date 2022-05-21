#include "select.h"

static int get_input()
{
    while(1) {
        if(kbhit()) {
            return getch();
        }
        usleep(100); // for slow systems
    }
}

static void select_menu_move(int prev, int cur)
{
    switch(prev) {
        case 1: {
            fBOX(20, 28, 80, 5, BF_LGRAY_BLACK, ' ');
            printc(57, 30, BF_LGRAY_BLACK, "1 vs 1");
            break;
        }
        case 2: {
            fBOX(120, 28, 80, 5, BF_LGRAY_BLACK, ' ');
            printc(156, 30, BF_LGRAY_BLACK, "1 vs CPU");
            break;
        }
        case 3: {
            fBOX(20, 35, 80, 5, BF_LGRAY_BLACK, ' ');
            printc(56, 37, BF_LGRAY_BLACK, "Settings");
            break;
        }
        case 4: {
            fBOX(120, 35, 80, 5, BF_LGRAY_BLACK, ' ');
            printc(155, 37, BF_LGRAY_BLACK, "Information");
            break;
        }
        case 5: {
            fBOX(70, 42, 80, 5, BF_LGRAY_BLACK, ' ');
            printc(108, 44, BF_LGRAY_BLACK, "Quit");
            break;
        }
        default: {
            return;
        }
    }

    switch(cur) {
        case 1: {
            fBOX(20, 28, 80, 5, BF_LCYAN_BLACK, ' ');
            printc(57, 30, BF_LCYAN_BLACK, "1 vs 1");
            break;
        }
        case 2: {
            fBOX(120, 28, 80, 5, BF_LCYAN_BLACK, ' ');
            printc(156, 30, BF_LCYAN_BLACK, "1 vs CPU");
            break;
        }
        case 3: {
            fBOX(20, 35, 80, 5, BF_LCYAN_BLACK, ' ');
            printc(56, 37, BF_LCYAN_BLACK, "Settings");
            break;
        }
        case 4: {
            fBOX(120, 35, 80, 5, BF_LCYAN_BLACK, ' ');
            printc(155, 37, BF_LCYAN_BLACK, "Information");
            break;
        }
        case 5: {
            fBOX(70, 42, 80, 5, BF_LCYAN_BLACK, ' ');
            printc(108, 44, BF_LCYAN_BLACK, "Quit");
            break;
        }
        default: {
            return;
        }
    }
}

int select_play_order(int mode, void *op_info)
{
    printf("select play order!\n");   
    return 0;
}

int select_settings()
{
    printf("configure settings!\n");   
    return 0;
}

int select_info()
{
    printf("credit/info exit option!\n");   
    return 0;
}

/*
1 2
3 4
5 5
*/
int select_menu()
{
    char array[3][2] = {{1,2},{3,4},{5,5}};
    int previous = -1;
    int current = 0;
    int flag_selected = 0;
    int x = 0;
    int y = 0;

    while(1) {
        switch(get_input()) {
            case KEY_ARROW_UP: { // Y--
                previous = array[y][x];

                if((y-1) < 0) {
                    y = MENU_ARRAY_Y_SIZE - 1; 
                } else {
                    y--;
                }

                current = array[y][x];
                select_menu_move(previous, current);
                break;
            }
            case KEY_ARROW_DOWN: { // Y++
                previous = array[y][x];

                if((y+1) >= MENU_ARRAY_Y_SIZE) {
                    y = 0; 
                } else {
                    y++;
                }

                current = array[y][x];
                select_menu_move(previous, current);
                break;
            }
            case KEY_ARROW_LEFT: { // X--
                previous = array[y][x];

                if((x-1) < 0) {
                    x = MENU_ARRAY_X_SIZE - 1; 
                } else {
                    x--;
                }

                current = array[y][x];
                if (y < MENU_ARRAY_Y_SIZE - 1) {
                    select_menu_move(previous, current);
                }
                break;
            }
            case KEY_ARROW_RIGHT: { // X++
                previous = array[y][x];

                if((x+1) >= MENU_ARRAY_X_SIZE) {
                    x = 0; 
                } else {
                    x++;
                }

                current = array[y][x];
                if (y < MENU_ARRAY_Y_SIZE - 1) {
                    select_menu_move(previous, current);
                }
                break;
            }
            case KEY_ESC: 
            case KEY_ENTER: {
                flag_selected = 1;
                break;
            }
        } 

        if(flag_selected) break;
    }

    switch(current) {
        case 0:
        case 1: return MENU_PLAY_ONLINE;
        case 2: return MENU_PLAY_SINGLE;
        case 3: return MENU_SETTINGS;
        case 4: return MENU_INFO;
        default: return MENU_EXIT;
    }
}

int select_input_ip()
{
    get_input();
}