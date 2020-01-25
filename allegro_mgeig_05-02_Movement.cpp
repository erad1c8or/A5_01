
#include <iostream>     //includes the header file iostream
using namespace std;    //tells the compiler to use the std library

#include <allegro5/allegro.h>	//ALLEGRO
#include <allegro5/allegro_native_dialog.h>	//ALLEGRO dialog
#include <allegro5/allegro_font.h>	//ALLEGRO Fonts
#include <allegro5/allegro_ttf.h>	//ALLEGRO True Type Fonts (TTF) Support
#include <allegro5/allegro_primitives.h> //ALLEGRO primitives

#include "objects1.h"



//globals
const int display_width = 800;
const int display_height = 400;
int FPS = 60;
bool keys[4]{ false, false, false, false };	//array for key states
bool quitapp = false;
bool redraw = true;	//the bool named 'redraw' is used to ensure we render per the timer, but to move the rendering outside of the timer event handler
//int count = 1;
//int testing = 0;


//function prototypes - C++ requires functions to be declared before they are called and these are called function prototypes
void InitShip(SpaceShip &plyr1);	//declare/fwd define & pass by reference
void DrawShip(SpaceShip &plyr1);	//declare/fwd define & pass by reference
void MoveShipUp(SpaceShip &plyr1);
void MoveShipDown(SpaceShip &plyr1);
void MoveShipLeft(SpaceShip &plyr1);
void MoveShipRight(SpaceShip &plyr1);





int main(void)
{
	//primitive variables
	//bool done = false;

	//object variables
	//SpaceShip plyr1;	//plyr1 is an object of structure type SpaceShip
	

	//initialize allegro
	if (!al_init())
	{
		al_show_native_message_box(NULL, "ERROR", "ERROR", "failed to initialize allegro!", NULL, NULL);
		return -1;
		/*Upon error the al_show_native_message_box does not display the specified error message unless text is specified for the third parameter.
		for example... al_show_native_message_box(NULL, “ERROR”, “ERROR”,“Failed to initialize allegro!”, NULL, NULL);*/
	}

	//initialize allegro display
	ALLEGRO_DISPLAY *display = al_create_display(display_width, display_height);
	if (!display)
	{
		al_show_native_message_box(NULL, "ERROR", "ERROR!", "failed to initialize display!", NULL, NULL);
		return -1;
	}

	//initialize allegro addons
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();


	//Setup fonts
	//ALLEGRO_FONT* font = al_create_builtin_font();
	ALLEGRO_FONT *bebasneuereg24pt = al_load_font("BebasNeue_Reg.ttf", 24, 0);
	ALLEGRO_FONT *bebasneuereg16pt = al_load_font("BebasNeue_Reg.ttf", 16, 0);


	//initialize objects
	InitShip(plyr1);	//initialize


	ALLEGRO_TIMER* gamelooptimer = al_create_timer(1.0 / 60.0);		//declare???, create timer and set interval = 1 second / FPS... 1/60 = 60 FPS
	ALLEGRO_EVENT_QUEUE* event_que = al_create_event_queue();

	al_register_event_source(event_que, al_get_keyboard_event_source());	//get keyboard event and register to the applicable queue
	al_register_event_source(event_que, al_get_mouse_event_source());	//get mouse event and register to the applicable queue
	al_register_event_source(event_que, al_get_display_event_source(display));
	al_register_event_source(event_que, al_get_timer_event_source(gamelooptimer));	//register timer event to the event_que





	while (!quitapp)	//while variable quitapp is false
	{
		ALLEGRO_EVENT event; //Declare event var
		al_start_timer(gamelooptimer);	//start timer
		{
			//std::cout << "start of loop" << endl;
			al_wait_for_event(event_que, &event);    //wait for an event from event_que and send it the address of event


			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)	//detect the display window being closed
			{
				quitapp = true;
			}


			else if (event.type == ALLEGRO_EVENT_TIMER)	//update position of player every frame
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
				case ALLEGRO_KEY_ESCAPE:
					std::cout << "ESC_KEY_UP" << endl;
					quitapp = true;
					break;
				}
			}


			//if (al_is_event_queue_empty(event_que) == true)
				//std::cout << "event_que is empty" << event_que << endl;
				//testing = 100;
			//if (al_is_event_queue_empty(event_que) == false)
				//std::cout << "not empty event_que is not empty " << event_que << endl;
				//testing = 0;
			if (redraw && al_is_event_queue_empty(event_que)) //only redraw if plyr position has changed and event_que is empty so we know the new position is representative of input
			{
				//std::cout << "in render " << redraw << endl;
				redraw = false;	//the bool named 'redraw' is used to ensure we render per the timer, but to move the rendering outside of the timer event handler

				//al_draw_textf(bebasneuereg24pt, al_map_rgb(255, 0, 255), display_width / 2, 600, ALLEGRO_ALIGN_CENTRE, "Frames = %d", redraw);
				//count = count + 1;

				DrawShip(plyr1);
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));	//Clear the back buffer

				//al_draw_filled_rectangle(plyrx - 10, plyry - 10, plyrx + 10, plyry + 10, al_map_rgb(255, 0, 255));
				//al_draw_textf(bebasneuereg24pt, al_map_rgb(255, 0, 255), display_width / 2, display_height / 2, ALLEGRO_ALIGN_CENTRE, "Frames = %i", count);
				//al_flip_display();
				//al_clear_to_color(al_map_rgb(0, 0, 0));	//Clear the back buffer
			}
			//std::cout << "end of loop" << endl;
		}
	}




	//Cleanup
	al_destroy_display(display);	//Cleanup display... created via al_create_display
	al_destroy_event_queue(event_que);
	al_destroy_timer(gamelooptimer);
	al_destroy_font(bebasneuereg24pt);
	al_destroy_font(bebasneuereg16pt);

	return true;
}









