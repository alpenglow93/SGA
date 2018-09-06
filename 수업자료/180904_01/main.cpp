#include <iostream>

using namespace std;

//call by value : ���� ���� ȣ��
void Swap(int num1, int num2)
{
	int temp = num1;
	num1 = num2;
	num2 = temp;
}
//call by Reference : �ּҰ��� ���� ȣ�� 
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
	//������ -> �ּҰ� ������ �ϴ� ������ �� 
	//������ ���� ��� ������* ������
	int* pNum;
	float* pfNum;
	bool* pBool;
	char* pCStr;
	string* pStr;
	int num = 10;
	cout << &num << endl;
	//�������� ������ 4byte;
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

	//���� �Ҵ� : ���α׷��� �������϶� �޸� ī�� ����
	//�� �Ҵ� -> new, malloc
	//���� �����Ҵ�� ������ ���� ����� �ȴ�
	//new - delete -> malloc - free
	//���� Ÿ�� , ��Ÿ�� 

	//�迭�� ������ 
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