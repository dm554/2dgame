#include "simple_logger.h"
#include "Player.h"
#include "level.h"

#define ES_DEAD 1

void player_move(Entity *self){
	//slog("Player Move Function called");
	Uint8 *buttons = SDL_GetKeyboardState(NULL);
	vector2d_set(self->velocity, 1, 1);
	
	
	if (buttons[SDL_SCANCODE_RIGHT] && buttons[SDL_SCANCODE_UP]){
		self->position.x += 1.5;
		self->position.y -= 0.5;
		return;
	}
	if (buttons[SDL_SCANCODE_RIGHT] && buttons[SDL_SCANCODE_DOWN]){
		self->position.x += 1.5;
		self->position.y += 0.5;
		return;
	}
	if (buttons[SDL_SCANCODE_LEFT] && buttons[SDL_SCANCODE_UP]){
		self->position.x -= 1.5;
		self->position.y -= 0.5;
		return;
	}
	if (buttons[SDL_SCANCODE_LEFT] && buttons[SDL_SCANCODE_DOWN]){
		self->position.x -= 1.5;
		self->position.y += 0.5;
		return;
	}
	if (buttons[SDL_SCANCODE_RIGHT]){
		self->position.x += 3;
		//self->sprite = gf2d_sprite_load_all("images/playerWalk.png", 110, 200, 5);
		return;
	}
	if (buttons[SDL_SCANCODE_LEFT]){	
		self->position.x -= 3;
		//self->sprite = gf2d_sprite_load_all("images/playerWalk.png", 110, 200, 5);
		return;
	}
	if (buttons[SDL_SCANCODE_UP]){
		self->position.y -= 2;
		return;
	}
	if (buttons[SDL_SCANCODE_DOWN]){
		self->position.y += 2;
		return;
	}
}

void player_think(Entity *self){

	player_move(self);

}

Entity *player_new(Vector2D position){
	slog("player new called");
	Entity *self;
	self = entity_new();
	slog("entity new called");
	self->sprite = gf2d_sprite_load_all("images/playerSprite2.png", 160, 200, 5);
	slog("spite loaded");
	self->think = player_think;
	slog("player new finished");
	return self;
}
