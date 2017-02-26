#include "stdafx.h"
#include "Weapon.h"
#include "TextureHolder.h"

Weapon::Weapon() {
	m_Type = Item::Type::Weapon;
}

void Weapon::setMaxCD(float cd)
{
	m_MaxCD = cd;
}

float Weapon::getMaxCD()
{
	return m_MaxCD;
}

void Weapon::setCurrCD(float cd)
{
	m_CurrCD = cd;
}

float Weapon::getCurrCD()
{
	return m_CurrCD;
}

Item::Type Weapon::getType() {
	return m_Type;
}

void Weapon::draw(sf::RenderTarget &window, sf::RenderStates states) const
{
	window.draw(m_Sprite);
}

Potion::Potion() {
	m_Speed = 500;
	m_Range = 500;
	m_Damage = 15;
	m_MaxCD = 3;
	m_Texture = TextureHolder::GetTexture(
		"graphics/items/weapons/potion.png");
	m_Sprite.setTexture(m_Texture);
}

std::unique_ptr<Projectile> Potion::Use(float angle, Vector2f position, Character& owner) {
	if (getCurrCD() <= 0) {
		setCurrCD(getMaxCD());
		return Projectile::factory(Projectile::PotionType, m_Speed, m_Range, angle, m_Damage, position, owner);
	}
	else {
		return nullptr;
	}
}




Melee::Melee() {
	m_Speed = 500;
	m_Range = 40;
	m_Damage = 15;
	m_MaxCD = 1;

	m_Texture = TextureHolder::GetTexture(
		"graphics/items/weapons/melee.png");

	m_Sprite.setTexture(m_Texture);
}

std::unique_ptr<Projectile> Melee::Use(float angle, Vector2f position, Character& owner) {
	if (getCurrCD() <= 0) {
		setCurrCD(getMaxCD());
		return Projectile::factory(Projectile::PotionType, m_Speed, m_Range, angle, m_Damage, position, owner);
	}
	else {
		return nullptr;
	}
}