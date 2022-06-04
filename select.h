#ifndef __SELECT_H__
#define __SELECT_H__

#include <stdio.h>

#include "g.h"
#include "screen.h"

// key defines
#define KEY_ARROW_UP 72
#define KEY_ARROW_DOWN 80
#define KEY_ARROW_LEFT 75
#define KEY_ARROW_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESC 27

// menu values
#define MENU_ARRAY_X_SIZE 2
#define MENU_ARRAY_Y_SIZE 3

int get_input();
int select_play_order(int mode, void *op_info);
int select_settings(void);
int select_info(void);
int select_menu(void);
int select_input_ip(void);

#endif // __SELECT_H__