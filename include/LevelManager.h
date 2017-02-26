#pragma once

#include <SFML/Graphics.hpp>
#include "Environment.h"
using namespace sf;
using namespace std;


class LevelManager
{
private:
	
	Vector2f m_StartPosition;
	float m_TimeModifier = 1;
	float m_BaseTimeLimit = 0;
	int m_CurrentLevel = 0;
	const int NUM_LEVELS = 4;

public:



	float getTimeLimit();

	Vector2f getStartPosition();

	void nextLevel(Environment& env);

	

	int getCurrentLevel();

};
