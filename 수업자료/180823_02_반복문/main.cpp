#include <iostream>
#include <time.h>
using namespace std;

void main()
{
	//�ݺ��� : Ư�� �ڵ带 �ݺ� �����ϴ� �༮ 

	//for while

	//for(�ʱⰪ ; ���� ; ������)
	//{
	//	������ �����Ҷ� �����Ѵ�.
	//}
	// �ʱⰪ ���� -> ����(��) -> �ڵ���� -> ������ ->����(��)->����
	//  -> ����(����)

	for (int i = 10; i > 0; i--)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << i  << ", " << j << "��° �ݺ��� ����" << endl;
		}
	}

	for (int i = 1; i < 100; i += 2)
	{
		//if (i % 2 == 1)
		{
			cout << i << endl;
		}
	}

	//while( ���� )
	//{
	//	������ ���̸� �ڵ带 �����ϰڴ�.
	//}
	int nNum = 0;		//�ʱⰪ
	while (nNum < 10)	//����
	{
		cout << nNum << "��° �ڵ� ����" << endl;
		nNum++;			//������ 
	}
	//���� �ݺ���
	//while (true)
	//{
	//	cout << nNum << " ";
	//	nNum++;
	//}

	srand(time(NULL)); //rand() ����� 1���� ��� 
	for (int i = 0; i < 10; i++)
	{
		//0~ 9;
		int nRandom = rand() % 10;
		cout << nRandom << endl;
	}
}