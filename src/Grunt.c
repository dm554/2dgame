#include "simple_logger.h"
#include "Grunt.h"
#include "Level.h"

Entity *playerTarget;
static int attackTimer = 0;

Entity *grunt_new(Vector2D position, Entity *target){
	
	Entity *self;
	playerTarget = target;
	self = entity_new();
	self->position = vector2d(700, 450);
	self->sprite = gf2d_sprite_load_all("images/playerIdle.png", 64, 64, 5);
	self->think = grunt_think;
	self->collide = grunt_collide;
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

void grunt_think(Entity *self){
	grunt_move(self, playerTarget);
	if (self->health < 1){
		entity_free(self);
		return;
	}
}

void grunt_move(Entity *self, Entity *target){
	vector2d_set(self->velocity, 1, 1);
	float xDistance = abs(self->position.x - target->position.x);
	float yDistance = abs(self->position.y - target->position.y);
	
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

		if (yDistance > 10){
			if (self->position.y > target->position.y){
				self->position.y -= 0.5;
				return;
			}
			if (self->position.y < target->position.y){
				self->position.y += 0.5;
				return;
			}
		}
	}

	grunt_attack(self);


}

void grunt_attack(Entity *self){
	
	if (attackTimer < 60){
		attackTimer++;
		return;
	}
	
	self->minFrame = 56;
	self->maxFrame = 61;

	if (attackTimer < 120){
		self->attacking = 1;
		self->sprite = gf2d_sprite_load_all("images/playerAttack.png", 64, 64, 12);
		attackTimer++;
		return;
	}
	
	attackTimer = 0;
	self->attacking = 0;
	self->minFrame = 0;
	self->maxFrame = 5;
	self->sprite = gf2d_sprite_load_all("images/playerIdle.png", 64, 64, 5);

}

void grunt_collide(Entity*self, Entity *other){
	if (other->type = 1){
		if (other->attacking){
			self->health -= 1;
			self->position.x += 10;
		}
		
	}
}
