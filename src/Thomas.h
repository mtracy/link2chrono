#pragma once
#include "PlayableCharacter.h"

class Thomas : public PlayableCharacter
{
public:
	Thomas::Thomas(Engine *eng);
	bool virtual handleInput();
};
