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
	cout << "================= ��ġ =================" << endl;
	cout << "1. ���� 2. �κ��丮[�Ǹ�] 3. �κ��丮[����]" << endl;
	cout << "==========================================" << endl;
	cin >> selectNum;
	SetLocation(selectNum);
}

void MainGame::SetShopPage()
{
	while (1)
	{
		system("cls");
		cout << "================= ���� =================" << endl;
		cout << "1. ���� 2. ���� 3. ���� 4. ���� 0. ������" << endl;
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
		//������ ���� �ݾ� ���� 
		if (selectNum == 0)
		{
			return;
		}
	}
}

void MainGame::SetSellInventoryPage()
{
	////////////////////////////////////////////////////////////////////
	//1. �κ��丮�� ����� ������ ���
	//2. ����� ������ ���ý� �Ǹ�
}

void MainGame::SetInventoryPage()
{
}
