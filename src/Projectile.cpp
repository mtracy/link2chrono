#include "Projectile.h"
#include "Weapon.h"
#include <memory>

using namespace sf;
using namespace std;


std::unique_ptr<Projectile> Projectile::factory(Projectile::Types weap, float speed, float range, float angle, float dmg, Vector2f position, Character& owner)
{
	switch (weap)
	{
	case Projectile::PotionType:
		return std::unique_ptr<PotionProjectile>(new PotionProjectile(speed, range, angle, dmg, position, owner));
		break;
	case Projectile::MeleeType:
		return std::unique_ptr<MeleeProjectile>(new MeleeProjectile(speed, range, angle, dmg, position, owner));
		break;
	default:
		return nullptr;
		break;
	}
}

Projectile::Projectile(float speed, float range, float angle, float dmg, Vector2f position, Character& owner)
	: m_Speed(speed), m_Maxrange(range), m_Angle(angle), m_ImpactDmg(dmg), m_Position(position), m_DistTraveled(0), m_Owner(owner)
{
}

void Projectile::setPosition(Vector2f pos)
{
	m_Position = pos;
}

void Projectile::setDistanceTraveled(float dist)
{
	m_DistTraveled = dist;
}

void Projectile::setSpeed(float speed)
{
	m_Speed = speed;
}

void Projectile::setAngle(float angle)
{
	m_Angle = angle;
}

float Projectile::getImpactDmg()
{
	return m_ImpactDmg;
}

RectangleShape Projectile::getDrawable()
{
	return m_Shape;
}

Character& Projectile::getOwner()
{
	return m_Owner;
}

void Projectile::setCanDmgSelf(bool selfdmg)
{
	m_CanDmgSelf = selfdmg;
}

bool Projectile::getCanDmgSelf()
{
	return m_CanDmgSelf;
}


PotionProjectile::PotionProjectile(float speed, float range, float angle, float dmg, Vector2f position, Character& owner)
	: Projectile(speed, range, angle, dmg, position, owner)
{
	m_Shape.setSize(sf::Vector2f(5, 5));
	m_Shape.setPosition(m_Position);
	setCanDmgSelf(false);
}

bool PotionProjectile::update(float elapsedTime)
{
	m_Position.x += m_Speed * elapsedTime * cos(m_Angle);
	m_Position.y += m_Speed * elapsedTime * sin(m_Angle);
	m_DistTraveled += m_Speed * elapsedTime;
	m_Shape.setPosition(m_Position);
	return m_DistTraveled >= m_Maxrange;
}

MeleeProjectile::MeleeProjectile(float speed, float range, float angle, float dmg, Vector2f position, Character& owner)
	: Projectile(speed, range, angle, dmg, position, owner)
{
	m_Shape.setSize(sf::Vector2f(15, 5));
	m_Shape.setPosition(m_Position);
	setCanDmgSelf(false);
}

bool MeleeProjectile::update(float elapsedTime)
{
	//m_Shape.setSize(sf::Vector2f(5, 5));
	m_Position.x += m_Speed * elapsedTime * cos(m_Angle);
	m_Position.y += m_Speed * elapsedTime * sin(m_Angle);
	m_DistTraveled += m_Speed * elapsedTime;
	m_Shape.setPosition(m_Position);
	return m_DistTraveled >= m_Maxrange;
}