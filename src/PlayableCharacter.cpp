#include "PlayableCharacter.h"
#include "Projectile.h"
#include <iostream>
#include <memory>
#include "Engine.h"

using ProjVec = std::vector<std::unique_ptr<Projectile>>;

Character::Dir dirFromRads(float rads) {
	float pi = 3.1415926;
	if (rads > pi / 4 && rads <= 3 * pi / 4) {
		return Character::Dir::Up;
	}
	else if (rads > 3 * pi / 4 && rads <= 5 * pi / 4) {
		return Character::Dir::Right;
	}
	else if (rads > 5 * pi / 4 && rads <= 7 * pi / 4) {
		return Character::Dir::Down;
	}
	else {
		return Character::Dir::Left;
	}

}


void PlayableCharacter::updatePosition(float elapsedTime) {
	int ydel(0);
	int xdel(0);
	float speed(m_Speed);

	if (m_UpPressed && !m_CollidingUp)
	{
		ydel--;
	}

	if (m_DownPressed && !m_CollidingDown)
	{
		ydel++;
	}

	if (m_RightPressed && !m_CollidingRight)
	{
		xdel++;
	}

	if (m_LeftPressed && !m_CollidingLeft)
	{
		xdel--;
	}

	if (xdel != 0 && ydel != 0) {
		speed *= .707106;
	}

	m_trajectory = atan2(ydel, xdel);

	m_Position.x += xdel * speed * elapsedTime;
	m_Position.y += ydel * speed * elapsedTime;

}

void PlayableCharacter::update(float elapsedTime)
{

	//std::cout << m_Speed << " * " << elapsedTime << std::endl;
	float rads = atan2(m_Eng->mouseWorldPosition.y - m_Position.y,
		m_Eng->mouseWorldPosition.x - m_Position.x) + 3.1415;

	updatePosition(elapsedTime);
	resetColliding();
	getRHItem()->update(elapsedTime);

	auto dirfacing = dirFromRads(rads);

	updateRegions();

	// Move the sprite into position
	m_Sprite.setPosition(m_Position);
	
	switch (dirfacing) {
		case Character::Dir::Up:
			m_Sprite.setTextureRect(m_UpPosition);
			break;
		case Character::Dir::Down:
			m_Sprite.setTextureRect(m_DownPosition);
			break;
		case Character::Dir::Left:
			m_Sprite.setTextureRect(m_LeftPosition);
			break;
		case Character::Dir::Right:
			m_Sprite.setTextureRect(m_RightPosition);
			break;
		default:
			m_Sprite.setTextureRect(m_DownPosition);
			break;
	}
	

	if (m_SpacePressed)
	{
		auto p = getRHItem()->Use(rads + 3.1415, m_Position, *this);
		if (p != nullptr) {
			m_Eng->m_Projectiles.push_back(std::move(p));
		}
	}

	if (m_Num1Pressed) {
		auto p = m_Inventory.getWeapon(0);
		if (p != nullptr) {
			setRHItem(p);
		}
	}

	if (m_Num2Pressed) {
		auto p = m_Inventory.getWeapon(1);
		if (p != nullptr) {
			setRHItem(p);
		}
	}

	if (m_Num3Pressed) {
		auto p = m_Inventory.getWeapon(2);
		if (p != nullptr) {
			setRHItem(p);
		}
	}

	if (m_EPressed) {
		activate(dirfacing);
	}


	// Update the rect for all body parts	

	//Vector2f center = getCenter();

	// calculate rotation in degrees and subtract 90 for the sprite offset
	//m_Sprite.setRotation(rads * 180 / 3.141 - 90);

}



void PlayableCharacter::activate(Character::Dir dir) {
	//rads += 3.1415926;
	int vecposy = m_Position.y / Engine::getTileSize();
	int vecposx = m_Position.x / Engine::getTileSize();
	//std::cout << "at " << vecposx << ", " << vecposy << "; ";
	switch (dir)
	{
	case Character::Up:
		vecposy--;
		break;
	case Character::Down:
		vecposy++;
		break;
	case Character::Left:
		vecposx--;
		break;
	case Character::Right:
		vecposx++;
		break;
	default:
		break;
	}
	//std::cout << rads << "->" << dir << std::endl;
	auto active = m_Eng->getActive(vecposx, vecposy);
	if (active == nullptr) {
		return;
	}
	else {
		//std::cout << "HIT" << std::endl;
		active->activate(*this, &(m_Eng->m_Env));
	}

}




