#pragma once
#include "Point.h"
#include "general.h"
#include <iostream>
class GameObject
{
protected :
	char representation;
	Point pos;
public : 
	GameObject(char _representation, Point _pos) : pos(_pos), representation(_representation){}
	GameObject(char _representation) : representation(_representation){}
	void draw() const {
		gotoxy(pos.getX(), pos.getY());std::cout << representation;
	}
	char getRepresentation() { return representation; };
	Point getPos() const { return pos; } 
	void setPos(const Point& _newpos) { pos = _newpos; }
	GameObject operator =(const GameObject& other);
	virtual ~GameObject() {} //Make the class polymorphic
};

