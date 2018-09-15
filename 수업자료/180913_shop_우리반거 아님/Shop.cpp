#include "stdafx.h"
#include "Shop.h"


Shop::Shop()
{
}


Shop::~Shop()
{
}

void Shop::SetUpItem()
{
	//ITEM_INFO temp;
	//ZeroMemory(&temp, sizeof(ITEM_INFO));
	//temp.itemKind = ITEM_ARMOR;
	//temp.name = "가죽 바지";
	//temp.price = 50;
	//temp.attribute = 1;
	//temp.description = "가죽으로 만든 바지";
	//temp.count = 1;
	//vItem.push_back(temp);

	//fopen(c), fstream(c++)
	string fileName = "Item.txt";
	string filePath = _TEXT_PATH + fileName;


	FILE* fp;
	fopen_s(&fp, filePath.c_str(), "r");
	{
		//end of file 
		while (!feof(fp))
		{
			char szBuf2[256];
			char* szBuf;
			szBuf = fgets(szBuf2, 256, fp);

			ITEM_INFO item;
			string temp;

			temp = strtok_s(szBuf, "][", &szBuf);
			item.itemKind = (ITEM)stoi(temp);

			temp = strtok_s(szBuf, "][", &szBuf);
			item.name = temp;

			temp = strtok_s(szBuf, "][", &szBuf);
			item.price = stoi(temp);

			temp = strtok_s(szBuf, "][", &szBuf);
			item.attribute = stoi(temp);

			temp = strtok_s(szBuf, "][", &szBuf);
			item.description = temp;

			temp = strtok_s(szBuf, "][", &szBuf);
			item.count = stoi(temp);

			vItem.push_back(item);
		}
	}
	fclose(fp);

}

int Shop::OutputItem(int num)
{
	int itemCount = 0;
	auto iter = vItem.begin();
	for (iter; iter != vItem.end(); iter++)
	{
		//내가 선택한 아이템 종류만 나와라
		if (iter->itemKind != num) continue;
		cout << "==========================================" << endl;
		cout << "아이템 번호 : " << ++itemCount << endl;
		cout << "이름 : " << iter->name << endl;
		cout << "가격 : " << iter->price << endl;
		cout << "능력치 : " << iter->attribute << endl;
		cout << "설명 : " << iter->description << endl;
		cout << "갯수 : ";
		(iter->count > 0) ? cout << iter->count << endl
			: cout << "매진" << endl;
		cout << "==========================================" << endl;

	}

	return itemCount;
}

ITEM_INFO Shop::BuyItem(int itemKind, int num, int & gold)
{
	ITEM_INFO buyItem;
	buyItem.itemKind = ITEM_EMPTY;
	int itemCount = 0;
	auto iter = vItem.begin();
	for (iter; iter != vItem.end(); iter++)
	{
		if (iter->itemKind != itemKind) continue;
		if (++itemCount == num)
		{
			if (gold >= iter->price)
			{
				if (iter->count > 0)
				{
					buyItem = *(iter);
					iter->count--;
					gold -= iter->price;
					cout << buyItem.name << "을 " <<
						buyItem.price << "에 구매" << endl;
				}
				else
				{
					cout << "재고 없음" << endl;
				}
			}
			else
			{
				cout << "돈 없음" << endl;
			}
			break;
		}
	}
	return buyItem;
}

void Shop::AddItem(ITEM_INFO item)
{
	bool isNewItem = true;

	auto iter = vItem.begin();
	for (iter; iter != vItem.end(); iter++)
	{
		if (iter->itemKind != item.itemKind) continue;

		if (iter->name.compare(item.name) == 0)
		{
			iter->count++;
			isNewItem = false;
			break;
		}
	}
	if (isNewItem)
	{
		vItem.push_back(item);
	}
}
