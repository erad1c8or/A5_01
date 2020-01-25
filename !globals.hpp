#pragma once

#include <iostream>																			//includes the header file iostream
#include <string>
#include <vector>


//#include "!globals.hpp"
#include "+App.hpp"
//#include "+Sprite.hpp"																		//Required re declaration of Sprite objects herein
#include "02_gamecode_01.hpp"																//Required re definition of variables specific to invaders


extern float old_time;
extern int invadctr;
extern bool invadersMovementState[3];
enum invadersMovementState { INVADERSMOVINGRIGHT, INVADERSATLEFTEDGE, INVADERSATRIGHTEDGE };


//forward declarations
//A pointer is a variable that holds a memory address where a value lives

extern Sprite *plyr01_glob_ptr;																//forward declaration
extern Sprite *invader_glob_ptr;															//declare pointer re the definition of a dynamic array is the same as defining a pointer for a single item.

//Vector of invaders...
//extern std::vector<Sprite> invader_glob_vector;
//

extern application *myapp;																	//forward declaration
//extern ALLEGRO_FONT *defaultfont;

//extern Sprite plyr01;
//extern Sprite invader01;
//extern Sprite invader02;


extern std::string assetsDir;

extern const float displayWidth;										//Might be able to make this type int, currently a float so can be used in Explosion Trigonometry
extern const float displayHeight;										//Might be able to make this type int, currently a float so can be used in Explosion Trigonometry
extern const float FPS;
extern const float invadersStartPosX;


//Move to keys at some time...
enum keys { UP, DOWN, LEFT, RIGHT, SPACE };
extern bool keys[5];												//Declare 4 bools per the above enumeration


extern const double PI;												//Declare PI


extern int CurrFrame;												//Keeps track current frame of animation
extern int FrameCount;												//Keeps track of ticks/cycles since last frame of animation played
extern int FrameDelay;												//Delay to wait between animation frames


extern const int NumPlyr1Bullets;
extern const int NumComets;
extern const int NumParticles;

extern const int NumPoints;											//Redundenat???? - Think this was used for a Triangle array of some sorts but not sure.


//*Rudimentary Animation - Declared in... +Sprite.hpp so not needed here*/
//extern std::string objectName;
//extern std::string assetName;
//extern std::string assetCategory;
//extern std::string assetFormat;
//extern std::string assetFrameNumAsString;
//extern std::string asset_filepath;/



//Forward declarations...
int ConcatenateSpriteFrames(std::string sourceAnimName, std::string sourceFormat);




