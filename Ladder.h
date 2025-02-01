#pragma once
#include "GameObject.h"
class Ladder : public GameObject
{
	int steps;
public:
	Ladder(Point _startpos, int _steps = 1) : GameObject('H',_startpos),steps(_steps*GameConfig::FLOORDIFF){}
	void draw() const;
	int getSteps() const { return steps; }
	Ladder operator =(const Ladder& other);
};

typedef struct Laddebuild
{

}Ladderbuild;
