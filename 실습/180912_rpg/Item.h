#pragma once

enum ITEM	//������ ����, ������, ������
{
	ITME_EMPTY,	//������ ����(������, �ʱ�ȭ ���� ����)
	ITEM_ARMOR,	//��
	ITEM_WEAPON,
	ITME_RING,
	ITEM_POTION,
	ITEM_SOLDOUT	//�Ǹ� �Ϸ�(��� ����)
};

typedef struct tagItemInfo
{
	ITEM itemKind;		//������ ����
	string name;		//������ �̸�
	string description;	//������ ����
	int attribute;		//������ Ư��
	int price;			//������ ����
	int count;			//������ ����
}ITEM_INFO, *LPITEM_INFO;