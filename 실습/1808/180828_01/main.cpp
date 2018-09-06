#include <iostream>
using namespace std;


//함수(function): 미리 코드를 작성해놓고 가져다 쓰는 것
//반환값 함수명(매개변수)
//반환값(데이터형)	함수명(임의적으로 짓는다)

void Function1(void)
{
	cout << "함수 테스트 " << endl;
}
void Function2(int num)
{
	cout << "매개변수 테스트: " << num << endl;
}
int SumNumber(int num1, int num2)
{
	int result = num1 + num2;
	return result;
}
//call by value(값에 의한 호출) -> 면접
void Sum(int result, int num1, int num2)
{
	result = num1 + num2;
	cout << "함수 내부 계산: " << result << endl;
}
//함수 전방선언: 함수가 존재한다는 것을 컴퓨터에 미리 알려주고, 함수 선언은 아래에 해준다
float Mul(float num1, float num2);
float Mul(float num1);
float Mul(int num1);
//int Mul(int num1);
//함수 오버로딩(OverLoading): 함수 이름이 같아도 매개변수와 리턴값의 차이에 따라 다른 함수로 인식하는 기능. 하지만 함수의 데이터형이 다른것은 적용되지 않는다.
//함수의 이름이 같고 함수 인자값이 다른 함수들을 다른 함수로 인식하는 기능 -> 면접

void main()
{
	//사용할 코드는 무조건 main 안에서 작성
	for (int i = 0; i < 2; i++)
	{
		Function1();
	}
	Function2(200);
	int nNumber = 400;
	Function2(nNumber);
	int nNumber2 = SumNumber(100, 200);
	cout << nNumber2 << endl;
	int nResult = 0, nNum1 = 10, nNum2 = 20;
	Sum(nResult, nNum1, nNum2);
	cout << "함수 종료 후 계산값: " << nResult << endl;
	
	float fNum = Mul(10.25f, 4.6f);
	float fNum2 = Mul(24.0f);
	cout << fNum << endl;
	//오류...가 난다는데 왜 안 난다냐.. 물론 계산은 안되는데.
	//아무튼 오류가 나는 이유는 코드는 위에서부터 읽어나가기 때문에 Mul 함수가 있는지 모르기 때문에 에러를 낸다
	//zzㅋㅋㅋㅋㅋㅋ 시바 이거 c++이라 그런가
}
float Mul(float num1, float num2)
{
	return num1 * num2;
}
float Mul(float num1)	
{
	return num1 * 100;
}