#pragma once
class Shop
{
private:
	vector<ITEM_INFO> vItem;
public:
	Shop();
	~Shop();

	void SetupItem();	//초기아이템 셋팅
	int OutputItem(int num);	//아이템 출력

	//아이템 구매
	ITEM_INFO BuyItem(int itemKind, int num, int& gold);
	//아이템 판매시 상점에 추가
	//다른 종류의 아이템을 추가
	void AddItem(ITEM_INFO item);
};

