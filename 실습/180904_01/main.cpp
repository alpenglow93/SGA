#include <iostream>
using namespace std;

//������: �ּҰ��� ������ �ϴ� ����������

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
	////������ ����
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
	Sum(&result, &num1, 24.25f, 25.43f);	//������ �ƴ� ���ڰ����� �޾Ƽ� ����� �޴� ���
	cout << result << endl;			//������ �ƴ� �����ͷ� ��ȯ���� ��� ���������� ������������ �������� ���� ���� �� �ִ�.
	cout << result << endl;
	cout << num1 << endl;

	int** ppNum;	//����������: �ּҰ��� ����Ű�� �ּҰ�

	//�迭�� ������
	//�迭�� �����ϰ� �ڿ� �ε��� ���� �迭������ ����ϸ� �ּҰ��� ���´�
	//�� �ּҰ��� �迭�� ù��° �޸� ������ �ּҰ���
	int aNum[5] = { 10, 20, 30, 40, 50 };
	cout << aNum << endl;
	cout << &aNum[0] << endl;
	cout << &aNum[1] << endl;
	cout << &aNum[2] << endl;
	cout << sizeof(int) << endl;	//int ������ ũ�⸸ŭ �ּҰ��� ������

	cout << *aNum << endl;
	cout << *(aNum + 1) << endl;	//�迭�� +1 �� �ϸ� ���� �迭 �ּҰ�

	char str[64] = "charTest";		//char �� Ư���� �̾��� ���ڱ��� �� ��µ�
	cout << str << endl;
	cout << str + 2 << endl;

	//�����Ҵ�: �����߿� �޸� ���� �Ҵ�
	//new �Ҵ� -> ���� new �� ����ϸ� delete�� ������ �ؾߵȴ�
	int* pTest = new int(100);	//new Ű���� ���
	cout << *pTest << endl;
	delete pTest;

	int* arrTest = new int[3];

	delete[] arrTest;
	//�޸𸮸� ����ѵ� �����ϰ� �� �����ϸ� ���������
}