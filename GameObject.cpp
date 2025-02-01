#include "GameObject.h"
GameObject GameObject:: operator =(const GameObject& other)
{
	if (&other != this)
	{
		this->pos = other.pos;
		this->representation = other.representation;
	}
		
	return *this;
	//Not copying representation because its const
}