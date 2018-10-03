#include <iostream>
#include <time.h>
#include <Windows.h>
using namespace std;

enum CARD
{
	CARD_1G, CARD_2A, CARD_3G, CARD_4A, CARD_5A,
	CARD_6A, CARD7A, CARD_8G, CARD_9A, CARD_10A,
	CARD_1B, CARD_2B, CARD_3B, CARD_4B, CARD_5B,
	CARD_6B, CARD_7B, CARD_8B, CARD_9B, CARD_10B
};
enum JOKBO
{
	JK_38G, JK_18G, JK_13G, JK_1010, JK_99, JK_88, JK_77,
	JK_66, JK_55, JK_44, JK_33, JK_22, JK_11,JK_12, JK_14,
	JK_19, JK_101, JK_104, JK_46, JK_9, JK_8, JK_7, JK_6,
	JK_5, JK_4, JK_4, JK_2, JK_1, JK_0
};
struct tagPlayer
{
	string name;
	int money;
	CARD card[2];
	JOKBO jokbo;
};

JOKBO GetJokbo(CARD* card);	//���� ���
void OutCard(CARD cardNum);	//ȭ�� ���
void Shuffle(CARD* card);	//����
void Swap(CARD* card1, CARD* card2);	//����

void main()
{
	tagPlayer* player;
	int select;

	JOKBO max = JK_0;
	for (int i = 0; i < 20; i++)
		card[i] = CARD(i);
	srand(time(NULL));
	Shuffle(card);
	
	while (1)
	{
		if (isStart == false)
		{
			cout << "�÷��̾��� ��: ";
			cin >> select;

			player = new tagPlayer[select];

			for (int i = 0; i < select; i++)
			{
				cout << i + 1 << "��° �÷��̾� �̸�: ";
				cin >> player[i].name;
				player[i].money = 10000;
			}
		}
	}

	//ī�� �ޱ�
	for (int i = 0; i < select; i++)
	{
		player[i].card[0] = card[i];
		player[i].card[1] = card[i + select];
	}
	//���� ī�� ���
	for (int i = 0; i < select; i++)
	{
		cout << player[i].name << " :\t";
		OutCard(player[i].card[0]);
		cout << "\t";
		OutCard(player[i].card[i]);
		cout << "\t";
		player[i].jokbo =
			GetJokbo(player[i].card);
		cout << endl;
	}
	//��
	int totalMoney = 0;
	for (int i = 0; i < select; i++)
	{
		if (max > player[i].jokbo)
		{
			max = player[i].jokbo;
		}
	}
	for (int i = 0; i < select; i++)
	{
		if (max == player[i].jokbo)
		{
			cout << player[i].name << "�¸�!" << endl;
			player[i].money += totalMoney;
		}
	}

	delete[] player;
}

JOKBO GetJokbo(CARD * card)
{
	//46	->4A 4B 6A 6B
	//(4A 6A, 4A 6B, 4B 6A, 4B 6B) * 2,
	//(4A, 6A), (4A, 6B), (6A, 4B), (4B, 6B)
	//���� �༮�� ���ʿ� ��ġ

	if (card[0] > card[1])
	{
		Swap(&card[0], &card[1]);
	}
	if (card[0] == CARD_3G && card[1] == CARD_8G)
	{
		cout << "38����";
		return JK_38G;
	}
	else if()
	else //���� �� ���� ó��
	{
		int a, b, c;
		JOKBO jok;
		a = card[0] + 1;
		b = card[1] + 1;
		jok = JOKBO(JK_0 - (a + b) % 10);
		c = (a + b) % 10;
		switch (c)
		{
		case 9:
			cout << "����";
			break;
		case 0:
			cout << "����";
			break;
		default:
			cout << c << "��";
			break;
		}
	}
	return JOKBO();
}

void OutCard(CARD cardNum)
{
}

void Shuffle(CARD * card)
{
}

void Swap(CARD * card1, CARD * card2)
{
}
