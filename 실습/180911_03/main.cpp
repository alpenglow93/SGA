#include <iostream>
#include "Card.h"
using namespace std;

//함수 포인터. 함수에도 포인터를 붙일 수 있고 변수로도 활용할 수 있다
void Test()
{
	cout << "Functional" << endl;
}
void Test2()
{
	cout << "Pointer" << endl;
}
void Test3(void(*fp1)(void), void(*fp2)(void))
{
	fp1();
	fp2();
}
int Test4(int num)
{
	cout << num << endl;
	return num;
}

//함수 포인터를 쓰는 이유
//1. 인자값은 데이터 형태가 같고 같은 위치에서 실행 하는데 전혀 다른 함수를 동작시킬때
//2. 비동기 함수를 만들기 위해
//	A -> B(동기, 무한루프) -> C
//	A -> B(비동기, 무한루프) -> C (a가 실행되면 b가 실행되고 무한루프랑 상관없이 c가 실행된다) (CALLBACK 함수)
//이벤트 처리

void main()
{
	void(*fp)(void);
	//fp = Test;
	//fp();
	//fp = Test2;
	//fp();
	Test3(Test, Test2);
	int(*fp2)(int);
	fp2 = Test4;
	fp2(20);
}