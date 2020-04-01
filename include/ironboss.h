#ifndef __IRONBOSS_H__
#define __IRONBOSS_H__

#include "Entity.h"

Entity *iron_new(Entity *target);

void iron_think(Entity *self);

void iron_move(Entity *self);

void iron_attack(Entity *self);

void iron_collide(Entity*self, Entity *other);

#endif