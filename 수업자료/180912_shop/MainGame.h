#pragma once
#include <Windows.h>
#include "Shop.h"

enum LOCATION //��� 
{
	LOCATION_SHOP = 1,		//������ ���� ���
	LOCATION_SELL_INVENTORY, //������ �Ǹ�
	LOCATION_INVENTORY		//������ ���� 

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

	//����,�κ��丮�� �Ѿ�� �Լ�
	void SetLocation(int num);
	//����������
	void SetMainPage();
	//������ �����ִ� �Լ�
	void SetShopPage();
	//���� �������� �����ִ� �Լ�
	void SetShopItemPage(int itemKind);
	//�κ��丮 ���� �Ǹ� ������
	void SetSellInventoryPage();
	//�κ��丮 ���� ������
	void SetInventoryPage();
};

