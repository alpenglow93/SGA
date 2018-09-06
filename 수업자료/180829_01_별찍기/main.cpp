#include <iostream>

using namespace std;

void ShowStar(int num, char ch[6])
{
	cout << ch[num];					//1
	if (num < 0) return;				//2

	ShowStar(num - 1, ch); //재귀 함수   //3
										//4
}
void ShowSpace(int num, char ch[6])
{
	if (num > 4) return;
	cout << ch[num];					//1
	ShowSpace(num + 1, ch); //재귀 함수   //3
}
//1 -> 3(1) -> 1 -> 3(2) -> 1 -> 3(3) -> 1 -> 2
//->4(3) -> 4(2) -> 4(1) -> 함수 종료 
void Test(int n)
{ // 1
	cout << n << " : 재귀함수 전" << endl;
	if(n > 0) Test(n - 1); //x
	cout << n << " : 재귀함수 후" << endl;
} //2 

void main()
{
	//*
	//**
	//***
	char star[6] = "*****";
	char space[6] = "     ";
	cout << star[5] << "Test" << endl;
	for (int i = 0; i < strlen(star); i++)
	{
		ShowStar(i, star);
		cout << endl;
	}
	for (int i = strlen(star) - 1; i >= 0 ; i--)
	{
		ShowStar(i, star);
		cout << endl;
	}
	for (int i = strlen(star) - 1; i >= 0; i--)
	{
		ShowSpace(i + 1, space);
		ShowStar(i, star);
		cout << endl;
	}
	for (int i = 0; i < strlen(star);i++)
	{
		ShowSpace(i +1, space);
		ShowStar(i, star);
		cout << endl;
	}

	//for (int i = 0; i < strlen(star); i++)
	//{
	//	cout << star + i << endl;
	//}
	//for (int i = strlen(star) - 1; i >= 0; i--)
	//{
	//	cout << star + i << endl;
	//}
	//for (int i = 0; i < strlen(star); i++)
	//{
	//	cout << space + i;
	//	cout << star + (strlen(star) - (i  + 1)) << endl;
	//}


	//문자열 뒤집기
	char str[64] = "abcdefg";

	for (int i = strlen(str); i >= 0; i--)
		cout << str[i];
	cout << endl;
}