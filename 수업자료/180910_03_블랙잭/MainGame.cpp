#include "MainGame.h"
#include <time.h>
#include <Windows.h>


MainGame::MainGame()
{
	srand(time(NULL));
	for (int i = 0; i < 52; i++)
		card[i] = Card(i);
	com = Player("����");
	my = Player("�÷��̾�");
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
		while (true) //ī�� �޴� ��
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
				cout << "ī�带 �ްڽ��ϱ�?(0,1) : ";
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

		//���� 
		if (my.SumAllCard() > 21)
		{
			if (com.SumAllCard() > 21)
			{
				cout << "����" << endl;
			}
			else
			{
				cout << "����" << endl;
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
						cout << "����" << endl;
						my.SetMoney(-1000);
					}
					else if (com.CardCount() < my.CardCount())
					{
						cout << "�̰��" << endl;
						my.SetMoney(1000);
					}
					else
					{
						cout << "����" << endl;
					}
				}
			}
			else
			{
				if (com.SumAllCard() < 21 &&
					com.SumAllCard() > my.SumAllCard())
				{
					cout << "����" << endl;
					my.SetMoney(-1000);
				}
				else
				{
					cout << "�̰��" << endl;
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
