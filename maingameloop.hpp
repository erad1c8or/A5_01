#pragma once

//object IDS
enum ids { PLYR, BULLET, ENEMY };	//Gives every object a unique ID

//key IDS
enum keys { UP, DOWN, LEFT, RIGHT, SPACE, ESC, TAB, X };	//enum to specify the array




struct Bullet
{
	int id;
	int posx;
	int posy;
	int speed;
	bool live;
};


struct Comet
{
	int id;
	int posx;
	int posy;
	int speed;
	bool live;
	int boundx;
	int boundy;
};
