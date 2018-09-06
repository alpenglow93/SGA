#include <iostream>
using namespace std;

//포인터: 주소값을 저장을 하는 데이터형태

//call by Reference
void Swap(int *num1, int *num2)
{
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}
void Sum(float* out, int* out2, float num1, float num2)
{
	*out2 = num1 + num2;
	*out = num1 + num2;
}

void main()
{
	//int num = 10;
	////포인터 선언
	int *pNum;
	float* pFNum;

	//cout << &num << endl;
	//pNum = &num;
	//cout << pNum << endl;

	//cout << *pNum << endl;

	int num1 = 10; int num2 = 20;
	Swap(&num1, &num2);
	cout << num1 << " , " << num2 << endl;

	float result;
	Sum(&result, &num1, 24.25f, 25.43f);	//리턴이 아닌 인자값으로 받아서 결과를 받는 방법
	cout << result << endl;			//리턴이 아닌 포인터로 반환받을 경우 여러가지의 데이터형으로 여러가지 값을 받을 수 있다.
	cout << result << endl;
	cout << num1 << endl;

	int** ppNum;	//이중포인터: 주소값을 가리키는 주소값

	//배열과 포인터
	//배열을 선언하고 뒤에 인덱스 없이 배열변수를 출력하면 주소값이 나온다
	//이 주소값은 배열의 첫번째 메모리 공간의 주소값임
	int aNum[5] = { 10, 20, 30, 40, 50 };
	cout << aNum << endl;
	cout << &aNum[0] << endl;
	cout << &aNum[1] << endl;
	cout << &aNum[2] << endl;
	cout << sizeof(int) << endl;	//int 변수의 크기만큼 주소값이 증가함

	cout << *aNum << endl;
	cout << *(aNum + 1) << endl;	//배열에 +1 을 하면 다음 배열 주소값

	char str[64] = "charTest";		//char 의 특성상 이어진 문자까지 다 출력됨
	cout << str << endl;
	cout << str + 2 << endl;

	//동적할당: 실행중에 메모리 공간 할당
	//new 할당 -> 주의 new 를 사용하면 delete를 무조건 해야된다
	int* pTest = new int(100);	//new 키워드 사용
	cout << *pTest << endl;
	delete pTest;

	int* arrTest = new int[3];

	delete[] arrTest;
	//메모리를 사용한뒤 삭제하고 또 삭제하면 에러생긴다
}