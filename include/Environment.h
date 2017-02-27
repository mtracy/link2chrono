#pragma once
#include "Scaffold.h"
#include "Activatable.h"
#include <SFML/Graphics.hpp>
#include <tmx/MapLoader.h>




class Environment : public sf::Drawable  {
public:
	Environment();
	void loadLevel();
	tmx::MapLoader m_ml;
	virtual void draw(sf::RenderTarget &window, sf::RenderStates states) const { 
		window.draw(m_ml);
	};

	void update(const sf::FloatRect& rootArea) {
		m_ml.UpdateQuadTree(rootArea);
	}

	std::vector<tmx::MapObject*> getIntersects(sf::FloatRect box) {
		return m_ml.QueryQuadTree(box);
	}

	std::unique_ptr<sf::FloatRect> convertToFloatRect(tmx::MapObject*);	

	std::vector<std::unique_ptr<sf::FloatRect>> convertToFloatRect(std::vector<tmx::MapObject*>&);

};