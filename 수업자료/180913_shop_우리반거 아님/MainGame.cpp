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
	cout << "================== ��ġ ===================" << endl;
	cout << "1.����   2.�κ��丮[�Ǹ�]   3.�κ��丮[����]" << endl;
	cout << "===========================================" << endl;
	cin >> select;
	SetLocation(select);
}

void MainGame::SetShopPage()
{
	while (true)
	{
		system("cls");
		cout << "================== ���� ===================" << endl;
		cout << "1.��  2.����  3.����  4.����  5.������" << endl;
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
		cout << "���� gold : " << gold << endl;
		cout << "������ ������ ��ȣ �Է� " << endl;
		cout << "itemCount : " << itemCount << endl;
		cout << "�������� 0�� �Է� " << endl;
		cout << "=========================================" << endl;
		cin >> select;
		if (select == 0)
		{
			SetShopPage();
		}
		else if (select > 0  && select <= itemCount)
		{
			//������ ���� 
			i->AddItem(s->BuyItem(itemKind, select, gold));
			Sleep(1000);
			//s->AddItem(item);
		}
	}
}

void MainGame::SetSellInventoryPage()
{
	//������ �Ǹ� 
	int itemCount = 0;
	while (true)
	{

		system("cls");
		itemCount = i->ShowInventory();
		cout << "=========================================" << endl;
		cout << "���� gold : " << gold << endl;
		cout << "�Ǹ��� ������ ��ȣ �Է� " << endl;
		cout << "itemCount : " << itemCount << endl;
		cout << "�������� 0�� �Է� " << endl;
		cout << "=========================================" << endl;
		cin >> select;
		if (select == 0)
		{
			MainPage();
		}
		else if (select > 0 && select <= itemCount)
		{
			//������ �Ǹ�
			s->AddItem(i->SellItem(select, gold));
			Sleep(1000);
			//s->AddItem(item);
		}
	}
}

void MainGame::SetInventoryPage()
{
}
