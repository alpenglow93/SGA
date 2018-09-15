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

	//상점 , 판매 , 장착 
	void SetLocation(int num);

	//메인 페이지 
	void MainPage();

	//상점 페이지 
	void SetShopPage();

	//상점 아이템 출력 
	void SetShopItemPage(int itemKind);

	//인벤토리 판매 페이지
	void SetSellInventoryPage();

	//인벤토리 장착 페이지 
	void SetInventoryPage();
};

