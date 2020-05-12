#ifndef __PERKMENU_H__
#define __PERKMENU_H__

#include "Menu.h"
static int perkscreen;
Menu *perk_menu_new();
void perk_menu_think();
void perk_menu_option_select();
void perk_menu_option_1();
void perk_menu_option_2();
void perk1(int perkscreen);
void perk2(int perkscreen);
#endif