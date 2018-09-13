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
	//temp.name = "���� ����";
	//temp.price = 50;
	//temp.attribute = 1;
	//temp.description = "�������� ���� ����";
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

			char* result;	//�ڸ� ���

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
	int itemCount = 0;	//�������� ����
	auto iter = vItem.begin();
	for (iter; iter != vItem.end(); iter++)
	{
		//���� ������ ������ ������ ���
		if (iter->itemKind != num) continue;
		cout << "================================" << endl;
		cout << "������ ��ȣ: " << ++itemCount << endl;
		cout << "�̸�: " << iter->name << endl;
		cout << "����: " << iter->price << endl;
		cout << "�ɷ�ġ: " << iter->attribute << endl;
		cout << "����: " << iter->description << endl;
		cout << "����: ";
		(iter->count > 0) ? cout << iter->count << endl : cout << "����" << endl;
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
