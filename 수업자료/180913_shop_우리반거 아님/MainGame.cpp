#include "stdafx.h"
#include "MainGame.h"


MainGame::MainGame()
{
	s = new Shop;
	s->SetUpItem();

	i = new Inventory;

	gold = 10000;
	select = 0;

	MainPage();
}


MainGame::~MainGame()
{
	if (s != 0)
	{
		delete s;
		s = 0;
	}
	if (i != 0)
	{
		delete i;
		i = 0;
	}
}

void MainGame::SetLocation(int num)
{
	switch (num)
	{
	case 1:
		SetShopPage();
		break;
	case 2:
		SetSellInventoryPage();
		break;
	case 3:
		SetInventoryPage();
		break;
	default:
		MainPage();
		break;
	}
}

void MainGame::MainPage()
{
	system("cls");
	cout << "================== 위치 ===================" << endl;
	cout << "1.상점   2.인벤토리[판매]   3.인벤토리[장착]" << endl;
	cout << "===========================================" << endl;
	cin >> select;
	SetLocation(select);
}

void MainGame::SetShopPage()
{
	while (true)
	{
		system("cls");
		cout << "================== 상점 ===================" << endl;
		cout << "1.방어구  2.무기  3.반지  4.포션  5.나가기" << endl;
		cout << "===========================================" << endl;
		cin >> select;
		if (select == 0)
		{
			MainPage();
			return;
		}
		else if (select > 0 && select < 5)
		{
			SetShopItemPage(select);
		}
	}
}

void MainGame::SetShopItemPage(int itemKind)
{
	int itemCount = 0;
	while (true)
	{

		system("cls");
		itemCount = s->OutputItem(itemKind);
		cout << "=========================================" << endl;
		cout << "현재 gold : " << gold << endl;
		cout << "구매할 아이템 번호 입력 " << endl;
		cout << "itemCount : " << itemCount << endl;
		cout << "나가려면 0번 입력 " << endl;
		cout << "=========================================" << endl;
		cin >> select;
		if (select == 0)
		{
			SetShopPage();
		}
		else if (select > 0  && select <= itemCount)
		{
			//아이템 구매 
			i->AddItem(s->BuyItem(itemKind, select, gold));
			Sleep(1000);
			//s->AddItem(item);
		}
	}
}

void MainGame::SetSellInventoryPage()
{
	//아이템 판매 
	int itemCount = 0;
	while (true)
	{

		system("cls");
		itemCount = i->ShowInventory();
		cout << "=========================================" << endl;
		cout << "현재 gold : " << gold << endl;
		cout << "판매할 아이템 번호 입력 " << endl;
		cout << "itemCount : " << itemCount << endl;
		cout << "나가려면 0번 입력 " << endl;
		cout << "=========================================" << endl;
		cin >> select;
		if (select == 0)
		{
			MainPage();
		}
		else if (select > 0 && select <= itemCount)
		{
			//아이템 판매
			s->AddItem(i->SellItem(select, gold));
			Sleep(1000);
			//s->AddItem(item);
		}
	}
}

void MainGame::SetInventoryPage()
{
}
