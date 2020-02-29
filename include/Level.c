#include "Level.h"
#include "gf2d_draw.h"
#include "simple_logger.h"

Level *level_new(char *backgroundFile, SDL_Rect bounds)
{
	Level *level;
	if (!backgroundFile){
		slog("no background file");
		return NULL;
	}
	level = (Level*)gfc_allocate_array(sizeof(Level), 1);
	if (!level){
		return NULL;
	}
	level->background = gf2d_sprite_load_image(backgroundFile);
	gfc_rect_set(level->bounds, bounds.x, bounds.y, bounds.w, bounds.h);
	return level;
}

void level_free(Level *level)
{	
	if (!level){
		return;
	}
	gf2d_sprite_free(level->background);
	free(level);
}

void level_draw(Level *level){
	
	if (!level){
		return;
	}
	gf2d_sprite_draw_image(level->background, vector2d(0, 0));
	gf2d_draw_rect(level->bounds, vector4d(255, 0, 0, 255));
}