#pragma once
class Shop
{
private:
	vector<ITEM_INFO> vItem;
public:
	Shop();
	~Shop();

	void SetUpItem(); //초기 아이템 셋팅
	int OutputItem(int num); //아이템 출력 

	//상점 아이템 구매
	ITEM_INFO BuyItem(int itemKind, int num, int& gold);
	//상점 아이템 추가 
	void AddItem(ITEM_INFO item);
};

