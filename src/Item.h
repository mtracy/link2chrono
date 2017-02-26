#pragma once
#include <SFML/Graphics.hpp>

class Item : public sf::Drawable {
public:
	enum Type {
		Weapon,
		Armor,
		Consumable
	};

	Type m_Type;
	sf::Sprite m_Sprite;
	sf::Texture m_Texture;

	virtual Type getType() = 0;
	virtual void draw(sf::RenderTarget &window, sf::RenderStates states) const = 0;

};