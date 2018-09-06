#include <iostream>
#include <time.h>
using namespace std;

void main()
{
	//연산자 

	//대입 연산자
	// A = B (B를 A에 넣겠다)
	int nNum_1 = 10;

	//산술 연산자
	// +, - , *, /, %(나머지)
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
	//비교 연산자 
	// >(크다), <(작다), 
	//>=(크거나 같다), <=(작거나 같다),
	//==(같다), !=(틀리다)
	bool result = 10 < 4;
	cout << result << endl;

	result = 10 > 4;
	cout << result << endl;
	//논리 연산자 
	//&& => and, ||(shift + \) or
	// A         &&       B
	//A(true)  && B(true) => 참  //  
	bool result2 = true && true;
	cout << result2 << endl;

	//A(true) && B(false) = 거짓
	result2 = true && false;
	cout << result2 << endl;

	//A(false) && B(false) => 거짓
	result2 = false && false;
	cout << result2 << endl;

	//or 연산(||) 
	//A(true) || B(true) = > true
	result2 = true || true;
	cout << result2 << endl;

	//A(true) || B(false) => true
	result2 = true || false;
	cout << result2 << endl;

	//A(false) || B(false) = > false
	result2 = false || false;
	cout << result2 << endl;

	//숙제 ~ : 조건문(2개), 반복문(2개)

	//조건문과 반복문 한줄조사
	//과제 제출에 한줄로 요약 작성

	//조건문 2개 -> 머고, 어떻게작성 동작
	//반복문 2개 -> 

	//rand() : 0 ~ 32676
	//ex) 0~ 10 = > % 11
	//ex) 1 ~ 10; => (0 ~ 9) + 1
	//ex) 7 ~ 16; => (0 ~ 9) + 7
	//ex) 0~ 10배수 100
	//    => (0~ 10) * 10
	srand(time(NULL));

	int rnd = rand() % 100;
	cout << rnd << endl;
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