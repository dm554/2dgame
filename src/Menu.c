#include <SDL_image.h>
#include <stdlib.h>
#include "simple_logger.h"
#include "Menu.h"
#include "MainMenu.h"
#include "gf2d_draw.h"
#include "gf2d_sprite.h"
#include "gfc_types.h"
#include "PauseMenu.h"

static Menu *THE_MENU = NULL;
static int cursorTimer = 0;
static int buttonTimer = 0;
static int genUpdates = 0;

void menu_update(Menu *self){
	slog("cursor handler");
	cursor_handler(self);
	slog("draw");
	menu_draw(self);
	self->think(self);
}

void cursor_handler(Menu *self){
	Uint8 *buttons = SDL_GetKeyboardState(NULL);
	
	buttonTimer++;

	if (buttonTimer > 1){
		buttonTimer = 0;
		return;
	}

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
	if (cursorTimer < 3){
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

void menu_set_active(Menu *activeMenu){
	THE_MENU = activeMenu;
}

Menu *menu_get_active(){
	return THE_MENU;
}

int get_genUpdates(){
	return genUpdates;
}

void SceneController(int sceneNo, Menu *menu){

	switch (sceneNo)
	{
	case 1:
		{
			Menu *mainmenu = main_menu_new();
		}
		genUpdates = 0;
		break;
		//Main Menu
	case 2:
		genUpdates = 1;
		break;
		//Gameplay
	case 3:
		{
			Menu *pausemenu = pause_menu_new();
		}
		genUpdates = 0;
		//Pause Menu
		break;
	case 4:
		{
			Menu *upgrademenu = upgrade_menu_new();
		}
		genUpdates = 0;
		break;
		//Stat Menu
	case 5:
		{
			Menu *perkmenu = perk_menu_new();
		}
		//Perk Menu
		break;
	}
}