

#include "+sprite_JJH.hpp"

//#include "+application.hpp"



//Globals... or not as the case is right now
//Sprite plyr1{ 1, 640, 360, 0, 0, 0, 0, 0, 0, 0, 0, 0 };	//create object of type spaceShip named plyr1, via unform initialization
//Sprite plyr1{ 1, displayWidth / 2, displayHeight / 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };	//create object of type spaceShip named plyr1, via unform initialization
//Sprite plyr2{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };	//create object of type spaceShip named plyr2, via uniform initialization




void Sprite_JJH::draw()
{
	al_draw_filled_circle(plyr1.m_posx, plyr1.m_posy, 25, al_map_rgb(0, 0, 255));
	//al_draw_bitmap(bitmap, x, y, NULL);
}



/*player::player()
{
}


player::~player()
{
}


void InitPlyrShip(SpaceShip &someSpaceShip)	//InitPlyrShip Function, don't return anything because its doing it by reference so all changes stay
{
	std::cout << "InitPlyrShip" << endl;
	someSpaceShip.id = PLYR;
	someSpaceShip.posx = DisplayWidth / 2;
	someSpaceShip.posy = DisplayHeight / 2;
	someSpaceShip.angle = 0.0;
	someSpaceShip.length = 0.0;
	someSpaceShip.velx = 0.0;
	someSpaceShip.vely = 0.0;
	someSpaceShip.speed = 5;		//not used???
	someSpaceShip.lives = 3;
	someSpaceShip.boundx = 6;
	someSpaceShip.boundy = 7;
	someSpaceShip.score = 0;
	std::cout << "plyr1.lives = " << plyr1.lives << endl;
}


*/