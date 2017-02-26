#include "stdafx.h"
#include "Inventory.h"
#include "Item.h"


void Inventory::addItem(std::shared_ptr<Item> item) {
	switch (item->getType())
	{
	case Item::Type::Weapon:
		addWeapon(std::dynamic_pointer_cast<Weapon> (item));
		break;
	case Item::Type::Armor:
		addArmor(std::dynamic_pointer_cast<Armor> (item));
		break;
	default:
		break;
	}
}

void Inventory::addWeapon(std::shared_ptr<Weapon> w) {
	m_Weapons.push_back(w);
}

void Inventory::addArmor(std::shared_ptr<Armor> w) {
	m_Armor.push_back(w);
}

std::shared_ptr<Weapon> Inventory::getWeapon(size_t index) {
	if (index < 0 || index >= m_Weapons.size()) {
		return nullptr;
	}
	else {
		return m_Weapons[index];
	}
}

std::shared_ptr<Armor> Inventory::getArmor(size_t index) {
	if (index < 0 || index >= m_Armor.size()) {
		return nullptr;
	}
	else {
		return m_Armor[index];
	}
}