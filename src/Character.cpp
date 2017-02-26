#include "stdafx.h"
#include "Character.h"
#include <memory>
#include "TextureHolder.h"
#include <iostream>

using namespace sf;
using ProjVec = std::vector<std::unique_ptr<Projectile>>;
using CharVec = std::vector<std::unique_ptr<Character>>;


void Character::spawn(Vector2f startPosition)
{
	// Place the player at the starting point

	m_Position.x = startPosition.x;
	m_Position.y = startPosition.y;
	m_Resolution.x = VideoMode::getDesktopMode().width;
	m_Resolution.y = VideoMode::getDesktopMode().height;


	m_Sprite.setOrigin(m_Origin);
	// Move the sprite in to position
	m_Sprite.setPosition(m_Position);


}

FloatRect Character::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

float Character::getTrajectory() {
	return m_trajectory;
}


Vector2f Character::getOrigin()
{
	return m_Origin;
}

Vector2f Character::getCenter()
{
	return Vector2f(
		m_Position.x + m_Sprite.getGlobalBounds().width / 2,
		m_Position.y + m_Sprite.getGlobalBounds().height / 2
	);
}

Sprite Character::getSprite()
{
	return m_Sprite;
}

float Character::getHealth()
{
	return m_Health;
}

float Character::setHealth(float health)
{
	m_Health = (health < 0) ? 0 : health;
	return m_Health;
}

FloatRect Character::getHitBox()
{
	return m_Sprite.getGlobalBounds();
}

void Character::setAlive(bool alive)
{
	m_IsAlive = alive;
}

void Character::setName(std::string name)
{
	m_Name = name;
}

std::string Character::getName()
{
	return m_Name;
}

void Character::updateRegions()
{
	FloatRect r = getPosition();
	printf("%f, %f, %f, %f\n", r.top, r.left, r.height, r.width);

	// Feet
	m_Feet.left = r.left + 6;
	m_Feet.top = r.top + r.height - 1;
	m_Feet.width = r.width - 12;
	m_Feet.height = 1;

	// Head
	m_Head.left = r.left + 6;
	m_Head.top = r.top;
	m_Head.width = r.width - 12;
	m_Head.height = 1;

	// Right
	m_Right.left = r.left + r.width - 1;
	m_Right.top = r.top + 5;
	m_Right.width = 1;
	m_Right.height = r.height - 10;

	// Left
	m_Left.left = r.left;
	m_Left.top = r.top + 5;
	m_Left.width = 1;
	m_Left.height = r.height - 10;
}

FloatRect Character::getFeet()
{
	return m_Feet;
}

FloatRect Character::getHead()
{
	return m_Head;
}

FloatRect Character::getLeft()
{
	return m_Left;
}

FloatRect Character::getRight()
{
	return m_Right;
}

void Character::stopDir(Dir dir, float dtAsSeconds)
{
	switch (dir)
	{
	case Character::Down:
		m_Position.y -= m_Speed * dtAsSeconds;
		break;
	case Character::Up:
		m_Position.y += m_Speed * dtAsSeconds;
		break;
	case Character::Left:
		m_Position.x += m_Speed * dtAsSeconds;
		break;
	case Character::Right:
		m_Position.x -= m_Speed * dtAsSeconds;
		break;
	default:
		break;
	}
	m_Sprite.setPosition(m_Position);
}


void Character::addItem(std::unique_ptr<Item> item) {
	m_Inventory.addItem(std::shared_ptr<Item>(std::move(item)));
}