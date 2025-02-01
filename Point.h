#pragma once
#include "GameConfig.h"
#include <cmath>
class Point
{
	int x;
	int y;

public:
	Point(int x = 0, int y = 0);
	
	double calculateDistance(const Point& other);
	int getX() const { return x; };
	int getY() const { return y; };
	void setX(int x) { this->x = x; };
	void setY(int y) { this->y = y; };
	bool operator ==(const Point& other) { return x == other.x && y == other.y; };
};