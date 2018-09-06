#include <iostream>
#include <time.h>
#include <Windows.h>

using namespace std;

void main()
{
	//형변환 : 데이터 형태를 변환 시키는 녀석

	//문자 -> 정수
	//cout << (int)'A' << endl;
	//cout << (char)97 << endl;
	//cout << (int) 25.63637 << endl;
	//
	//cout << (char)35 << endl;

	int bingo[25];	//빙고판
	int select;		//숫자선택

	int lineCount =0; //1줄 빙고 여부
	int bingoCount =0;

	for (int i = 0; i < 25; i++)
		bingo[i] = i;

	srand(time(NULL));

	for (int i = 0; i < 1000; i++)
	{
		int temp, sour, dest;
		sour = rand() % 25;
		dest = rand() % 25;

		temp = bingo[sour];
		bingo[sour] = bingo[dest];
		bingo[dest] = temp;
	}
	while (true)
	{
		cout << "====================================" << endl;
		cout << " BINGO GAME          BINGOCOUNT : " << bingoCount << endl;;
		cout << "====================================" << endl;
		for (int i = 0; i < 25; i++)
		{
			cout << "[";
			if (bingo[i] < 10 || bingo[i] == 35) cout << " ";
			//cout << bingo[i];
			(bingo[i] == 35) ? cout << (char)bingo[i] :
				cout << bingo[i];
	
			//삼항 연산자 -> (조건 ) ? 참 : 거짓;
			cout << "]\t";
			if (i % 5 == 4) cout << endl;
		}
		cout << "====================================" << endl;
		cout << endl;
		cout << "====================================" << endl;

		COORD coord = { 4, 9 };
		SetConsoleCursorPosition(
			GetStdHandle(STD_OUTPUT_HANDLE), coord);
		if (bingoCount >= 2)
		{

			cout << "  BINGOCLEAR!!" << endl;
			break;
		}
		else
		{
			cout << "  숫자 입력 하시오 : ";
			cin >> select;
		}

		Sleep(500);
		system("cls");

		//선택한 숫자는 35(#)으로 변경
		for (int i = 0;i < 25; i++)
		{
			if (bingo[i] == 35) continue;
			if (bingo[i] == select)
			{
				bingo[i] = 35;
				break;
			}
		}
		bingoCount = 0; //빙고 계산전 초기화
		//빙고 계산
		//가로 빙고 
		for (int i = 0; i < 5;i++)
		{
			lineCount = 0;
			for (int j = 0; j < 5; j++)
			{
				int index = i * 5 + j;
				if (bingo[index] == 35)
				{
					lineCount++;
					if (lineCount == 5) bingoCount++;
				}
			}
		}
		//세로 빙고
		for (int i = 0; i < 5; i++)
		{
			lineCount = 0;
			for (int j = 0; j < 5; j++)
			{
				int index = j * 5 + i;
				if (bingo[index] == 35)
				{
					lineCount++;
					if (lineCount == 5) bingoCount++;
				}
			}
		}

		//대각선 왼상->오르쪽 
		lineCount = 0;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5;j++)
			{
				if (i == j && bingo[i * 5 + j] == 35)
				{
					lineCount++;
					if (lineCount == 5) bingoCount++;
				}
			}
		}

		//대각선 오상 -> 왼하 
		lineCount = 0;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5;j++)
			{
				if (i == 4 - j && bingo[i * 5 + j] == 35)
				{
					lineCount++;
					if (lineCount == 5) bingoCount++;
				}
			}
		}
	}
}