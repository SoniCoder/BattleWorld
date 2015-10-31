#pragma once
class CPlayer
{
public:
	CPlayer(int initial_x,int initial_y);
	~CPlayer();
	int getX();
	int getY();
	void setX(int passed_x);
	void setY(int passed_y);
private:
	int x;
	int y;
};
