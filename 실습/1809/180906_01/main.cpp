//클래스 참조
//비주얼 설치 할 때 생긴 파일 참조 <>
//내가 만든 클래스를 참조 ""
#include "MainGame.h"
#include "Gamenode.h"

void main()
{
	//클래스 캐릭터
	// 캐릭터, 궁수, 전사, 마법사
	//클래스 선언
	//MainGame mg;
	//포인터로 선선시
	//-> 포인터 연산자

	//MainGame* pMg;
	//포인터로 선언만하고 실행하면 실행 내용이 없다. 주소값이 할당되어있는 상태가 아니기 때문
	MainGame* pMg = new MainGame;
	//이 단계만 하면 소멸자가 불러오지 않는다. 소멸되지 않은 것.

	pMg->nInt = 200;
	cout << pMg->nInt << endl;

	pMg->SetDistance(150.0f);
	cout << pMg->GetDistance() << endl;
	MainGame* pMg2 = new MainGame;

	Gamenode* pGn = new Gamenode;

	//상속일때만
	//하지만 자식을 호출하고 부모로 초기화 하는 것은 불가능
	MainGame* pGn2 = new Gamenode;

	pGn->hp = 100;
	pGn->att = 20;
	pGn2->hp = 200;
	pGn2->att = 15;
	pGn->SetDamage(pGn2);
	pGn2->SetDamage(pGn);
	cout << endl;
	cout << "1. " << pGn->hp << endl;
	cout << "2. " << pGn2->hp << endl;

	cout << endl;

	delete pGn2;
	delete pGn;
	delete pMg2;
	delete pMg;	//이 명령어로 소멸자가 불러와진다
}