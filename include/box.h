#ifndef __BOX_H__
#define __BOX_H__

#include "Entity.h"

Entity *box_new();

void box_think(Entity *self);

void box_collide(Entity*self, Entity *other);

#endif