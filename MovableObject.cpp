#include "MovableObject.h"
void MovableObject::move()
{
	switch (dir)
	{
	case GameConfig::UP:
		(pos.setY(pos.getY() - 1));
		break;
	case GameConfig::DOWN:
		(pos.setY(pos.getY() + 1));
		break;
	case GameConfig::RIGHT:
		(pos.setX(pos.getX() + 1));
		break;
	case GameConfig::LEFT:
		(pos.setX(pos.getX() - 1));
		break;
	case GameConfig::STAY:
		break;
	case GameConfig::DOWNANDLEFT:
		(pos.setY(pos.getY() + 1));
		(pos.setX(pos.getX() - 1));
		break;
	case GameConfig::DOWNANDRIGHT:
		(pos.setY(pos.getY() + 1));
		(pos.setX(pos.getX() + 1));
		break;
	case GameConfig::UPANDLEFT:
		(pos.setY(pos.getY() - 1));
		(pos.setX(pos.getX() - 1));
		break;
	case GameConfig::UPANDRIGHT:
		(pos.setY(pos.getY() - 1));
		(pos.setX(pos.getX() + 1));
		break;
	}
}