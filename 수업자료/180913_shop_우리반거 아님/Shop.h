#pragma once
class Shop
{
private:
	vector<ITEM_INFO> vItem;
public:
	Shop();
	~Shop();

	void SetUpItem(); //�ʱ� ������ ����
	int OutputItem(int num); //������ ��� 

	//���� ������ ����
	ITEM_INFO BuyItem(int itemKind, int num, int& gold);
	//���� ������ �߰� 
	void AddItem(ITEM_INFO item);
};

