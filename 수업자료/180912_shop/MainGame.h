#pragma once
#include <Windows.h>
#include "Shop.h"

enum LOCATION //장소 
{
	LOCATION_SHOP = 1,		//아이템 구매 장소
	LOCATION_SELL_INVENTORY, //아이템 판매
	LOCATION_INVENTORY		//아이템 장착 

};
class MainGame
{
private:
	Shop * shop;
	LOCATION loc;

	int gold;
	int selectNum;
public:
	MainGame();
	~MainGame();

	//상점,인벤토리로 넘어가는 함수
	void SetLocation(int num);
	//메인페이지
	void SetMainPage();
	//상점을 보여주는 함수
	void SetShopPage();
	//상점 아이템을 보여주는 함수
	void SetShopItemPage(int itemKind);
	//인벤토리 상점 판매 페이지
	void SetSellInventoryPage();
	//인벤토리 장작 페이지
	void SetInventoryPage();
};

