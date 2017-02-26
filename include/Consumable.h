#pragma once
#include "Item.h"

class Consumable : public Item {
public:
	Item::Type getType() {
		return Item::Consumable;
	}
};
