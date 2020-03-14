#ifndef __GRUNT_H__
#define __GRUNT_H__

#include "Entity.h"

Entity *grunt_new(Vector2D position);

void grunt_think(Entity *self);

void grunt_move(Entity *self);

void grunt_attack(Entity *self);

void grunt_collide(Entity*self, Entity *other);

#endif