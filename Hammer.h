#pragma once
#include "GameObject.h"
#include <iostream>
class Hammer : public GameObject
{
private:
	bool isVisible;
public:
	Hammer(Point _pos) : GameObject('P',_pos) { isVisible = true; }
	Hammer() : isVisible(false),GameObject('P') {}
	bool getIsVisible() const { return isVisible; }
	void setIsVisible(bool _isVisible) { isVisible = _isVisible; }
	void draw() const;
};

