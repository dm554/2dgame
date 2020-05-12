#include "simple_logger.h"
#include "PerkMenu.h"
#include "Entity.h"

static int perkscreen = 0;
Menu *perk_menu_new(){
	Menu *self;
	//self = menu_new();
	self = (Menu*)gfc_allocate_array(sizeof(Menu), 1);

	self->cursorPoint = 1;
	self->cursorPointTotal = 2;
	self->backPosition = vector2d(0, 0);
	self->cursorPoint_1 = vector2d(0, 300);
	self->cursorPoint_2 = vector2d(0, 400);
	self->cursorPostion = self->cursorPoint_1;
	self->think = perk_menu_think;
	perkscreen++;
	if (perkscreen < 2){
		self->backsprite = gf2d_sprite_load_image("images/ui/pausemenu/perkchoice1.png");
	}
	else{
		self->backsprite = gf2d_sprite_load_image("images/ui/pausemenu/perkchoice2.png");
	}
	self->cursorSprite = gf2d_sprite_load_image("images/ui/smallarrow.png");
	slog("Menu made");
	menu_set_active(self);
	return self;

}

void perk_menu_think(Menu *self){

	perk_menu_option_select(self->select, self);

}

void perk_menu_option_select(int select, Menu *self){
	switch (select){
	case 0:
		break;
	case 1:
		perk_menu_option_1(self);
		break;
	case 2:
		perk_menu_option_2(self);
		break;
	}
}

void perk_menu_option_1(Menu *self){
	//activate perk
	perk1(perkscreen);
	self->select = 0;
	menu_free(menu_get_active());
	SceneController(2);
}

void perk_menu_option_2(Menu *self){
	//activate perk
	perk2(perkscreen);
	self->select = 0;
	menu_free(menu_get_active());
	SceneController(2);
}

void perk1(int perkscreen){
	if (perkscreen < 2){
		//slow it down
		entity_set_perkspeed(-0.2);
	}
	else{
		entity_set_perkstun(20);
		//stun gun
	}
}

void perk2(int perkscreen){
	if (perkscreen < 2){
		entity_set_perkxp(2);
		//experience required
	}
	else{
		entity_set_perkpower(-1);
		//i can take it
	}
}