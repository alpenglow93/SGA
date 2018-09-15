#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::ShowStatus()
{
	int addAtt = equipWeapon.attribute;
	int addDef = equipArmor.attribute;

	cout << "공격력\t\t: " << att << " + " << addAtt << endl;
	printf("방어력\t\t: %d + %d\n", def, addDef);
	printf("무기\t\t: %s\n", equipWeapon.name);
	printf("방어구\t\t: %s\n", equipArmor.name);

}

void Player::EquipItem(int num)
{
	auto iter = vItem.begin() + (num - 1);
	if (iter->itemKind != ITEM_WEAPON)
	{
		ITEM_INFO temp = equipWeapon;
		equipWeapon = *iter;
		vItem.erase(iter);
		if (temp.itemKind != ITEM_EMPTY)
		{
			vItem.push_back(temp);
		}
	}
}
