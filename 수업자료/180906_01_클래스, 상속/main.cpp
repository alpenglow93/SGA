//클래스 참조 
//비쥬얼 설치 할때 파일을 참조 할떄는 <>
//내가 만든 클래스를 참조 할때는 ""
#include "GameNode.h" 

void main()
{
	//클래스 케릭터 
	//케릭터 , 궁수, 전사, 마법사 
	//클래스 선언
	//MainGame mg;
	//포인터로 선언시
	//-> 포인터 연산자 
	MainGame* pMg = new MainGame;
	pMg->nInt = 200;
	cout << pMg->nInt << endl;

	pMg->SetDistance(150.0f);
	cout << pMg->GetDistance() << endl;
	MainGame* pMg2 = new MainGame;

	GameNode* pGn = new GameNode;

	//상속일때만 
	GameNode* pGn2 = new GameNode;

	pGn->hp = 100;
	pGn->att = 20;
	pGn2->hp = 200;
	pGn2->att = 15;
	pGn->SetDamage(pGn2);
	pGn2->SetDamage(pGn);
	cout << endl;
	cout << "1.   " << pGn->hp << endl;
	cout << "2.   " << pGn2->hp << endl;


	cout << endl;


	delete pGn2;
	delete pGn;
	delete pMg2;
	delete pMg;
}