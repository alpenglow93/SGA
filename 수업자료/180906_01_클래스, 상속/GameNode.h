#pragma once
#include "MainGame.h"
//GameNode.h 
//상속 : 부모 클래스 데이터(변수, 함수)를 물려 받아
//자식이 사용하는것
//unit class 
//플레이랑, 몬스터 

//플레이어 , 몬스터 
//플레이어 -> 직업별 케릭터 
//몬스터 -> 종류
class GameNode : public MainGame 
{
public:
	GameNode();
	~GameNode();
};

