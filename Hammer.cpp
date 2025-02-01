#include "Hammer.h"

void Hammer::draw() const //Overrides Base function
{
	if (isVisible)
		GameObject::draw();
}