#include "stdafx.h"
#include "Baddie.h"
#include "TextureHolder.h"
#include <iostream>
#include "Weapon.h"
#include "Engine.h"



Baddie::Baddie(Engine *eng)
{
	// Associate a texture with the sprite
	//std::cout << "baddie constructor called" << std::endl;
	m_Speed = 200;
	m_Health = 20;
	m_IsAlive = true;
	m_Eng = eng;

	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/bob.png"));
	m_Origin = Vector2f(25, 25);
	m_Inventory.addWeapon(std::shared_ptr<Weapon>(new Melee()));
	setRHItem(m_Inventory.getWeapon(0));
	setName("Patul");
}

void Baddie::update(float elapsedTime)
{
	if (m_IsAlive)
	{
		getRHItem()->update(elapsedTime);
		Vector2f playerpos = m_Eng->getPlayer()->m_Position;
		auto diffy = m_Position.y - playerpos.y;
		auto diffx = m_Position.x - playerpos.x;
		float rads = atan2(diffy, diffx);
		rads += 3.1415;
		m_trajectory = rads;
		m_Position.x += m_Speed * elapsedTime * cos(rads);
		m_Position.y += m_Speed * elapsedTime * sin(rads);
		m_Sprite.setPosition(m_Position);
		updateRegions();
		float distance = sqrt(diffy*diffy + diffx*diffx);
		if (distance <= 50 && getRHItem()->getCurrCD() <= 0)
		{
			
			auto p = getRHItem()->Use(rads, m_Position, *this);
			m_Eng->m_Projectiles.push_back(std::move(p));
		}
		//std::cout << m_Position.x << ", " << m_Position.y << std::endl;
	}
}