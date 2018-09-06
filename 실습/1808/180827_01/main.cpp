#include <iostream>
#include <time.h>
//srand(time(NULL)); 을 사용하기 위한 헤더

using namespace std;

//숙제풀이
//1. 가위바위보 게임 만들기

//나 vs 컴퓨터

void main()
{
	srand(time(NULL));	//rand() 함수를 사용하기 전 랜덤한 수를 받기 위해 사용

	int nSelectNum;	//내가 입력한 숫자를 저장
	int nComNumber;	//컴퓨터가 랜덤하게 선택한 숫자 저장

	int nWin = 0;	//내가 이긴 횟수
	int nLose = 0;	//내가 진 횟수

	//게임 시작
	for (int i = 0; i < 5; i++)	//게임 5판 하겠다
	{
		//반복문 안에서 게임 한번을 작성

		//1. 내가 원하는 숫자를 선택
		cout << "가위(0), 바위(1), 보(2) 중에 선택 하시오 :";
		cin >> nSelectNum;
		//2. 컴퓨터가 랜덤한 숫자를 선택
		nComNumber = rand() % 3;	//0 ~ 2
		
		cout << endl;

		switch (nSelectNum)
		{
		case 0:
			cout << "플레이어: 가위 vs ";
			break;
		case 1:
			cout << "플레이어: 바위 vs ";
			break;
		case 2:
			cout << "플레이어: 보 vs ";
			break;
		}

		switch (nComNumber)
		{
		case 0:
			cout << "가위 :컴퓨터" << endl;
			break;
		case 1:
			cout << "바위 :컴퓨터" << endl;
			break;
		case 2:
			cout << "보 :컴퓨터" << endl;
			break;
		}

		//3. 나와 컴퓨터를 비교 후, 결과 저장
		//가위(0), 바위(1), 보(2)
		//0 - 1, 1 - 2, 2 - (3 % 3)
		//비겼을때
		if (nSelectNum == nComNumber)
		{
			cout << "비겼다" << endl;
		}
		//이겼을때
		//컴퓨터보다 내가 +1
		else if ((nComNumber + 1) % 3 == nSelectNum)
		{
			cout << "내가 이겼다" << endl;
			nWin++;
		}
		//졌을때
		//컴퓨터보다 내가 -1
		else if ((nSelectNum + 1) % 3 == nComNumber)
		{
			cout << "내가 졌다" << endl;
			nLose++;
		}
		cout << endl;
	}

	//4. 최종적인 결과를 출력
	cout << "승리: " << nWin << endl << "패배: " << nLose << endl << "비김: " << 5 - nWin - nLose << endl;
}