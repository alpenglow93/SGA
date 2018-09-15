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
		cout << "������ ��ȣ : " << ++itemCount << endl;
		cout << "�̸� : " << iter->name << endl;
		cout << "���� : " << iter->price << endl;
		cout << "�ɷ�ġ : " << iter->attribute << endl;
		cout << "���� : " << iter->description << endl;
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
	cout << sellItem.name << "�� " <<
		sellPrice << "�� �Ǹ�" << endl;
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
