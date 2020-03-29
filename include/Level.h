#ifndef __LEVEL_H__
#define __LEVEL_H__
	
#include "gf2d_sprite.h"
#include "Player.h"
#include "Grunt.h"

typedef struct
{
	Sprite *background;
	SDL_Rect bounds;
	Vector2D position;
	Uint8 maxStages;
	Uint8 winCon;
	Uint8 spawnStage; //1,2,3
	Uint8 levelComplete;
	Uint8 currentStage;
	int screenCount;


}Level;

Level *level_new();
void level_free(Level *level);
void level_move(Level *level, Entity *player);
void level_draw(Level *level);
void level_spawner();
void level_mover(Level *level, Entity *player);
Level *level_get_active();

#endif