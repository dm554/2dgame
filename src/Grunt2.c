#include "simple_logger.h"
#include "Grunt2.h"
#include "Level.h"

Entity *playerTarget;
static int attackTimer = 0;

Entity *grunt2_new(Entity *target){

	Entity *self;
	playerTarget = target;
	self = entity_new();

	Uint8 randomspawns = rand() % 8;
	Vector2D oppspawn;

	Vector2D spawn1 = vector2d(-400, 800);
	Vector2D spawn2 = vector2d(-500, 500);
	Vector2D spawn3 = vector2d(-600, 200);
	Vector2D spawn4 = vector2d(-700, 450);
	Vector2D spawn5 = vector2d(1000, 400);
	Vector2D spawn6 = vector2d(750, 600);
	Vector2D spawn7 = vector2d(350, 700);
	Vector2D spawn8 = vector2d(500, 500);

	switch (randomspawns){
	case 1:
		oppspawn = spawn1;
		break;
	case 2:
		oppspawn = spawn2;
		break;
	case 3:
		oppspawn = spawn3;
		break;
	case 4:
		oppspawn = spawn4;
		break;
	case 5:
		oppspawn = spawn5;
		break;
	case 6:
		oppspawn = spawn6;
		break;
	case 7:
		oppspawn = spawn7;
		break;
	case 8:
		oppspawn = spawn8;
		break;
	}


	self->position = oppspawn;
	self->sprite = gf2d_sprite_load_all("images/Grunt2idle.png", 64, 64, 5);
	self->think = grunt2_think;
	self->collide = grunt2_collide;
	self->bodyHitbox.x = self->position.x;
	self->bodyHitbox.y = self->position.y;
	self->bodyHitbox.w = 64;
	self->bodyHitbox.h = 64;
	self->minFrame = 0;
	self->maxFrame = 5;
	self->attacking = 0;
	self->type = 2;
	self->health = 10;

	return self;
}

void grunt2_think(Entity *self){
	grunt2_move(self, playerTarget);
	if (self->health < 1){
		entity_free(self);
		return;
	}
}

void grunt2_move(Entity *self, Entity *target){
	vector2d_set(self->velocity, 1, 1);
	float xDistance = abs(self->position.x - target->position.x);
	float yDistance = abs(self->position.y - target->position.y);

	if (self->position.x > target->position.x){
		self->forward = 0;
		self->sprite = gf2d_sprite_load_all("images/Grunt2idleflip.png", 64, 64, 5);
	}
	if (self->position.x < target->position.x){
		self->forward = 1;
		self->sprite = gf2d_sprite_load_all("images/Grunt2idle.png", 64, 64, 5);
	}

	if (!self->attacking){
		
		if (xDistance > 50){
			if (self->position.x > target->position.x){
				self->position.x -= 1;
				return;
			}
			if (self->position.x < target->position.x){
				self->position.x += 1;
				return;
			}
		}

		if (yDistance > 50){
			if (self->position.y > target->position.y){
				self->position.y -= 1;
				return;
			}
			if (self->position.y < target->position.y){
				self->position.y += 1;
				return;
			}
		}

		if (xDistance > 10){
			if (self->position.x > target->position.x){
				self->position.x -= 1;
				return;
			}
			if (self->position.x < target->position.x){
				self->position.x += 1;
				return;
			}
		}
	}

	grunt2_attack(self);


}

void grunt2_attack(Entity *self){

	if (attackTimer < 60){
		attackTimer++;
		return;
	}

	self->minFrame = 56;
	self->maxFrame = 61;

	if (attackTimer < 120){
		self->attacking = 1;
		self->sprite = gf2d_sprite_load_all("images/Grunt2attack.png", 64, 64, 12);
		attackTimer++;
		return;
	}

	attackTimer = 0;
	self->attacking = 0;
	self->minFrame = 0;
	self->maxFrame = 5;
	self->sprite = gf2d_sprite_load_all("images/Grunt2idle.png", 64, 64, 5);

}

void grunt2_collide(Entity*self, Entity *other){
	if (other->type == 1){
		if (other->attacking && self->forward != other->forward){
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
