//frprintf

#include <iostream>     //includes the header file iostream
using namespace std;    //tells the compiler to use the std library

#include <allegro5/allegro.h>	//ALLEGRO
#include <allegro5/allegro_native_dialog.h>	//ALLEGRO dialog
#include <allegro5/allegro_font.h>	//ALLEGRO Fonts
#include <allegro5/allegro_ttf.h>	//ALLEGRO True Type Fonts (TTF) Support
#include <allegro5/allegro_primitives.h> //ALLEGRO primitives

#include "objects1.h"



//globals
const int DisplayWidth = 1200;
const int DisplayHeight = 600;
const int FPS = 60;
const int NumPlyr1Bullets = 10;
const int NumComets = 10;

bool keys[5]{ false, false, false, false, false };	//array for key states


//function prototypes - C++ requires functions to be declared before they are called and these are called function prototypes
void InitShip(SpaceShip &someSpaceShip);	//declare/fwd define & pass by reference
void DrawShip(SpaceShip &someSpaceShip);
void MoveShipUp(SpaceShip &someSpaceShip);
void MoveShipDown(SpaceShip &someSpaceShip);
void MoveShipLeft(SpaceShip &someSpaceShip);
void MoveShipRight(SpaceShip &someSpaceShip);
void InitBullet(Bullet someBullets[], int NumBullets);
void FireBullet(Bullet someBullets[], int NumBullets, SpaceShip &someSpaceShip);
void DrawBullet(Bullet someBullets[], int NumBullets);	//
void UpdateBullet(Bullet someBullets[], int NumBullets);
void InitComet(Comet comets[], int size);
void SpawnComet(Comet comets[], int size);
void DrawComet(Comet comets[], int size);
void UpdateComet(Comet comets[], int size);
void CollideBullet(Bullet PlyrBullets[], int NumBullets, Comet comets[], int cometSize, SpaceShip &someSpaceShip);
void CollideComet(Comet comets[], int cometSize, SpaceShip &someSpaceShip);							//cometSize is NumComets kinda... Active Comets might be a better name


