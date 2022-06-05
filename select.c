#include "select.h"

int get_input()
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
    int color = BF_LWHITE_BLACK;
    switch(prev) {
        case 1: {
            fBOX(20, 28, 80, 5, color, ' ');
            printc(57, 30, color, "1 vs 1");
            break;
        }
        case 2: {
            fBOX(120, 28, 80, 5, color, ' ');
            printc(156, 30, color, "1 vs CPU");
            break;
        }
        case 3: {
            fBOX(20, 35, 80, 5, color, ' ');
            printc(56, 37, color, "Settings");
            break;
        }
        case 4: {
            fBOX(120, 35, 80, 5, color, ' ');
            printc(155, 37, color, "Information");
            break;
        }
        case 5: {
            fBOX(70, 42, 80, 5, color, ' ');
            printc(108, 44, color, "Quit");
            break;
        }
        default: {
            return;
        }
    }

    color = BF_LCYAN_BLACK;
    switch(cur) {
        case 1: {
            fBOX(20, 28, 80, 5, color, ' ');
            printc(57, 30, color, "1 vs 1");
            break;
        }
        case 2: {
            fBOX(120, 28, 80, 5, color, ' ');
            printc(156, 30, color, "1 vs CPU");
            break;
        }
        case 3: {
            fBOX(20, 35, 80, 5, color, ' ');
            printc(56, 37, color, "Settings");
            break;
        }
        case 4: {
            fBOX(120, 35, 80, 5, color, ' ');
            printc(155, 37, color, "Information");
            break;
        }
        case 5: {
            fBOX(70, 42, 80, 5, color, ' ');
            printc(108, 44, color, "Quit");
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
Position Numbering
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
    char ip[32] = {0};
    int port = 0;

    // TODO: need a keyboard reader instead of scanf
    gotoXY(77, 24); scanf("%s", ip);
    gotoXY(77, 27); scanf("%d", &port);

    
}

static void select_network_mode_move(int prev, int cur)
{
    int color = BF_LWHITE_BLACK;
    switch(prev) {
        case 1: {
            eBOX(50, 11, 59, 26, color, ' ');
            break;
        }
        case 2: {
            eBOX(113, 11, 59, 26, color, ' ');
            break;
        }
        default: {
            return;
        }
    }

    color = BF_LCYAN_BLACK;
    switch(cur) {
        case 1: {
            eBOX(50, 11, 59, 26, color, ' ');
            break;
        }
        case 2: {
            eBOX(113, 11, 59, 26, color, ' ');
            break;
        }
        default: {
            return;
        }
    }
}

/*
Position Numbering
1 2
*/
int select_network_mode()
{
    char array[1][2] = {{1,2}};
    int previous = -1;
    int current = 0;
    int flag_selected = 0;
    int x = 0;
    int y = 0;

    while(1) {
        switch(get_input()) {
            case KEY_ARROW_LEFT: { // X--
                previous = array[y][x];

                if((x-1) < 0) {
                    x = NMODE_ARRAY_X_SIZE - 1; 
                } else {
                    x--;
                }

                current = array[y][x];
                select_network_mode_move(previous, current);
                break;
            }
            case KEY_ARROW_RIGHT: { // X++
                previous = array[y][x];

                if((x+1) >= NMODE_ARRAY_X_SIZE) {
                    x = 0; 
                } else {
                    x++;
                }

                current = array[y][x];
                select_network_mode_move(previous, current);
                break;
            }
            case KEY_ESC:
                current = NMODE_EXIT;
            case KEY_ENTER: {
                flag_selected = 1;
                break;
            }
        } 

        if(flag_selected) break;
    }

    switch(current) {
        case 1: return NMODE_SERVER;
        case 2: return NMODE_CLIENT;
        default: return NMODE_EXIT;
    }
}