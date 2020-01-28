//#include <string>
//#include <vector>

#include "!globals.hpp"
//#include "02_gamecode_01.hpp"




/* Dynamic Global Pointers*/
//A pointer is a variable that holds a memory address where a value lives.
//new int;																							//dynamically allocate an integer (and discard the result)
Sprite *plyr01_glob_ptr = new Sprite{ "plyr01_glob_ptr", "Square_16x16_Green", displayWidth/2, displayHeight-16, 2.0 };			//dynamically allocate (=new etc.) a Sprite & assign the address returned to ptr so it can be accessed later.




application *myapp = new application;							//create *myapp (ptr), where type of data pointed to is... new (dynamic/heap) instance of application (class) 					




extern std::string assetsDir = "assets/";

extern const float displayWidth { 224 };										//Might be able to make this type int, currently a float so can be used in Explosion Trigonometry
extern const float displayHeight { 256 };										//Might be able to make this type int, currently a float so can be used in Explosion Trigonometry
extern const float FPS { 60.00 };


extern bool keys[5]{ false, false, false, false, false};							//Initialize all keys as not pressed

extern const double PI { 3.14159 };											//Initialize PI with value of 3.14159

extern int CurrFrame = 0;
extern int FrameCount = 0;
extern int FrameDelay = 0;

extern const int NumPlyr1Bullets = 10;
extern const int NumComets = 10;
extern const int NumParticles = 100;

extern const int NumPoints = 3;												//Redundenat???? - Think this was used for a Triangle array of some sorts but not sure.




//The followig should be made more local when everything is finalized.
extern float old_time = 0.0;
extern int invadctr = 0;
extern bool invadersMovementState[3]{ false, false, false };							//Initialize invadersDir



//extern const float invadersStartPosX = { ((displayWidth - ((invadersNum - float(0.5)) * 32)) / 2) + 1 };
extern const float invadersStartPosX = { ((displayWidth - ((11 - float(0.5)) * 32)) / 2) + 1 };

/*ARRAYS... This works to define an array of sprites, but when each item is then defined, a Destructor is called for the initial instance...*/
//Sprite *invader_glob_ptr{ new Sprite[numInvaders] {} };	//dynamically allocate (=new etc.) an ARRAY of Sprites & assign the address returned to ptr so it can be accessed later.

/*Thus, the correct syntax for defining a standard Dynamic array (utilizing new/delete) via Uniform Initialization is...*/
//There is no better way to construct all elements with the same value, unless they are all initialized as 0. 
Sprite *invader_glob_ptr{ new Sprite[invadersNum]
	{
		{ "invader_glob_ptr", "Square_16x16_Green", invadersStartPosX, 100, 2.0 },
		{ "invader_glob_ptr", "Square_16x16_Green", invadersStartPosX, 100, 2.0 },
		{ "invader_glob_ptr", "Square_16x16_Green", invadersStartPosX, 100, 2.0 },
		{ "invader_glob_ptr", "Square_16x16_Green", invadersStartPosX, 100, 2.0 },
		{ "invader_glob_ptr", "Square_16x16_Green", invadersStartPosX, 100, 2.0 },
		{ "invader_glob_ptr", "Square_16x16_Green", invadersStartPosX, 100, 2.0 },
		{ "invader_glob_ptr", "Square_16x16_Green", invadersStartPosX, 100, 2.0 },
		{ "invader_glob_ptr", "Square_16x16_Green", invadersStartPosX, 100, 2.0 },
		{ "invader_glob_ptr", "Square_16x16_Green", invadersStartPosX, 100, 2.0 },
		{ "invader_glob_ptr", "Square_16x16_Green", invadersStartPosX, 100, 2.0 },
		//		{ "invader_glob_ptr", "Square_16x16_Green", invadersStartPosX, 100, 2.0 },
		//		{ "invader_glob_ptr", "Square_16x16_Green", invadersStartPosX, 100, 2.0 },
		//		{ "invader_glob_ptr", "Square_16x16_Green", invadersStartPosX, 100, 2.0 },
		//		{ "invader_glob_ptr", "Square_16x16_Green", invadersStartPosX, 100, 2.0 },
				{ "invader_glob_ptr", "Square_16x16_Green", invadersStartPosX, 100, 2.0 }
			}
};
//dynamically allocate (=new etc.) an ARRAY of Sprites & assign the address returned to ptr so it can be accessed later.
//Ideally we could set each entry in the array to have the same parameters, without having to enter each one individually
//But C++ does not seem to support this, hence these do not work...
//Sprite *invader_glob_ptr{ new Sprite[2] { std::fill_n(invader_glob_ptr,2, { "invader_glob_ptr", "Square_16x16_Green", 300, 300 })} };	//dynamically allocate (=new etc.) an ARRAY of Sprites & assign the address returned to ptr so it can be accessed later.
//Sprite *invader_glob_ptr{ new Sprite[1] {{ "invader_glob_ptr", "Square_16x16_Green", 300, 300 }} };	//dynamically allocate (=new etc.) an ARRAY of Sprites & assign the address returned to ptr so it can be accessed later.
//Sprite *invader_glob_ptr = new Sprite(15, Sprite("invader_glob_ptr", "Square_16x16_Green", startInvaders, 100));


