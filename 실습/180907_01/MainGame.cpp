#include "MainGame.h"



MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}

void MainGame::Init()	//�ʱ�ȭ ������ �ѹ��� ����
{
	srand(time(NULL));
	for (int i = 0; i < 16; i++)
	{
		cards[i] = Card(65 + i);
		cards[8 + i] = Card(65 + i);
	}
	Shuffle(cards);
}

void MainGame::Release()
{
}

void MainGame::Update()
{
	int gameEnd = 0;
	while (1)
	{
		this->Render();
		if (gameEnd == 8) break;
		//ī�� ����
		for (int i = 0; i < 2; )
		{
			cout << "���ڸ� �Է� �ϼ���";
			cin >> select;
			if (cards[select].GetBool()) continue;
			cards[select].ChangeShow();
			saveCard[i] = select;
			
			i++;
			Sleep(10);
			system("cls");
			this->Render();
		}
		//ī�� ��
		if (cards[saveCard[0]].IsCheck(&cards[saveCard[1]]))
		{
			gameEnd++;
		}
		Sleep(500);
		system("cls");
	}
}

void MainGame::Render()
{
	for (int i = 0; i < 16; i++)
	{
		cards[i].Render(i);
		if (i % 4 == 3) cout << endl;
	}
}

void MainGame::Shuffle(Card * card)
{
	for (int i = 0; i < 1000; i++)
	{
		int sour = rand() % 16, dest = rand() % 16;
		Card temp = card[sour];
		card[sour] = card[dest];
		card[dest] = temp;
	}
}
