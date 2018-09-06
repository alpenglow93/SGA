#include <iostream>
using namespace std;

//전처리 -> 매크로
#define ARRAY_MAX 15
#define SHOW(p) {cout << p << endl;}
void main()
{
	//배열은 다중배열이 가능
	int aNum[ARRAY_MAX];

	int aNum2[10][10];	//2차원 배열


	for (int i = 0; i < ARRAY_MAX; i++)
	{
		aNum[i] = i;
		//cout << i << " ";
		SHOW(aNum[i]);
	}
	cout << endl;

	//for (int i = 0; i < a; i++)
	//{
	//	for (int j = 0; j < 10; j++)
	//	{
	//		aNum2[i][j] = i * 10 + j;
	//	}
	//}
	//int aNum3[10][10][10][10];
}