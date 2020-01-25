
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
int InitAllegro();
int InitAllegroDisplay();
void InitAllegroAddonsandSetupFonts();





int main(void)
{
	InitAllegro();
	InitAllegroDisplay();
	InitAllegroAddonsandSetupFonts();


	//Cleanup
	//al_destroy_display(display);	//Cleanup display... created via al_create_display
	//al_destroy_event_queue(event_que);
	//al_destroy_timer(gamelooptimer);
	//al_destroy_font(bebasneuereg24pt);
	//al_destroy_font(bebasneuereg16pt);



	return 0;

}






int InitAllegro()	//function to initialize Allegro
{
	if (!al_init())
	{
		al_show_native_message_box(NULL, "ERROR", "ERROR", "failed to initialize allegro!", NULL, NULL);
		return false;
		/*Upon error the al_show_native_message_box does not display the specified error message unless text is specified for the third parameter.
		for example... al_show_native_message_box(NULL, “ERROR”, “ERROR”,“Failed to initialize allegro!”, NULL, NULL);*/
	}
	return true;
}



int InitAllegroDisplay()	//function to initialize Allegro display
{
ALLEGRO_DISPLAY *display = al_create_display(display_width, display_height);
if (!display)
{
	al_show_native_message_box(NULL, "ERROR", "ERROR!", "failed to initialize display!", NULL, NULL);
	return false;
}
return true;
}



void InitAllegroAddonsandSetupFonts()	//function to //initialize allegro addons & setup fonts
{
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();
	//Setup fonts
	//ALLEGRO_FONT* font = al_create_builtin_font();
	ALLEGRO_FONT *bebasneuereg24pt = al_load_font("BebasNeue_Reg.ttf", 24, 0);
	ALLEGRO_FONT *bebasneuereg16pt = al_load_font("BebasNeue_Reg.ttf", 16, 0);
	
	al_destroy_display(display);	//Cleanup display... created via al_create_display
	//al_destroy_event_queue(event_que);
	//al_destroy_timer(gamelooptimer);
	al_destroy_font(bebasneuereg24pt);
	al_destroy_font(bebasneuereg16pt);
	
	return;
}


/*

//initialize functions?
InitShip(plyr1);	//initialize


ALLEGRO_TIMER* gamelooptimer = al_create_timer(1.0 / 60.0);		//declare???, create timer and set interval = 1 second / FPS... 1/60 = 60 FPS
ALLEGRO_EVENT_QUEUE* event_que = al_create_event_queue();

al_register_event_source(event_que, al_get_keyboard_event_source());	//get keyboard event and register to the applicable queue
al_register_event_source(event_que, al_get_mouse_event_source());	//get mouse event and register to the applicable queue
al_register_event_source(event_que, al_get_display_event_source(display));
al_register_event_source(event_que, al_get_timer_event_source(gamelooptimer));	//register timer event to the event_que

//return;
}*/