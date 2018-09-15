#pragma once

enum ITEM //아이템 종류, 재고없음, 미 장작
{
	ITEM_EMPTY,		//아이템 없음(미 장착, 초기화x)
	ITEM_ARMOR,		//방어구
	ITEM_WEAPON,	//무기
	ITEM_RING,		//반지
	ITEM_POTION,	//포션
	ITEM_SOLDOUT	//판매 완료(재고 없음)
};

typedef struct tagItemInfo
{
	ITEM itemKind;		//아이템 종류 
	string name;		//아이템 이름
	string description;	//아이템 설명
	int attribute;		//아이템 특성
	int price;			//아이템 가격
	int count;			//아이템 갯수
}ITEM_INFO, *LPITEM_INFO;