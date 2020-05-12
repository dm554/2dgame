#include <SDL_image.h>
#include <stdlib.h>
#include "simple_logger.h"
#include "Entity.h"
#include "gf2d_draw.h"
#include "Collider.h"
#include "Level.h"
#include "gfc_types.h"


typedef struct{
	
	Uint32 maxEnts;
	Entity *entityList;

}EntityManager;

static EntityManager entity_manager = { 0 };

static int perkpower = 0;
static int perkstun = 0;
static int perkxp = 0;
static float perkspeed = 1;

void entity_manager_close()
{
	int i;
	for (i = 0; i < entity_manager.maxEnts; i++)
	{
		if (entity_manager.entityList[i]._inuse)
		{
			entity_free(&entity_manager.entityList[i]);
		}
	}
	entity_manager.maxEnts = 0;
	free(entity_manager.entityList);
	entity_manager.entityList = NULL;
	slog("entity manager closed");
}

void entity_manager_init(Uint32 maxEnts)
{
	if (entity_manager.entityList != NULL)
	{
		//TODO: cleanup
	}
	if (!maxEnts)
	{
		slog("cannot intialize a zero size entity list!");
		return;
	}
	entity_manager.entityList = (Entity *)malloc(sizeof(Entity)* maxEnts);
	if (entity_manager.entityList == NULL)
	{
		slog("failed to allocate %i entities for the entity manager", maxEnts);
		return;
	}
	entity_manager.maxEnts = maxEnts;
	memset(entity_manager.entityList, 0, sizeof(Entity)*maxEnts);
	slog("entity manager initialized");
	atexit(entity_manager_close);
}


Entity *entity_new()
{
	int i;
	for (i = 0; i < entity_manager.maxEnts; i++)
	{
		if (entity_manager.entityList[i]._inuse)continue;
		entity_manager.entityList[i]._inuse = 1;
		return &entity_manager.entityList[i];
	}
	slog("out of open entity slots in memory!");
	return NULL;
}


void entity_free(Entity *self)
{
	if (!self)return;
	gf2d_sprite_free(self->sprite);
	if (self->type = 2)level_get_active()->levelComplete++;
	memset(self, 0, sizeof(Entity));
	
}

void entity_free_all(){
	
	int i;
	for (i = 0; i < entity_manager.maxEnts; i++)
	{
		if (!entity_manager.entityList[i]._inuse)continue;
		entity_free(&entity_manager.entityList[i]);
	}
}

void entity_update(Entity *self)
{
	if (!self)return;
	
	if (!self->attacking || self->forward){
		self->frame = self->frame + 0.1;
		if (self->frame < self->minFrame)self->frame = self->minFrame;
		if (self->frame > self->maxFrame){ self->frame = self->minFrame; self->reset = 1; }
	}
	if (self->attacking && !self->forward){
		self->frame = self->frame - 0.1;
		if (self->frame > self->maxFrame)self->frame = self->maxFrame;
		if (self->frame < self->minFrame){ self->frame = self->maxFrame; self->reset = 1; }
	}

	self->bodyHitbox.x = self->position.x;
	self->bodyHitbox.y = self->position.y;
	entity_collide_check(self);
}

void entity_update_all()
{
	int i;
	for (i = 0; i < entity_manager.maxEnts; i++)
	{
		if (!entity_manager.entityList[i]._inuse)continue;
		if (entity_manager.entityList[i].think)
		{
			entity_manager.entityList[i].think(&entity_manager.entityList[i]);
		}
		entity_update(&entity_manager.entityList[i]);
	}
	
}

void entity_collide(Entity *e1, Entity *e2)
{
	if (collide_rect(e1->bodyHitbox, e2->bodyHitbox))
	{
		if (e1->collide)
		{
			e1->collide(e1, e2);
		}
	}
}

void entity_collide_check(Entity *entity)
{
	int i;
	if (!entity)return;
	for (i = 0; i < entity_manager.maxEnts; i++)
	{
		if (!entity_manager.entityList[i]._inuse)continue;
		if (&entity_manager.entityList[i] == entity)continue;
		entity_collide(entity, &entity_manager.entityList[i]);
	}
}

