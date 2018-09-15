#pragma once
//아이템 저장 
class Inventory
{
protected:
	vector<ITEM_INFO> vItem;

	ITEM_INFO equipArmor;
	ITEM_INFO equipWeapon;
public:
	Inventory();
	~Inventory();

	int ShowInventory();
	ITEM_INFO SellItem(int num,int& gold);
	void AddItem(ITEM_INFO item);
};

