#ifndef __G_H__ // global variables
#define __G_H__

// PINFO->mode_menu
enum {
    MENU_UNSELECTED = 0,
    MENU_EXIT,
    MENU_INFO,
    MENU_SETTINGS,
    MENU_PLAY_SINGLE,
    MENU_PLAY_ONLINE,
    MENU_MAX
};

// PINFO->mode_network
enum {
    NMODE_UNSELECTED = 0,
    NMODE_SERVER,
    NMODE_CLIENT,
    NMODE_MAX
};

// PINFO->mode_gamemode
enum {
    GAMEMODE_UNSELECTED = 0,
    GAMEMODE_CPU,
    GAMEMODE_PLAYER,
    GAMEMODE_MAX
};

// program info structure
typedef struct {
    int mode_menu;
    int mode_network;
    int mode_gamemode;
    int socket_server;
    int socket_client;
} PINFO;

#endif // __G_H__