#include <iostream>
#include <time.h>
using namespace std;

void main()
{
	//�ݺ���: Ư�� �ڵ带 �ݺ� �����ϴ� ����

	//for while �ΰ����� �ִ�

	//for( �ʱⰪ ; ���ǹ� ; ������ )
	//{
	//	������ �����Ҷ� �����Ѵ�.
	//}
	//
	//	�ʱⰪ ���� ->  ����(��) -> �ڵ� ���� -> ������ ���� -> ����(��) -> �ڵ� ���� -> ... -> ����(����)

	for (int i = 0; i < 10; i++)
	{
		cout << i << "��° �ݺ��� ����" << endl;
	}

	cout << "===============" << endl;


	for (int i = 10; i > 0; i--)
	{
		cout << i << "��° �ݺ��� ����" << endl;

	}

	cout << "===============" << endl;

	for (int i = 10; i > 0; i--)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << i << ", " << j << "��° �ݺ��� ����" << endl;
		}
	}

	for (int i = 0; i < 100; i++)
	{
		if (i % 2 == 0)
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
	////���� �ݺ���
	//while (1)	//������ true�� ��´�
	//{
	//	cout << nNum << " ";
	//	nNum++;
	//}

	srand(time(NULL));
	for (int i = 0; i < 10; i++)
	{
		//0 ~ 9;
		int nRandom = rand() % 10;
		cout << nRandom << endl;
	}
}