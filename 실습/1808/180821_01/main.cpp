#include <iostream>

using namespace std;

//void main() -> 진입점
void main()
{
	//실행할 내용들은 무조건 main 안에 작성
	//실행은 ctrl + F5
	//(;) -> 세미콜론: 코드의 끝을 알려 주는 녀석
	cout << "Hello C++ world!!" << endl;

	//endl -> 줄바꿈
	//cout -> 화면에 출력 하는 명령어

	cout << "문자열 출력" << endl;

	//정수(integer): 소수점이 없는 숫자
	cout << 1245 << endl;

	//실수(float): 소수점이 있는 숫자
	cout << 25.56f << endl;

	//문자 + 숫자
	cout << "10 + 20 = ";
	cout << 30 << endl;

	cout << "20 + 50 = " << 20 + 50 << endl;

	cout << "숙제 1번은 Visual studio 2017 설치" << endl;
	cout << "숙제 2번은 간단한 자기소개서 작성" << endl;
	cout << "1. 이름: ~~~~" << endl;
	cout << "2. 나이: ~~~~" << endl;
	cout << "3. 좋아하는 게임(장르): ~~~~" <<
		"4. 취업하고 싶은 회사(~~만든 회사)" << endl;

}