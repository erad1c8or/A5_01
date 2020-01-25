#pragma once																				//guards per C++11???

/*dependencies*/
#include <iostream>																			//includes the header file iostream
//#include <vector>

#include "!Globals.hpp"
//#include "+Sprite.hpp"																		//The definition for Sprite class must be included as objects of this type are created in within +App.cpp		
#include "+Sprite.hpp"																		//Required re declaration of Sprite objects herein


//I did think this was going to work, until discovering it crashes because the destructor is called immediately and then after everything else is shutdown
//extern Sprite invader01;
//I could have hacked the destructor to check if Allegro was initialized/not initialized and doing appropriately, assuming I also called the destructor once, before Allegro was shut down
//So instead of this now using Global Pointer, and manual destruction...
//application *myapp = new application();


extern const int scaleFactor;																//scaleFactor for source assets
extern float invadersNum;																//Number of Invaders


//std::vector<Sprite> vectorarrayofinvaders;												//now declaring here, moved from main.hpp
//std::vector<Sprite> vectorarrayofinvaders2;												//now declaring here, moved from main.hpp


//member function prototypes - C++ requires functions to be declared before they are called and these are called function prototypes


void createarrayofinvaders();


std::vector<Sprite> createarrayofinvaders2();


//void initarrayofinvaders3(std::vector<Sprite> &input_vectorarray);




void initarrayofinvaders(std::vector<int> &input_vectorarray);
void initarrayofinvaders2(std::vector<int> &input_vectorarray);






void somegamecode();
void initialize_Invaders();
void somegamecode3();
int arraytest();
void arraytest_passbyreference(std::vector <int> &input_vect);

//void somegamecode(Sprite invaderglobtest &invaderglob);


//int init();																				//Initialize ALLEGRO
//int createWindow(int displayWidth, int displayHeight, float FPS);							//Create Window
