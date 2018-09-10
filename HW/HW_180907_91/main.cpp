#include <iostream>
#include <time.h>
#include <cstring>
//#include <conio.h>
using namespace std;

#define BLACKJACK 21
#define COM_LIMIT 17
#define MAX_CARD 11

void PrintTitle(string title);
void PrintCard(int* card, int counts);
void ShuffleCard(int* card, int counts);
void InitReceivedCard(int* card);
void ShowReceivedCard(int * player, int* computer);
void ShowResult(int playerSum, int computerSum);
bool IsYesOrNo(string str);
int GetCardSum(int* card);
int money = 10000;

void main()
{
	srand(time(NULL));

	int card[52] = { 0 };
	int counts = sizeof(card) / sizeof(int);

	//ī�� �ʱ�ȭ
	for (int row = 0; row < 4; row++)
	{
		for (int column = 0; column < 13; column++)
		{
			int cardNum = column + row * 13;

			if (column < 10) card[cardNum] = column + 1;
			else card[cardNum] = 10;
		}
	}

	//ī�� ���
	//PrintTitle("ī�� ���");
	//PrintCard(card, counts);

	//cout << endl << "������ �����Ϸ��� Enter Ű�� ��������." << endl;
	//_getch();

	//�÷��̾�� ��ǻ�� ī�� ����.
	int player[MAX_CARD] = { 0 };
	int computer[MAX_CARD] = { 0 };

	bool isGameStrart = true;
	bool isGameEnd;
	bool stayPlayer;
	bool stayComputer;

	int nowCardNum = 0;
	int receivedCounts = 0;

	//���� ����
	while (1)
	{
		system("cls");

		cout << "������: " << money << endl;

		//���� �ʱ�ȭ: ���� ���۽ÿ��� ����Ǿ���Ѵ�
		if (isGameStrart)
		{
			isGameStrart = false;
			isGameEnd = false;
			stayPlayer = false;
			stayComputer = false;

			receivedCounts = 0;
			nowCardNum = 0;

			InitReceivedCard(player);
			InitReceivedCard(computer);

			ShuffleCard(card, counts);

			for (int i = 0; i < 2; i++)
			{
				player[receivedCounts] = card[nowCardNum++];
				computer[receivedCounts] = card[nowCardNum++];

				receivedCounts++;
			}
		}

		if (isGameEnd)
		{
			system("cls");
			PrintTitle("�ºΰ� �����ϴ�.");
			ShowReceivedCard(player, computer);
			ShowResult(GetCardSum(player), GetCardSum(computer));

			if (money < 1000)
			{
				cout << "�������� �����մϴ�" << endl;
				cout << "������ �����մϴ�" << endl;
				break;
			}
			else if (IsYesOrNo("������ ��� �Ͻðڽ��ϱ�?"))
			{
				isGameStrart = true;
				continue;
			}
			else
			{
				break;
			}
		}

		cout << "�÷��̾��� ī�� " << endl;
		ShowReceivedCard(player, NULL);

		if (stayPlayer == false)
		{
			int player_sum = GetCardSum(player);

			if (player_sum > BLACKJACK)
			{
				isGameEnd = true;
				continue;
			}
			else if (player_sum == BLACKJACK)
			{
				stayPlayer = true;
			}
			else
			{
				if (IsYesOrNo("�߰� ī�带 �����ðڽ��ϱ�?"))
				{
					player[receivedCounts] = card[nowCardNum++];
				}
				else
				{
					stayPlayer = true;
				}
			}
		}

		if (stayComputer == false)
		{
			int computer_sum = GetCardSum(computer);

			if (computer_sum > BLACKJACK)
			{
				isGameEnd = true;
				continue;
			}
			else if (computer_sum >= COM_LIMIT)
			{
				stayComputer = true;
			}
			else
			{
				computer[receivedCounts] = card[nowCardNum++];
			}
		}

		if (stayPlayer && stayComputer) isGameEnd = true;

		receivedCounts++;
	}

}

void PrintTitle(string title)
{
	cout << "===============================================================" << endl;
	cout << "> ";
	title;
	cout << endl;
	cout << "===============================================================" << endl;
}

void PrintCard(int * card, int counts)
{
	for (int i = 0; i < counts; i++)
	{
		cout << card[i] << "\t";
	}
	cout << endl;
}

void ShuffleCard(int * card, int counts)
{
	for (int i = 0; i < counts; i++)
	{
		int rnd = (rand() % counts);
		int temp = card[i];
		card[i] = card[rnd];
		card[rnd] = temp;
	}
}

void InitReceivedCard(int * card)
{
	for (int i = 0; i < MAX_CARD; i++)
	{
		card[i] = 0;
	}
}

void ShowReceivedCard(int * player, int* computer)
{
	if (player == NULL && computer == NULL) return;

	bool showPlayer = (player == NULL) ? false : true;
	bool showComputer = (computer == NULL) ? false : true;

	if (showPlayer) cout << "�÷��̾�";
	cout << "\t";
	if (showComputer) cout << "����";
	cout << endl;

	for (int i = 0; i < MAX_CARD; i++)
	{
		if (showPlayer == false && showComputer == false) break;

		if (showPlayer)
		{
			if (player[i] != 0) cout << player[i];
			else showPlayer = false;
		}

		cout << "\t\t";

		if (showComputer)
		{
			if (computer[i] != 0) cout << computer[i];
			else showComputer = false;
		}
		cout << endl;
	}
}

void ShowResult(int playerSum, int computerSum)
{
	enum WINNER
	{
		NONE,
		PLAYER,
		COMPUTER,
		DRAW
	};

	cout << "���" << "\t\t" << "���" << endl;
	cout << playerSum << "\t\t" << computerSum << endl;

	WINNER winner = NONE;

	if (playerSum > 21) winner = COMPUTER;
	else if (computerSum > 21) winner = PLAYER;
	else
	{
		if (playerSum < computerSum) winner = PLAYER;
		else if (playerSum < computerSum) winner = COMPUTER;
		else winner = DRAW;
	}

	switch (winner)
	{
	case PLAYER:
		cout << "�÷��̾� �¸�!" << endl;
		money += 1000;
		break;
	case COMPUTER:
		cout << "���� �¸�!" << endl;
		money -= 1000;
		break;
	case DRAW:
		cout << "���º�!" << endl;
		break;
	}

	cout << "���� ������: " << money;

	cout << endl << endl;
}

bool IsYesOrNo(string str)
{
	char yesorno = ' ';
	str;
	cout << " (Y/N) : ";
	cin >> yesorno;
	cout << endl;

	if (yesorno == 'y' || yesorno == 'Y')
	{
		return true;
	}
	else
		return false;
}

int GetCardSum(int * card)
{
	int sum = 0;
	for (int i = 0; i < MAX_CARD; i++)
	{
		if (card[i] == 0) break;

		sum += card[i];
	}

	return sum;
}
