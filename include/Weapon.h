#pragma once
#include "Item.h"
#include "Projectile.h"
#include <SFML/Graphics.hpp>



class Weapon : public Item {
	
public:
	Weapon();
	virtual std::unique_ptr<Projectile> Use(float angle, Vector2f position, Character& owner) = 0;
	float m_Speed;
	float m_Range;
	float m_Damage;
	float m_MaxCD;
	float m_CurrCD = 0;

	
	void draw(sf::RenderTarget & window, sf::RenderStates states) const;
	void setMaxCD(float cd);
	float getMaxCD();
	void setCurrCD(float cd);
	float getCurrCD();
	Item::Type getType();
	void update(float elapsedTime) {
		if (getCurrCD() > 0) {
			setCurrCD(getCurrCD() - elapsedTime);
		}
	};
};

class Potion : public Weapon {
public:
	Potion();
	std::unique_ptr<Projectile> Use(float angle, Vector2f position, Character& owner);	
};

class Melee : public Weapon {
public:
	Melee();
	std::unique_ptr<Projectile> Use(float angle, Vector2f position, Character& owner);
};