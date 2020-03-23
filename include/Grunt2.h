#ifndef __GRUNT2_H__
#define __GRUNT2_H__

#include "Entity.h"

Entity *grunt2_new(Entity *target);

void grunt2_think(Entity *self);

void grunt2_move(Entity *self);

void grunt2_attack(Entity *self);

void grunt2_collide(Entity*self, Entity *other);

#endif