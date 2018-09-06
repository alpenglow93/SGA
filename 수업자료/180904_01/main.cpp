#include <iostream>

using namespace std;

//call by value : 값에 의한 호출
void Swap(int num1, int num2)
{
	int temp = num1;
	num1 = num2;
	num2 = temp;
}
//call by Reference : 주소값에 의한 호출 
void Swap(int* num1, int* num2)
{
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}
void Swap2(int** pNum1, int** pNum2)
{
	int* temp = *pNum1;
	*pNum1 = *pNum2;
	*pNum2 = temp;
}
void Sum(float* out, bool* check, float a, float b)
{
	*out = a + b;
	*check = (a > b);
}
void main()
{
	//포인터 -> 주소값 저장을 하는 데이터 형 
	//포인터 선언 방법 데이형* 변수명
	int* pNum;
	float* pfNum;
	bool* pBool;
	char* pCStr;
	string* pStr;
	int num = 10;
	cout << &num << endl;
	//포인터의 사이즈 4byte;
	//cout << sizeof(char) << endl;
	//cout << sizeof(char*) << endl;

	pNum = &num;
	*pNum = 100;
	cout << num << endl;
	//cout << pNum << endl;
	//cout << *pNum << endl;

	int* num1 = new int(10);
	int* num2 = new int(20);
	Swap2(&num1, &num2);
	cout << *num1 << " , " << *num2 << endl;

	delete num1;
	delete num2;

	float out;
	bool check;
	Sum(&out, &check, 15.4f, 22.32f);
	cout << out << ", " << check << endl;

	//동적 할당 : 프로그램이 실행중일때 메모리 카드 공간
	//을 할당 -> new, malloc
	//주의 동적할당시 무조건 해제 해줘야 된다
	//new - delete -> malloc - free
	//빌드 타임 , 런타임 

	//배열과 포인터 
	int aNum[5] = { 10,20,30,40,50 };
	cout << aNum << endl;
	cout << &aNum[0] << endl;
	cout << &aNum[1] << endl;
	cout << &aNum[2] << endl;

	cout << *aNum << endl;
	cout << *(aNum + 1) << endl;

	char str[64] = "Char Point Test";
	pCStr = (char*)"Input Char Point";
	cout << pCStr << endl;
	cout << str << endl;
	cout << str + 5 << endl;
	int* pArrNum = new int[3];
	pArrNum[0] = 10;
	delete[] pArrNum;
}