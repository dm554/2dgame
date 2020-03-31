#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"

Entity *player_new(Vector2D position);

void player_think(Entity *self);

void player_move(Entity *self);

void player_attack(Entity *self);

void player_attacked(Entity *self);

void player_collide(Entity*self, Entity *other);

Vector2D player_get_health(Entity* self);

void player_health_image_set(Vector2D healthicons, Vector2D tenPosition, Vector2D onesPosition);

void player_health_display(Entity* self);

#endif