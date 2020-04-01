#include "simple_logger.h"
#include "boss3.h"
#include "Level.h"

Entity *playerTarget;
static int attackTimer = 0;

Entity *boss3_new(Entity *target){

	Entity *self;
	playerTarget = target;
	self = entity_new();

	self->position = vector2d(-1000, target->position.y);
	self->sprite = gf2d_sprite_load_all("images/boss2/ironrun.png", 150, 121, 3);
	self->think = boss3_think;
	self->collide = boss3_collide;
	self->bodyHitbox.x = self->position.x;
	self->bodyHitbox.y = self->position.y;
	self->bodyHitbox.w = 150;
	self->bodyHitbox.h = 121;
	self->minFrame = 1;
	self->maxFrame = 8;
	self->attacking = 0;
	self->type = 2;
	self->health = 30;

	return self;
}

void boss3_think(Entity *self){
	boss3_attack(self);
	if (self->health < 1){
		level_get_active()->winCon = 1;
		entity_free(self);
		return;
	}
}

void boss3_move(Entity *self, Entity *target){
	vector2d_set(self->velocity, 1, 1);
	float xDistance = abs(self->position.x - target->position.x);
	float yDistance = abs(self->position.y - target->position.y);

	self->minFrame = 1;
	self->maxFrame = 8;
	self->sprite = gf2d_sprite_load_all("images/boss2/ironrun.png", 150, 121, 3);
	self->bodyHitbox.w = 150;
	self->bodyHitbox.h = 121;


	if (!self->attacking){
		if (yDistance > 100){
			if (self->position.y > target->position.y - 100){
				self->position.y -= 1.5;
				return;
			}
			if (self->position.y < target->position.y){
				self->position.y += 1.5;
				return;
			}
		}
		if (self->position.x > target->position.x + 50){
			self->position.x -= 1.5;
			return;
		}
		if (self->position.x < target->position.x){
			self->position.x += 1.5;
			return;
		}
	}

}



void boss3_attack(Entity *self){

	////////////////////////////////////////////////
	if (attackTimer < 180){
		attackTimer++;
		boss3_move(self, playerTarget);
		return;
	}

	self->minFrame = 1;
	self->maxFrame = 11;

	if (attackTimer < 240){
		self->attacking = 1;
		self->sprite = gf2d_sprite_load_all("images/boss2/ironhit.png", 128, 180, 4);
		self->bodyHitbox.w = 128;
		self->bodyHitbox.h = 180;
		attackTimer++;
		return;
	}
	////////////////////////////////////////////

	attackTimer = 0;
	self->attacking = 0;

	///////////////////////////////
	self->minFrame = 1;
	self->maxFrame = 8;
	self->sprite = gf2d_sprite_load_all("images/boss2/ironrun.png", 150, 121, 3);
	self->bodyHitbox.w = 150;
	self->bodyHitbox.h = 121;
	/////////////////////////////////

}

void boss3_collide(Entity*self, Entity *other){
	if (other->type == 1){
		if (other->attacking){
			self->health -= 1;
		}
		if (other->type == 1 && self->attacking){
			other->position.y += 100;
		}
	}
}