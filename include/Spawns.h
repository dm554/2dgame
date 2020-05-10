#include "Entity.h"
#include "Player.h"
#include "Grunt.h"
#include "Grunt2.h"
#include "Grunt3.h"
#include "Level.h"

void spawn_all(Vector2D playerPosition, char *backgroundFile, Uint8 stages);

void spawn_grunts(Entity *player);

void spawn_levels(char *backgroundFile, Uint8 stages);
