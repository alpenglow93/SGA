#pragma once

enum ITEM //������ ����, ������, �� ����
{
	ITEM_EMPTY,		//������ ����(�� ����, �ʱ�ȭx)
	ITEM_ARMOR,		//��
	ITEM_WEAPON,	//����
	ITEM_RING,		//����
	ITEM_POTION,	//����
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