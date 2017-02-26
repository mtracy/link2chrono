#include "stdafx.h"
#include "Activatable.h"
#include <iostream>
#include "Engine.h"

Chest::Chest(std::unique_ptr<Item> item, sf::Vector2u pos) : m_Contents(std::move(item)), m_Filled(true) { m_Position = pos; }

void Chest::activate(Character& actor, Environment *env) {
	if (m_Filled) {
		std::cout << "activated chest" << std::endl;
		actor.addItem(std::move(m_Contents));
		m_Filled = false;
		auto empty = IntRect(50, 50, 50, 50);
		env->setObjectVertexTexture(m_Position, empty);
	}
}

bool Chest::isFilled() {
	return m_Filled;
}
