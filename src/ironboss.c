#include "simple_logger.h"
#include "ironboss.h"
#include "Level.h"

Entity *playerTarget;
static int attackTimer = 0;

Entity *iron_new(Entity *target){

	Entity *self;
	playerTarget = target;
	self = entity_new();

	self->position = vector2d(-1000, target->position.y);
	self->sprite = gf2d_sprite_load_all("images/boss3/guilerun.png", 128, 91, 5);
	self->think = iron_think;
	self->collide = iron_collide;
	self->bodyHitbox.x = self->position.x;
	self->bodyHitbox.y = self->position.y;
	self->bodyHitbox.w = 128;
	self->bodyHitbox.h = 91;
	self->minFrame = 1;
	self->maxFrame = 8;
	self->attacking = 0;
	self->type = 2;
	self->health = 30;

	return self;
}

void iron_think(Entity *self){
	iron_attack(self);
	if (self->health < 1){
		level_get_active()->winCon = 1;
		entity_free(self);
		return;
	}
}

void iron_move(Entity *self, Entity *target){
	vector2d_set(self->velocity, 1, 1);
	float xDistance = abs(self->position.x - target->position.x);
	float yDistance = abs(self->position.y - target->position.y);

	self->minFrame = 1;
	self->maxFrame = 8;
	self->sprite = gf2d_sprite_load_all("images/boss3/guilerun.png", 128, 91, 5);
	self->bodyHitbox.w = 128;
	self->bodyHitbox.h = 91;


	if (!self->attacking){
		if (yDistance > 100){
			if (self->position.y > target->position.y){
				self->position.y -= 3;
				return;
			}
			if (self->position.y < target->position.y){
				self->position.y += 3;
				return;
			}
		}
		if (self->position.x > target->position.x - 100){
			self->position.x -= 3;
			return;
		}
		if (self->position.x < target->position.x){
			self->position.x += 3;
			return;
		}
	}

}



void iron_attack(Entity *self){

	////////////////////////////////////////////////
	if (attackTimer < 180){
		attackTimer++;
		iron_move(self, playerTarget);
		return;
	}

	self->minFrame = 1;
	self->maxFrame = 12;

	if (attackTimer < 240){
		self->attacking = 1;
		self->sprite = gf2d_sprite_load_all("images/boss3/guilehit.png", 146, 109, 5);
		self->bodyHitbox.w = 149;
		self->bodyHitbox.h = 109;
		attackTimer++;
		return;
	}
	////////////////////////////////////////////

	attackTimer = 0;
	self->attacking = 0;

	///////////////////////////////
	self->minFrame = 1;
	self->maxFrame = 8;
	self->sprite = gf2d_sprite_load_all("images/boss3/guilerun.png", 128, 91, 5);
	self->bodyHitbox.w = 128;
	self->bodyHitbox.h = 91;
	/////////////////////////////////

}

void iron_collide(Entity*self, Entity *other){
	if (other->type == 1){
		if (other->attacking){
			self->health -= 1;
		}
		if (other->type == 1 && self->attacking){
				other->position.x += 75;
		}
	}
}