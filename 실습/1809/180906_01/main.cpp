//Ŭ���� ����
//���־� ��ġ �� �� ���� ���� ���� <>
//���� ���� Ŭ������ ���� ""
#include "MainGame.h"
#include "Gamenode.h"

void main()
{
	//Ŭ���� ĳ����
	// ĳ����, �ü�, ����, ������
	//Ŭ���� ����
	//MainGame mg;
	//�����ͷ� ������
	//-> ������ ������

	//MainGame* pMg;
	//�����ͷ� �����ϰ� �����ϸ� ���� ������ ����. �ּҰ��� �Ҵ�Ǿ��ִ� ���°� �ƴϱ� ����
	MainGame* pMg = new MainGame;
	//�� �ܰ踸 �ϸ� �Ҹ��ڰ� �ҷ����� �ʴ´�. �Ҹ���� ���� ��.

	pMg->nInt = 200;
	cout << pMg->nInt << endl;

	pMg->SetDistance(150.0f);
	cout << pMg->GetDistance() << endl;
	MainGame* pMg2 = new MainGame;

	Gamenode* pGn = new Gamenode;

	//����϶���
	//������ �ڽ��� ȣ���ϰ� �θ�� �ʱ�ȭ �ϴ� ���� �Ұ���
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
	delete pMg;	//�� ��ɾ�� �Ҹ��ڰ� �ҷ�������
}