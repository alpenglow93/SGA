#pragma once
#include "Inventory.h"
#include "Unit.h"
class Player : public Inventory, public Unit
{
public:
	Player();
	~Player();

	void ShowStatus();
	void EquipItem(int num);
};

