#include <iostream>
#include <time.h>
using namespace std;

void main()
{
	//배열 (Array)
	//데이터형 변수명[갯수];
	
	int nNum[10];
	//인덱스번호
	//번호의 시작은 0번부터
	nNum[4] = 10;
	nNum[3] = 20;

	cout << nNum[4] << endl;
	cout << nNum[3] << endl;

	cout << "=============" << endl;
	
	for (int i = 0; i < 10; i++)
	{
		nNum[i] = i;
		cout << nNum[i] << " ";
	}

	cout << endl;

	//셔플 알고리즘
	//rand() 사용할 것

	//cout << "셔플 알고리즘" << endl;

	srand(time(NULL));
	
	for (int i = 0; i < 1000; i++)
	{
		int temp, sour, dest;

		sour = rand() % 10; //10 -> 배열의 크기
		dest = rand() % 10;	//10 -> 배열의 크기

		//swap;
		temp = nNum[sour];
		nNum[sour] = nNum[dest];
		nNum[dest] = temp;
	}

	for (int i = 0; i < 10; i++)
	{
		cout << nNum[i] << " ";
	}
	cout << endl;

}