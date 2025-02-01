#include "Ghost.h"


Ghost::Ghost(Point _pos,char rep) : MovableObject(rep, _pos, GameConfig::ARROWKEYS::STAY)
{
	//Generate rand number 0 or 1 for the starting moving direction
	char num = rand() % 2;
	num == 0 ? dir = GameConfig::ARROWKEYS::RIGHT : dir = GameConfig::ARROWKEYS::LEFT;
	pos = _pos;
}
void Ghost::move()
{
	switch (dir)
	{

	case GameConfig::RIGHT:
		(pos.setX(pos.getX() + 1));
		break;
	case GameConfig::LEFT:
		(pos.setX(pos.getX() - 1));
		break;
	case GameConfig::STAY:
		break;
	}
	
}


