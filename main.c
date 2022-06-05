#include <stdio.h>
#include <stdbool.h> 
#include <windows.h>

#include "g.h"
#include "log.h"
#include "screen.h"
#include "select.h"
#include "network.h"
#include "game.h"

static const char* get_menu_selection_string(int menu_selection)
{
    switch(menu_selection) {
        case MENU_EXIT: return "MENU_EXIT";
        case MENU_INFO: return "MENU_INFO";
        case MENU_SETTINGS: return "MENU_SETTINGS";
        case MENU_PLAY_SINGLE: return "MENU_PLAY_SINGLE";
        case MENU_PLAY_ONLINE: return "MENU_PLAY_ONLINE";
        case MENU_MAX: return "MENU_MAX";
        default: return "MENU_UNKNOWN";
    }
}

static int menu() {
    screen_menu();
    return select_menu();
}

int main(int argc, char **argv)
{
    int loop = 0;
    void *opponet_info;
    int mode = -1;

    init_log();
    log(LOG_NOTICE, "starting program"); 

    log(LOG_NOTICE, "starting main switch loop, opening menu"); 
    while(true) {
        switch( (loop?loop:(loop=menu())) ) {
            case MENU_PLAY_ONLINE: {
                log(LOG_NOTICE, "selected %s", get_menu_selection_string(loop)); 
                loop = 0;

                screen_network_mode();
                mode = select_network_mode();

                switch(mode) {
                    case NMODE_SERVER: {
                        screen_waiting_on_opponet();
                        break;
                    }
                    case NMODE_CLIENT: {
                        screen_find_opponet();
                        select_input_ip();
                        break;
                    }
                    default: {
                        loop = 1;
                        break;
                    }
                }

                if(loop) { // return to main menu
                    break;
                }

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
                game();
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