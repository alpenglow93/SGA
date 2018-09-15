#include <iostream>
#include <time.h>
#include <Windows.h>
#include <conio.h>
using namespace std;

#define POW(p) (p * p)

void Swap(int* pNum1, int* pNum2)
{
	int temp = *pNum1;
	*pNum1 = *pNum2;
	*pNum2 = temp;
}

void main()
{
	cout << "게임판 입력: ";
	int line;
	cin >> line;

	int* rect = new int[POW(line)];

	for (int i = 0; i < POW(line); i++)
		rect[i] = i;

	srand(time(NULL));
	for (int i = 0; i < 1000; i++)
	{
		int sour = rand() % (POW(line) - 1);
		int dest = rand() % (POW(line) - 1);
		Swap(&rect[sour], &rect[dest]);
	}
	int index = POW(line) - 1;
	int nCount = 0;

	while (1)
	{
		Sleep(50);
		system("cls");

		for (int i = 0; i < POW(line); i++)
		{
			cout << "[";
			if (rect[i] < 10 && rect[i] != POW(line) - 1)
				cout << " ";
			if (rect[i] == POW(line) - 1)
				cout << " @";
			else cout << rect[i];
			cout << "]";
			if (i % line == line - 1) cout << endl;
		}
		if (nCount == POW(line)) break;

		int move = getch();
		
		switch (move)
		{
		case 'w':
			if (index / line > 0)
			{
				Swap(&rect[index], &rect[index - line]);
				index -= line;
			}
			break;
		case 's':
			if (index / line < line - 1)
			{
				Swap(&rect[index], &rect[index + line]);
				index += line;
			}
			break;
		case 'a':
			if (index / line > 0)
			{
				Swap(&rect[index], &rect[index - 1]);
				index -= 1;
			}
			break;
		case 'd':
			if (index % line < line - 1)
			{
				Swap(&rect[index], &rect[index + 1]);
				index += 1;
			}
			break;
			//치트
		case 'g':
			for (int i = 0; i < POW(line) - 2; i++)
				rect[i] = i;
			rect[POW(line) - 2] = POW(line) - 1;
			rect[POW(line) - 1] = POW(line) - 2;
			index = POW(line) - 2;
			break;
		}
		//종료 조건
		nCount = 0;
		for (int i = 0; i < POW(line); i++)
		{
			if (i == rect[i]) nCount++;
		}
	}
	delete[] rect;
}

//숙제풀이
//슬라이드 퍼즐

//void main()
//{
//	cout << "게임판 갯수 선택: ";
//	int select;
//	cin >> select;
//
//	int gameRect = select * select;
//	int* rect = new int[gameRect];
//
//	for (int i = 0; i = gameRect; i++)
//		rect[i] = i;
//	srand(time(NULL));
//	for (int i = 0; i < gameRect; i++)
//	{
//		int temp, sour, dest;
//		sour = rand() % (gameRect - 1);
//		dest = rand() % (gameRect - 1);
//
//		temp = rect[sour];
//		rect[sour] = rect[dest];
//		rect[dest] = temp;
//	}
//	int index = gameRect - 1;
//	while (1)
//	{
//		Sleep(500);
//		system("cls");
//		for (int i = 0; i < gameRect; i++)
//		{
//			cout << "[";
//			if (rect[i] < 10) cout << " ";
//			if (rect[i] == gameRect - 1)
//			{
//				cout << "#";
//			}
//			else
//			{
//				cout << rect[i];
//			}
//			cout << rect[i];
//			cout << "]";
//			if (i % select == select - 1) cout << endl;
//		}
//		char move = getch();
//		switch (move)
//		{
//		case 'w':
//			if (index / select > 0)
//			{
//				swap(rect[index], rect[index - select]);
//				index -= select;
//			}
//			swap(rect[index], );
//			break;
//		case 's':
//			if (index / select < select - 1)
//			{
//				swap(rect[index], rect[index - select]);
//				index -= select;
//			}
//			break;
//		case 'a':
//			if (index % select > 0)
//			{
//				swap(rect[index], rect[index - select]);
//				index -= select;
//			}
//			break;
//		case 'd':
//			if (index % select < select - 1)
//			{
//				swap(rect[index], rect[index - select]);
//				index -= select;
//			}
//			break;
//		case 'g':	//치트
//			for (int i = 0; i < gameRect - 1; i++)
//			{
//				rect[i] = i;
//			}
//			rect[gameRect - 1] = gameRect - 2;
//			rect[gameRect - 2] = gameRect - 1;
//			index = gameRect - 2;
//		}
//		//게임이 종료되는 조건
//		int check = 0;
//		for (int i = 0; i < gameRect; i++)
//		{
//			if (rect[i] == i) check++;
//		}
//		if (check == gameRect) break;
//	}
//	delete[] rect;
//}