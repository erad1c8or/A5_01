#pragma once											//guards per per C++11???


/*dependencies*/
#include <iostream>										//includes the header file iostream
using namespace std;									//tells the compiler to use the std library
#include <string>
using namespace std;									//tells the compiler to use the std library

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h> //ALLEGRO - Primitives

//Hmmm re notes below but I guess this does make sense...
//#include "+application.hpp"							//This breaks the build if included because Sprite class is not yet defined
//#include "main.hpp"									//This breaks the build if included because Sprite class is not yet defined




//used to be a struct but now it a class because....  struct SpaceShip	// mostly floats as required for use with sin and cos

class Sprite_JJH											//a sprite is a two-dimensional bitmap that may be integrated into a larger scene. 
	
{

public:
	//i don't get why the member vars can't be private.
	//set default values for each class member variable, via uniform initialization
	int m_id{ 0 };										//id
	float m_posx{ 0 };									//posx
	float m_posy{ 0 };									//posy
	float m_angle{ 0 };									//angle of the velocity vector in Radians
	float m_length{ 0 };								//length of the velocity vector
	float m_velx{ 0 };									//x coordinate of the velocity vector
	float m_vely{ 0 };									//y coordinate of the velocity vector
	int m_speed{ 0 };									//no longer used
	int m_lives{ 0 };									//lives
	int m_boundx{ 0 };									//bounding box x
	int m_boundy{ 0 };									//bounding box y
	int m_score{ 0 };									//score
	//due to use of member initializer list below, it's not critical to initialize each member variable with default values, but the performance benefit for not doing so is negligable...
	//...and initializing with default values, ensures each variable isn't ever garbage.



	//default constructor, in this case a parameterized default constructor
	Sprite_JJH(int id, float posx, float posy, float angle, float length, float velx, float vely, int speed, int lives, int boundx, int boundy, int score)
		:												//start of member initializer list, initializes all member variables, via C++11 style uniform initialization
		m_id{id},										//m_id = id
		m_posx{posx},									//position x
		m_posy{posy},									//position y
		m_angle{angle},									//angle of the velocity vector in Radians
		m_length{length},								//length of the velocity vector
		m_velx{velx},									//x coordinate of the velocity vector
		m_vely{vely},									//y coordinate of the velocity vector
		m_speed{speed},									//no longer used
		m_lives{lives},
		m_boundx{boundx},								//bounding box x
		m_boundy{boundy},								//bounding box y
		m_score{score}
		{
		//all member variables are initialized per the initializer list, so there is no need for assignment or initialization here
		}


	//default destructor
	~Sprite_JJH()
	{
	}


	//virtual ~Sprite();


	/*function prototypes - C++ requires functions to be declared before they are called and these are called function prototypes*/
	//void setBitmap(std::string filePath);
	//ALLEGRO_BITMAP *getBitmap();
	
	void draw();



protected:
	//ALLEGRO_BITMAP *bitmap;


private:




	// https://www.geeksforgeeks.org/constructors-c/




	//void InitPlyrShip(SpaceShip &someSpaceShip);	//declare/fwd define & pass by reference
	///void DrawShip(SpaceShip &someSpaceShip);
	///void MoveShipUp(SpaceShip &someSpaceShip);
	///void MoveShipDown(SpaceShip &someSpaceShip);
	///void MoveShipLeft(SpaceShip &someSpaceShip);
	///void MoveShipRight(SpaceShip &someSpaceShip);
	///float RotateShipLeft(float image2Degree);
	///float RotateShipRight(float image2Degree);


};