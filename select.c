#include "select.h"

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