#include "Barrel.h"


void Barrel::move()
{
	MovableObject::move();
	if (dir == GameConfig::DOWNANDLEFT || dir == GameConfig::DOWNANDRIGHT)
		fallsecs++;
}