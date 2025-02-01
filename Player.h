#pragma once
#include "MovableObject.h"
#include "general.h"
class Player :public MovableObject
{

private:
	GameConfig::ARROWKEYS dirHammer;
public:
	Player(char _representation, Point _pos) : MovableObject(_representation, _pos, GameConfig::ARROWKEYS::STAY) { dirHammer = GameConfig::ARROWKEYS::STAY; }
	void setDir(GameConfig::ARROWKEYS newdir, bool sethammerdir = true);
	void setHammer(GameConfig::ARROWKEYS havinghammer) { dirHammer = havinghammer; };
	GameConfig::ARROWKEYS getHammer() const { return dirHammer; };
	void draw(bool climbmode = false) const;
	
};
