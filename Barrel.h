#pragma once
#include <iostream>
#include "MovableObject.h"
#include "general.h"


class Barrel : public MovableObject
{
private:
	int fallsecs;
	
public:
	Barrel(Point _startpos, GameConfig::ARROWKEYS _dir) : MovableObject('O', _startpos, _dir) { fallsecs = 0; }
	void move();
	int getFallSecs() const { return fallsecs; }
	void setFallSecs(int _fallsecs) { fallsecs = _fallsecs; }
};
	
typedef struct  LEVELSETTINGS
{
	int size; //The size of the barrels array to repeat  
	int* intervalsBetweenBarrels; //the intervals between each barrel (size)
	GameConfig::ARROWKEYS* dirs; // the initial direction of each barrel

} LevelSettings;