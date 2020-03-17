#include "Entity.h"
#include "Player.h"
#include "simple_logger.h"

int collide_rect(SDL_Rect r1, SDL_Rect r2)
{
	if (((r1.x + r1.w) < r2.x) ||
		((r2.x + r2.w) < r1.x) ||
		((r1.y + r1.h) < r2.y) ||
		((r2.y + r2.h) < r1.y))
	{
		return 0;
	
	}
	return 1;
}
