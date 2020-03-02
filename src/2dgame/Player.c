#include "simple_logger.h"
#include "Player.h"
#include "level.h"

#define ES_DEAD 1

static int walking = 0;


void player_think(Entity *self){
	
	player_attack(self);
	if (!self->attacking){
		player_move(self);
	}

	//entity_collision_check(self);

}

Entity *player_new(Vector2D position){

	Entity *self;
	self = entity_new();

	self->sprite = gf2d_sprite_load_all("images/playerSprite2.png", 160, 200, 5);
	self->think = player_think;
	self->attacking = 0;
	return self;
}

void player_move(Entity *self){

	Uint8 *buttons = SDL_GetKeyboardState(NULL);
	vector2d_set(self->velocity, 1, 1);

	if (buttons[SDL_SCANCODE_RIGHT] && buttons[SDL_SCANCODE_UP]){
		self->position.x += 1.5;
		self->position.y -= 0.5;
		int walking = 1;
		self->sprite = gf2d_sprite_load_all("images/playerWalk.png", 110, 200, 5);
		return;
	}
	if (buttons[SDL_SCANCODE_RIGHT] && buttons[SDL_SCANCODE_DOWN]){
		self->position.x += 1.5;
		self->position.y += 0.5;
		int walking = 1;
		self->sprite = gf2d_sprite_load_all("images/playerWalk.png", 110, 200, 5);
		return;
	}
	if (buttons[SDL_SCANCODE_LEFT] && buttons[SDL_SCANCODE_UP]){
		self->position.x -= 1.5;
		self->position.y -= 0.5;
		int walking = 1;
		self->sprite = gf2d_sprite_load_all("images/playerWalk.png", 110, 200, 5);
		return;
	}
	if (buttons[SDL_SCANCODE_LEFT] && buttons[SDL_SCANCODE_DOWN]){
		self->position.x -= 1.5;
		self->position.y += 0.5;
		int walking = 1;
		self->sprite = gf2d_sprite_load_all("images/playerWalk.png", 110, 200, 5);
		return;
	}
	if (buttons[SDL_SCANCODE_RIGHT]){
		self->position.x += 3;
		int walking = 1;
		self->sprite = gf2d_sprite_load_all("images/playerWalk.png", 110, 200, 5);
		return;
	}
	if (buttons[SDL_SCANCODE_LEFT]){
		self->position.x -= 3;
		int walking = 1;
		self->sprite = gf2d_sprite_load_all("images/playerWalk.png", 110, 200, 5);
		return;
	}
	if (buttons[SDL_SCANCODE_UP]){
		self->position.y -= 2;
		int walking = 1;
		self->sprite = gf2d_sprite_load_all("images/playerWalk.png", 110, 200, 5);
		return;
	}
	if (buttons[SDL_SCANCODE_DOWN]){
		self->position.y += 2;
		int walking = 1;
		self->sprite = gf2d_sprite_load_all("images/playerWalk.png", 110, 200, 5);
		return;
	}

	int walking = 0;
	self->sprite = gf2d_sprite_load_all("images/playerSprite2.png", 160, 200, 5);
}

void player_attack(Entity *self){
	
	Uint8 *buttons = SDL_GetKeyboardState(NULL);
	
	if (buttons[SDL_SCANCODE_Z]){
		self->attacking = 1;
		self->sprite = gf2d_sprite_load_all("images/playerHit.png", 188, 248, 5);
		slog("attack");
		return;
	}

	self->attacking = 0;
	self->sprite = gf2d_sprite_load_all("images/playerSprite2.png", 160, 200, 5);
}

