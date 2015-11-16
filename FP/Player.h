#ifndef HPLAYER
#define HPLAYER

#include "Engine.h"

class CPlayer
{
public:
	CPlayer(int initial_x,int initial_y);
	~CPlayer();
	int getX();
	int getY();
	int getVx();
	int getVy();
	void controls();
	void keyHandler();
	void setX(int passed_x);
	void setY(int passed_y);
	void setWidth(float w);
	void setHeight(float h);
	void Draw();
	void playerPhysics();
	void positionUpdater();
	void setID(int id);
	void setPlColor();
	void setPlVelocity(int vx, int vy);
private:
	bool plColorSet;

	int animCol;
	int colorColOffset;
	int colorRowOffset;
	int plColorIndex;
	int plFacing;
	int plID;
	int plMaxSpeed;
	int time_delta;
	int velocity[2];
	int x;
	int y;
	
	float reduced_delta;
	float spriteScale;
	Uint32 lastUpdate;
};
#endif