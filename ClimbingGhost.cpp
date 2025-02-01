#include "ClimbingGhost.h"


ClimbingGhost::ClimbingGhost(Point _pos) : Ghost(_pos, 'X'), isNearLadder(false)
{
	Reset();
}
void ClimbingGhost::Reset()
{
	ladderSteps[0] = ladderSteps[1] = 0;
	climb[0] = climb[1] = 0;
	indexOfcurrladder[0] = indexOfcurrladder[1] = -1;
	currArrIndex = -1;
}
void ClimbingGhost::move() 
{
	switch (dir)
	{
	case GameConfig::UP:
		(pos.setY(pos.getY() - 1));
		climb[currArrIndex]--;
		break;
	case GameConfig::DOWN:
		(pos.setY(pos.getY() + 1));
		climb[currArrIndex]--;
		break;
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