#ifndef __GRUNT3_H__
#define __GRUNT3_H__

#include "Entity.h"

Entity *grunt3_new(Entity *target);

void grunt3_think(Entity *self);

void grunt3_move(Entity *self);

void grunt3_attack(Entity *self);

void grunt3_collide(Entity*self, Entity *other);

#endif