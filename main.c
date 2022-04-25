#include <stdio.h>
#include <stdbool.h> 
#include <windows.h>

#include "g.h"
#include "log.h"
#include "screen.h"

int select_menu() {
    int sel;
    scanf("%d", &sel);

    switch(sel) {
        case 1: return MENU_PLAY_ONLINE;
        case 2: return MENU_PLAY_SINGLE;
        case 3: return MENU_SETTINGS;
        case 4: return MENU_INFO;
        default: return MENU_EXIT;
    }
}
void* network_find_opponet() {
    printf("find net opponet!\n");   
    return NULL;
}
int select_play_order(int mode, void *op_info) {
    printf("select play order!\n");   
    return 0;
}
int select_settings() {
    printf("configure settings!\n");   
    return 0;
}
int select_info() {
    printf("credit/info exit option!\n");   
    return 0;
}

static int menu() {
    screen_menu();
    return select_menu();
}

int main(int argc, char **argv)
{
    int loop = 0;
    void *opponet_info;

    init_log();
    log(LOG_NOTICE, "starting program"); 

    log(LOG_WARNING, "disable cursor"); 
    setCursor(0);
    log(LOG_NOTICE, "disabled cursor"); 

    log(LOG_WARNING, "initiate border"); 
    //init_border(120, 30);
    init_border(150, 40);
    log(LOG_NOTICE, "initiated border"); 

    log(LOG_NOTICE, "starting main switch loop, opening menu"); 
    while(true) {
        switch( (loop?loop:(loop=menu())) ) {
            case MENU_PLAY_ONLINE: {
                log(LOG_NOTICE, "selected %s", get_menu_selection_string(loop)); 
                loop = 0;

                break; // TODO
                screen_find_opponet();
                opponet_info = network_find_opponet();
                if(opponet_info != NULL) {
                    screen_board();
                    screen_select_order();
                    loop = select_play_order(GAMEMODE_PLAYER, &opponet_info);
                } else {
                    loop = 0;
                }
                break;
            }
            case MENU_PLAY_SINGLE: {
                log(LOG_NOTICE, "selected %s", get_menu_selection_string(loop)); 
                screen_board();
                screen_select_order();
                loop = select_play_order(GAMEMODE_CPU, NULL);
                break;
            }
            case MENU_SETTINGS: {
                log(LOG_NOTICE, "selected %s", get_menu_selection_string(loop)); 
                screen_settings();
                loop = select_settings(); // should always return 0
                break;
            }
            case MENU_INFO: {
                log(LOG_NOTICE, "selected %s", get_menu_selection_string(loop)); 
                screen_info();
                loop = select_info(); // should always return 0
                break;
            }
            default: { //MENU_EXIT
                log(LOG_NOTICE, "selected %s", get_menu_selection_string(loop)); 
                return 0;
            }
        }
    }
}