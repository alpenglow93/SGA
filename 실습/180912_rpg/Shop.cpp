#include "stdafx.h"
#include "Shop.h"


Shop::Shop()
{
}


Shop::~Shop()
{
}

void Shop::SetupItem()
{
	//ITEM_INFO temp;
	//memset(&temp, 0, sizeof(ITEM_INFO));
	//temp.itemKind = ITEM_ARMOR;
	//temp.name = "가죽 바지";
	//temp.price = 50;
	//temp.attribute = 1;
	//temp.description = "가죽으로 만든 바지";
	//temp.count = 1;
	//vItem.push_back(temp);

	//1. fopen, 2. fStream

	string fileName = "Item.txt";
	string filePath = TEXT_PATH + fileName;

	FILE* fp;
	fopen_s(&fp, filePath.c_str(), "r");
	{
		//feof
		while (!feof(fp))
		{
			char szBuf[256];
			char* temp;
			temp = fgets(szBuf, 256, fp);

			char* result;	//자른 결과

			ITEM_INFO item;
			item.itemKind = (ITEM)stoi(strtok_s(temp, "][", &result));
			item.name = strtok_s(temp, "][", &result);
			item.price = stoi(strtok_s(temp, "][", &result));
			item.attribute = stoi(strtok_s(temp, "][", &result));
			item.description = strtok_s(temp, "][", &result);
			item.count = stoi(strtok_s(temp, "][", &result));

			vItem.push_back(item);
			
		}
	}
	fclose(fp);
}

int Shop::OutputItem(int num)
{
	int itemCount = 0;	//아이템의 갯수
	auto iter = vItem.begin();
	for (iter; iter != vItem.end(); iter++)
	{
		//내가 선택한 아이템 종류만 출력
		if (iter->itemKind != num) continue;
		cout << "================================" << endl;
		cout << "아이템 번호: " << ++itemCount << endl;
		cout << "이름: " << iter->name << endl;
		cout << "가격: " << iter->price << endl;
		cout << "능력치: " << iter->attribute << endl;
		cout << "설명: " << iter->description << endl;
		cout << "갯수: ";
		(iter->count > 0) ? cout << iter->count << endl : cout << "매진" << endl;
		cout << "================================" << endl;
	}
		return itemCount;
}

ITEM_INFO Shop::BuyItem(int itemKind, int num, int & gold)
{
	return ITEM_INFO();
}

void Shop::AddItem(ITEM_INFO item)
{
}
