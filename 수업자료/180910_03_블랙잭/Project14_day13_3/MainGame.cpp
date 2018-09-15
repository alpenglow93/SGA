#include "MainGame.h"
#include <time.h>
#include <Windows.h>


MainGame::MainGame()
{
	srand(time(NULL));
	for (int i = 0; i < 52; i++)
		card[i] = Card(i);
	com = Player("딜러");
	my = Player("플레이어");
}


MainGame::~MainGame()
{
}

void MainGame::Init()
{
	

	Shuffle();

	for (int i = 0; i < 2; i++)
	{
		com.PushCard(card[com.CardCount() + my.CardCount()]);
		my.PushCard(card[com.CardCount() + my.CardCount()]);
	}
}

void MainGame::Update()
{
	int select;
	while (true)
	{
		this->Init();
		this->Render();
		while (true) //카드 받는 것
		{
			if (com.SumAllCard() < 18)
			{
				this->Render();
				com.PushCard(card[com.CardCount() + my.CardCount()]);
			}
			else
				com.SetBool(true);
			if (my.GetBool() == false)
			{
				cout << "카드를 받겠습니까?(0,1) : ";
				cin >> select;
				if (select == 0)
				{
					this->Render();
					my.PushCard(card[com.CardCount() + my.CardCount()]);
				}
				else
					my.SetBool(true);
			}
			if (com.GetBool() && my.GetBool()) break;
		}
		Sleep(500);
		this->Render();

		//조건 
		if (my.SumAllCard() > 21)
		{
			if (com.SumAllCard() > 21)
			{
				cout << "비겼다" << endl;
			}
			else
			{
				cout << "졌다" << endl;
				my.SetMoney(-1000);
			}
		}
		else
		{
			if (com.SumAllCard() == 21)
			{
				if (my.SumAllCard() == 21)
				{
					if (com.CardCount() > my.CardCount())
					{
						cout << "졌다" << endl;
						my.SetMoney(-1000);
					}
					else if (com.CardCount() < my.CardCount())
					{
						cout << "이겼다" << endl;
						my.SetMoney(1000);
					}
					else
					{
						cout << "비겼다" << endl;
					}
				}
			}
			else
			{
				if (com.SumAllCard() < 21 &&
					com.SumAllCard() > my.SumAllCard())
				{
					cout << "졌다" << endl;
					my.SetMoney(-1000);
				}
				else
				{
					cout << "이겼다" << endl;
					my.SetMoney(1000);
				}
			}
		}
	}
}

void MainGame::Render()
{
	Sleep(500);
	system("cls");
	com.Render();
	my.Render();
}

void MainGame::Shuffle()
{
	for (int i = 0; i < 1000;i++)
	{
		int sour = rand() % 52;
		int dest = rand() % 52;
		Card temp = card[sour];
		card[sour] = card[dest];
		card[dest] = temp;
	}
}
