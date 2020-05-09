#include "simple_logger.h"
#include "Grunt.h"
#include "Level.h"

Entity *playerTarget;
static int attackTimer = 0;
Sprite* digit1;
Sprite* digit2;

Entity *grunt_new(Entity *target){
	
	Entity *self;
	playerTarget = target;
	self = entity_new();

	Uint8 randomspawns = rand() % 8;
	Vector2D oppspawn;


	Vector2D spawn1 = vector2d(-700, 800);
	Vector2D spawn2 = vector2d(-800, 500);
	Vector2D spawn3 = vector2d(-750, 600);
	Vector2D spawn4 = vector2d(-1000, 450);
	Vector2D spawn5 = vector2d(1125, 400);
	Vector2D spawn6 = vector2d(1000, 600);
	Vector2D spawn7 = vector2d(1200, 700);
	Vector2D spawn8 = vector2d(800, 500);

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
	self->sprite = gf2d_sprite_load_all("images/Grunt1idle.png", 64, 64, 5);
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
	self->hitstun = 0;
	self->hitstunTimer = 0;

	return self;
}

void grunt_think(Entity *self){
	grunt_move(self, playerTarget);
	if (self->health < 1){
		entity_free(self);
		return;
	}
	//grunt_health_display(self);
}

void grunt_move(Entity *self, Entity *target){
	vector2d_set(self->velocity, 1, 1);
	float xDistance = abs(self->position.x - target->position.x);
	float yDistance = abs(self->position.y - target->position.y);
	
	if (self->position.x > target->position.x){
		self->forward = 0;
		self->sprite = gf2d_sprite_load_all("images/Grunt1idleflip.png", 64, 64, 5);
	}
	if (self->position.x < target->position.x){
		self->forward = 1;
		self->sprite = gf2d_sprite_load_all("images/Grunt1idle.png", 64, 64, 5);
	}

	if (!self->attacking && !self->hitstun){
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
	if (self->hitstun){
		if (self->hitstunTimer < 200){
			self->hitstunTimer++;
			return;
		}
		self->hitstun = 0;
		self->hitstunTimer = 0;
	}
	grunt_attack(self);


}

void grunt_attack(Entity *self){
	
	if (attackTimer < 60){
		attackTimer++;
		return;
	}
	
	if (attackTimer < 120){
		self->attacking = 1;
		
		if (self->forward){
			self->sprite = gf2d_sprite_load_all("images/Grunt1attack.png", 64, 64, 12);
			self->minFrame = 56;
			self->maxFrame = 61;
		}
		if (!self->forward){
			self->sprite = gf2d_sprite_load_all("images/Grunt1attackflip.png", 64, 64, 12);
			self->minFrame = 49;
			self->maxFrame = 53;
		}
		attackTimer++;
		return;
	}
	
	attackTimer = 0;
	self->attacking = 0;
	self->minFrame = 0;
	self->maxFrame = 5;
	self->sprite = gf2d_sprite_load_all("images/Grunt1idle.png", 64, 64, 5);

}

void grunt_collide(Entity*self, Entity *other){
	if (other->type == 1){
		if (other->attacking && self->forward != other->forward){

			if (other->lastAttack == 1){
				self->health -= 1;
				if (self->forward){
					self->position.x -= 10;
				}
				if (!self->forward){
					self->position.x += 10;
				}
			}

			if (other->lastAttack == 2){
				self->health -= 1;
				if (self->forward){
					self->position.x -= 10;
					self->position.y -= 15;
				}
				if (!self->forward){
					self->position.x += 10;
					self->position.y -= 15;
				}
			}

			if (other->lastAttack == 3){
				self->health -= 1;
				if (self->forward){
					self->position.x -= 25;
				}
				if (!self->forward){
					self->position.x += 25;
				}
			}

			if (other->lastAttack == 4){
				self->health -= 1;
				if (self->forward){
					self->position.x -= 10;
					self->position.y += 15;
				}
				if (!self->forward){
					self->position.x += 10;
					self->position.y += 15;
				}
			}

			if (other->lastAttack == 1){
				self->health -= 1;
				if (self->forward){
					self->position.x -= 10;
				}
				if (!self->forward){
					self->position.x += 10;
				}
			}
			
			self->hitstun = true;
		}
	}
}
/*
Vector2D grunt_get_health(Entity* self){
	//slog("get health");
	int ones = self->health % 10;
	int tens = (self->health - ones) / 10;

	Vector2D healthIcons = vector2d(tens, ones);
	return(healthIcons);
}

void grunt_health_image_set(Vector2D healthicons, Vector2D tenPosition, Vector2D onesPosition){
	//slog("image set");
	int tens = healthicons.x;
	int ones = healthicons.y;

	char *tensPath;
	char *onesPath;

	switch (tens){
	case 1:
		tensPath = "images/UI/Nums/1.png";
		break;
	case 2:
		tensPath = "images/UI/Nums/2.png";
		break;
	case 3:
		tensPath = "images/UI/Nums/3.png";
		break;
	case 4:
		tensPath = "images/UI/Nums/4.png";
		break;
	case 5:
		tensPath = "images/UI/Nums/5.png";
		break;
	case 6:
		tensPath = "images/UI/Nums/6.png";
		break;
	case 7:
		tensPath = "images/UI/Nums/7.png";
		break;
	case 8:
		tensPath = "images/UI/Nums/8.png";
		break;
	case 9:
		tensPath = "images/UI/Nums/9.png";
		break;
	case 0:
		tensPath = "images/UI/Nums/0.png";
		break;
	}

	switch (ones){
	case 1:
		onesPath = "images/UI/Nums/1.png";
		break;
	case 2:
		onesPath = "images/UI/Nums/2.png";
		break;
	case 3:
		onesPath = "images/UI/Nums/3.png";
		break;
	case 4:
		onesPath = "images/UI/Nums/4.png";
		break;
	case 5:
		onesPath = "images/UI/Nums/5.png";
		break;
	case 6:
		onesPath = "images/UI/Nums/6.png";
		break;
	case 7:
		onesPath = "images/UI/Nums/7.png";
		break;
	case 8:
		onesPath = "images/UI/Nums/8.png";
		break;
	case 9:
		onesPath = "images/UI/Nums/9.png";
		break;
	case 0:
		onesPath = "images/UI/Nums/0.png";
		break;
	}


	digit1 = gf2d_sprite_load_image(tensPath);
	digit2 = gf2d_sprite_load_image(onesPath);

	gf2d_sprite_draw_image(digit1, tenPosition);
	gf2d_sprite_draw_image(digit2, onesPosition);
}

void grunt_health_display(Entity* self){
	//slog("health display");
	grunt_health_image_set(grunt_get_health(self), vector2d(self->position.x + 100, self->position.y + 100), self->position);
}
*/