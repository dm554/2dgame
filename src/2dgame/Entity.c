#include <SDL_image.h>
#include <stdlib.h>
#include "simple_logger.h"
#include "Entity.h"
#include "gf2d_draw.h"
#include "Collider.h"
#include "gfc_types.h"


typedef struct{
	
	Uint32 maxEnts;
	Entity *entityList;

}EntityManager;

static EntityManager entity_manager = { 0 };

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
	memset(self, 0, sizeof(Entity));
}

void entity_update(Entity *self)
{
	if (!self)return;
	self->frame = self->frame + 0.1;
	if (self->frame < self->minFrame)self->frame = self->minFrame;
	if (self->frame > self->maxFrame){ self->frame = self->minFrame; self->reset = 1; }
	
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
		self-> scale,
		NULL,
		NULL,
		NULL,
		NULL,
		(Uint32)self->frame);
	gfc_rect_set(rect, self->bodyHitbox.x, self->bodyHitbox.y, self->bodyHitbox.w, self->bodyHitbox.h);
	gf2d_draw_rect(rect, vector4d(64, 64, 255, 255));
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
