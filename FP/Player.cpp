#include "Player.h"
#include "bw_structs.h"

extern mainData dataUnit;



CPlayer::CPlayer(int initial_x, int initial_y)
	:x(initial_x),y(initial_y)
{
	colorColOffset = 0;
	colorRowOffset = 0;
	plColorIndex = 0;
	plColorSet = false;
	animCol = 0;
	plFacing = 0;
	plID = 0;
	plMaxSpeed = 2;
	velocity[0] = 0;
	velocity[1] = 0;
	spriteScale = 2.0;
	lastUpdate = m_struct.time_unit.sdl_time;
}


CPlayer::~CPlayer()
{
}

void CPlayer::controls() {
	keyHandler();
}

void CPlayer::Draw() {
	if (!plColorSet) {
		setPlColor();
		plColorSet = true;
	}
	if (velocity[0] > 0) plFacing = 6;
	else if (velocity[0] < 0) plFacing = 2;
	else if (velocity[1] > 0) plFacing = 4;
	else if (velocity[1] < 0) plFacing = 0;
	animCol = ((getX()/5)%2) ? (((getY()/5)%2)?1:0) : (((getY()/5)%2)?0:1);
	dataUnit.mastersprite->Draw(animCol+plFacing+colorColOffset, colorRowOffset, x, y, spriteScale);
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
		velocity[0] =  0;
	}
	else if (FP_isPressed(SDL_SCANCODE_DOWN)) {
		velocity[1] = plMaxSpeed;
		velocity[0] = 0;
	}
	else {
		velocity[1] = 0;
	}
	if (FP_isPressed(SDL_SCANCODE_LEFT)) {
		velocity[0] = -plMaxSpeed;
		velocity[1] = 0;
	}
	else if (FP_isPressed(SDL_SCANCODE_RIGHT)) {
		velocity[0] = plMaxSpeed;
		velocity[1] = 0;
	}
	else {
		velocity[0] = 0;
	}
}

void CPlayer::playerPhysics() {
	positionUpdater();
}

void CPlayer::positionUpdater() {
	time_delta = m_struct.time_unit.sdl_time - lastUpdate;
	reduced_delta = time_delta / 10.0;
	setX(getX() + (int)(velocity[0] * reduced_delta));
	setY(getY() + (int)(velocity[1] * reduced_delta));
	lastUpdate = m_struct.time_unit.sdl_time;
}

void CPlayer::setID(int id) {
	plID = id;
}

void CPlayer::setPlColor(){
	plColorIndex = plID % 4;
	std::cout << "Player Color Index set to : " << plColorIndex << std::endl;
	if (plColorIndex == 1) {
		colorRowOffset = 8;
	}
	else if (plColorIndex == 2) {
		colorColOffset = 8;
		colorRowOffset = 8;
	}
	else if (plColorIndex == 3) {
		colorColOffset = 8;
	}
}
void CPlayer::setX(int passed_x)
{
	x = passed_x;
}

void CPlayer::setY(int passed_y)
{
	y = passed_y;
}

void CPlayer::setPlVelocity(int vx, int vy) {
	velocity[0] = vx;
	velocity[1] = vy;
	return;
}