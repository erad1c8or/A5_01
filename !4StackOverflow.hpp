
//Top of globals.cpp... I need to fix the calcfor invadersStartPosX so it uses invadersPerRow as basis, insted of invadersNum
//gamecode.cpp initialise invaders,still needs the correct calculation to be imlemented for the if check too re next row



/*
>>>globals.h
#include <iostream>																			//includes the header file iostream
#include <string>
#include <vector>
extern std::vector<Sprite> glob_vector_enemy;

>>>>globals.cpp
#include "globals.h"
extern std::vector<Sprite> glob_vector_enemy(15, Sprite("enemy", "Square_16x16_Green", 100, 300));


>>>Sprite.h

>>>Sprite.cpp


>>>main.h
#include "globals.h"
int main();


>>>main.cpp
#include "main.h"

int main()
{
	std::cout << "entered main() \n";
	system("pause");
	std::cout <<  "glob_vector_enemy.size = " << glob_vector_enemy.size() << "\n";
	//glob_vector_enemy.size = 15... but it's been deconstructed already? 
	system("pause");
	return 0;
}


//Whenever I construct a vector of class type objects, I then see the corresponding deconstructor called immediately after.
//And, even after seeing the deconstructor called, I can still access objects in the vector.
//See the simplest example I could figure which creates the vector as global instance, and I figure this way that I'm not seeing the destructor called because of the array dropping out of scope? 
//What am I doing wrong and misunderstanding?




//This all works but when invader are stored in a vector and the bitmaps are loaded in, it fails at exit point when...
//vector destructor calls after Allegro has been shutdown so... al_delete_bitmap then fails.

//Try destructing the plyr01 manually and then attempt to output its member values and draw it, to see what happens

//Remember to go back to +Sprite.cpp re Globals for displayWidth, displayHeight and AssetsDir
//And the system pause that is now commented out in the destructow within +Sprite.Cpp
//Behaviour is different if !Globals.hpp is/is not included in +Sprite.hpp and I don't think it should be included.
//Dynamic arrays with constructors/destructors
//vectors
//02_biplane.cpp is definitely a module that I should get going again.

//Learn to do from memory...
//for (int i = 0; i < numInvaders; i++)


//Things to do...
//Add GUI or fonts class?
//Create player class, using inheritance of +Sprite class
//Create enemy class, using inheritance of +Sprite class

//Notes...
/*within gameloop I changed the order of the following from...
if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
else if (ev.type == ALLEGRO_EVENT_KEY_UP)
if (ev.type == ALLEGRO_EVENT_TIMER)
to...
if (ev.type == ALLEGRO_EVENT_TIMER)
else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
else if (ev.type == ALLEGRO_EVENT_KEY_UP)
*/


/*
I don't think it's too relevant but my project currently consists of...
main.h		&	main.c
App.h		&	App.c						//The gameloopexists in here.
sprite.h	&	sprite.c
globals.h	&	globals.c

*/

