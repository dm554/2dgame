#ifndef __BOSS3_H__
#define __BOSS3_H__

#include "Entity.h"

Entity *boss3_new(Entity *target);

void boss3_think(Entity *self);

void boss3_move(Entity *self);

void boss3_attack(Entity *self);

void boss3_collide(Entity*self, Entity *other);

#endif