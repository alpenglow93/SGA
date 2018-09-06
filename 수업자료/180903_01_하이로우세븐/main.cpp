#include <iostream>
#include <time.h>
#include <Windows.h>

using namespace std;

#define CARDCOUNT 52

enum STATE
{
	STATE_HIGH,
	STATE_LOW,
	STATE_SEVEN,
	STATE_NONE
};

STATE GetState(int num)
{
	int number = num % 13 + 1;

	if (number > 7)
	{
		return STATE_HIGH;
	}
	else if (number < 7)
	{
		return STATE_LOW;
	}
	else
	{
		return STATE_SEVEN;
	}
	return STATE_NONE;
}

void main()
{
	int card[CARDCOUNT]; //ī��
	int money = 10000;	//������
	int select;			
	int batting;

	for (int i = 0;i < CARDCOUNT; i++)
		card[i] = i;

	srand(time(NULL));

	for (int i = 0; i < 1000; i++)
	{
		int temp, sour, dest;
		sour = rand() % CARDCOUNT;
		dest = rand() % CARDCOUNT;
		//swap
		temp = card[sour];
		card[sour] = card[dest];
		card[dest] = temp;
	}
	int gameCount = 0; // ������ drop �̶� ���� ��Ȱ

	STATE state = STATE_NONE; //���� ���� ī�尡 � �༮���� 

	//���� �ο� ���� ���� 

	while (true)
	{
		cout << "������ : " << money << endl;
		for (int i = gameCount; i < gameCount +5 ; i++)
		{
			if (i == gameCount + 4) cout << "ġƮ : ";

			int number = card[i] % 13;
			int shape = card[i] / 13;

			switch (shape)
			{
			case 0: 
				cout << "��";
				break;
			case 1:
				cout << "��";
				break;
			case 2:
				cout << "��";
				break;
			case 3:
				cout << "��";
				break;
			}
			switch (number)
			{
			case 0:
				cout << "A\t";
				break;
			case 10:
				cout << "J\t";
				break;
			case 11:
				cout << "Q\t";
				break;
			case 12:
				cout << "K\t";
				break;
			default:
				cout << number + 1 << "\t";
				break;
			}
		}
		state = GetState(card[gameCount + 4]);
		
		cout << endl;
		cout << "����(0), �ο�(1), ����(2) �Է� : ";
		cin >> select;
		
		cout << "���� : ";
		cin >> batting;

		if (state == select)
		{
			money += batting;
			if (select == STATE_SEVEN) money += batting;
		}
		else
		{
			money -= batting;
			if (select == STATE_SEVEN) money -= batting;
		}

		Sleep(1000);	//1�ʵ��� ��� ȭ�� ���
		system("cls");	// ȭ���� ����ڴ�.
		gameCount += 5;
		if (gameCount >= 50)
			break;
	}

}