#include <iostream>
#include "MainGame.h"
using namespace std;

//STL: standard template libary

void Print(float f);
void Print(int i);
void Print(const char* str);
//��� �Լ��� �̷��� ���� ����°��� �����

//���ø����� � Ÿ���� ���������� t��� ���� ����ϰڴ�
template <typename T>
void Show(T t)
{
	cout << t << endl;
}

void main()
{
	//Show(10);
	//Show(102.5f);
	//Show('b');
	//Show("String");
	MainGame<int> vInt(10);
}