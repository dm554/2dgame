#include "simple_logger.h"
#include "box.h"
#include "Level.h"


Entity *box_new(){

	Entity *self;
	self = entity_new();


	self->sprite = gf2d_sprite_load_all("images/lilbox.png", 50, 51, 1);
	self->think = box_think;
	self->collide = box_collide;
	self->position = vector2d(600, 600);
	self->bodyHitbox.x = self->position.x;
	self->bodyHitbox.y = self->position.y;
	self->bodyHitbox.w = 50;
	self->bodyHitbox.h = 51;
	self->minFrame = 0;
	self->maxFrame = 1;
	self->attacking = 0;
	self->type = 3;
	self->health = 15;

	return self;
}

void box_think(Entity *self){
	if (self->health < 1){
		entity_free(self);
		return;
	}
}



void box_collide(Entity*self, Entity *other){
	if (other->type == 1 && self->forward != other->forward){
		if (other->attacking){
			self->health -= 1;
			if (self->forward){
				self->position.x -= 10;
			}
			if (!self->forward){
				self->position.x += 10;
			}
		}

	}
}