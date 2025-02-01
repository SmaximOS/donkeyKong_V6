#pragma once
#include "GameObject.h"
#include "GameConfig.h"
class MovableObject : public GameObject
{
protected:
	GameConfig::ARROWKEYS dir;
public: 
	MovableObject(char _representation,Point _pos,GameConfig::ARROWKEYS _dir) : GameObject(_representation,_pos), dir(_dir) {}
	GameConfig::ARROWKEYS getDir () const { return dir; }
	void setDir(GameConfig::ARROWKEYS _dir) { dir = _dir; }
	void move();
};

