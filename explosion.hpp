#pragma once

/*It seems that must be in this order...
Variables
Structures
Function prototypes - C++ requires functions to be declared before they are called and these are called function prototypes
*/



//Variables...

const float PI = 3.14159;		//Initialize PI with value of 3.14159



//Structures...

struct Explosion
{
	//int id;
	bool live = false;
	int age;
	float posx, posy;			//position x and y
	float velx, vely;			//x- and y- coordinates of the velocity vector
};



//Function Prototypes...

//void InitDefenderExplosion(Explosion defendersplosion[], int NumPieces);
//void InitDefenderExplosion(ALLEGRO_DISPLAY *&display, Explosion somesplosion[], int NumParticles, int x, int y, int Speed);
void InitDefenderExplosion(Explosion somesplosion[], int NumParticles, float x, float y, int Speed);
void UpdateDefenderExplosion(Explosion somesplosion[], int NumParticles);
void DrawDefenderExplosion(Explosion somesplosion[], int NumParticles);