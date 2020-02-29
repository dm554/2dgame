#ifndef __LEVEL_H__
#define __LEVEL_H__
	
#include "gf2d_sprite.h"

typedef struct
{
	Sprite *background;
	SDL_Rect bounds;
}Level;

Level *level_new();
void level_free(Level *level);
void level_draw(Level *level);
Level *level_get_active();

#endif