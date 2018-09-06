#include <iostream>
using namespace std;

//숙제풀이
//별 찍기

void ShowStar(int num, char ch[6])
{
	cout << ch[num];
	if (num < 0) return;
	ShowStar(num - 1, ch);	//재귀 함수: 함수 내부에서 자기 자신을 사용하는것
}
void ShowSpace(int num, char ch[6])
{
	if (num > 4) return;
	cout << ch[num];
	ShowSpace(num + 1, ch);
}
void Test(int n)	//재귀함수 호출과 리턴 과정을 보여주기 위한 테스트 함수
{
	cout << n << ": 재귀 함수 전" << endl;
	if (n > 0) Test(n - 1);
	cout << n << ": 재귀 함수 후" << endl;
}
void main()
{
	//Test(5);
	char star[6] = "*****";
	char space[6] = "     ";
	cout << star[5] << "Test" << endl;
	for (int i = 0; i < strlen(star) - 1; i++)
	{
		ShowStar(i, star);
		cout << endl;
	}
	for (int i = strlen(star); i > 0; i--)
	{
		ShowStar(i, star);
		cout << endl;
	}
	for (int i = strlen(star); i > 0; i--)
	{
		ShowSpace(i + 1, space);
		ShowStar(i, star);
		cout << endl;
	}
	for (int i = 0; i < strlen(star); i++)
	{
		ShowSpace(i, space);
		ShowStar(i, star);
		cout << endl;
	}
	for (int i = 0; i < strlen(star); i++)
	{
		cout << star + i << endl;
	}

	for (int i = 0; i < strlen(star); i++)
	{
		cout << star + i << endl;
	}
	for (int i = strlen(star) - 1; i >= 0; i--)
	{
		cout << star + i << endl;
	}
	for (int i = 0; i < strlen(star); i++)
	{
		cout << space + i;
		cout << star + (strlen(star) - i) << endl;
	}

	//숙제 잘못 내주셨다고 합니다
	//원래는 문자열 뒤집기를 했어야함

	char str[64] = "abcdefg";

	for (int i = strlen(str); i >= 0; i--)
		cout << str[i];
	cout << endl;
}