#pragma once
#include "Character.h"

using namespace sf;
using ProjVec = std::vector<std::unique_ptr<Projectile>>;
using CharVec = std::vector<std::unique_ptr<Character>>;

class PlayableCharacter : public Character
{
protected:
	bool m_LeftPressed;
	bool m_RightPressed;
	bool m_UpPressed;
	bool m_DownPressed;
	bool m_SpacePressed;
	bool m_Num1Pressed;
	bool m_Num2Pressed;
	bool m_Num3Pressed;
	bool m_EPressed;



public:
	
	
	void updatePosition(float elapsedTime);
	void update(float elapsedTime);
	bool virtual handleInput() = 0;	
	void activate(Character::Dir);
	
};
