#pragma once
#include <SFML/Graphics.hpp>
#include "PlayableCharacter.h"

using namespace sf;

class Hud
{
private:
	Font m_Font;
	Text m_StartText;
	Text m_TimeText;
	Text m_LevelText;

public:
	Hud();
	Text getMessage();
	Text getLevel();
	Text getTime();

	void setLevel(String text);
	void setTime(String text);
	void updateHUD(float timeRemaining, PlayableCharacter& player);
};