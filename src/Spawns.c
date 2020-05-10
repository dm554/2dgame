#include "Spawns.h"

void spawn_all(Vector2D playerPosition, char *backgroundFile, Uint8 stages){
	player_new(playerPosition);
	spawn_grunts(player_get_active());
	spawn_levels(backgroundFile, stages);
}

void spawn_grunts(Entity *player){
	grunt_new(player);
	grunt_new(player);
	grunt2_new(player);
	grunt2_new(player);
	grunt3_new(player);
	grunt3_new(player);
}

void spawn_levels(char *backgroundFile, Uint8 stages){
	level_new(backgroundFile, stages);
}