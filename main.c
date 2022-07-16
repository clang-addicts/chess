#include "g.h"
#include "log.h"
#include "network.h"
#include "screen.h"
#include "select.h"
#include "game.h"

#include <stdio.h>
#include <stdbool.h> 
#include <windows.h>

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

static int menu()
{
    int ret;


    return ret;
}

int main(int argc, char **argv)
{
//////////////////////////////////////////////////////////////////////////
// variable init
//////////////////////////////////////////////////////////////////////////
    PINFO *p = NULL;
    void *opponet_info;
    int mode = -1;

//////////////////////////////////////////////////////////////////////////
// initialization
//////////////////////////////////////////////////////////////////////////
    log(LOG_NOTICE, "initializing..."); 
    // init log
    init_log();

    // init program info
    p = (PINFO*)malloc(sizeof(PINFO));
    memset(p, 0, sizeof(PINFO));
    p->mode_menu = MENU_UNSELECTED;
    p->mode_network = NMODE_UNSELECTED;
    p->mode_gamemode = GAMEMODE_UNSELECTED;

//////////////////////////////////////////////////////////////////////////
// program loop
//////////////////////////////////////////////////////////////////////////
    log(LOG_NOTICE, "starting main switch loop, opening menu"); 
    while(true) {
        screen_menu();
        p->mode_menu = select_menu();
        log(LOG_NOTICE, "selected %s", get_menu_selection_string(p->mode_menu));

        switch(p->mode_menu) {
            case MENU_PLAY_ONLINE: {

                screen_network_mode();
                mode = select_network_mode();
                log(LOG_NOTICE, "set program mode to %d", mode); 

                switch(mode) {
                    case NMODE_SERVER: {
                        wait_for_opponet();
                        screen_waiting_on_opponet();
                        break;
                    }
                    case NMODE_CLIENT: {
                        screen_find_opponet();
                        select_input_ip();
                        find_opponet();
                        break;
                    }
                    default: {
                        p->mode_menu = 1;
                        break;
                    }
                }

                if(p->mode_menu) { // return to main menu
                    break;
                }

                opponet_info = network_find_opponet();
                if(opponet_info != NULL) {
                    screen_board();
                    screen_select_order();
                    p->mode_menu = select_play_order(GAMEMODE_PLAYER, &opponet_info);
                } else {
                    p->mode_menu = 0;
                }
                break;
            }
            case MENU_PLAY_SINGLE: {
                log(LOG_NOTICE, "selected %s", get_menu_selection_string(p->mode_menu)); 
                screen_board();
                screen_select_order();
                game();
                p->mode_menu = select_play_order(GAMEMODE_CPU, NULL);
                break;
            }
            case MENU_SETTINGS: {
                log(LOG_NOTICE, "selected %s", get_menu_selection_string(p->mode_menu)); 
                screen_settings();
                p->mode_menu = select_settings(); // should always return 0
                break;
            }
            case MENU_INFO: {
                log(LOG_NOTICE, "selected %s", get_menu_selection_string(p->mode_menu)); 
                screen_info();
                p->mode_menu = select_info(); // should always return 0
                break;
            }
            case MENU_EXIT: { //MENU_EXIT
                log(LOG_NOTICE, "selected %s", get_menu_selection_string(p->mode_menu)); 
                deinit_log();
                return 0;
            }
        }
    }
}