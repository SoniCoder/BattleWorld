#include "Player.h"



CPlayer::CPlayer(int initial_x, int initial_y)
	:x(initial_x),y(initial_y)
{
}


CPlayer::~CPlayer()
{
}

int CPlayer::getX()
{
	return x;
}

int CPlayer::getY()
{
	return y;
}

void CPlayer::setX(int passed_x)
{
	x = passed_x;
}

void CPlayer::setY(int passed_y)
{
	y = passed_y;
}
