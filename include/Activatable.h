#pragma once
#include "Item.h"
//#include "Environment.h"
#include "Character.h"
#include <SFML/Graphics.hpp>

class Environment;

class Activatable {
public:
	virtual void activate(Character &actor, Environment *env) = 0;
	sf::Vector2u m_Position;
};

class Chest : public Activatable {
public:
	Chest(std::unique_ptr<Item>, sf::Vector2u);
	void activate(Character& actor, Environment *env);
	//void setContents(std::unique_ptr<Item> item);
	bool isFilled();


private:
	std::unique_ptr<Item> m_Contents;
	bool m_Filled;
};