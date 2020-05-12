#include "simple_logger.h"
#include "PauseMenu.h"
#include "Entity.h"
#include "Level.h"


Menu *pause_menu_new(){
	Menu *self;
	//self = menu_new();
	self = (Menu*)gfc_allocate_array(sizeof(Menu), 1);

	//change these for pause
	self->cursorPoint = 1;
	self->cursorPointTotal = 3;
	self->backPosition = vector2d(0, 0);
	self->cursorPoint_1 = vector2d(250, 160);
	self->cursorPoint_2 = vector2d(250, 280);
	self->cursorPoint_3 = vector2d(250, 400);
	self->cursorPostion = self->cursorPoint_1;
	self->think = pause_menu_think;
	self->backsprite = gf2d_sprite_load_image("images/ui/pausemenu/pausemenu.png");
	self->cursorSprite = gf2d_sprite_load_image("images/ui/smallarrow.png");


	menu_set_active(self);
	return self;

}

void pause_menu_think(Menu *self){

	pause_menu_option_select(self->select, self);

}

void pause_menu_option_select(int select, Menu *self){
	switch (select){
	case 0:
		break;
	case 1:
		pause_menu_option_1(self);
		break;
	case 2:
		pause_menu_option_2(self);
		break;
	case 3:
		pause_menu_option_3(self);
		break;
	}
}

void pause_menu_option_1(Menu *self){
	self->select = 0;
	SceneController(2);
	menu_free(menu_get_active());
	//resume game
}

void pause_menu_option_2(Menu *self){
	//menu_free(menu_get_active());
	//save state
}

void pause_menu_option_3(Menu *self){
	menu_free(menu_get_active());
	entity_free_all();
	level_free(level_get_active());
	SceneController(1);
	//return to main menu
}
