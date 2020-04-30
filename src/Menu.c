#include <SDL_image.h>
#include <stdlib.h>
#include "simple_logger.h"
#include "Menu.h"
#include "gf2d_draw.h"
#include "gfc_types.h"


void menu_update(Menu *self, Entity *player){
	cursor_handler(self);
	menu_draw(self);
	self->option(self->select);
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
	gf2d_sprite_draw_image(self->backsprite, self->backPosition);
	gf2d_sprite_draw_image(self->cursorSprite, self->cursorPostion);
}

void menu_free(Menu *self){
	gf2d_sprite_free(self->backsprite);
	gf2d_sprite_free(self->cursorSprite);
	memset(self, 0, sizeof(Menu));
}