void entity_draw(Entity *self)
{
	SDL_Rect rect;
	if (self == NULL)
	{
		slog("cannot draw sprite, NULL entity provided!");
		return;
	}
	gf2d_sprite_draw(
		self->sprite,
		self->position,
		self->scale,
		self->scalePoint,
		NULL,
		NULL,
		NULL,
		(Uint32)self->frame);
	gfc_rect_set(rect, self->bodyHitbox.x, self->bodyHitbox.y, self->bodyHitbox.w, self->bodyHitbox.h);
	gf2d_draw_rect(rect, vector4d(64, 64, 255, 255));
	if (self->type == 2){
		grunt_health_display(self);
	}
}

void entity_draw_all()
{
	int i;
	for (i = 0; i < entity_manager.maxEnts; i++)
	{
		if (!entity_manager.entityList[i]._inuse)continue;
		entity_draw(&entity_manager.entityList[i]);
	}
}

Vector2D grunt_get_health(Entity* self){
	//slog("get health");
	int ones = self->health % 10;
	int tens = (self->health - ones) / 10;

	Vector2D healthIcons = vector2d(tens, ones);
	return(healthIcons);
}

void grunt_health_image_set(Vector2D healthicons, Vector2D tenPosition, Vector2D onesPosition, Entity *self){
	//slog("image set");
	int tens = healthicons.x;
	int ones = healthicons.y;

	char *tensPath;
	char *onesPath;

	switch (tens){
	case 1:
		tensPath = "images/UI/Nums/1.png";
		break;
	case 2:
		tensPath = "images/UI/Nums/2.png";
		break;
	case 3:
		tensPath = "images/UI/Nums/3.png";
		break;
	case 4:
		tensPath = "images/UI/Nums/4.png";
		break;
	case 5:
		tensPath = "images/UI/Nums/5.png";
		break;
	case 6:
		tensPath = "images/UI/Nums/6.png";
		break;
	case 7:
		tensPath = "images/UI/Nums/7.png";
		break;
	case 8:
		tensPath = "images/UI/Nums/8.png";
		break;
	case 9:
		tensPath = "images/UI/Nums/9.png";
		break;
	case 0:
		tensPath = "images/UI/Nums/0.png";
		break;
	}

	switch (ones){
	case 1:
		onesPath = "images/UI/Nums/1.png";
		break;
	case 2:
		onesPath = "images/UI/Nums/2.png";
		break;
	case 3:
		onesPath = "images/UI/Nums/3.png";
		break;
	case 4:
		onesPath = "images/UI/Nums/4.png";
		break;
	case 5:
		onesPath = "images/UI/Nums/5.png";
		break;
	case 6:
		onesPath = "images/UI/Nums/6.png";
		break;
	case 7:
		onesPath = "images/UI/Nums/7.png";
		break;
	case 8:
		onesPath = "images/UI/Nums/8.png";
		break;
	case 9:
		onesPath = "images/UI/Nums/9.png";
		break;
	case 0:
		onesPath = "images/UI/Nums/0.png";
		break;
	}


	self->digit1 = gf2d_sprite_load_image(tensPath);
	self->digit2 = gf2d_sprite_load_image(onesPath);

	gf2d_sprite_draw_image(self->digit1, tenPosition);
	gf2d_sprite_draw_image(self->digit2, onesPosition);
}

void grunt_health_display(Entity* self){
	//slog("health display");
	grunt_health_image_set(grunt_get_health(self), vector2d(self->position.x - 15, self->position.y - 20), vector2d(self->position.x + 15, self->position.y -20), self);
}

int entity_get_perkpower(){
	return perkpower;
}

float entity_get_perkspeed(){
	return perkspeed;
}

int entity_get_perkxp(){
	return perkxp;
}

int entity_get_perkstun(){
	return perkstun;
}

int entity_set_perkpower(int pp){
	perkpower += pp;
}

float entity_set_perkspeed(float ps){
	perkspeed += ps;
}

int entity_set_perkxp(int pxp){
	perkxp += pxp;
}

int entity_set_perkstun(int pst){
	perkstun += pst;
}
