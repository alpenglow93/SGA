#include <iostream>
#include <time.h>
#include <string>
using namespace std;
enum CARD
{
	CARD_1G, CARD_2A, CARD_3G, CARD_4A, CARD_5A,
	CARD_6A, CARD_7A, CARD_8G, CARD_9A, CARD_10A,
	CARD_1B, CARD_2B, CARD_3B, CARD_4B, CARD_5B,
	CARD_6B, CARD_7B, CARD_8B, CARD_9B, CARD_10B,
};
enum JOKBO
{
	JB_38G, JB_18G, JB_13G, JB_1010, JB_99, JB_88, JB_77,
	JB_66, JB_55, JB_44, JB_33, JB_22, JB_11, JB_12, JB_14,
	JB_19, JB_101,JB_104,JB_46, JB_9, JB_8, JB_7, JB_6,
	JB_5, JB_4, JB_3, JB_2, JB_1, JB_0
};
struct tagPlayer
{
	string name;
	CARD card[2];
	JOKBO jokbo;
};

void Shuffle(CARD* card);
void Swap(CARD* card1, CARD* card2);
void OutCard(int num);
JOKBO OutJokbo(CARD card1, CARD card2);
void main()
{
	tagPlayer* player;
	int playNum;
	CARD card[20];

	for (int i = 0; i < 20; i++)
		card[i] = CARD(i);

	Shuffle(card);

	cout << "ÇÃ·¹ÀÌ¾îÀÇ ¼ö : ";
	cin >> playNum;

	player = new tagPlayer[playNum];
	for (int i = 0; i < playNum; i++)
	{
		cout << i + 1 << "¹øÂ° ÇÃ·¹ÀÌ¾î ÀÌ¸§ : ";
		cin >> player[i].name;
	}
	//Ä«µå¸¦ ¹Þ´Â´Ù.
	for (int i = 0; i < playNum;i++)
	{
		player[i].card[0] = card[i];
		player[i].card[1] = card[i + playNum];
	}

	//È­¸é¿¡ Ãâ·Â
	for (int i = 0; i < playNum;i++)
	{
		cout << player[i].name << " :\t";
		OutCard(player[i].card[0]);
		cout << "\t";
		OutCard(player[i].card[1]);
		cout << "\t";
		player[i].jokbo = OutJokbo(
			player[i].card[0], player[i].card[1]);
		cout << endl;
	}
	//ºñ±³ 
	JOKBO min = JB_0;
	for (int i = 0; i < playNum;i++)
	{
		if (min > player[i].jokbo)
			min = player[i].jokbo;
	}

	for (int i = 0; i < playNum; i++)
	{
		if (min == player[i].jokbo)
		{
			cout << player[i].name << " ½Â¸®!" << endl;
		}
	}

	delete[] player;
}

void Shuffle(CARD * card)
{
	srand(time(NULL));
	for (int i = 0; i < 1000; i++)
	{
		int sour = rand() % 20;
		int dest = rand() % 20;
		Swap(&card[sour], &card[dest]);
	}
}

void Swap(CARD* card1, CARD* card2)
{
	CARD temp = *card1;
	*card1 = *card2;
	*card2 = temp;
}

void OutCard(int num)
{
	switch (num)
	{
	case 0:
		cout << "1±¤";
		break;
	case 2:
		cout << "3±¤";
		break;
	case 7:
		cout << "8±¤";
		break;
	default:
		cout << num % 10 + 1 << "¿ù";
		break;
	}
}

