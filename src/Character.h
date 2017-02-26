#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Projectile.h"
#include "Weapon.h"
#include "Inventory.h"

using namespace sf;
using ProjVec = std::vector<std::unique_ptr<Projectile>>;
class Engine;


using namespace sf;
class Character
{
public:
	enum Dir { Right, Up, Left, Down};
	enum Piece {
		HEAD,
		CHEST,
		LHAND,
		RHAND,
		FEET
	};
	Sprite m_Sprite;
	Vector2f m_Resolution;
	Vector2f m_Origin;
	Vector2f m_Position;
	Texture m_Texture;
	float m_Health;
	bool m_IsAlive;
	float m_Speed;
	Inventory m_Inventory;
	Engine *m_Eng; //lol.
	float m_trajectory = 0;
	
	virtual void Character::update(float) = 0;
	float getTrajectory();
	void addItem(std::unique_ptr<Item>);
	float getHealth();
	FloatRect getPosition();
	Sprite getSprite();
	Vector2f getCenter();
	Vector2f getOrigin();
	void spawn(Vector2f startPosition);
	float setHealth(float health);
	void setAlive(bool alive);
	void updateRegions();
	FloatRect getHitBox();
	FloatRect getFeet();
	FloatRect getHead();
	FloatRect getRight();
	FloatRect getLeft();	
	void stopDir(Dir dir, float dtAsSeconds);
	void setName(std::string name);
	std::string getName();
	

private:
	FloatRect m_Feet;
	FloatRect m_Head;
	FloatRect m_Right;
	FloatRect m_Left;
	std::string m_Name;
	std::map<const Piece, std::shared_ptr<Item>> m_Equipped;

public:
	std::shared_ptr<Item> getHeadItem() { return m_Equipped[HEAD]; }
	std::shared_ptr<Item> getChestItem() { return m_Equipped[CHEST]; }
	std::shared_ptr<Weapon> getRHItem() { return std::dynamic_pointer_cast<Weapon>(m_Equipped[RHAND]); }
	std::shared_ptr<Item> getLHItem() { return m_Equipped[LHAND]; }
	std::shared_ptr<Item> getFeetItem() { return m_Equipped[FEET]; }

	void setHeadItem(std::shared_ptr<Item> i) { m_Equipped[HEAD] = i; }
	void setChestItem(std::shared_ptr<Item> i) { m_Equipped[CHEST] = i; }
	void setRHItem(std::shared_ptr<Weapon> i) { m_Equipped[RHAND] = i; }
	void setLHItem(std::shared_ptr<Item> i) { m_Equipped[LHAND] = i; }
	void setFeetItem(std::shared_ptr<Item> i) { m_Equipped[FEET] = i; }
};