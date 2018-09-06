#include <iostream>
#include <time.h>
using namespace std;

//���� �߱�

//1~9 ���� �߿��� �ߺ����� �ʴ� 3���� ����(����)�� ��ǻ�Ͱ� ����
//�÷��̾�� 3���� ���ڸ� �Է��ؼ� �ڸ� ���ڸ� ���Ͽ� �����ϴ� ����

void main()
{
	int aNumber[9];	//1 ~ 9 ������ ���ڸ� ����
	int aSelect[3];	//���� ���� �� ���� 3���� ����

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
		sour = rand() % 9;	//9 -> �迭�� ũ��
		dest = rand() % 9;	//9 -> �迭�� ũ��

		//swap
		temp = aNumber[sour];
		aNumber[sour] = aNumber[dest];
		aNumber[dest] = temp;
	}

	//���� �����
	for (int i = 0; i < 10; i++)	//10�� ���� �ϰڴ�
	{
		cout << "ġƮ: ";
		for (int j = 0; j < 3; j++)
		{
			cout << aNumber[j] << " ";
		}
		cout << endl;

		//���� ���� 3���� �Է�
		cout << "���� �Է�" << endl;
		for (int j = 0; j < 3; j++)
		{
			cin >> aSelect[j];
		}
		
		//�� ��
		int nStrike = 0;
		int nBall = 0;

		for (int j = 0; j < 3; j++)	//���� ������ 3��
		{
			for (int k = 0; k < 3; k++)	//��ǻ�Ͱ� ������ 3��
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

		cout << "S: " << nStrike << " B: " << nBall << " O: " << 3 - nStrike - nBall << endl;

		if (nStrike == 3)
		{
			bIsWin = true;
			break;	//switch of for, while���� ���������� ����ϴ� ��ɾ�
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