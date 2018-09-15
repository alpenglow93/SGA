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
	//temp.name = "���� ����";
	//temp.price = 50;
	//temp.attribute = 1;
	//temp.description = "�������� ���� ����";
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
		//���� ������ ������ ������ ���Ͷ�
		if (iter->itemKind != num) continue;
		cout << "==========================================" << endl;
		cout << "������ ��ȣ : " << ++itemCount << endl;
		cout << "�̸� : " << iter->name << endl;
		cout << "���� : " << iter->price << endl;
		cout << "�ɷ�ġ : " << iter->attribute << endl;
		cout << "���� : " << iter->description << endl;
		cout << "���� : ";
		(iter->count > 0) ? cout << iter->count << endl
			: cout << "����" << endl;
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
					cout << buyItem.name << "�� " <<
						buyItem.price << "�� ����" << endl;
				}
				else
				{
					cout << "��� ����" << endl;
				}
			}
			else
			{
				cout << "�� ����" << endl;
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
