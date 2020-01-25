#pragma once																				//guards per C++11???

/*dependencies*/	
#include <iostream>																			//includes the header file iostream
#include <vector>
//#include <iomanip>																		//required for custom cout formats
//#include <string>
//#include <random>
//#include <chrono>
//#include <tuple>																			//includes the header file tuple

#include <allegro5/allegro.h>
//#include <allegro5/display.h>																//ALLEGRO - Display, which seemingly isn't used
#include <allegro5/allegro_image.h>

#include <allegro5/allegro_native_dialog.h>													//ALLEGRO - dialog, unlike the above, this is somewhat optional
#include <allegro5/allegro_font.h>															//ALLEGRO - Fonts, unlike the above, this is somewhat optional
#include <allegro5/allegro_ttf.h>															//ALLEGRO True Type Fonts (TTF) Support, unlike the above, this is somewhat optional
#include <allegro5/allegro_primitives.h>													//ALLEGRO - Primitives, unlike the above, this is somewhat optional

//#include "!globals.hpp"
//#include "+App.hpp"
#include "+Sprite.hpp"																	//needs this to understand Sprite struct

//#include "02_gamecode_01.hpp"

//#include "keyboard.h"



class application

{
public:	
	//Default Constructor & Destructor
	application();																			//Constructor - forward declaration of the default constructor

	~application();																			//Destructor - forward declaration of the default destructor

	//member function prototypes - C++ requires functions to be declared before they are called and these are called function prototypes
	int init();																				//Initialize ALLEGRO
	int createWindow(int displayWidth, int displayHeight, float FPS);						//Create Window
	void gameLoop(std::vector<Sprite> &vectorarrayofinvaders2);								//Needs Plyr01, Plyr01_Shots, Invaders, Invaders_Shots etc...																	//Start gameloop
	//void BiplaneFloatPoint(ALLEGRO_DISPLAY *&display, sprite &somesprite);
	   
protected:
	   
private:
	ALLEGRO_DISPLAY *display;																//create *display (ptr), where type of data pointed to is... of type ALLEGRO_DISPLAY
	ALLEGRO_TIMER *timer;																	//create *timer (ptr), where type of data pointed to is... of type ALLEGRO_TIMER
	ALLEGRO_EVENT_QUEUE *event_queue;														//create *event_queue (ptr), where type of data pointed to is... of type ALLEGRO_EVENT_QUEUE
	//Keyboard keyboard;

	//Player ply1;
	//Player plyr1{ 1, displayWidth / 2, displayHeight / 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };	//create object of type Sprite named plyr1, via unform initialization
	//Sprite plyr1{ 1, displayWidth / 2, displayHeight / 2 };								//create object of type Sprite named plyr1, via unform initialization
	
	bool looping, redraw;

};