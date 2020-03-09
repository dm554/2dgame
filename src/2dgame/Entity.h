#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "gf2d_sprite.h"

typedef struct Entity_S
{
	Uint8	_inuse;
	Uint8	type;	//1 = Player, 2 = Enemy, 3 = Neutral Object
	Sprite	*sprite;
	float frame;
	float minFrame;
	float maxFrame;

	
	
	Vector2D *scale;
	Vector2D position;
	Vector2D velocity;

	float attacking;
	
	SDL_Rect bodyHitbox;

	void(*think)(struct Entity_S *self);
	void(*collide)(struct Entity_S *self);

}Entity;

Entity *entity_new();

void entity_manager_init(Uint32 maxEnts);
void entity_free(Entity *self);

void entity_update_all();
void entity_draw_all();
void entity_collide_check(Entity *self);
void entity_collide(Entity *e1, Entity *e2);

#endif