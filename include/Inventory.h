#pragma once
#include "Weapon.h"
#include "Armor.h"
#include <vector>

class Inventory {

public:
	void addItem(std::shared_ptr<Item> item);
	void addWeapon(std::shared_ptr<Weapon> w);
	void addArmor(std::shared_ptr<Armor> w);
	std::shared_ptr<Weapon> getWeapon(size_t index);
	std::shared_ptr<Armor> getArmor(size_t index);
	
private:
	std::vector<std::shared_ptr<Weapon>> m_Weapons;
	std::vector<std::shared_ptr<Armor>> m_Armor;
};