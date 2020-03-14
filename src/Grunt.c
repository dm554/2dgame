#include "simple_logger.h"
#include "Grunt.h"

Entity *grunt_new(Vector2D position){
	
	Entity *self;
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

	return self;
}

void grunt_think(Entity *self){

}

void grunt_move(Entity *self){

}

void grunt_attack(Entity *self){

}

void grunt_collide(Entity*self, Entity *other){

}
