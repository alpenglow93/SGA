#include "stdafx.h"
#include "Inventory.h"


Inventory::Inventory()
{
	ZeroMemory(&equipArmor, sizeof(ITEM_INFO));
	ZeroMemory(&equipWeapon, sizeof(ITEM_INFO));

}


Inventory::~Inventory()
{
}

int Inventory::ShowInventory()
{
	int itemCount = 0;
	auto iter = vItem.begin();
	for (iter; iter != vItem.end(); iter++)
	{
		cout << "==========================================" << endl;
		cout << "아이템 번호 : " << ++itemCount << endl;
		cout << "이름 : " << iter->name << endl;
		cout << "가격 : " << iter->price << endl;
		cout << "능력치 : " << iter->attribute << endl;
		cout << "설명 : " << iter->description << endl;
		cout << "==========================================" << endl;

	}
	return itemCount;
}

ITEM_INFO Inventory::SellItem(int num, int & gold)
{
	ITEM_INFO sellItem;
	auto iter = vItem.begin() + (num - 1);
	sellItem = (*iter);
	vItem.erase(iter);

	int sellPrice = sellItem.price / 2;
	cout << sellItem.name << "을 " <<
		sellPrice << "에 판매" << endl;
	gold += sellPrice;
	return sellItem;
}

void Inventory::AddItem(ITEM_INFO item)
{
	if (item.itemKind != ITEM_EMPTY)
	{
		vItem.push_back(item);
	}
}
