#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"

Entity *player_new(Vector2D position);

void player_think(Entity *self);

void player_move(Entity *self);

void player_attack(Entity *self);

void player_collide(Entity*self, Entity *other);

#endif