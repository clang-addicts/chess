#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <windows.h>
#include <stdio.h>

#include "log.h"

// background color only
#define BGO_COLOR_GRAY 119

// background and front
#define BF_COLOR_GRAY_WHITE 143

void screen_menu();
void screen_board();
void screen_select_order();
void screen_info();
void screen_find_opponet();
void screen_settings();

#endif // __SCREEN_H__