int main(void)
{
	//primitive variables
	bool quitapp = false;
	bool redraw = true;	//the bool named 'redraw' is used to ensure we render per the timer, but to move the rendering outside of the timer event handler
	bool isGameOver = false;

	//object variables
	//SpaceShip plyr1;	//plyr1 is an object of structure type SpaceShip
	//SpaceShip plyr2;	//plyr2 is an object of structure type SpaceShip
	Bullet PlyrBullets[NumPlyr1Bullets]; //PlyrBullets is an array of type Bullet, and the size of the array is... NumPlyr1Bullets
	Comet comets[NumComets];
	// !!! Thanks for the great videos! I suggest you to change Bullet bullets[5]; to Bullet bullets[NUM_BULLETS]; and use sizeof(bullet) besides of int size! :)


	//allegro variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_que = NULL;
	ALLEGRO_TIMER *gamelooptimer = NULL;


	//initialize allegro
	if (!al_init())
	{
		al_show_native_message_box(NULL, "ERROR", "ERROR", "failed to initialize allegro!", NULL, NULL);
		return -1;
		/*Upon error the al_show_native_message_box does not display the specified error message unless text is specified for the third parameter.
		for example... al_show_native_message_box(NULL, “ERROR”, “ERROR”,“Failed to initialize allegro!”, NULL, NULL);*/
	}

	//setup & initialize allegro display
	al_set_new_display_option(26, 1, 1);	//int option, int value, int importance... 
	/*
	the line above forces vsync to be on and sets the option, valu and importance as noted below
	option = 26 = ALLEGRO_VSYNC
	value = 1 means force on... 2 means forced off and 0 means default behaviour that may be on or off
	importance = 1 means ALLEGRO_REQUIRE... Other options are 2 = ALLEGRO_SUGGEST and 0 = ALLEGRO_DONTCARE
	*/
	display = al_create_display(DisplayWidth, DisplayHeight);
	if (!display)
	{
		al_show_native_message_box(NULL, "ERROR", "ERROR!", "failed to initialize display!", NULL, NULL);
		return -1;
	}


	//initialize allegro addons
	al_install_keyboard();
	al_install_mouse();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();

	//At some time I should add error checking to these.


	//setup fonts
	//ALLEGRO_FONT* font = al_create_builtin_font();
	ALLEGRO_FONT *bebasneuereg24pt = al_load_font("BebasNeue_Reg.ttf", 24, 0);
	//ALLEGRO_FONT *bebasneuereg16pt = al_load_font("BebasNeue_Reg.ttf", 16, 0);


	//initialize objects
	srand(time(NULL));	//seed the random number generator
	InitShip(plyr1);	//initialize ship for plyr1
	//InitShip(plyr2);	//initialize ship for plyr2
	InitBullet(PlyrBullets, NumPlyr1Bullets);	//initialize bullets for plyr1
	InitComet(comets, NumComets);	//initialize comets


	event_que = al_create_event_queue();
	gamelooptimer = al_create_timer(1.0 / FPS);		//declare???, create timer and set interval = 1 second / FPS... 1/60 = 60 FPS
	if (!gamelooptimer) 
	{
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	al_register_event_source(event_que, al_get_keyboard_event_source());	//get keyboard event and register to the applicable queue
	al_register_event_source(event_que, al_get_mouse_event_source());	//get mouse event and register to the applicable queue
	al_register_event_source(event_que, al_get_display_event_source(display));
	al_register_event_source(event_que, al_get_timer_event_source(gamelooptimer));	//register timer event to the event_que


	
	al_start_timer(gamelooptimer);	//start timer and main loop immediately follows
	while (!quitapp)	//while variable quitapp is false
	{
		//al_wait_for_vsync();	//commented out as this always occurs once when flipdisplay
		ALLEGRO_EVENT event; //Declare event var
		//std::cout << "start of loop" << endl;
		al_wait_for_event(event_que, &event);    //wait for an event from event_que and send it the address of event

		if (event.type == ALLEGRO_EVENT_TIMER)	//update position of player every frame
		{
			redraw = true;	//the bool named 'redraw' is used to ensure we render per the timer, but the rendering is done outside of the timer event handler
			if (keys[UP])
				MoveShipUp(plyr1);
			if (keys[DOWN])
				MoveShipDown(plyr1);
			if (keys[LEFT])
				MoveShipLeft(plyr1);
			if (keys[RIGHT])
				MoveShipRight(plyr1);
			/*if (keys[SPACE])
				FireBullet(bullets, NumBullets, plyr1);*/

			if (!isGameOver)
			{
				UpdateBullet(PlyrBullets, NumPlyr1Bullets);
				SpawnComet(comets, NumComets);
				UpdateComet(comets, NumComets);
				CollideBullet(PlyrBullets, NumPlyr1Bullets, comets, NumComets, plyr1);
				CollideComet(comets, NumComets, plyr1);

				if (plyr1.lives <= 0)
				{
				isGameOver = true;
				}
			}
			//std::cout << "in timer " << redraw << endl;	
			//al_draw_textf(bebasneuereg24pt, al_map_rgb(255, 0, 255), display_width / 2, 500, ALLEGRO_ALIGN_CENTRE, "Frames = %d", redraw);
			//NEED TO FIND HOW TO PRINT TO CONSOLE OR TO FILE - The contents of the EVENT CUE
		}
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (event.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				//count = count + 1000;
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				FireBullet(PlyrBullets, NumPlyr1Bullets, plyr1);
				break;
			case ALLEGRO_KEY_ESCAPE:
				//std::cout << "ESC_KEY_DOWN" << endl;
				quitapp = true;
				break;
			}
		}
		else if (event.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (event.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			case ALLEGRO_KEY_ESCAPE:
				//std::cout << "ESC_KEY_UP" << endl;
				quitapp = true;
				break;
			}
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)	//detect the display window being closed
		{
			quitapp = true;
		}



		//Rendertime
		if (redraw && al_is_event_queue_empty(event_que)) //only redraw if timer event fired and event_que is empty so we know the new position is representative of input
		{
			//std::cout << "in render " << redraw << endl;
			redraw = false;	//the bool named 'redraw' is used to ensure we render per the timer, but to move the rendering outside of the timer event handler

			if (!isGameOver)
			{
				DrawShip(plyr1);
				//DrawShip(plyr2);
				DrawBullet(PlyrBullets, NumPlyr1Bullets);
				DrawComet(comets, NumComets);
				al_draw_textf(bebasneuereg24pt, al_map_rgb(255, 0, 255), 50, DisplayHeight-30, ALLEGRO_ALIGN_CENTRE, "LIVES: %i", plyr1.lives);
				al_draw_textf(bebasneuereg24pt, al_map_rgb(255, 0, 255), DisplayWidth-150, DisplayHeight-30, ALLEGRO_ALIGN_CENTRE, "SCORE: %i", plyr1.score);
			}
			else
			{
				al_draw_textf(bebasneuereg24pt, al_map_rgb(255, 0, 255), DisplayWidth/2, DisplayHeight/2, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
				al_draw_textf(bebasneuereg24pt, al_map_rgb(255, 0, 255), DisplayWidth/2, DisplayHeight/2+150, ALLEGRO_ALIGN_CENTRE, "FINAL SCORE: %i", plyr1.score);
			}

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));	//Clear the back buffer
			
			//al_draw_filled_rectangle(plyrx - 10, plyry - 10, plyrx + 10, plyry + 10, al_map_rgb(255, 0, 255));
			//al_draw_textf(bebasneuereg24pt, al_map_rgb(255, 0, 255), display_width / 2, display_height / 2, ALLEGRO_ALIGN_CENTRE, "Frames = %i", count);
		}
		//std::cout << "end of loop" << endl;
	}




	//cleanup
	al_destroy_timer(gamelooptimer);
	al_destroy_event_queue(event_que);
	al_destroy_display(display);	//Cleanup display... created via al_create_display
	al_destroy_font(bebasneuereg24pt);
	//al_destroy_font(bebasneuereg16pt);

	return true;
}









