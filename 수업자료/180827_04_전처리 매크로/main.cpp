#include <iostream>

using namespace std;

//전처리 -> 매크로 
#define ARRAY_MAX 20
#define SHOW(p) {cout << p << endl;}
void main()
{
	//배열은 다중 배열 
	int aNum[ARRAY_MAX];

	for (int i = 0; i < ARRAY_MAX; i++)
	{
		aNum[i] = i;
		SHOW("Test");
	}
	cout << endl;
	//int aNum2[10][10]; //2차원 배열 
	//
	//for (int i = 0; i < 10; i++)
	//{
	//	for (int j = 0; j < 10; j++)
	//	{
	//		aNum2[i][j] = i * 10 + j;
	//	}
	//}
}