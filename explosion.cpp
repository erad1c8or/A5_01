/*include standard headers*/
//fprintf
#include <iostream>     //includes the header file iostream
//using namespace std;    //tells the compiler to use the std library

#include <random>
//using namespace std;

#include <chrono>
//using namespace std;

#include <tuple>     //includes the header file tuple
//using namespace std;    //tells the compiler to use the std library


//#include <cstdlib>     //
//using namespace std;    //tells the compiler to use the std library


#include <allegro5/allegro.h>	//ALLEGRO
//#include <allegro5/display.h>	//ALLEGRO - Display
//#include <allegro5/allegro_image.h>	//ALLEGRO - Image support for JPG, PNG etc
//#include <allegro5/allegro_native_dialog.h>	//ALLEGRO - dialog
//#include <allegro5/allegro_font.h>	//ALLEGRO - Fonts
//#include <allegro5/allegro_ttf.h>	//ALLEGRO True Type Fonts (TTF) Support
//#include <allegro5/allegro_primitives.h> //ALLEGRO - Primitives


//#include "maingameloop.h"
#include "explosion.hpp"



void InitDefenderExplosion(Explosion somesplosion[], int NumParticles, float x, float y, int Speed)
{

	float Drag = 0.8;		//how much a particle slows down by each second
	//PARTICLE_COLOR = 255, 230, 128	//the colour of each particle in R, G, B values
	//int Age = 3;	//the time in seconds for which a particle is displayed
	//float particles = [500];	//an array to hold 100 sets of the details of the explosion particles on the screen

	//std::cout << "NumParticles=" << NumParticles << endl;



	//C++11... Random number generation

	//method 1
	//We use random_device once to seed the random number generator named mt. 
	//random_device() is slower than mt19937, but it does not need to be seeded because it requests random data from your operating system (which will source from various locations, like RdRand for example).
	std::random_device rd;	//rd is a pointer to random_device
	std::mt19937 mt(rd());	//mt is a pointer to mt19937 (standard mersenne twister) random number generator, and here we seed our instance of the generator with rd()
	std::uniform_real_distribution<float> myrandom01(0.0, 1.0);	//was <double>
	std::cout << myrandom01(mt) << "\n";


	//method 2
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();	//Seed via system clock
	std::default_random_engine mygenerator(seed);	//generator is a pointer to default_random_engine, nd here we seed our instance of the generator with seed 
	std::uniform_real_distribution<float> myrandom02(0.0, 1.0);
	std::cout << myrandom02(mygenerator) << "\n";  // generates number in the range 1..6 << "\n";


	//method 3 is as above but using the faster mt19937 (standard mersenne twister)
	unsigned seed2 = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 mygenerator2(seed2);
	std::uniform_real_distribution<float> myrandom03(0.0, 1.0);
	std::cout << myrandom03(mygenerator2) << "\n";  // generates number in the range 1..6 << "\n";


	/*
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_real_distribution<float> distribution(0.0, 1.0);
	float myrandom = distribution(generator);  // generates number in the range 1..6
	std::cout << dist(mt) << "\n";
	*/



	for (int i = 0; i < NumParticles; i++)		// //generate 100 particles per explosion
	{
		//defendersplosion[i].id = EXPLOSION;
		somesplosion[i].live = true;
		somesplosion[i].age = 1;
		somesplosion[i].posx = x;
		somesplosion[i].posy = y;

		/*for each particle, generate a random angle and distance*/
		//angle = random.uniform(0, 2 * PI)
		float angle = (static_cast <float> (rand()) / static_cast <float> (2 * PI));

		//radius = random.uniform(0, 1) ** 0.5
		//float radius = rand() % 10;
		//float radius = static_cast <float> (rand()) / (static_cast <float> (100.0));
		float radius = (float)rand() / RAND_MAX / 2;		// /2 is a cludge factor to decrease the initial length of the radius



		//int test = rand() %10;
		//std::cout << "myrandom=" << myrandom << endl;
		//std::cout << "randmax=" << RAND_MAX << endl;

		//float radius = rand()%1;
		//radius = std::pow(radius, 0.5);


		//std::cout << "angle=" << angle << endl;
		//std::cout << "radius" << radius << endl;

		/*convert angle and distance from the explosion point into x and y velocity for the particle*/
		somesplosion[i].velx = Speed * radius * sin(angle);	//vx = speed * radius * math.sin(angle)
		somesplosion[i].vely = Speed * radius * cos(angle);	//vy = speed * radius * math.cos(angle)
		//somesplosion[i].age = 0;

		//std::cout << "particle# = " << i << endl;
		//std::cout << "particle age = " << somesplosion[i].age << endl;
		//std::cout << "particle velx= " << somesplosion[i].velx <<endl;
		//std::cout << "particle vely = " << somesplosion[i].vely <<endl;
		//std::cout << "" << endl;
		//al_rest(0.01);
	}
}



void UpdateDefenderExplosion(Explosion somesplosion[], int NumParticles)	//This function updates the array of particles
{
	float Drag = 0.08;

	for (int i = 0; i < NumParticles; i++)		//Loop through 100 particles
	{
		int burnout = rand() % 100;
		if (somesplosion[i].live && somesplosion[i].age < 1000 && burnout > 1)	//If all true, particle is updated
		{
			somesplosion[i].age += 1;
			somesplosion[i].posx += (somesplosion[i].velx *Drag);
			somesplosion[i].posy += (somesplosion[i].vely *Drag);
		}
		else   //else particle is culled
		{
			somesplosion[i].live = false;
		}
	}
}



/* This didn't work so well but I left a lot of the mods I made included too:(
void UpdateDefenderExplosionV2(Explosion somesplosion[], int NumParticles)
{
	//# This function updates the array of particles
	//int age = rand() % 1 * 10;
	float deltatime = 0.016;
	float Drag = 0.8 * deltatime;	//0.8 ** deltatime


	for (int i = 0; i < NumParticles; i++)		//Loop through 100 particles
	{
		int burnout = rand() % 100;
		if (somesplosion[i].live && somesplosion[i].age < 1000 && burnout > 1)	//If all true, particle is updated
		{
			somesplosion[i].age += 1;

			somesplosion[i].velx *= Drag;
			somesplosion[i].vely *= Drag;

			somesplosion[i].posx += (somesplosion[i].velx *deltatime);
			somesplosion[i].posy += (somesplosion[i].vely *deltatime);
		}
		else   //else particle is culled
		{
		somesplosion[i].live = false;
		}
	}
}
*/





void DrawDefenderExplosion(Explosion somesplosion[], int NumParticles)
{
	for (int i = 0; i < NumParticles; i++)		// loop through 100 particles per explosion
	{
		//al_draw_pixel(100, 100, al_map_rgb(255, 0, 255));
		if (somesplosion[i].live)
		{
			al_draw_pixel(somesplosion[i].posx, somesplosion[i].posy, al_map_rgb(255, 0, 255));
			//al_flip_display();
		}
	}
}