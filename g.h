#ifndef __G_H__ // global variables
#define __G_H__


enum {
    MENU_EXIT = 0,
    MENU_INFO,
    MENU_SETTINGS,
    MENU_PLAY_SINGLE,
    MENU_PLAY_ONLINE,
    MENU_MAX
};

enum {
    GAMEMODE_CPU = 0,
    GAMEMODE_PLAYER,
    GAMEMODE_MAX
};

const char* get_menu_selection_string(int menu_selection)
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

#endif // __G_H__