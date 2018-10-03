#include "stdafx.h"
#include "MainGame.h"


MainGame::MainGame()
{
	shop = new Shop;
	shop->SetupItem();

	gold = 10000;
	selectNum = 0;

	SetMainPage();
}


MainGame::~MainGame()
{
	delete shop;
	shop = 0;
}

void MainGame::SetLocation(int num)
{
	switch (num)
	{
	case LOCATION_SHOP:
		SetShopPage();
		break;
	case LOCATION_SELL_INVENTORY:
		SetSellInventoryPage();
		break;
	case LOCATION_INVENTORY:
		SetInventoryPage();
		break;
	default:
		SetMainPage();
		break;
	}
}

void MainGame::SetMainPage()
{
	system("cls");
	cout << "================= 위치 =================" << endl;
	cout << "1. 상점 2. 인벤토리[판매] 3. 인벤토리[장착]" << endl;
	cout << "==========================================" << endl;
	cin >> selectNum;
	SetLocation(selectNum);
}

void MainGame::SetShopPage()
{
	while (1)
	{
		system("cls");
		cout << "================= 상점 =================" << endl;
		cout << "1. 상점 2. 무기 3. 반지 4. 포션 0. 나가기" << endl;
		cout << "==========================================" << endl;
		cin >> selectNum;
		if (selectNum == 0)
		{
			SetMainPage();
		}
		else if(selectNum < 5 && selectNum > 0)
		{
			SetShopItemPage(selectNum);
		}
	}
}

void MainGame::SetShopItemPage(int itemKind)
{
	int itemCount = 0;
	while (1)
	{
		system("cls");
		itemCount = shop->OutputItem(itemKind);
		cin >> selectNum;

		//////////////////////////////////////////////////////////////////
		//아이템 구매 금액 감소 
		if (selectNum == 0)
		{
			return;
		}
	}
}

void MainGame::SetSellInventoryPage()
{
	////////////////////////////////////////////////////////////////////
	//1. 인벤토리에 저장된 아이템 출력
	//2. 저장된 아이템 선택시 판매
}

void MainGame::SetInventoryPage()
{
}
