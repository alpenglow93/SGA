//1.가위 바위 보 게임 만들기 

//나 vs 컴퓨터 
#include <iostream>
#include <time.h>
//srand(time(NULL)) time(NULL)를 사용하기 위해 time.h 참조

using namespace std;

void main()
{
	srand(time(NULL)); //rand() 녀석의 수를 랜덤하게 받기 위해

	int nSelectNum; //내가 입력한 숫자를 저장 
	int nComNumber; //컴퓨터가 랜덤하게 선택한 숫자 저장

	int nWin = 0; //내가 이긴횟수
	int nLose = 0; //내가 진회수 

	//여기 아래서 부터 게임 시작 
	for (int i = 0; i < 5; i++) //게임 5판 하겠다. 
	{
		//반복문 안에서 게임 1번을 작성
		//1. 내가 원하는 숫자 선택
		cout << "가위(0), 바위(1), 보(2) 중에 선택 하시오 : ";
		cin >> nSelectNum;
		//2. 컴퓨터가 랜덤한 숫자를 선택
		nComNumber = rand() % 3; // 0 ~ 2
		//2_5. 선택한 녀석 출력
		cout << endl;

		switch (nSelectNum)
		{
		case 0:
			cout << "[플레이어 : 가위 vs ";
			break;
		case 1:
			cout << "[플레이어 : 바위 vs ";
			break;
		case 2:
			cout << "[플레이어 :  보  vs ";
			break;
		}

		switch (nComNumber)
		{
		case 0:
			cout << "가위 : 컴퓨터]" << endl;
			break;
		case 1:
			cout << "바위 : 컴퓨터]" << endl;
			break;
		case 2:
			cout << " 보  : 컴퓨터]" << endl;
			break;
		}
		//3. 내 , 컴퓨터 비교후 결과 저장 
		//가위(0), 바위(1), 보(2)
		//0 - 1, 1 - 2, 2 - (3 % 3)
		//비겼을때
		if (nSelectNum == nComNumber)
		{
			cout << "비겼다" << endl;
		}
		//이겼을때 
		//컴퓨터 보다 내가 +1
		else if ((nComNumber + 1) % 3 == nSelectNum)
		{
			cout << "내가 이겼다." << endl;
			nWin++;
		}
		//젔을때 
		//
		else if ((nSelectNum + 1) % 3 == nComNumber)
		{
			cout << "내가 졌다 " << endl;
			nLose++;
		}
		cout << endl;
	}
	//4.최종적인 결과를 출력 
	cout << "승리 : " << nWin << " 패배 : " << nLose << " 비김 : " <<
		5 - nWin - nLose << endl;
}