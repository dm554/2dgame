#include <SDL_image.h>
#include <stdlib.h>
#include "simple_logger.h"
#include "Menu.h"
#include "gf2d_draw.h"
#include "gf2d_sprite.h"
#include "gfc_types.h"

static Menu *THE_MENU = NULL;
static int cursorTimer = 0;
void menu_update(Menu *self){
	slog("cursor handler");
	cursor_handler(self);
	slog("draw");
	menu_draw(self);
	//self->think(*self);
}

void cursor_handler(Menu *self){
	Uint8 *buttons = SDL_GetKeyboardState(NULL);
	
	if (buttons[SDL_SCANCODE_DOWN]){
		if (self->cursorPoint < self->cursorPointTotal){
			self->cursorPoint += 1;
		}
		else{
			self->cursorPoint = 1;
		}
	}
	if (buttons[SDL_SCANCODE_UP]){
		if (self->cursorPoint > 1){
			self->cursorPoint -= 1;
		}
		else{
			self->cursorPoint = 3;
		}
	}
	cursor_set_position(self);
	if (buttons[SDL_SCANCODE_Z]){
		cursor_option_select(self);
	}

}

void cursor_set_position(Menu *self){
	if (cursorTimer < 10){
		cursorTimer++;
		return;
	}
	switch (self->cursorPoint){
		case 1:
			self->cursorPostion = self->cursorPoint_1;
			break;
		case 2:
			self->cursorPostion = self->cursorPoint_2;
			break;
		case 3:
			self->cursorPostion = self->cursorPoint_3;
			break;
	}
	cursorTimer = 0;
}

void cursor_option_select(Menu *self){
	
	switch (self->cursorPoint){
	case 1:
		self->select = 1;
		break;
	case 2:
		self->select = 2;
		break;
	case 3:
		self->select = 3;
		break;
	}

}

void menu_draw(Menu *self){
	slog("drawing");
	if (!self)return;
	gf2d_sprite_draw_image(self->backsprite, self->backPosition);
	gf2d_sprite_draw_image(self->cursorSprite, self->cursorPostion);
}

void menu_free(Menu *self){
	gf2d_sprite_free(self->backsprite);
	gf2d_sprite_free(self->cursorSprite);
	memset(self, 0, sizeof(Menu));
}

Menu *menu_get_active(){
	return THE_MENU;
}