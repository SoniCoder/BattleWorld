#include "Player.h"
#include "bw_structs.h"

extern mainData dataUnit;



CPlayer::CPlayer(int initial_x, int initial_y)
	:x(initial_x),y(initial_y)
{
	animCol = 0;
	plFacing = 0;
	plMaxSpeed = 1;
	velocity[0] = 0;
	velocity[1] = 0;
	spriteScale = 2.0;
	lastUpdate = m_struct.time_unit.sdl_time;
}


CPlayer::~CPlayer()
{
}

void CPlayer::Draw() {
	animCol = ((getX()/5)%2) ? (((getY()/5)%2)?1:0) : (((getY()/5)%2)?0:1);
	dataUnit.mastersprite->Draw(animCol+plFacing, 0, x, y, spriteScale);
	//dataUnit.mastersprite->Draw(1, 0, 400, 300, spriteScale);
}

int CPlayer::getX()
{
	return x;
}

int CPlayer::getY()
{
	return y;
}

int CPlayer::getVx()
{
	return velocity[0];
}

int CPlayer::getVy()
{
	return velocity[1];
}

void CPlayer::keyHandler() {
	if (FP_isPressed(SDL_SCANCODE_UP)) {
		velocity[1] = -plMaxSpeed;
		plFacing = 0;
		velocity[0] =  0;
	}
	else if (FP_isPressed(SDL_SCANCODE_DOWN)) {
		plFacing = 4;
		velocity[1] = plMaxSpeed;
		velocity[0] = 0;
	}
	else {
		velocity[1] = 0;
	}
	if (FP_isPressed(SDL_SCANCODE_LEFT)) {
		plFacing = 2;
		velocity[0] = -plMaxSpeed;
		velocity[1] = 0;
	}
	else if (FP_isPressed(SDL_SCANCODE_RIGHT)) {
		plFacing = 6;
		velocity[0] = plMaxSpeed;
		velocity[1] = 0;
	}
	else {
		velocity[0] = 0;
	}
}

void CPlayer::playerPhysics() {
	keyHandler();
	positionUpdater();
}

void CPlayer::positionUpdater() {
	time_delta = m_struct.time_unit.sdl_time - lastUpdate;
	reduced_delta = time_delta / 10.0;
	setX(getX() + (int)(velocity[0] * reduced_delta));
	setY(getY() + (int)(velocity[1] * reduced_delta));
	lastUpdate = m_struct.time_unit.sdl_time;
}
void CPlayer::setX(int passed_x)
{
	x = passed_x;
}

void CPlayer::setY(int passed_y)
{
	y = passed_y;
}