/*Now vectors... THAT SEEM TO BE THE BEST SOLUTION OF ALL???*/
//extern std::vector<Sprite> invader_glob_ptr;
//extern std::vector<Sprite*> invader_glob_ptr(numInvaders, Sprite("invader_glob_ptr", "Square_16x16_Green", 500, 100));

/*OMG - THE LINE BELOW ACTUALLY WORKS... except...*/
//extern std::vector<Sprite> invader_glob_vector(numInvaders, Sprite());
//invader_glob_vector.reserve(15);
//The next line is the one that works.
//std::vector<Sprite> invader_glob_vector(numInvaders, Sprite("invader_glob_vector", "Square_16x16_Green", startInvaders, 300));

//BUT the destructor is called, immediately after the constructor, I think deleting a temp copy.
//THEN the destructor is called, after allegro is destroyed, so the destructor doesn't work then. :(

//Also, I'm not sure how to write the above to do the same via Uniform Initialization...
//extern std::vector<Sprite> invader_glob_ptr{ (numInvaders, Sprite("invader_glob_ptr", "Square_16x16_Green", startInvaders, 100)) };















/*
{
	std::cout << "Enter a positive integer: ";
	int length{};
	std::cin >> length;

	int *array{ new int[length] {} }; // use array new.  Note that length does not need to be constant!

	std::cout << "I just allocated an array of integers of length " << length << '\n';

	array[0] = 5; // set element 0 to value 5

	delete[] array; // use array delete to deallocate array
	// we don't need to set array to nullptr/0 here because it's going to go out of scope immediately after this anyway
	return 0;
}

*/



//Create a pointer of type Sprite and equate it to a dynamically allocated Sprite whose address is returned to the ptr so it can be accessed later.



/* Prior to understanding Global Pointers, and not entirely sure this is accurate*/
//Sprite plyr02 = new Sprite{ "plyr02", "Square_16x16_Green", 300, 300 };						//This is definitely not legal, just for example.
//Unlike in C, in CPP, a const variable has internal linkage by default, so declaration (.hpp) and definitions (.cpp) and for global variables must both make use of extern
//***although it means somethign different in each case I believe.

//#include "+Sprite.hpp"
//Sprite invader01;
//Sprite invader01 { 300, 300 };																//This works:)
//Sprite invader01 (300, 300);																	//This works too.
//Sprite invader01 { "Square_16x16_Green", 300, 300 };											//This works:)
//Sprite invader01 ("Square_16x16_Green", "AnimatedSprite", ".png", 1, 300, 300);				//This crashes...
//Sprite plyr01 { "Agony/OwlAnimR", "AnimatedSprite", ".bmp", 16, 640, 360 };
//...I think due to trying to use an allegro function, before it is initialized.

//ALLEGRO_BITMAP *testbitmap = NULL;
//ALLEGRO_BITMAP *invader01_bitmap = NULL;

//and I think can go in any .cpp file, so long as defined outside of any function or block scope...