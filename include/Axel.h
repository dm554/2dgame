#ifndef __AXEL_H__
#define __AXEL_H__

#include "Entity.h"

Entity *axel_new(Entity *target);

void axel_think(Entity *self);

void axel_move(Entity *self);

void axel_attack(Entity *self);

void axel_collide(Entity*self, Entity *other);

#endif