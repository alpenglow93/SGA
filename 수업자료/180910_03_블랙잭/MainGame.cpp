#include "MainGame.h"
#include <time.h>
#include <Windows.h>



MainGame::MainGame()
{
	srand(time(NULL));
	for (int i = 0; i < 52; i++)
	{
		card[i] = Card(i);
	}
	com = Player("����");
	my = Player("�÷��̾�");
}


MainGame::~MainGame()
{
}

void MainGame::Init()
{
	Shuffle();
	
	com.SetBool(false);
	my.SetBool(false);

	com.SetClear();
	my.SetClear();

	for (int i = 0; i < 2; i++)
	{
		com.PushCard(card[com.CardCount() + my.CardCount()]);
		my.PushCard(card[com.CardCount() + my.CardCount()]);

	}
}

void MainGame::Update()
{
	int select;
	while (1)
	{
		this->Init();
		this->Render();
		while (1)	//ī�� �޴� ��
		{
			if (com.sumAllCard() < 18)
			{
				com.PushCard(card[com.CardCount() + my.CardCount()]);
				this->Render();
			}
			else
				com.SetBool(true);
			if (my.GetBool() == false)
			{
				cout << "ī�带 �ްڽ��ϱ�?(0, 1) : ";
				cin >> select;
				if (select == 0)
				{
					my.PushCard(card[com.CardCount() + my.CardCount()]);
					this->Render();
				}
				else
					my.SetBool(true);
			}
			if (com.GetBool() && my.GetBool()) break;
		}

		Sleep(500);
		this->Render();

		//���� ��
		if (my.sumAllCard() > 21)
		{
			if (com.sumAllCard() > 21)
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
			if (com.sumAllCard() == 21)
			{
				if (my.sumAllCard() == 21)
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
				if (com.sumAllCard() < 21 && com.sumAllCard() > my.sumAllCard())
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
	for (int i = 0; i < 1000; i++)
	{
		int sour = rand() % 52;
		int dest = rand() % 52;
		Card temp = card[sour];
		card[sour] = card[dest];
		card[dest] = temp;
	}
}
