#include <iostream>
#include <time.h>
using namespace std;

void main()
{
	//반복문: 특정 코드를 반복 실행하는 구문

	//for while 두가지가 있다

	//for( 초기값 ; 조건문 ; 증감식 )
	//{
	//	조건을 만족할때 실행한다.
	//}
	//
	//	초기값 실행 ->  조건(참) -> 코드 실행 -> 증감식 실행 -> 조건(참) -> 코드 실행 -> ... -> 조건(거짓)

	for (int i = 0; i < 10; i++)
	{
		cout << i << "번째 반복문 실행" << endl;
	}

	cout << "===============" << endl;


	for (int i = 10; i > 0; i--)
	{
		cout << i << "번째 반복문 실행" << endl;

	}

	cout << "===============" << endl;

	for (int i = 10; i > 0; i--)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << i << ", " << j << "번째 반복문 실행" << endl;
		}
	}

	for (int i = 0; i < 100; i++)
	{
		if (i % 2 == 0)
		{
			cout << i << endl;
		}
	}

	//while( 조건 )
	//{
	//	조건이 참이면 코드를 실행하겠다.
	//}

	int nNum = 0;		//초기값
	while (nNum < 10)	//조건
	{
		cout << nNum << "번째 코드 실행" << endl;
		nNum++;			//증감식
	}
	////무한 반복문
	//while (1)	//조건을 true로 잡는다
	//{
	//	cout << nNum << " ";
	//	nNum++;
	//}

	srand(time(NULL));
	for (int i = 0; i < 10; i++)
	{
		//0 ~ 9;
		int nRandom = rand() % 10;
		cout << nRandom << endl;
	}
}