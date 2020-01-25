#include "+sprite_player.hpp"


Player::Player(int id, float posx, float posy, float angle, float length, float velx, float vely, int speed, int lives, int boundx, int boundy, int score)
	:
	m_id{ id },										//m_id = id
	m_posx{ posx },									//position x
	m_posy{ posy },									//position y
	m_angle{ angle },									//angle of the velocity vector in Radians
	m_length{ length },								//length of the velocity vector
	m_velx{ velx },									//x coordinate of the velocity vector
	m_vely{ vely },									//y coordinate of the velocity vector
	m_speed{ speed },									//no longer used
	m_lives{ lives },
	m_boundx{ boundx },								//bounding box x
	m_boundy{ boundy },								//bounding box y
	m_score{ score }
	{
	health = 0;
	moveSpeed = 5;
	}


Player::~Player()
{
}



/*
void Player::doLogic(Keyboard keyboard)
{
	if (keyboard.key[UP])
		y -= moveSpeed;
	else if (keyboard.key[DOWN])
		y += moveSpeed;
	if (keyboard.key[LEFT])
		x -= moveSpeed;
	else if (keyboard.key[RIGHT])
		x += moveSpeed;
}
*/