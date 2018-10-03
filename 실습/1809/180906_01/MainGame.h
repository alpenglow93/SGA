#pragma once
#include <iostream>
using namespace std;

//클래스를 쓰는 이유
//1. C 언어 -> C++ 변화
//2. 절차지향 -> 객체 지향(특정 객체만 수정하면 됨)
//3. 유지보수 힘들다 (시간이 오래 걸린다)
//객체 지향 코딩 _기본적인 클래스 생성

//.h(헤더 파일) -> 대부분을 선언으로 작성

//ex) player class -> hp, mp, att, def, Attack, Move
//hp, mp, att, def -> private
//attack, move -> public

class MainGame
{
	//접근 지정자: 보안 단계를 설정하는 키워드
private:	//현 클래스 내부에서만 사용 가능
	//멤버 변수: 클래스 내부에 있는 변수들
	int data;
	float distance;

	int *pInt;
protected:	//클래스 상속 관계에서 현 클래스의 자식까지는 사용할 수 있는 지정자
	bool bCheck;

public:		//누구나 그냥 가져다 쓸 수 있는 지정자
	int nInt;

	int hp;
	int att;
	MainGame();		//생성자: 객체가 생성될때 실행되는 함수
	~MainGame();	//소멸자: 객체가 소멸될때 실행되는 함수

	void SetDistance(float f);
	float GetDistance();

	void SetDamage(MainGame* target);
};

