#include <iostream>
#include <time.h>
#include <Windows.h>
using namespace std;

//숙제풀이
//하이로우세븐

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
	int number = num % 13; +1;

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
	int card[CARDCOUNT];	//카드 52장
	int money = 10000;		//소지금
	int select;
	int batting;

	//카드에 숫자를 넣는다
	for (int i = 0; i < CARDCOUNT; i++)
		card[i] = i;

	srand(time(NULL));

	//카드섞기
	//셔플 알고리즘
	for (int i = 0; i < 1000; i++)
	{
		int temp, sour, dest;
		sour = rand() % CARDCOUNT;
		dest = rand() % CARDCOUNT;

		temp = card[sour];
		card[sour] = card[dest];
		card[dest] = temp;
	}

	int gameCount = 0;	//월남뽕에서 drop과 같은 역할	...모르겠는데?

	STATE state = STATE_NONE;	//현재 비교할 카드가 어떤 녀석인지

	//////////////////////////////////////////////
	//게임 시작
	while(1)
	{
		cout << "소지금: " << money << endl;
		for (int i = gameCount; i < gameCount + 5; i++)
		{
			if (i == gameCount + 4) cout << "치트: ";
			int number = card[i] % 13;
			int shape = card[i] / 13;

			switch (shape)
			{
			case 0:
				cout << "♠";
				break;
			case 1:
				cout << "♥";
				break;
			case 2:
				cout << "♣";
				break;
			case 3:
				cout << "◆";
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
		cout << "하이(0), 로우(1), 세븐(2) 입력: ";
		cin >> select;
		cout << "소지금: " << money;
		cout << "배팅: ";
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

		Sleep(1000);	//1초 동안 잠시 화면 대기
		system("cls");	//화면을 지우겠다

		gameCount += 5;
		if (gameCount >= 50)
			break;
	}
}