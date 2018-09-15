#pragma once
//item.h file

enum ITEM //�������� ����, ��� ����, �� ����
{
	ITEM_EMPTY,		//������ ���� 
	ITEM_ARMOR,		//��
	ITEM_WEAPON,	//����
	ITEM_RING,		//����
	ITEM_POTION,	//����
	ITEM_SOLDOUT,	//��� ���� 
};

typedef struct tagItemInfo
{
	ITEM itemKind;		//������ ����
	string name;		//������ �̸�
	string description;	//������ ����
	int attribute;		//������ �ɷ� 
	int price;			//������ ����
	int count;			//������ ����
}ITEM_INFO, *LPITEM_INFO;