void InitShip(SpaceShip &someSpaceShip)	//InitShip Function, don't return anything because its doing it by reference so all changes stay
{
	std::cout << "InitShip" << endl;
	someSpaceShip.id = PLYR;
	someSpaceShip.posx = 20;
	someSpaceShip.posy = DisplayHeight / 2;
	someSpaceShip.speed = 5;
	someSpaceShip.lives = 3;
	someSpaceShip.boundx = 6;
	someSpaceShip.boundy = 7;
	someSpaceShip.score = 0;
	std::cout << "plyr1.lives = " << plyr1.lives;
}


void DrawShip(SpaceShip &someSpaceShip)	//DrawShip Function, don't return anything because its doing it by reference so all changes stay
{
	al_draw_filled_rectangle(someSpaceShip.posx, someSpaceShip.posy - 9, someSpaceShip.posx + 10, someSpaceShip.posy - 7, al_map_rgb(255, 0, 0));
	al_draw_filled_rectangle(someSpaceShip.posx, someSpaceShip.posy + 9, someSpaceShip.posx + 10, someSpaceShip.posy + 7, al_map_rgb(255, 0, 0));
	al_draw_filled_triangle(someSpaceShip.posx - 12, someSpaceShip.posy - 17, someSpaceShip.posx + 12, someSpaceShip.posy, someSpaceShip.posx - 12, someSpaceShip.posy + 17, al_map_rgb(0, 255, 0));
	al_draw_filled_rectangle(someSpaceShip.posx - 12, someSpaceShip.posy - 2, someSpaceShip.posx + 15, someSpaceShip.posy + 2, al_map_rgb(0, 0, 255));
}


void MoveShipUp(SpaceShip &someSpaceShip)
{
	someSpaceShip.posy -= someSpaceShip.speed;
	if (someSpaceShip.posy < 17)
		someSpaceShip.posy = 17;
}


void MoveShipDown(SpaceShip &someSpaceShip)
{
	someSpaceShip.posy += someSpaceShip.speed;
	if (someSpaceShip.posy > DisplayHeight - 17)
		someSpaceShip.posy = DisplayHeight - 17;
}


void MoveShipLeft(SpaceShip &someSpaceShip)
{
	someSpaceShip.posx -= someSpaceShip.speed;
	if (someSpaceShip.posx < 20)
		someSpaceShip.posx = 20;
}


