
#include <iostream>     //includes the header file iostream
using namespace std;    //tells the compiler to use the std library

#include <allegro5/allegro.h>	//ALLEGRO
#include <allegro5/allegro_native_dialog.h>	//ALLEGRO dialog
#include <allegro5/allegro_font.h>	//ALLEGRO Fonts
#include <allegro5/allegro_ttf.h>	//ALLEGRO True Type Fonts (TTF) Support
#include <allegro5/allegro_primitives.h> //ALLEGRO primitives

//#include "objects1.h"

volatile long counter = 0;


void increment()
{
	counter++;
}




//globals
const int DisplayWidth = 800;
const int DisplayHeight = 400;
const int FPS = 60;
bool keys[5]{ false, false, false, false, false };	//array for key states
bool quitapp = false;
bool redraw = true;	//the bool named 'redraw' is used to ensure we render per the timer, but to move the rendering outside of the timer event handler



int main()
{
	
	//initialize allegro
	if (!al_init())
	{
		al_show_native_message_box(NULL, "ERROR", "ERROR", "failed to initialize allegro!", NULL, NULL);
		return -1;
		/*Upon error the al_show_native_message_box does not display the specified error message unless text is specified for the third parameter.
		for example... al_show_native_message_box(NULL, “ERROR”, “ERROR”,“Failed to initialize allegro!”, NULL, NULL);*/
	}

	//initialize allegro display
	ALLEGRO_DISPLAY *display = al_create_display(DisplayWidth, DisplayHeight);
	if (!display)
	{
		al_show_native_message_box(NULL, "ERROR", "ERROR!", "failed to initialize display!", NULL, NULL);
		return -1;
	}

	//initialize allegro addons
	al_install_keyboard();
	al_install_mouse();
	//al_install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, "A");
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	
	LOCK_VARIABLE (counter);
	LOCK_FUNCTON (increment);
	install_int_ex (increment, BPS_TO_TIMER(100));

	BITMAP *Buffer = create_bitmap(6000, 400);
	bool done = false;


	while (!done)
	{
	
		
		while (counter > 0)
		{
			//input
			if (key[KEY_ESC])
				done = true;

			//update
			counter --;
		}

		//draw
	
	}
	
	return 0;
}
END_OF_MAIN()