JOKBO OutJokbo(CARD card1, CARD card2)
{
	//3±¤ 8±¤ 
	//8±¤ 3±¤

	//¼¼·ú 4A 6A 4B 6B
	//4A 6A, 4A  6B, 4B 6A, 4B 6B

	//card1 < card2
	//4A (6A , 6B) , 6A( 4B) , 4B 6B 
	if (card1 > card2)
	{
		Swap(&card1, &card2);
	}

	if (card1 == CARD_3G && card2 == CARD_8G)
	{
		cout << "38±¤¶¯";
		return JB_38G;
	}

	else if (card1 == CARD_1G && card2 == CARD_8G)
	{
		cout << "18±¤¶¯";
		return JB_18G;
	}

	else if (card1 == CARD_1G && card2 == CARD_3G)
	{
		cout << "13±¤¶¯";
		return JB_13G;
	}

	else if (card1 == CARD_10A && card2 == CARD_10B)
	{
		cout << "10¶¯";
		return JB_1010;
	}

	else if (card1 == CARD_9A && card2 == CARD_9B)
	{
		cout << "9¶¯";
		return JB_99;
	}

	else if (card1 == CARD_8G && card2 == CARD_8B)
	{
		cout << "8¶¯";
		return JB_88;
	}

	else if (card1 == CARD_7A && card2 == CARD_7B)
	{
		cout << "7¶¯";
		return JB_77;
	}

	else if (card1 == CARD_6A && card2 == CARD_6B)
	{
		cout << "6¶¯";
		return JB_66;
	}

	else if (card1 == CARD_5A && card2 == CARD_5B)
	{
		cout << "5¶¯";
		return JB_55;
	}

	else if (card1 == CARD_4A && card2 == CARD_4B)
	{
		cout << "4¶¯";
		return JB_44;
	}

	else if (card1 == CARD_3G && card2 == CARD_3B)
	{
		cout << "3¶¯";
		return JB_33;
	}

	else if (card1 == CARD_2A && card2 == CARD_2B)
	{
		cout << "2¶¯";
		return JB_22;
	}

	else if (card1 == CARD_1G && card2 == CARD_1B)
	{
		cout << "1¶¯";
		return JB_11;
	}

	else if (card1 == CARD_1G && card2 == CARD_2A ||
		card1 == CARD_1G && card2 == CARD_2B ||
		card1 == CARD_2A && card2 == CARD_1B ||
		card1 == CARD_1B && card2 == CARD_2B)
	{
		cout << "¾Ë¸®";
		return JB_12;
	}

	else if (card1 == CARD_1G && card2 == CARD_4A ||
		card1 == CARD_1G && card2 == CARD_4B ||
		card1 == CARD_4A && card2 == CARD_1B ||
		card1 == CARD_1B && card2 == CARD_4B)
	{
		cout << "µ¶»ç";
		return JB_14;
	}

	else if (card1 == CARD_1G && card2 == CARD_9A ||
		card1 == CARD_1G && card2 == CARD_9B ||
		card1 == CARD_9A && card2 == CARD_1B ||
		card1 == CARD_1B && card2 == CARD_9B)
	{
		cout << "±¸»æ";
		return JB_19;
	}

	else if (card1 == CARD_1G && card2 == CARD_10A ||
		card1 == CARD_1G && card2 == CARD_10B ||
		card1 == CARD_10A && card2 == CARD_1B ||
		card1 == CARD_1B && card2 == CARD_10B)
	{
		cout << "Àå»æ";
		return JB_101;
	}

	else if (card1 == CARD_4A && card2 == CARD_10A ||
		card1 == CARD_4A && card2 == CARD_10B ||
		card1 == CARD_10A && card2 == CARD_4B ||
		card1 == CARD_4B && card2 == CARD_10B)
	{
		cout << "Àå»ç";
		return JB_104;
	}

	else if (card1 == CARD_4A && card2 == CARD_6A ||
		card1 == CARD_4A && card2 == CARD_6B ||
		card1 == CARD_6A && card2 == CARD_4B ||
		card1 == CARD_4B && card2 == CARD_6B)
	{
		cout << "¼¼·ú";
		return JB_46;
	}

	else
	{
		int a, b, c;
		JOKBO jok;
		a = card1 + 1;
		b = card2 + 1;
		jok = JOKBO(JB_0 - (a + b) % 10);
		c = (a + b) % 10;

		switch (c)
		{
		case 9:
			cout << "°©¿À";
			break;
		case 0:
			cout << "¸ÁÅë";
			break;
		default:
			cout << c << "²ý";
			break;
		}
		return jok;
	}
}
