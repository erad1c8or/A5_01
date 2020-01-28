//Dependencies...
//#include <vector>

#include "02_gamecode_01.hpp"

extern const int scaleFactor{ 1 };
extern float invadersNum{ 11 };															//Sadly, !globals.cpp must define the same number of entries



void createarrayofinvaders()
{
	//temporarily moved from !globals.cpp
	//invader_glob_vector.reserve(15);
	std::vector<Sprite> vectorarrayofinvaders(invadersNum, Sprite("vectorarrayofinvaders", "Square_16x16_Green", invadersStartPosX, 300, 2.0));
	std::cout << "...the current size of invader_glob_vector = " << vectorarrayofinvaders.size() << "\n";
	system("pause");
}


/*
void initarrayofinvaders(std::vector<Sprite> &input_vectorarray)
{
	int offset{ 32 };
	for (int i = 0; i < invadersNum; i++)
	{
		//invader_glob_vector[i].m_posx = invader_glob_vector[i].m_posx + (offset * i);
		input_vectorarray[i].m_bitmap = al_load_bitmap("Assets/Square_16x16_Green00.png");			//Set the bitmap for...

	}
}
*/



std::vector<Sprite> createarrayofinvaders2()
{
	//temporarily moved from !globals.cpp
	//invader_glob_vector.reserve(15);
	const int invadersNumRows{ 5 };
	const int invadersPerRow{ 11 };
	const int invadersTotal{ invadersNumRows * invadersPerRow };				//At this stage, this could be equated to the size of the array
	//const float invadersStartPosX = { ((displayWidth - ((11 - float(0.5)) * 32)) / 2) + 1 };
	//const int displayWidth2{ 1280 };

	const int invadersSpaceX{ 0 };
	const int invadersSpaceY{ 20 };
	const int invadersWidth{ 16 };								//This will be part of the sprite struct for final...


	int invadersColNum{ 0 };
	int invadersRowNum{ 0 };
	//const float invadersPosXMin = { ((displayWidth - ((invadersPerRow - float(0.5) * invadersSpacing)) / 2) + 1 };

	//Calculate the first posX that we should plot the first pixel of the first invader in a row at...
	//Each row of invaders, starts and ends with an invader, and each invader in the row separated by invaderSpaceX
	//int invadersPosXMin = (displayWidth2 - invadersPerRow * 16) / 2;			//552... Trying to get 472... Need to get 16 from some other variable that will be defined in the sprite struct.

	//int invadersPosXMin = (displayWidth2 - (invadersPerRow * invadersWidth) - ((invadersPerRow-1) * invadersWidth + invadersSpaceX)) /2;			// 464... Need to get 16 from some other variable that will be defined in the sprite struct.
	int invadersPosXMin = (displayWidth - (invadersPerRow * invadersWidth) - ((invadersPerRow - 1) * invadersSpaceX)) / 2;			//Need to get 16 from some other variable that will be defined in the sprite struct.

	
	std::vector<Sprite> vectorarrayofinvaders2(invadersTotal, Sprite("vectorarrayofinvaders2", "Invader01B", 0.0, 100.0, 2.0));
	std::cout << "...the current size of vectorarrayofinvaders2 = " << vectorarrayofinvaders2.size() << "\n";
	system("pause");
	
	for (int i = 0; i < invadersTotal; i++)
	{
		vectorarrayofinvaders2[i].m_posxInitial = invadersPosXMin + ((invadersWidth + invadersSpaceX) * invadersColNum);
		vectorarrayofinvaders2[i].m_posx = invadersPosXMin + ((invadersWidth + invadersSpaceX) * invadersColNum);
		std::cout << vectorarrayofinvaders2[i].m_posx << "\n";
		system("pause");
		vectorarrayofinvaders2[i].m_movSpeed = 2.0;
		vectorarrayofinvaders2[i].m_posyInitial = vectorarrayofinvaders2[i].m_posy - (invadersSpaceY * invadersRowNum);
		vectorarrayofinvaders2[i].m_posy = vectorarrayofinvaders2[i].m_posy - (invadersSpaceY * invadersRowNum);
		vectorarrayofinvaders2[i].m_bitmap = al_load_bitmap("Assets/Invader01B.png");			//Set the bitmap for...   THIS SHOULD AT LEAST USE THE NAME PASSED IN
		//if i = numInvadersPerRow
		invadersColNum++;
		//input_vectorarray[i]
		//if (input_vectorarray[i].m_posx > ((invadersStartPosX + ((invadersPerRow-=1) * 16))))
		if (vectorarrayofinvaders2[i].m_posx > (displayWidth - invadersPosXMin - invadersWidth*2))
			//if (input_vectorarray[i].m_posx > (473 + 319))
		{
			invadersRowNum++;
			invadersColNum = 0;
		}
	}

	//invadersNum = invadersTotal;				//****Need invadersTotal to have scope in the gameloop


	return vectorarrayofinvaders2;
}








