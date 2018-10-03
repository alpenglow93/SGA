#pragma once
#include "MainGame.h"
//GameNode.h
//상속: 부모 클래스 데이터(변수, 함수)를 물려받아
//	자식이 사용하는 것
//unit class
//플레이어, 몬스터

//vmffpdldj, ahstmxj
//플레이어 -> 직업별 캐릭터
//몬스터 -> 종류
class Gamenode: public MainGame
{
public:
	Gamenode();
	~Gamenode();
};

