#include <iostream>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define POW(p) (p * p)

using namespace std;
void Swap(int* pNum1, int* pNum2)
{
	int temp = *pNum1;
	*pNum1 = *pNum2;
	*pNum2 = temp;
}
void main()
{
	cout << "게임판 입력 : ";
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

	while (true)
	{
		Sleep(50);
		system("cls");

		for (int i = 0; i < POW(line); i++)
		{
			cout << "[";
			if (rect[i] < 10 && rect[i] != POW(line) - 1)
				cout << " ";
			if (rect[i] == POW(line) - 1)
				cout << "■";
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
			if (index % line > 0)
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
			for (int i = 0; i < POW(line) - 2;i++)
				rect[i] = i;
			rect[POW(line) - 2] = POW(line) - 1;
			rect[POW(line) - 1] = POW(line) - 2;
			index = POW(line) - 2;
			break;
		}
		//종료 조건
		nCount = 0;
		for (int i = 0; i < POW(line);i++)
		{
			if (i == rect[i]) nCount++;
		}
	}
	delete[] rect;
}