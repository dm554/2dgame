#include "simple_logger.h"
#include "Axel.h"
#include "Level.h"

Entity *playerTarget;
static int attackTimer = 0;

Entity *axel_new(Entity *target){

	Entity *self;
	playerTarget = target;
	self = entity_new();

	self->position = vector2d(1000, target->position.y);
	self->sprite = gf2d_sprite_load_all("images/playerSprite2.png", 160, 200, 5);
	self->think = axel_think;
	self->collide = axel_collide;
	self->bodyHitbox.x = self->position.x;
	self->bodyHitbox.y = self->position.y;
	self->bodyHitbox.w = 160;
	self->bodyHitbox.h = 200;
	self->minFrame = 1;
	self->maxFrame = 11;
	self->attacking = 0;
	self->type = 2;
	self->health = 30;

	return self;
}

void axel_think(Entity *self){
	axel_move(self, playerTarget);
	if (self->health < 1){
		level_get_active()->winCon = 1;
		entity_free(self);
		return;
	}
}

void axel_move(Entity *self, Entity *target){
	vector2d_set(self->velocity, 1, 1);
	float xDistance = abs(self->position.x - target->position.x);
	float yDistance = abs(self->position.y - target->position.y);

	if (self->position.x > target->position.x){
		self->forward = 0;
		self->sprite = gf2d_sprite_load_all("images/playerSprite2Flip.png", 160, 200, 5);
	}
	if (self->position.x < target->position.x){
		self->forward = 1;
		self->sprite = gf2d_sprite_load_all("images/playerSprite2.png", 160, 200, 5);
	}

	if (!self->attacking){
		if (yDistance > 50){
			if (self->position.y > target->position.y){
				self->position.y -= 0.5;
				return;
			}
			if (self->position.y < target->position.y){
				self->position.y += 0.5;
				return;
			}
		}

		if (xDistance > 50){
			if (self->position.x > target->position.x){
				self->position.x -= 0.5;
				return;
			}
			if (self->position.x < target->position.x){
				self->position.x += 0.5;
				return;
			}
		}

	}

	axel_attack(self);


}

void axel_attack(Entity *self){

	////////////////////////////////////////////////
	if (attackTimer < 180){
		attackTimer++;
		return;
	}

	self->minFrame = 6;
	self->maxFrame = 10;
	
	if (attackTimer < 240){
		self->attacking = 1;
		if (self->forward){
			self->sprite = gf2d_sprite_load_all("images/playerHit.png", 188, 248, 5);
		}
		if (!self->forward){
			self->sprite = gf2d_sprite_load_all("images/playerHitFlip.png", 188, 248, 5);
		}
		self->bodyHitbox.w = 188;
		self->bodyHitbox.h = 248;
		attackTimer++;
		return;
	}
	////////////////////////////////////////////

	attackTimer = 0;
	self->attacking = 0;

///////////////////////////////
	self->minFrame = 0;
	self->maxFrame = 11;
	self->sprite = gf2d_sprite_load_all("images/playerSprite2.png", 160, 200, 5);
	self->bodyHitbox.w = 160;
	self->bodyHitbox.h = 200;
/////////////////////////////////

}

void axel_collide(Entity*self, Entity *other){
	if (other->type == 1 && self->forward != other->forward){
		if (other->attacking){
			self->health -= 1;
		}
		if (other->type == 1 && self->attacking){
			if (self->forward){
				other->position.x += 30;
				other->position.y -= 40;
			}
			if (!self->forward){
				other->position.x -= 30;
				other->position.y -= 40;
			}
		}
	}
}