#include <iostream>
#include <string>
//해당 파일을 참조하겠다

using namespace std;

void main()
{
	//실행은 ctrl + F5
	cout << "출력을 위한 코드" << endl;

	//변수: 변경이 가능한 수(value)
	//상수: 변경이 불가능한 수

	//변수의 선언
	//데이터의 형태 + 변수이름(임의로 지정)
	//정수(integer)의 데이터 형 => int
	int nNum;
	//실수(float)의 데이터 형 => float
	float fNum;
	//문자(charactor)의 데이터 형 => char
	char ch;
	//문자열(string)의 데이터 형 => string
	string str;
	//(참 or 거짓) boolean => bool
	bool check;

	//대입 (초기화): 변수에 값을 넣는 것
	//A = B -> B(B의 값)을 A에 넣겠다.
	nNum = 20;
	fNum = 15.6f;
	ch = 'A';
	str = "문자열";
	check = true;	//참 == 1;
	check = false;	//거짓 == 0;

	cout << nNum << endl;
	cout << fNum + nNum << endl;
	nNum = 50;
	cout << nNum << endl;

	//상수
	const int cnNum = 20;	//선언 및 초기화. 선언과 초기화를 동시에 해준다.
	cout << cnNum << endl;

	cout << str << endl;	//string 은 기본적으로 출력을 하지 못 한다. #include <string> 을 삽입해줘야 가능.
	//c + out, c + in

	cout << "원하는 숫자를 입력: ";
	cin >> nNum;

	cout << "입력 하신 숫자는 " << nNum << "입니다." << endl;

	cin >> str;
	cout << str << endl;
	//문자 입력시 띄어쓰기를 쓰고 입력을 하면 띄어쓰기 전 까지의 데이터만 입력되고 출력된다

	int sumA;
	int sumB;
	cout << "1번 숫자: ";
	cin >> sumA;
	cout << "2번 숫자: ";
	cin >> sumB;

	cout << sumA << " + " << sumB << " + " << sumA + sumB << endl;
}