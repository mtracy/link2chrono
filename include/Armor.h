#pragma once
#include "Item.h"
#include "TextureHolder.h"

class Armor : public Item {

public:
	Armor() { m_Type = Item::Type::Armor; }
	void draw(sf::RenderTarget &window, sf::RenderStates states) const
	{
		window.draw(m_Sprite);
	}


	Item::Type getType() {
		return m_Type;
	}
};

class HeadArmor : public Armor {
public:
	HeadArmor() {
		m_Texture = TextureHolder::GetTexture(
			"graphics/items/armor/hood.png");
		m_Sprite.setTexture(m_Texture);
	}
};

class ChestArmor : public Armor {
public:
	ChestArmor() {
		m_Texture = TextureHolder::GetTexture(
			"graphics/items/armor/robes.png");
		m_Sprite.setTexture(m_Texture);
	}
};

class FeetArmor : public Armor {
public:
	FeetArmor() {
		m_Texture = TextureHolder::GetTexture(
			"graphics/items/armor/leatherboots.png");
		m_Sprite.setTexture(m_Texture);
	}
};

class Shield : public Armor {
public:
	Shield() {
		m_Texture = TextureHolder::GetTexture(
			"graphics/items/weapons/shield.png");
		m_Sprite.setTexture(m_Texture);
	}
};
