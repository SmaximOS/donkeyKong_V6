#pragma once
#include <iostream>
#include "MovableObject.h"
#include "general.h"

using namespace std;

class Ghost : public MovableObject
{
  public:
	Ghost(Point _pos,char rep='x');
	virtual void move() ;
};

