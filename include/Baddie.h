#pragma once
#include "Character.h"

class Baddie : public Character
{
public:
	Baddie(Engine *eng);
	void update(float elapsedTime);
};