#pragma once
class Shop
{
private:
	vector<ITEM_INFO> vItem;
public:
	Shop();
	~Shop();

	void SetupItem();	//�ʱ������ ����
	int OutputItem(int num);	//������ ���

	//������ ����
	ITEM_INFO BuyItem(int itemKind, int num, int& gold);
	//������ �ǸŽ� ������ �߰�
	//�ٸ� ������ �������� �߰�
	void AddItem(ITEM_INFO item);
};

