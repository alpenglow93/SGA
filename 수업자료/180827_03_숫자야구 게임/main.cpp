//숫자 야구 
#include <iostream>
#include <time.h>
using namespace std;
//1~9숫자 중에서 중복되는 않는 3개의 숫자(셔플)를 컴퓨터가 고르고 
//나는 3개의 수를 입력 해서 자리 숫자 

void main()
{
	int aNumber[9]; //1~9까지의 숫자를 저장 
	int aSelect[3]; //내가 선택 할 숫자 3개를 저장

	bool bIsWin = false;

	//숫자 초기화
	for (int i = 0; i < 9; i++)
	{
		aNumber[i] = i + 1;
	}
	//셔플 알고리즘
	srand(time(NULL));
	for (int i = 0; i < 1000; i++)
	{
		int temp = 0, sour = 0, dest = 0;
		sour = rand() % 9; //9 -> 배열의 크기
		dest = rand() % 9; //9 -> 배열의 크기 

		//Swap 
		temp = aNumber[sour];
		aNumber[sour] = aNumber[dest];
		aNumber[dest] = temp;
	}
	//게임 만들기 
	cout << "[치트 : ";
	for (int j = 0; j < 3; j++)
	{
		cout << aNumber[j] << " ";
	}
	cout  << "]"<< endl;
	for (int i = 0;i < 10; i++) //10번 선택 하겠다. 
	{

		//내가 숫자 3개를 입력
		cout << "숫자 입력 : ";
		for (int j = 0; j < 3; j++)
		{
			cin >> aSelect[j];
		}
		//비교 후 
		int nStrike = 0;
		int nBall = 0;

		for (int j = 0; j < 3; j++) //내가 선택한 3개
		{
			for (int k = 0; k < 3; k++) //컴퓨터 선택한 3개 
			{
				if (aSelect[j] == aNumber[k])
				{
					if (j == k)
					{
						nStrike++;
					}
					else
					{
						nBall++;
					}
				}
			}
		}
		cout << "Strike : " << nStrike <<endl << "Ball : " << nBall 
			<<  endl<< "Out : "<< 3 - nStrike - nBall << endl;
		cout << endl;

		if (nStrike == 3)
		{
			bIsWin = true;
			break; //switch or for, while문을 빠져나갈때 사용하는 녀석
		}
	}

	if (bIsWin == true)
	{
		cout << "3Strike 승리 " << endl;
	}
	else
	{
		cout << "10번의 기회를 모두 사용했습니다." << endl;
	}
}