#include <iostream>
using namespace std;


//함수 포인터 
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
//1.인자값은 데이터 형태가 같고
//같은 위치에서 실행 하는데 전혀 다른 함수를 
//동작시킬때
//2.비동기 함수를 만들기 위해서 
//A -> B(동기,무한루프) -> C 
//A -> B(비동기, 무한 루프) (CALLBACK 함수)
//  -> c
//이벤트 처리 
void main()
{
	void(*fp)(void);
	Test3(Test, Test2);
	int(*fp2)(int);
	fp2 = Test4;
	fp2(20);
}