void somegamecode()
//void somegamecode(Sprite invaderglobtest &invaderglob)
{
	std::cout << "02_gameloop_01.cpp - somegamecode\n";
	plyr01_glob_ptr->m_bitmap = al_load_bitmap("Assets/Square_16x16_Green00.png");				//Set the bitmap for...
	//invader_glob_ptr[0].m_bitmap = al_load_bitmap("Assets/Square_16x16_Green00.png");			//Set the bitmap for...
	//invader_glob_ptr[1].m_bitmap = al_load_bitmap("Assets/Square_16x16_Green00.png");			//Set the bitmap for...

	//invader_glob_ptr[0] = { "invader_glob_ptr", "Square_16x16_Green", 640, 10 };
}



//Setup default values and bitmaps for Invaders
void initialize_Invaders()
{
	int offset{ 32 };
	for (int i = 0; i < invadersNum; i++)
		{
		//The line below caused Invaders to be constructed here, and then something was immediately destructed 
		//std::cout << "passing construction parameters to invader..." << i << "\n";
		//invader_glob_ptr[i] = { "invader_glob_ptr", "Square_16x16_Green", 640, 10 + (offset * i) };
		invader_glob_ptr[i].m_posx = invader_glob_ptr[i].m_posx + (offset * i);
		invader_glob_ptr[i].m_bitmap = al_load_bitmap("Assets/Square_16x16_Green00.png");			//Set the bitmap for...
		
		//invader_glob_vector[i].m_posx = invader_glob_vector[i].m_posx + (offset * i);
		//invader_glob_vector[i].m_bitmap = al_load_bitmap("Assets/Square_16x16_Green00.png");			//Set the bitmap for...

		}
}

void somegamecode3()
{
	std::cout << "02_gameloop_01.cpp - somegamecode2\n";
	//invader01.~Sprite();
	//delete invader01;
/*
	std::cout << "02_gameloop01.cpp - Plyr1_Sprite_Loader\n";
	int num_zero = 2;																//number digits used in anim sequence file names
	for (int i = 0; i < plyr01.m_MaxFrame; i++)
		{
		std::cout << "adding sprite frame..." << i << "\n";
		std::string assetFrameNumAsString = std::to_string(i);
		std::string  asset_filepath = "assets/" + assetName + std::string(num_zero - assetFrameNumAsString.length(), '0') + assetFrameNumAsString + assetFormat;
		//std::string  asset_filepath = assetsDir + assetName + std::string(num_zero -assetFrameNumAsString.length(), '0') + assetFrameNumAsString + assetFormat;
		std::cout << "+Sprite.cpp - Animated Sprite Constructor loading... " << asset_filepath << "\n";
		PlyrAnimFrame[i] = al_load_bitmap(asset_filepath.c_str());
		al_convert_mask_to_alpha(PlyrAnimFrame[i], al_map_rgb(255, 0, 255));		//assign defined color to alpha
		}
*/
}



// C++ program to demonstrate that when vectors are passed to functions without &, a copy is created. 
//#include<bits/stdc++.h> 
//using namespace std;
// The vect here is a copy of vect in main()
void arraytest_passbyreference(std::vector<int> &input_vector)
{
	input_vector.push_back(30);
}



//Per LearnCPP, a short function, illustrating the difference between arrays and pointers
int arraytest()
{
	// an array with 5 elements.
	double balance[5] = { 1000.0, 2.0, 3.4, 17.0, 50.0 };
	double *p;

	p = balance;

	// output each array element's value
	std::cout << "Array values using pointer " << "\n";

	for (int i = 0; i < 5; i++) {
		std::cout << "*(p + " << i << ") : ";
		std::cout << *(p + i) << "\n";
	}
	std::cout << "Array values using balance as address " << "\n";

	for (int i = 0; i < 5; i++) {
		std::cout << "*(balance + " << i << ") : ";
		std::cout << *(balance + i) << "\n";
	}

	return 0;
}






