#include <iostream>

using namespace std;
//�Լ�(function) : �̸� �ڵ带 �ۼ��� ���� ���� ���³༮ 
//��ȯ��[������ ����] �Լ���[������] (���ڰ�) 

void Function1(void)
{
	cout << "�Լ� �׽�Ʈ " << endl;
}
void Function2(int num)
{
	cout << "�Ű����� �׽�Ʈ : " << num << endl;
}
int SumNumber(int num1, int num2)
{
	int result = num1 + num2;
	return result;
}
//�� ���� ��� (���� ���� ȣ��) -> ����
void Sum(int result, int num1, int num2)
{
	result = num1 + num2;
	cout << "�Լ� ���� ���" << result << endl;
}
//�Լ� ���漱�� : 
//�̸� �̷��� �Լ��� �ִٶ�� �˷��ְ� ���߿� ����Ѵ�?
float Mul(float num1, float num2);
//���� �ε� (OverLoading) -> ����
//�Լ��� �̸��� ���� �Լ� ���ڰ��� �ٸ� �Լ����� 
float Mul(float num1);
float Mul(int num1);
void main()   //������ ����� �ڵ�� main �ȿ��� �ۼ�
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
	cout << "�Լ� ������ ��갪 : " << nResult << endl;

	float fNum = Mul(10.25f, 4.6f);
	float fNum2 = Mul(24.0f);
	//�ڵ� ������ ���� �о �������µ� 
}
float Mul(float num1, float num2)
{
	return num1 * num2;
}
float Mul(float num1)
{
	return num1 * 100;
}