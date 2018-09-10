#include "CardTable.h"



void CardTable::SaveShuffle()
{

	srand(time(NULL));
	char sour, dest, temp;
	for (int i = 0; i < 100; i++)
	{
		sour = rand() % 16;
		dest = rand() % 16;

		temp = m_card_table[sour];
		m_card_table[sour] = m_card_table[dest];
		m_card_table[dest] = temp;
	}
}

void CardTable::NumPrint()
{
	for (int i = 0; i < 16; i++)
	{
		cout << "[";
		if (i < 10) cout << " ";
		cout << i << "]";
		if ((i + 1) % 4 == 0)
		{
			cout << endl;
		}
	}
}

void CardTable::WordPrint()
{
	for (int i = 0; i < 16; i++)
	{
		cout << "[";
		switch (m_card_table[i])
		{
		case 0:
			cout << "¡Ú";
			break;
		case 1:
			cout << "¢¾";
			break;
		case 2:
			cout << "¡ß";
			break;
		case 3:
			cout << "¢¼";
			break;
		case 4:
			cout << "¢À";
			break;
		case 5:
			cout << "¡á";
			break;
		case 6:
			cout << "¡Ü";
			break;
		case 7:
			cout << "¡ã";
			break;
		}
		cout << "]";
		//cout << "[" << m_card_table[i] << "]";
		if ((i + 1) % 4 == 0)
		{
			cout << endl;
		}
	}
	
}

CardTable::CardTable()
{
	for (int i = 0; i < 8; i++)
	{
		m_card_table[i] = i;
		m_card_table[i + 8] = i;
	}
}



CardTable::~CardTable()
{
}