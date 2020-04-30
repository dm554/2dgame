#include <SDL.h>
#include "Entity.h"
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"
#include "Player.h"
#include "Level.h"
#include "Axel.h"
#include "boss3.h"
#include "ironboss.h"
#include <SDL_image.h>
#include <stdlib.h>

static int genUpdates = 1;
//creates a function of data type Entity
Entity *newEnt(){
	Entity *self;
	self = entity_new();
	if (!self)return NULL;
	self->sprite = gf2d_sprite_load_all("images/space_bug.png",
		128,
		128,
		16);
	return self;
}

void SceneController(int sceneNo){
	
	switch (sceneNo)
	{
	//Main Menu
	case 1:
		genUpdates = 0;
		level_free(level_get_active());
		entity_free_all();
		//create menu object here
		break;
	//In Game
	case 2:
		genUpdates = 1;
		break;
	//Pause Menu
	case 3: 
		genUpdates = 0;
		//create menu object here
		break;
	}
	
}

int main(int argc, char * argv[])
{
    /*variable declarations*/
    int done = 0;
    const Uint8 * keys;
    Sprite *sprite;
	Sprite *healthbar;
	Sprite *healthicon;

    
    int mx,my;
    float mf = 0;
    Sprite *mouse;
    Vector4D mouseColor = {255,100,255,200};
    

	Entity *player1;
	Entity *grunt1;
	Entity *grunt2;
	Entity *grunt3;
	Entity *grunt4;
	Entity *grunt5;
	Entity *grunt6;
	Entity *box;
	Uint8 currentStage;
	Level *test;
	Level *level2;
	Level *level3;
	SDL_Rect bounds = { 0, 0, 1200, 720 };
    /*program initializtion*/
    init_logger("gf2d.log");
    slog("---==== BEGIN ====---");
    gf2d_graphics_initialize(
        "gf2d",
        1200,
        720,
        1200,
        720,
        vector4d(0,0,0,255),
        0);
    gf2d_graphics_set_frame_delay(16);
    gf2d_sprite_init(1024);
    SDL_ShowCursor(SDL_DISABLE);
	entity_manager_init(100);
    
    /*demo setup*/
    //sprite = gf2d_sprite_load_image("images/backgrounds/Stage1ss.png");
    mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16);
	healthbar = gf2d_sprite_load_image("images/ui/healthbackground.png");
	
	player1 = player_new(vector2d(1100,1100));
	grunt1 = grunt_new(player1);
	grunt2 = grunt_new(player1);
	grunt3 = grunt3_new(player1);
	grunt4 = grunt3_new(player1);
	grunt5 = grunt2_new(player1);
	grunt6 = grunt2_new(player1);
	//box = box_new();

	test = level_new("images/backgrounds/Stage1ss.png", bounds, 2);//was at 5
	int screencount = 0;
	int currentLevel = 1;
	slog("player ent made");
    /*main game loop*/
    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        /*update things here*/
        SDL_GetMouseState(&mx,&my);
        mf+=0.1;
        if (mf >= 16.0)mf = 0;
        
		if (genUpdates){
			//////////////////////////////////////////////Level Controller//////////////////////////////////////////////////
			level_mover(level_get_active(), player1);
			if (level_get_active()->spawnStage){
				slog("spawnstage");
				if (level_get_active()->maxStages == level_get_active()->currentStage){
					//spawn boss here
					slog("boss spawn");
					level_get_active()->spawnStage = 0;
					if (currentLevel == 1){
						Entity *boss1;
						boss1 = axel_new(player1);
					}
					if (currentLevel == 2){
						Entity *boss2;
						boss2 = iron_new(player1);
					}
					if (currentLevel == 3){
						Entity *boss3;
						boss3 = boss3_new(player1);
					}
				}
				if (level_get_active()->currentStage < level_get_active()->maxStages){
					level_get_active()->currentStage++;
					Entity *grunt1;
					Entity *grunt2;
					Entity *grunt3;
					Entity *grunt4;
					Entity *grunt5;
					Entity *grunt6;
					//Entity *box;
					grunt1 = grunt_new(player1);
					grunt2 = grunt_new(player1);
					grunt3 = grunt3_new(player1);
					grunt4 = grunt3_new(player1);
					grunt5 = grunt2_new(player1);
					grunt6 = grunt2_new(player1);
					//box = box_new();
					level_get_active()->spawnStage = 0;
				}

			}
			if (level_get_active()->winCon){
				currentLevel++;
				level_free(level_get_active());
				if (currentLevel == 2){
					level2 = level_new("images/backgrounds/Stage2.png", bounds, 2);//4
					level_get_active()->spawnStage = 1;
					player1->health += 40;
					//initialize next level here
				}
				if (currentLevel == 3){
					level3 = level_new("images/backgrounds/Stage3.png", bounds, 1);
					level_get_active()->spawnStage = 1;
					player1->health += 30;
					//initialize next level here
				}
			}
			/////////////////////////////////////////////Level Controller Done//////////////////////////////////////////////////

			entity_update_all();
		}
        
		gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //backgrounds drawn first
		
		if (genUpdates){
			level_draw(level_get_active());
			//gf2d_sprite_draw_image(sprite,vector2d(0,0));
			//entities second
			entity_draw_all();
			//UI elements last
			gf2d_sprite_draw(
				mouse,
				vector2d(mx, my),
				NULL,
				NULL,
				NULL,
				NULL,
				&mouseColor,
				(int)mf);
			//Health UI
			gf2d_sprite_draw_image(healthbar, vector2d(0, 10));
			player_health_display(player1);
		}
        gf2d_grahics_next_frame();// render current draw frame and skip to the next frame
		
		//draw menus here

        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
        //slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
    }
    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/
