#include "Environment.h"
#include <sstream>
#include <fstream>
#include <iostream>

//#include <string>

Environment::Environment() : m_ml("/home/mitchell/link2chrono/levels") {}

void Environment::loadLevel() {
	m_ml.Load("cliff.tmx");
	//assert(m_ml.GetLayers().size() > 1);
}

std::unique_ptr<sf::FloatRect> Environment::convertToFloatRect(tmx::MapObject* mo) {
	auto position = mo->GetPosition();
	auto size = mo->PolyPoints()[2];
	return std::unique_ptr<sf::FloatRect>(new FloatRect(position, size));    			
}

std::vector<std::unique_ptr<sf::FloatRect> > Environment::convertToFloatRect(std::vector<tmx::MapObject*>& mos) {
	std::vector<std::unique_ptr<sf::FloatRect> > floatrects;

	for (auto mo : mos) {
		floatrects.push_back(convertToFloatRect(mo));
	}
	return floatrects;
}