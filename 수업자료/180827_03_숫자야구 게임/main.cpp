//���� �߱� 
#include <iostream>
#include <time.h>
using namespace std;
//1~9���� �߿��� �ߺ��Ǵ� �ʴ� 3���� ����(����)�� ��ǻ�Ͱ� ���� 
//���� 3���� ���� �Է� �ؼ� �ڸ� ���� 

void main()
{
	int aNumber[9]; //1~9������ ���ڸ� ���� 
	int aSelect[3]; //���� ���� �� ���� 3���� ����

	bool bIsWin = false;

	//���� �ʱ�ȭ
	for (int i = 0; i < 9; i++)
	{
		aNumber[i] = i + 1;
	}
	//���� �˰���
	srand(time(NULL));
	for (int i = 0; i < 1000; i++)
	{
		int temp = 0, sour = 0, dest = 0;
		sour = rand() % 9; //9 -> �迭�� ũ��
		dest = rand() % 9; //9 -> �迭�� ũ�� 

		//Swap 
		temp = aNumber[sour];
		aNumber[sour] = aNumber[dest];
		aNumber[dest] = temp;
	}
	//���� ����� 
	cout << "[ġƮ : ";
	for (int j = 0; j < 3; j++)
	{
		cout << aNumber[j] << " ";
	}
	cout  << "]"<< endl;
	for (int i = 0;i < 10; i++) //10�� ���� �ϰڴ�. 
	{

		//���� ���� 3���� �Է�
		cout << "���� �Է� : ";
		for (int j = 0; j < 3; j++)
		{
			cin >> aSelect[j];
		}
		//�� �� 
		int nStrike = 0;
		int nBall = 0;

		for (int j = 0; j < 3; j++) //���� ������ 3��
		{
			for (int k = 0; k < 3; k++) //��ǻ�� ������ 3�� 
			{
				if (aSelect[j] == aNumber[k])
				{
					if (j == k)
					{
						nStrike++;
					}
					else
					{
						nBall++;
					}
				}
			}
		}
		cout << "Strike : " << nStrike <<endl << "Ball : " << nBall 
			<<  endl<< "Out : "<< 3 - nStrike - nBall << endl;
		cout << endl;

		if (nStrike == 3)
		{
			bIsWin = true;
			break; //switch or for, while���� ���������� ����ϴ� �༮
		}
	}

	if (bIsWin == true)
	{
		cout << "3Strike �¸� " << endl;
	}
	else
	{
		cout << "10���� ��ȸ�� ��� ����߽��ϴ�." << endl;
	}
}