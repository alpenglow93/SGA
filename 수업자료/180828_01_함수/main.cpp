#include <iostream>

using namespace std;
//함수(function) : 미리 코드를 작성해 놓고 가져 쓰는녀석 
//반환값[데이터 형태] 함수명[임의적] (인자값) 

void Function1(void)
{
	cout << "함수 테스트 " << endl;
}
void Function2(int num)
{
	cout << "매개변수 테스트 : " << num << endl;
}
int SumNumber(int num1, int num2)
{
	int result = num1 + num2;
	return result;
}
//콜 바이 밸류 (값에 의한 호출) -> 면접
void Sum(int result, int num1, int num2)
{
	result = num1 + num2;
	cout << "함수 내부 계산" << result << endl;
}
//함수 전방선언 : 
//미리 이러한 함수가 있다라고 알려주고 나중에 사용한다?
float Mul(float num1, float num2);
//오버 로딩 (OverLoading) -> 면접
//함수의 이름이 같고 함수 인자값이 다른 함수들을 
float Mul(float num1);
float Mul(int num1);
void main()   //무조건 사용할 코드는 main 안에서 작성
{

	rand();
	for (int i = 0; i < 2; i++){
		Function1();
	}
	Function2(200);
	int nNumber = 400;
	Function2(nNumber);
	int nNumber2 = SumNumber(100, 200);
	cout << nNumber2 << endl;
	int nResult = 0, nNum1 = 10, nNum2 = 20;
	Sum(nResult, nNum1, nNum2);
	cout << "함수 종료후 계산값 : " << nResult << endl;

	float fNum = Mul(10.25f, 4.6f);
	float fNum2 = Mul(24.0f);
	//코드 위에서 부터 읽어서 내려오는데 
}
float Mul(float num1, float num2)
{
	return num1 * num2;
}
float Mul(float num1)
{
	return num1 * 100;
}