void MoveShipRight(SpaceShip &someSpaceShip)
{
	someSpaceShip.posx += someSpaceShip.speed;
	if (someSpaceShip.posx > 300)
		someSpaceShip.posx = 300;
}


void InitBullet(Bullet someBullets[], int NumBullets)	//
{
	for (int i = 0; i < NumBullets; i++)
	{
		someBullets[i].id = BULLET;
		someBullets[i].speed = 10;
		someBullets[i].live = false;
	}
}


void FireBullet(Bullet someBullets[], int NumBullets, SpaceShip &someSpaceShip)
{
	for (int i = 0; i < NumBullets; i++)
	{
		if (!someBullets[i].live)
		{
			someBullets[i].posx = someSpaceShip.posx + 17;
			someBullets[i].posy = someSpaceShip.posy;
			someBullets[i].live = true;
			break;
		}
	}
}


void DrawBullet(Bullet someBullets[], int NumBullets)	//
{
	for (int i = 0; i < NumBullets; i++)
	{
		if (someBullets[i].live)
			al_draw_filled_circle(someBullets[i].posx, someBullets[i].posy, 2, al_map_rgb(255, 255, 255));
	}
}


void UpdateBullet(Bullet someBullets[], int NumBullets)
{
	for (int i = 0; i < NumBullets; i++)
	{
		if (someBullets[i].live)
		{
			someBullets[i].posx += someBullets[i].speed;
			if (someBullets[i].posx > DisplayWidth)
				someBullets[i].live = false;
		}
	}
}


void CollideBullet(Bullet someBullets[], int NumBullets, Comet comets[], int cometSize, SpaceShip &someSpaceShip)
{
	for (int i = 0; i < NumBullets; i++)
	{
		if (someBullets[i].live)
		{
			for (int j = 0; j < cometSize; j++)
			{
				if (comets[j].live)
				{
					if (someBullets[i].posx > (comets[j].posx - comets[j].boundx) &&
						someBullets[i].posx < (comets[j].posx + comets[j].boundx) &&
						someBullets[i].posy > (comets[j].posy - comets[j].boundy) &&
						someBullets[i].posy < (comets[j].posy + comets[j].boundy))
					{
						someBullets[i].live = false;
						comets[j].live = false;
						someSpaceShip.score++;
					}
				}
			}
		}
	}
}



void InitComet(Comet comets[], int size)
{
	for (int i = 0; i < size; i++)
	{
		comets[i].id = ENEMY;
		comets[i].live = false;
		comets[i].speed = 5;
		comets[i].boundx = 18;
		comets[i].boundy = 18;
	}
}


void SpawnComet(Comet comets[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (!comets[i].live)
		{
			if (rand() % 50 == 0)
			{
				comets[i].live = true;
				comets[i].posx = DisplayWidth;
				comets[i].posy = 30 + rand() % (DisplayHeight - 60);

				break;
			}
		}
	}
}


void DrawComet(Comet comets[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (comets[i].live)
		{
			al_draw_filled_circle(comets[i].posx, comets[i].posy, 20, al_map_rgb(255, 0, 0));
		}
	}
}


void UpdateComet(Comet comets[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (comets[i].live)
		{
			comets[i].posx -= comets[i].speed;

			if (comets[i].posx < 0)
				comets[i].live = false;
		}
	}
}


void CollideComet(Comet comets[], int cometSize, SpaceShip &someSpaceShip)
{
	for (int i = 0; i < cometSize; i++)
	{
		if (comets[i].live)
		{
			if (comets[i].posx - comets[i].boundx < someSpaceShip.posx + someSpaceShip.boundx &&
				comets[i].posx + comets[i].boundx > someSpaceShip.posx - someSpaceShip.boundx &&
				comets[i].posy - comets[i].boundy < someSpaceShip.posy + someSpaceShip.boundy &&
				comets[i].posy + comets[i].boundy > someSpaceShip.posy - someSpaceShip.boundy)
			{
				someSpaceShip.lives--;
				comets[i].live = false;
			}
			/*else if (comets[i].posx < 0)	//This is disabled as I decided I didn't want a game rule that makes the player lsoe a life for each comet the player fails to shoot down
			{
				comets[i].live = false;
				someSpaceShip.lives--;
			}*/
		}
	}
}
