#include "simple_logger.h"
#include "Player.h"
#include "level.h"

#define ES_DEAD 1

static int walking = 0;
static Entity *THE_PLAYER;
Sprite* digit1;
Sprite* digit2;
Sprite* xp10;
Sprite* xp1;
Sprite* cap10;
Sprite* cap1;
Sprite* levelnum;

void player_think(Entity *self){
	//slog("%f", self->position.y);
	player_attack(self);
	if (!self->attacking){
		player_move(self);
	}
	if (self->xp >= self->xpcap){
		self->xp -= self->xpcap;
		self->level++;
	}
}

Entity *player_new(Vector2D position){

	Entity *self;
	self = entity_new();

	self->position = vector2d(600, 500);
	self->sprite = gf2d_sprite_load_all("images/playerIdle.png", 64, 64, 5);
	self->think = player_think;
	self->collide = player_collide;
	self->forward = 1;
	self->bodyHitbox.x = self->position.x;
	self->bodyHitbox.y = self->position.y;
	self->bodyHitbox.w = 64;
	self->bodyHitbox.h = 64;
	self->minFrame = 0;
	self->maxFrame = 5;
	self->attacking = 0;
	self->type = 1;
	self->health = 99;
	self->level = 1;
	self->xpcap = self->level * 50;
	self->xp = 0;
	self->bonk = gfc_sound_load("audio/oof.mp3", 0.5, 3);
	
	THE_PLAYER = self;
	return self;
}

void player_move(Entity *self){

	Uint8 *buttons = SDL_GetKeyboardState(NULL);
	vector2d_set(self->velocity, 1, 1);
	if (self->position.y < 400){
		self->position.y += 2;
	}
	if (buttons[SDL_SCANCODE_RIGHT] && buttons[SDL_SCANCODE_UP]){
		self->position.x += 1.5;
		self->position.y -= 0.5;
		int walking = 1;
		self->forward = 1;
		self->sprite = gf2d_sprite_load_all("images/playerIdle.png", 64, 64, 5);
		return;
	}
	if (buttons[SDL_SCANCODE_RIGHT] && buttons[SDL_SCANCODE_DOWN]){
		self->position.x += 1.5;
		self->position.y += 0.5;
		int walking = 1;
		self->forward = 1;
		self->sprite = gf2d_sprite_load_all("images/playerIdle.png", 64, 64, 5);
		//self->sprite = gf2d_sprite_load_all("images/playerWalk.png", 110, 200, 5);
		return;
	}
	if (buttons[SDL_SCANCODE_LEFT] && buttons[SDL_SCANCODE_UP]){
		self->position.x -= 1.5;
		self->position.y -= 0.5;
		int walking = 1;
		self->forward = 0;
		self->sprite = gf2d_sprite_load_all("images/playerIdleFlip.png", 64, 64, 5);
		//self->sprite = gf2d_sprite_load_all("images/playerWalk.png", 110, 200, 5);
		return;
	}
	if (buttons[SDL_SCANCODE_LEFT] && buttons[SDL_SCANCODE_DOWN]){
		self->position.x -= 1.5;
		self->position.y += 0.5;
		int walking = 1;
		self->forward = 0;
		self->sprite = gf2d_sprite_load_all("images/playerIdleFlip.png", 64, 64, 5);
		//self->sprite = gf2d_sprite_load_all("images/playerWalk.png", 110, 200, 5);
		return;
	}
	if (buttons[SDL_SCANCODE_RIGHT]){
		self->position.x += 2;
		int walking = 1;
		self->forward = 1;
		self->sprite = gf2d_sprite_load_all("images/playerIdle.png", 64, 64, 5);
		//self->sprite = gf2d_sprite_load_all("images/playerWalk.png", 110, 200, 5);
		return;
	}
	if (buttons[SDL_SCANCODE_LEFT]){
		self->position.x -= 2;
		int walking = 1;
		self->forward = 0;
		self->sprite = gf2d_sprite_load_all("images/playerIdleFlip.png", 64, 64, 5);
		//self->sprite = gf2d_sprite_load_all("images/playerWalk.png", 110, 200, 5);
		return;
	}
	if (buttons[SDL_SCANCODE_UP]){
		self->position.y -= 2;
		int walking = 1;
		//self->sprite = gf2d_sprite_load_all("images/playerWalk.png", 110, 200, 5);
		return;
	}
	if (buttons[SDL_SCANCODE_DOWN]){
		self->position.y += 2;
		int walking = 1;
		//self->sprite = gf2d_sprite_load_all("images/playerWalk.png", 110, 200, 5);
		return;
	}

	int walking = 0;
	self->minFrame = 0;
	self->maxFrame = 5;
	if (self->forward){
		self->sprite = gf2d_sprite_load_all("images/playerIdle.png", 64, 64, 5);
	}
	else{
		self->sprite = gf2d_sprite_load_all("images/playerIdleFlip.png", 64, 64, 5);
	}
	
}

