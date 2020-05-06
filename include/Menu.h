#include "gf2d_sprite.h"
#include "Entity.h"
#include "gf2d_graphics.h"
#include "gf2d_draw.h"

#ifndef __MENU_H__
#define __MENU_H__

typedef struct menu_S
{
	Uint8	_inuse;
	Uint8	cursorPoint;
	Uint8	cursorPointTotal;
	Uint8	select;

	Sprite	*backsprite;
	Sprite *cursorSprite;

	Vector2D backPosition;
	Vector2D cursorPostion;

	Vector2D cursorPoint_1;
	Vector2D cursorPoint_2;
	Vector2D cursorPoint_3;

	
	void(*think)(struct  menu_S *self);
	

}Menu;

static Menu *THE_MENU;
static int genUpdates;

Menu *menu_new();
Menu *menu_get_active();
void menu_free(Menu *self);
void menu_draw(Menu *self);
void cursor_handler();
void cursor_set_position(Menu *self);
void cursor_option_select(Menu *self);
void menu_update(Menu *self);
void menu_set_active(Menu *activeMenu);
int get_genUpdates();
void SceneController(int sceneNo, Menu *menu);

#endif