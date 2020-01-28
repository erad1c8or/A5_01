#pragma once																			//guards per per C++11???

/*dependencies*/
#include <iostream>																		//includes the header file iostream
#include <vector>																		//Introduced in C++03, std:: vectorprovides dynamic array functionality that handles its own memory management, enabling arrays to have their length set at runtime, without having to explicitly allocate and deallocate memory using new and delete.
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>												//ALLEGRO - Primitives

//#include "!globals.hpp"																//

class Sprite
{

public:
	//Constructor & Overrides
	Sprite();																			//default constructor
	Sprite(float posx, float posy);
	Sprite(std::string assetName, float posx, float posy);
	Sprite(std::string objectName, std::string assetName, float posx, float posy, float movSpeed);
	Sprite(std::string assetName, std::string assetCategory, std::string assetFormat, int lastFrame, float posx, float posy);


	~Sprite();																			//destructor (default)

	//moved all these from private, to make the member variables are visible to the +App\gameloop
	std::string m_objectName;
	float m_posx{ 0 };
	float m_posy{ 0 };
	float m_posxInitial{ 0 };
	float m_posyInitial{ 0 };
	float m_movSpeed{ 0 };
	ALLEGRO_BITMAP *m_bitmap = nullptr;													//create *bitmap (ptr)
	//end of the variables moved as noted above

	//Support for animated sprites...
	std::string m_Name;
	std::string m_Cat;
	std::string m_Format;
	int m_MaxFrame;
	int m_CurrFrame;
	ALLEGRO_BITMAP *PlyrAnimFrame[16] = {nullptr};										//Array of sprite X frames that will be stored as 0 - [X]-1
	//ALLEGRO BITMAP = std::vector<Sprite> vectorarrayofinvaders(lastFrame, Sprite("vectorarrayofinvaders", "Square_16x16_Green", startInvaders, 300));
	
	//The above also seems to work if I change nullptr to NULL too so I should learn what is the real difference of those.
	//The array that is created should be dynamic...
	//std::vector<ALLEGRO_BITMAP*> Plyrvector;											//Per 2019/03/18, I dont know what I'm doing with this exactly yet, arguably it should be a smart pointer?
	
	

	//member function prototypes - C++ requires functions to be declared before they are called and these are called function prototypes
	void setBitmap(std::string filePath);												//setter
	//ALLEGRO_BITMAP *getBitmap();														//getter
	

	void draw();
	void draw_test();
	void draw_bitmap();
	void draw_animated_bitmap();
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();


protected:


private:


};




