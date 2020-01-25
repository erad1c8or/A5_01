#pragma once											//guards per per C++11???

/*dependencies*/

#include "+sprite.hpp"
//#include "Keyboard.h"




class Player :
	public Sprite
{
public:
	Player(int id, float posx, float posy, float angle, float length, float velx, float vely, int speed, int lives, int boundx, int boundy, int score);
	~Player();

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
	//void doLogic(Keyboard keyboard);


protected:



private:
	int health, moveSpeed;


};