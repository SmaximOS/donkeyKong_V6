#pragma once
#include "Ghost.h"
class ClimbingGhost : public Ghost
{
private:

	int ladderSteps[2];
	int climb[2];
	int indexOfcurrladder[2];
	int currArrIndex; //0 or 1 to decide which ladder to go
	bool isNearLadder;

public:
	ClimbingGhost(Point _pos);
	void move() override;

	int* getLadderSteps()  { return ladderSteps; }
	int* getClimb()  { return climb; }
	bool getIsNearLadder() const { return isNearLadder; }
	int* getIndexofcurrladder() { return indexOfcurrladder; }
	int getarrIndex() const { return currArrIndex; }

	void setisNearLadder(bool sign) { isNearLadder = sign; }
	void setArrIndex(int index) { currArrIndex=index; }
	void Reset();
};

