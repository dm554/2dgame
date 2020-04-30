#ifndef __UI_H__
#define __UI_H__

#include "gf2d_sprite.h"

typedef struct UI_S
{
	Uint8	_inuse;
	Uint8	type;	//1 = MainMenu, 2 = PauseScreen, 3 = PerkScreen	

	Sprite	*sprite;
	
	Vector2D position;

	void(*think)(struct UI_S *self);


}UI;

UI *element_new();

void UI_manager_init(Uint32 maxElements);
void element_free(UI *self);

void UI_update_all();
void UI_draw_all();

#endif