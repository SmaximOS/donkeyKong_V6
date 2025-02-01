#include "Point.h"
Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}
double Point::calculateDistance(const Point& other)
{
	int dx = x - other.x;
	int dy = y - other.y;
	return sqrt(pow(dx, 2) + pow(dy, 2));
}

