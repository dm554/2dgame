#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "gf2d_sprite.h"
#include "gfc_audio.h"

typedef struct Entity_S
{
	Uint8	_inuse;
	Uint8	type;	//1 = Player, 2 = Enemy, 3 = Neutral Object
	Uint8	health;
	Uint8	reset;
	Uint8	lastAttack; //Attack1, Attack2
	Uint8	forward;
	
	int		level;
	int		xp;
	int		xpcap;

	Sprite	*sprite;
	
	float frame;
	float minFrame;
	float maxFrame;

	float powermodifier;
	float speedmodifier;
	
	Vector2D *scale;
	Vector2D *scalePoint;
	Vector2D position;
	Vector2D velocity;

	int hitstun;
	int hitstunTimer;

	float attacking;
	
	SDL_Rect bodyHitbox;

	Sound *bonk;

	Sprite *digit1;
	Sprite *digit2;

	void(*think)(struct Entity_S *self);
	void(*collide)(struct Entity_S *self);

}Entity;

Entity *entity_new();

static int perkpower;
static float perkspeed;
static int perkstun;
static int perkxp;

void entity_manager_init(Uint32 maxEnts);
void entity_free(Entity *self);
void entity_free_all();
void entity_update_all();
void entity_draw_all();
void entity_collide_check(Entity *self);
void entity_collide(Entity *e1, Entity *e2);

int entity_get_perkpower();
float entity_get_perkspeed();
int entity_get_perkxp();
int entity_get_perkstun();

int entity_set_perkpower(int pp);
float entity_set_perkspeed(float ps);
int entity_set_perkxp(int pxp);
int entity_set_perkstun(int pst);


#endif