void InitShip(SpaceShip &plyr1)	//InitShip Function, don't return anything because its doing it by reference so all changes stay
{
	plyr1.id = PLYR;
	plyr1.posx = 20;
	plyr1.posy = display_height / 2;
	plyr1.speed = 7;
	plyr1.lives = 3;
	plyr1.boundx = 6;
	plyr1.boundy = 7;
	plyr1.score = 0;
}


void DrawShip(SpaceShip &plyr1)	//DrawShip Function, don't return anything because its doing it by reference so all changes stay
{
	al_draw_filled_rectangle(plyr1.posx, plyr1.posy - 9, plyr1.posx + 10, plyr1.posy - 7, al_map_rgb(255, 0, 0));
	al_draw_filled_rectangle(plyr1.posx, plyr1.posy + 9, plyr1.posx + 10, plyr1.posy + 7, al_map_rgb(255, 0, 0));
	al_draw_filled_triangle(plyr1.posx - 12, plyr1.posy - 17, plyr1.posx + 12, plyr1.posy, plyr1.posx - 12, plyr1.posy + 17, al_map_rgb(0, 255, 0));
	al_draw_filled_rectangle(plyr1.posx - 12, plyr1.posy - 2, plyr1.posx + 15, plyr1.posy + 2, al_map_rgb(0, 0, 255));
}



void MoveShipUp(SpaceShip &plyr1)
{
	plyr1.posy -= plyr1.speed;
	if (plyr1.posy < 17)
		plyr1.posy = 17;
}


void MoveShipDown(SpaceShip &plyr1)
{
	plyr1.posy += plyr1.speed;
	if (plyr1.posy > display_height-17)
		plyr1.posy = display_height-17;
}


void MoveShipLeft(SpaceShip &plyr1)
{
	plyr1.posx -= plyr1.speed;
	if (plyr1.posx < 20)
		plyr1.posx = 20;
}


void MoveShipRight(SpaceShip &plyr1)
{
	plyr1.posx += plyr1.speed;
	if (plyr1.posx > 300)
		plyr1.posx = 300;
}
