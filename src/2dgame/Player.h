#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"

static Entity *THE_PLAYER;

Entity *player_new(Vector2D position);

void player_think(Entity *self);

void player_move(Entity *self);

void player_attack(Entity *self);

void player_attacked(Entity *self);

void player_collide(Entity*self, Entity *other);

Vector2D player_get_health(Entity* self);

void player_health_image_set(Vector2D healthicons, Vector2D tenPosition, Vector2D onesPosition);

void player_health_display(Entity* self);

void player_xp_display(Entity *self);

void player_xp_image_set(Vector2D xpIcons, Vector2D capIcons, Vector2D xpposition, Vector2D capposition);

char *num_pathfinder(int num);
void player_level_display(Entity *self);

Vector2D player_get_cap(Entity *self);

Vector2D player_get_xp(Entity *self);


Entity *player_get_active();
#endif