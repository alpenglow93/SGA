//Ŭ���� ���� 
//����� ��ġ �Ҷ� ������ ���� �ҋ��� <>
//���� ���� Ŭ������ ���� �Ҷ��� ""
#include "GameNode.h" 

void main()
{
	//Ŭ���� �ɸ��� 
	//�ɸ��� , �ü�, ����, ������ 
	//Ŭ���� ����
	//MainGame mg;
	//�����ͷ� �����
	//-> ������ ������ 
	MainGame* pMg = new MainGame;
	pMg->nInt = 200;
	cout << pMg->nInt << endl;

	pMg->SetDistance(150.0f);
	cout << pMg->GetDistance() << endl;
	MainGame* pMg2 = new MainGame;

	GameNode* pGn = new GameNode;

	//����϶��� 
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