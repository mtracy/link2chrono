#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

using namespace sf;
class Character;


class Projectile
{
public:
	enum Types {
		PotionType,
		MeleeType
	};

	Projectile(float speed, float range, float angle, float dmg, Vector2f position, Character& owner);

	static std::unique_ptr<Projectile> factory(Projectile::Types weap, float speed, float range, float angle, float dmg, Vector2f position, Character& owner);
	void setPosition(Vector2f pos);
	void setDistanceTraveled(float dist);
	void setSpeed(float speed);
	void setAngle(float angle);
	void setCanDmgSelf(bool selfdmg);
	bool getCanDmgSelf();
	float getImpactDmg();
	RectangleShape getDrawable();
	Character& getOwner();
	virtual bool update(float elapsedTime) = 0;

	Vector2f m_Position;
	float m_Speed;
	float m_DistTraveled;
	float m_Maxrange;
	float m_Angle;
	float m_ImpactDmg;
	bool m_CanDmgSelf;
	RectangleShape m_Shape;
	Character& m_Owner;
};


class PotionProjectile : public Projectile
{
public:
	PotionProjectile(float speed, float range, float angle, float dmg, Vector2f position, Character& owner);
	bool update(float elapsedTime);
};

class MeleeProjectile : public Projectile
{
public:
	MeleeProjectile(float speed, float range, float angle, float dmg, Vector2f position, Character& owner);
	bool update(float elapsedTime);
};