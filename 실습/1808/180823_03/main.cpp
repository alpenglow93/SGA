#include <iostream>
#include <time.h>
using namespace std;

void main()
{
	//�迭 (Array)
	//�������� ������[����];
	
	int nNum[10];
	//�ε�����ȣ
	//��ȣ�� ������ 0������
	nNum[4] = 10;
	nNum[3] = 20;

	cout << nNum[4] << endl;
	cout << nNum[3] << endl;

	cout << "=============" << endl;
	
	for (int i = 0; i < 10; i++)
	{
		nNum[i] = i;
		cout << nNum[i] << " ";
	}

	cout << endl;

	//���� �˰���
	//rand() ����� ��

	//cout << "���� �˰���" << endl;

	srand(time(NULL));
	
	for (int i = 0; i < 1000; i++)
	{
		int temp, sour, dest;

		sour = rand() % 10; //10 -> �迭�� ũ��
		dest = rand() % 10;	//10 -> �迭�� ũ��

		//swap;
		temp = nNum[sour];
		nNum[sour] = nNum[dest];
		nNum[dest] = temp;
	}

	for (int i = 0; i < 10; i++)
	{
		cout << nNum[i] << " ";
	}
	cout << endl;

}