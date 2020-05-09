#ifndef __GRUNT_H__
#define __GRUNT_H__

#include "Entity.h"

Entity *grunt_new(Entity *target);

void grunt_think(Entity *self);

void grunt_move(Entity *self);

void grunt_attack(Entity *self);

void grunt_collide(Entity*self, Entity *other);

Vector2D grunt_get_health(Entity* self);

void grunt_health_image_set(Vector2D healthicons, Vector2D tenPosition, Vector2D onesPosition);

void grunt_health_display(Entity* self);

#endif