#include <iostream>
#include <time.h>
//time 이란 식별자를 사용하기 위해 삽입

using namespace std;

void main()
{
	//연산자

	//대입연산자
	// A = B (B를 A에 넣겠다)
	int nNum_1 = 10;

	//산술연산자
	// +, -, *, /, %(나머지)
	int nNum_2 = 20;
	int nNum_3 = 8;
	int nNum_4;

	nNum_4 = nNum_2 + nNum_3;
	cout << nNum_4 << endl;

	nNum_4 = nNum_3 * nNum_1 - nNum_2;
	cout << nNum_4 << endl;

	nNum_4 = nNum_3 * (nNum_1 - nNum_2);
	cout << nNum_4 << endl;

	nNum_4 = nNum_2 / nNum_3;
	cout << nNum_4 << endl;
	nNum_4 = nNum_2 % nNum_3;
	cout << nNum_4 << endl;
	
	//비교연산자(관계연산자)
	// >(크다), <(작다), >=(크거나 같다), <=(작거나 같다), ==(같다), !=(다르다)
	bool result = 10 < 4;
	cout << result << endl;
	result = 10 > 4;
	cout << result << endl;

	//논리연산자
	// && => and, || => or

	// A	&&		B
	//A(ture) && B(true) => 참
	bool result2 = true && true;
	cout << result2 << endl;
	//A(true) && B(false) => 거짓
	result2 = true && false;
	cout << result2 << endl;
	//A(false) && B(false) => 거짓
	result2 = false && false;
	cout << result2 << endl;
	//둘 모두 참이어야 참

	//or 연산(||)
	//A		||		B
	//A(ture) || B(true) => ture
	result2 = true || true;
	cout << result2 << endl;
	//A(true) || B(false) => true
	result2 = true || false;
	cout << result2 << endl;
	//A(false) || B(false) => false
	result2 = false || false;
	cout << result2 << endl;
	//둘 중 하나만 참이면 참

	//숙제 ~: 조건문, 반복문 (각각 두가지)
	//조건문과 반복문 한줄조사
	//조건문이란 ~~~이다
	//반복문이란 ~~~이다
	//과제 제출에 한줄로 요약 작성 << 카페에 작성

	//조건문 2개가 무엇인지 어떻게 작성을 하는지
	//반복문도 마찬가지
	//이건 카페에 안 올려도 되고 개인적으로 조사



	///////////////////////////

	//rand(): 0~32676 까지의 숫자가 랜덤하게 나옴
	//그렇지만 계속 실행해도 같은 숫자 나옴

	//ex) 0~10 의 숫자만 나오게 하고 싶다면
	//cout << rand() % 11 << endl;
	//이런 식으로 11의 나머지를 구하는 식을 덧붙여주면 됨

	//ex) 1~10 의 숫자만 나오게 하고 싶다
	//(0 ~ 9) + 1
	//cout << rand() % 10 + 1 << endl;

	//ex) 7~16 의 숫자만 나오게 하고 싶다
	// (0 ~ 9) + 7
	//ex) 0 ~ 10의 배수만 나오게 하고 싶다 100
	//(0 ~ 10) * 10

	srand(time(NULL));
	//이걸 사용하면 실행할때마다 조금씩 숫자가 변함
	//한번은 선언해줘야 제대로 된 랜덤숫자가 나오게 됨

	cout << endl << endl;

	int rnd = rand() % 100;
	cout << rnd << endl;

	cout << endl << endl;

	cout << rand() % 10 + 1 << endl;
	cout << rand() % 10 + 1 << endl;
	cout << rand() % 10 + 1 << endl;
	cout << rand() % 10 + 1 << endl;
	cout << rand() % 10 + 1 << endl;
	cout << rand() % 10 + 1 << endl;
	cout << rand() % 10 + 1 << endl;
	cout << rand() % 10 + 1 << endl;
	cout << rand() % 10 + 1 << endl;
	cout << rand() % 10 + 1 << endl;
	
}