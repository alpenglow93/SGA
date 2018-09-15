#pragma once
#include "Shop.h"
#include "Inventory.h"
class MainGame
{
private:
	Shop * s;
	Inventory* i;
	int gold;
	int select;

public:
	MainGame();
	~MainGame();

	//���� , �Ǹ� , ���� 
	void SetLocation(int num);

	//���� ������ 
	void MainPage();

	//���� ������ 
	void SetShopPage();

	//���� ������ ��� 
	void SetShopItemPage(int itemKind);

	//�κ��丮 �Ǹ� ������
	void SetSellInventoryPage();

	//�κ��丮 ���� ������ 
	void SetInventoryPage();
};

