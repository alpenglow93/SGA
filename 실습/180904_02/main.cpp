#include <iostream>
#include <time.h>
#include <Windows.h>
using namespace std;

//숙제풀이
//슬라이드 퍼즐

void main()
{
	cout << "게임판 갯수 선택: ";
	int select;
	cin >> select;

	int gameRect = select * select;
	int* rect = new int[gameRect];

	for (int i = 0; i = gameRect; i++)
		rect[i] = i;
	srand(time(NULL));
	for (int i = 0; i < gameRect; i++)
	{
		int temp, sour, dest;
		sour = rand() % (gameRect - 1);
		dest = rand() % (gameRect - 1);

		temp = rect[sour];
		rect[sour] = rect[dest];
		rect[dest] = temp;
	}
	int index = gameRect - 1;
	while (1)
	{
		Sleep(500);
		system("cls");
		for (int i = 0; i < gameRect; i++)
		{
			cout << "[";
			if (rect[i] < 10) cout << " ";
			if (rect[i] == gameRect - 1)
			{
				cout << "#";
			}
			else
			{
				cout << rect[i];
			}
			cout << rect[i];
			cout << "]";
			if (i % select == select - 1) cout << endl;
		}
		char move = getch();
		switch (move)
		{
		case 'w':
			if (index / select > 0)
			{
				swap(rect[index], rect[index - select]);
				index -= select;
			}
			swap(rect[index], );
			break;
		case 's':
			if (index / select < select - 1)
			{
				swap(rect[index], rect[index - select]);
				index -= select;
			}
			break;
		case 'a':
			if (index % select > 0)
			{
				swap(rect[index], rect[index - select]);
				index -= select;
			}
			break;
		case 'd':
			if (index % select < select - 1)
			{
				swap(rect[index], rect[index - select]);
				index -= select;
			}
			break;
		case 'g':	//치트
			for (int i = 0; i < gameRect - 1; i++)
			{
				rect[i] = i;
			}
			rect[gameRect - 1] = gameRect - 2;
			rect[gameRect - 2] = gameRect - 1;
			index = gameRect - 2;
		}
		//게임이 종료되는 조건
		int check = 0;
		for (int i = 0; i < gameRect; i++)
		{
			if (rect[i] == i) check++;
		}
		if (check == gameRect) break;
	}
	delete[] rect;
}