void player_attack(Entity *self){
	
	Uint8 *buttons = SDL_GetKeyboardState(NULL);
	float maxFrame = self->maxFrame;

	if (buttons[SDL_SCANCODE_Z]){
		self->attacking = 1;
		if (self->forward){
			self->sprite = gf2d_sprite_load_all("images/playerAttack.png", 64, 64, 12);
			self->minFrame = 56;
			self->maxFrame = 61;
		}
		if (!self->forward){
			self->sprite = gf2d_sprite_load_all("images/playerAttackFlip.png", 64, 64, 12);
			self->minFrame = 49;
			self->maxFrame = 53;
		}
		self->lastAttack = 1;
		return;
	}
	if (buttons[SDL_SCANCODE_X]){
		self->attacking = 1;
		if (self->forward){
			self->sprite = gf2d_sprite_load_all("images/playerAttack.png", 64, 64, 12);
			self->minFrame = 104;
			self->maxFrame = 112;
		}
		if (!self->forward){
			self->sprite = gf2d_sprite_load_all("images/playerAttackFlip.png", 64, 64, 12);
			self->minFrame = 96;
			self->maxFrame = 102;
		}
		self->lastAttack = 2;
		return;
	}
	if (buttons[SDL_SCANCODE_C]){
		self->attacking = 1;
		if (self->forward){
			self->sprite = gf2d_sprite_load_all("images/playerAttack.png", 64, 64, 12);
			self->minFrame = 95;
			self->maxFrame = 104;
		}
		if (!self->forward){
			self->sprite = gf2d_sprite_load_all("images/playerAttackFlip.png", 64, 64, 12);
			self->minFrame = 102;
			self->maxFrame = 108;
		}
		self->lastAttack = 3;
		return;
	}
	if (buttons[SDL_SCANCODE_V]){
		self->attacking = 1;
		if (self->forward){
			self->sprite = gf2d_sprite_load_all("images/playerAttack.png", 64, 64, 12);
			self->minFrame = 84;
			self->maxFrame = 93;
		}
		if (!self->forward){
			self->sprite = gf2d_sprite_load_all("images/playerAttackFlip.png", 64, 64, 12);
			self->minFrame = 88;
			self->maxFrame = 95;
		}
		self->lastAttack = 4;
		return;
	}

	self->attacking = 0;
	self->lastAttack = 0;
	self->reset = 0;
	self->minFrame = 0;
	self->maxFrame = 5;
	if (self->forward){
		self->sprite = gf2d_sprite_load_all("images/playerIdle.png", 64, 64, 5);
	}
	else{
		self->sprite = gf2d_sprite_load_all("images/playerIdleFlip.png", 64, 64, 5);
	}
	return;
}

void player_collide(Entity *self, Entity *other){
	
	if (other->attacking && self->health > 0){
		self->health -= 1;
		gfc_sound_play(self->bonk, 0, 0.5, -1, -1);
	}
}

Vector2D player_get_xp(Entity *self){
	int ones = self->xp % 10;
	int tens = (self->xp - ones) / 10;

	Vector2D xpIcons = vector2d(tens, ones);
	return(xpIcons);
}

Vector2D player_get_cap(Entity *self){
	int ones = self->xpcap % 10;
	int tens = (self->xpcap - ones) / 10;

	Vector2D capIcons = vector2d(tens, ones);
	return(capIcons);
}

char *num_pathfinder(int num){
	char *numpath;
	
	switch (num){
	case 1:
		numpath = "images/UI/Nums/1.png";
		return(numpath);
		break;
	case 2:
		numpath = "images/UI/Nums/2.png";
		return(numpath);
		break;
	case 3:
		numpath = "images/UI/Nums/3.png";
		return(numpath);
		break;
	case 4:
		numpath = "images/UI/Nums/4.png";
		return(numpath);
		break;
	case 5:
		numpath = "images/UI/Nums/5.png";
		return(numpath);
		break;
	case 6:
		numpath = "images/UI/Nums/6.png";
		return(numpath);
		break;
	case 7:
		numpath = "images/UI/Nums/7.png";
		return(numpath);
		break;
	case 8:
		numpath = "images/UI/Nums/8.png";
		return(numpath);
		break;
	case 9:
		numpath = "images/UI/Nums/9.png";
		return(numpath);
		break;
	case 0:
		numpath = "images/UI/Nums/0.png";
		return(numpath);
		break;
	}
}

void player_xp_image_set(Vector2D xpIcons, Vector2D capIcons, Vector2D xpposition, Vector2D capposition, Entity *self){
	xp10 = gf2d_sprite_load_image(num_pathfinder(xpIcons.x));
	xp1 = gf2d_sprite_load_image(num_pathfinder(xpIcons.y));
	cap10 = gf2d_sprite_load_image(num_pathfinder(capIcons.x));
	cap1 = gf2d_sprite_load_image(num_pathfinder(capIcons.y));
	levelnum = gf2d_sprite_load_image(num_pathfinder(self->level));

	gf2d_sprite_draw_image(xp10, xpposition);
	gf2d_sprite_draw_image(xp1, vector2d(xpposition.x + 35, xpposition.y));
	gf2d_sprite_draw_image(cap10, capposition);
	gf2d_sprite_draw_image(cap1, vector2d(capposition.x + 35, capposition.y));
	gf2d_sprite_draw_image(levelnum, vector2d(80, 625));

}

Vector2D player_get_health(Entity* self){
	//slog("get health");
	int ones = self->health % 10;
	int tens = (self->health - ones) / 10;

	Vector2D healthIcons = vector2d(tens, ones);
	return(healthIcons);
}

void player_health_image_set(Vector2D healthicons, Vector2D tenPosition, Vector2D onesPosition){
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

void player_health_display(Entity* self){
	//slog("health display");
	player_health_image_set(player_get_health(self), vector2d(150, 25), vector2d(190, 25));
}

void player_xp_display(Entity *self){
	player_xp_image_set(player_get_xp(self), player_get_cap(self), vector2d(75, 660), vector2d(170, 660), self);
}

Entity *player_get_active(){
	return THE_PLAYER;
}