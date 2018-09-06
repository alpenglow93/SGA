#include <iostream>
#include <time.h>
using namespace std;

void main()
{
	//배열 (Array)
	//데이터형 변수명[갯수];

	int nNum[10];
	//인덱스번호의 시작은 0번부터
	nNum[4] = 10;
	nNum[3] = 20;

	cout << nNum[4] << endl;
	cout << nNum[3] << endl;

	for (int i = 0; i < 10; i++)
	{
		nNum[i] = i;
		cout << nNum[i] << " ";
	}
	cout << endl;
	srand(time(NULL));
	//셔플 알고리즘 
	for (int i = 0; i < 1000; i++)
	{
		int temp, sour, dest;
		sour = rand() % 10;// 10 -> 배열의 크기
		dest = rand() % 10;// 10->배열의 크기
		//swap;
		temp = nNum[sour]; //temp(nNum[sour])
		nNum[sour] = nNum[dest]; //nNum[sour](nNum[dest))
		nNum[dest] = temp;
	}
	//셔플 알고리즘 

	for (int i = 0; i < 10; i++)
	{
		cout << nNum[i] << " ";
	}
	cout << endl;
}