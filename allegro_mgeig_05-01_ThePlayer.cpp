/*#include header files... its not clear if these should use a / or \      */

#include <iostream>     //includes the header file iostream
using namespace std;    //tells the compiler to use the std library


#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include "objects1.h"

//enum KEYS { UP, DOWN, LEFT, RIGHT };	//enum to specify the array



//globals
const int DisplayWidth = 800;
const int DisplayHeight = 400;


SpaceShip plyr1;	//plyr1 is a SpaceShip


//function prototypes
void InitShip(SpaceShip test);	//declare/fwd define & pass by reference
void DrawShip(SpaceShip &test);	//declare/fwd define & pass by reference



int main(void)
{

	//primitive variable
	bool done = false;


	//object variables
	


	//initialize allegro
	if (!al_init())
	{
		al_show_native_message_box(NULL, "ERROR", "ERROR", "failed to initialize allegro!", NULL, NULL);
		return -1;

		/*It seems that upon error the al_show_native_message_box does not display the specified error message if you do not specify a text for the third parameter.
		Well, at least on my system it does not, so I did this:
		al_show_native_message_box(NULL, “ERROR”, “ERROR”,“Failed to initialize allegro!”, NULL, NULL);*/
	}


	//initialize allegro display
	ALLEGRO_DISPLAY *display = al_create_display(DisplayWidth, DisplayHeight);
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


	//initialize functions?
	InitShip(plyr1);	//initialize




	/*
	int FPS = 60;
	//int plyrx = display_width / 2;
	//int plyry = display_height / 2;
	bool keys[4]{ false, false, false, false };	//array for key states

	ALLEGRO_TIMER* looptimer = al_create_timer(1.0 / 60.0);		//declare???, create timer and set interval = 1 second / FPS... 1/60 = 60 FPS
	ALLEGRO_EVENT_QUEUE* event_que = al_create_event_queue();

	al_register_event_source(event_que, al_get_keyboard_event_source());	//get keyboard event and register to the applicable queue
	al_register_event_source(event_que, al_get_mouse_event_source());	//get mouse event and register to the applicable queue
	al_register_event_source(event_que, al_get_display_event_source(display));
	al_register_event_source(event_que, al_get_timer_event_source(looptimer));	//register timer event to the event_que
	*/




	//05-01

//ALLEGRO_EVENT event; //Declare event var
//al_start_timer(looptimer);	//start timer
	while (!done)	//while variable done is false
	{
		DrawShip(plyr1);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));	//Clear the back buffer
	}






	//Cleanup
	al_destroy_display(display);	//Cleanup display... created via al_create_display
	//al_destroy_event_queue(event_que);
	//al_destroy_timer(looptimer);
	al_destroy_font(bebasneuereg24pt);
	al_destroy_font(bebasneuereg16pt);



	return 0;

}




void InitShip(SpaceShip test)	//InitShip Function, don't return anything because its doing it by reference so all changes stay
{
	std::cout << "InitShip" << endl;
	test.id = PLYR;
	test.posx = 20;
	test.posy = DisplayHeight / 2;
	test.speed = 5;
	test.lives = 3;
	test.boundx = 6;
	test.boundy = 7;
	test.score = 0;
	std::cout << "plyr1.lives = " << plyr1.lives;
}


void DrawShip(SpaceShip &test)	//DrawShip Function, don't return anything because its doing it by reference so all changes stay
{
	al_draw_filled_rectangle(test.posx, test.posy - 9, test.posx + 10, test.posy - 7, al_map_rgb(255, 0, 0));
	al_draw_filled_rectangle(test.posx, test.posy + 9, test.posx + 10, test.posy + 7, al_map_rgb(255, 0, 0));
	al_draw_filled_triangle(test.posx - 12, test.posy - 17, test.posx + 12, test.posy, test.posx - 12, test.posy + 17, al_map_rgb(0, 255, 0));
	al_draw_filled_rectangle(test.posx - 12, test.posy - 2, test.posx + 15, test.posy + 2, al_map_rgb(0, 0, 255));
}